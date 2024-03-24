#include <thread>
#include "Exceptions.h"
#include "GomokuGameServerGUI.h"

template<class T>
static ssize_t getMessageSize(const T& message)
{
    std::string serializedMsg;
    message.SerializeToString(&serializedMsg);
    return serializedMsg.size();
}

GomokuGameServerGUI::GomokuGameServerGUI()
{
    //1. tell OS to allocate socket resource.
    unlink(k_SOCKET_GUI_NAME);
    m_sockMaster = socket(k_SOCKET_TYPE, SOCK_STREAM, 0);
    if(m_sockMaster==-1)
        throw game_except::General{"Os can not create master socket " + std::string{k_SOCKET_GUI_NAME}};

    //2. prepare a structure which points to allocated socket resource.
    memset(&m_sockName, 0, sizeof(m_sockName));
    m_sockName.sun_family = k_SOCKET_TYPE;
    strncpy(m_sockName.sun_path, k_SOCKET_GUI_NAME, sizeof(m_sockName.sun_path)-1);

    //3. “assigning a name to a socket” (bind) the socket that has been allocated to m_sockName, so I can use it then in the program
    int ret = bind(m_sockMaster,(const struct sockaddr *)&m_sockName, sizeof(m_sockName));

    if(ret==-1)
        throw game_except::General{"Os can not bind() socket " + std::string{k_SOCKET_GUI_NAME}};

    //dummy data just to get header size
	m_msgHeader.set_m_msgid(message::MsgID::KEEP_ME_LAST);
	m_msgHeader.set_m_msgsize(0);
	m_msgHeadSize = getMessageSize(m_msgHeader);
}

void GomokuGameServerGUI::listening()
{
     int ret = listen(m_sockMaster, 1);
     if(ret == -1)
         throw game_except::General{"Os can not listen() socket " + std::string{k_SOCKET_GUI_NAME}};

     int socketData{-1};

     for(; m_isRunning;)
     {
         socketData = accept(m_sockMaster, NULL, NULL);

         if(socketData == -1)
             continue;

		 //1. at the beginning header is sent. Read it
		 std::string receivedHeaderMessage(m_msgHeadSize,'\0');
		 if(read(socketData, &receivedHeaderMessage[0], m_msgHeadSize) != static_cast<ssize_t>(m_msgHeadSize))
		 {
			 throw game_except::General{"Socket server: Message header reading error."};
		 }

		 if(not m_msgHeader.ParseFromString(receivedHeaderMessage))
		 {
			 throw game_except::General{"Socket server: I got header but can not parse it."};
		 }

		 const uint32_t length = m_msgHeader.m_msgsize();
		 const uint32_t id = m_msgHeader.m_msgid();

		 cout<<"header id:"<<id<<endl;
		 cout<<"header size:"<<length<<endl;

		 //2.read the actual message
		 std::string receivedMessage(length,'\0');
		 if (read(socketData, &receivedMessage[0], length) != static_cast<ssize_t>(length))
		 {
			 throw game_except::General{"Socket server: Message reading error."};
		 }

		 //3. parse data into message type pointed by header
		 if(id >= message::MsgID::KEEP_ME_LAST)
		 {
			 throw game_except::General{"Socket server: Got unexpected message id."};
		 }
		 else if(id==message::MsgID::USR_MOVE_QUERY or
				  id == message::MsgID::REPLAY_QUERY)
		 {
			 if(m_msgQuery.ParseFromString(receivedMessage))
			 {
				 cout<<"got query message"<<endl;
			 }
		 }
		 else if(id == message::MsgID::USR_MOVE_INVALID_NOTIFY or
				  id == message::MsgID::CPU_MOVE_NOTIFY or
				  id == message::MsgID::WINNER_NOTIFY or
				  id == message::MsgID::STALEMATE_NOTIFY or
				  id == message::MsgID::RESTART_NOTIFY or
				  id == message::MsgID::END_NOTIFY)
		 {
			 if(m_msgNotify.ParseFromString(receivedMessage))
			 {
				 cout<<"got notify message"<<endl;
			 }
		 }


         close(socketData);
     }
}

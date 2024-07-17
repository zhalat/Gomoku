FROM jenkins/jenkins:jdk21

#Switching to root instead Jenkins user is needed due to potential problem with permission
USER root
RUN apt-get update && apt-get install -y lsb-release
RUN curl -fsSLo /usr/share/keyrings/docker-archive-keyring.asc \
  https://download.docker.com/linux/debian/gpg
RUN echo "deb [arch=$(dpkg --print-architecture) \
  signed-by=/usr/share/keyrings/docker-archive-keyring.asc] \
  https://download.docker.com/linux/debian \
  $(lsb_release -cs) stable" > /etc/apt/sources.list.d/docker.list

#avaliable plugin https://jenkins-plugin-hub.herokuapp.com/
#Set base plugins. The other you will install via GUI
RUN apt-get update && apt-get install -y docker-ce-cli
RUN jenkins-plugin-cli --plugins "ssh-credentials:337.v395d2403ccd4 ssh-slaves:2.973.v0fa_8c0dea_f9f github-api:1.318-461.v7a_c09c9fa_d63"


#Build & run
#'docker build --no-cache -t jenkins_img .'
#'docker run -dt --restart unless-stopped --privileged -v /var/run/docker.sock:/var/run/docker.sock -v /home/jenkins_home:/home/jenkins_home -p 8080:8080 -p 50000:50000 --name jenkins_container jenkins_img'
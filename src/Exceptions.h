#pragma once

#include <exception>
#include <string>

namespace exception
{
    struct General : public std::exception
    {
        std::string m_errMsg;
    public:
        General(std::string errMsg)
         : m_errMsg{errMsg}
        {}
        General(const General &) = delete;
        General(const General &&) = delete;
        General & operator=(const General &) = delete;
        General & operator=(const General &&) = delete;
        virtual ~General() = default;

        [[nodiscard]] const char * what() const noexcept override { return m_errMsg.c_str(); }
    };

};

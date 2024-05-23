//
// Created by shepherd on 20.5.24.
//

#ifndef AUTH_FILTER_HPP
#define AUTH_FILTER_HPP
#include <string>
#include <vector>
#include <crow/http_response.h>


namespace c1::jwt {

struct AuthFilter {
    struct context
    {
        std::string email;
        std::vector<std::string> roles;
        bool isAuthenticated = false;
    };

    void before_handle(crow::request& req, crow::response& res, context& ctx);
    void after_handle(crow::request& req, crow::response& res, context& ctx);

};

} // c1::jwt

#endif //AUTH_FILTER_HPP

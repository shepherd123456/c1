//
// Created by shepherd on 30.4.24.
//

#ifndef USER_HPP
#define USER_HPP

#include <string>
#include <crow/json.h>

namespace c1 {

struct User {
    User(const crow::json::rvalue &json);
    crow::json::wvalue toJson() const;

    int id;
    std::string email;
    std::string password;
};

} // c1

#endif //USER_HPP

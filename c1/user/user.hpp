//
// Created by shepherd on 30.4.24.
//

#ifndef USER_HPP
#define USER_HPP

#include <string>
#include <crow/json.h>
#include <vector>
#include <c1/role/role.hpp>
#include <c1/refreshtoken/refersh_token.hpp>

namespace c1 {

struct Role;

struct User {
    User() = default;
    User(const crow::json::rvalue &json);

    [[nodiscard]] bool isPasswordValid(const std::string& pass) const;
    [[nodiscard]] crow::json::wvalue toJson() const;

    int id{};
    std::string email;
    std::string password;
    std::vector<Role> roles;
    std::vector<RefreshToken> refreshTokens;
};

} // c1

#endif //USER_HPP

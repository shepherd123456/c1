//
// Created by shepherd on 21.5.24.
//

#ifndef ROLE_HPP
#define ROLE_HPP

#include <string>
#include <crow/json.h>
#include <vector>

namespace c1 {

struct User;

struct Role {
    Role() = default;
    Role(const std::string& n);
    explicit Role(const crow::json::rvalue& json);

    [[nodiscard]] crow::json::wvalue toJson() const;

    int id{};
    std::string name;
    std::vector<User> users;
};

} // c1

#endif //ROLE_HPP

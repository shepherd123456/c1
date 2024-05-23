//
// Created by shepherd on 21.5.24.
//

#include "role.hpp"
#include <c1/user/user.hpp>

namespace c1
{
Role::Role(const std::string& n)
{
    name = n;
}

Role::Role(const crow::json::rvalue& json)
{
    name = json["name"].s();
}

crow::json::wvalue Role::toJson() const
{
    return name;
}
} // c1

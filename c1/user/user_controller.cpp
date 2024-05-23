//
// Created by shepherd on 2.5.24.
//

#include <vector>
#include <crow/app.h>
#include <c1/user/user_controller.hpp>

namespace c1
{
UserController::UserController(const std::string& prefix, Storage& storage, UserRepository& userRepo)
    : Controller(prefix), storage_(storage), user_repository_(userRepo)
{
}

void UserController::setRoutes()
{
    CROW_BP_ROUTE(self, "/")([this]()
    {
        auto users = user_repository_.getAll();
        std::vector<crow::json::wvalue> jsonUsers;
        std::transform(users.begin(), users.end(), std::back_inserter(jsonUsers), [](const User& user)
        {
            return user.toJson();
        });
        return crow::json::wvalue(jsonUsers);
    });
}
} // c1

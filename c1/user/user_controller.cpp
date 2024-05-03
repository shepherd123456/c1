//
// Created by shepherd on 2.5.24.
//

#include "user_controller.hpp"
#include <crow/app.h>

namespace c1 {
void UserController::setRoutes()
{
    CROW_BP_ROUTE(get(), "/")([]()
    {
        return crow::json::wvalue({{"abc", 1}, {"def", 2}});
    });
}
} // c1
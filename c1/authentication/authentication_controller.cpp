//
// Created by shepherd on 2.5.24.
//

#include "authentication_controller.hpp"
#include <iostream>
#include <crow/app.h>

namespace c1
{
void AuthenticationController::setRoutes()
{
    CROW_BP_ROUTE(get(), "/sign-up").methods(crow::HTTPMethod::Post)([](const crow::request& req, crow::response& res)
    {
        const auto json = crow::json::load(req.body);
        std::cout << json << std::endl;
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "Content-Type, Authorization, X-Requested-With");
        res.set_header("Access-Control-Allow-Credentials", "true");
    });
}
} // c1

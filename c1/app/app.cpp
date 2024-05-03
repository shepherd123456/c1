//
// Created by shepherd on 1.5.24.
//

#include "app.hpp"
#include <vector>
#include "crow.h"
#include <crow/middlewares/cors.h>

#include <c1/authentication/authentication_controller.hpp>
#include <c1/user/user_controller.hpp>

namespace c1
{
void App::run()
{
    std::vector<Controller*> controllers{
        new AuthenticationController(""),
        new UserController("user")
    };

    crow::App<crow::CORSHandler> app;
    auto& cors = app.get_middleware<crow::CORSHandler>();
    cors
        .global()
        .origin("http://localhost:3000")
        .methods("POST"_method, "GET"_method, "PUT"_method, "DELETE"_method)
        .allow_credentials();

    for (const auto i : controllers)
    {
        app.register_blueprint(i->get());
        i->setRoutes();
    }

    app.port(4567).multithreaded().run();
}
} // c1

//
// Created by shepherd on 1.5.24.
//


#include <vector>
#include "crow.h"
#include <crow/middlewares/cors.h>

#include <c1/app/app.hpp>
#include <c1/app/storage.hpp>

#include <c1/user/user_repository.hpp>
#include <c1/role/role_repository.hpp>
#include <c1/refreshtoken/refresh_token_repository.hpp>

#include <c1/authentication/authentication_controller.hpp>
#include <c1/user/user_controller.hpp>


namespace c1
{
void App::run()
{
    Storage storage;
    UserRepository userRepo(storage.get());
    RoleRepository roleRepo(storage.get());
    RefreshTokenRepository refreshTokenRepo(storage.get());

    std::vector<Controller*> controllers{
        new AuthenticationController("", storage, userRepo, roleRepo, refreshTokenRepo),
        new UserController("users", storage, userRepo)
    };

    crow::App<crow::CORSHandler> app;
    auto& cors = app.get_middleware<crow::CORSHandler>();
    cors.global()
        .headers("Content-Type", "Authorization")
        .origin("http://localhost:3000")
        .allow_credentials();

    for (const auto i : controllers)
    {
        app.register_blueprint(i->self);
        i->setRoutes();
    }

    app.port(4000).multithreaded().run();
}
} // c1

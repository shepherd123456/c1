#include "crow.h"
#include <c1/app/storage.hpp>
#include <c1/app/jwt.hpp>
#include <c1/app/app.hpp>

void test()
{
    c1::Storage db;
    std::string jsonValue = R"({"email":"p.pastor@post.cz","password":"Mastracek123$"})";
    db.createObject<c1::User>(crow::json::load(jsonValue));
}

void test2()
{
    const std::string token = c1::jwt::generateToken(
        std::chrono::seconds(std::chrono::minutes(2)).count(),
        {{"email", "p.pastor@post.cz"}, {"roles", crow::json::wvalue::list({"USER", "SELLER"})}}
    );
    for (const auto& i : c1::jwt::extractRoles(token))
    {
        std::cout << i << std::endl;
    }
}


template <typename RT, typename... Args>
RT cb(std::function<RT(Args...)> function, const Args&... args)
{
    return function(args...);
}
template <typename... Args>
crow::json::wvalue cb(std::function<crow::json::wvalue(Args...)> function, const Args&... args)
{
    return function(args...);
}
void test3()
{
    auto a = cb<int, int>(std::function([](int a, int b) { a + b; return crow::json::wvalue({{"asd", 1}, {"bcd", 1}}); }), 1, 2);
}

void test4()
{

}

int main()
{
    c1::App::run();
}

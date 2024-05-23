//
// Created by shepherd on 1.5.24.
//

#ifndef APP_HPP
#define APP_HPP

#include <chrono>

namespace c1 {
// constexpr int REFRESH_TOKEN_DURATION_SECONDS = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::minutes(8)).count();
constexpr int REFRESH_TOKEN_DURATION_SECONDS = 20;
// constexpr int ACCESS_TOKEN_DURATION_SECONDS = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::minutes(2)).count();
constexpr int ACCESS_TOKEN_DURATION_SECONDS = 5;

class App {
public:
    static void run();
};

} // c1

#endif //APP_HPP

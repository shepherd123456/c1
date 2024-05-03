//
// Created by shepherd on 2.5.24.
//

#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <crow/routing.h>

namespace c1
{
class Controller
{
public:
    virtual ~Controller() = default;

    explicit Controller(const std::string& prefix) : bp_(prefix)
    {
    }

    crow::Blueprint& get()
    {
        return bp_;
    }

    virtual void setRoutes() = 0;

private:
    crow::Blueprint bp_;
};
} // c1

#endif //CONTROLLER_HPP

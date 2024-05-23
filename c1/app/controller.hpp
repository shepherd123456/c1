//
// Created by shepherd on 2.5.24.
//

#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <crow/routing.h>

namespace c1
{
struct Controller
{
    virtual ~Controller() = default;
    explicit Controller(const std::string& prefix) : self(prefix)
    {
    }
    virtual void setRoutes() = 0;
    crow::Blueprint self;
};
} // c1

#endif //CONTROLLER_HPP

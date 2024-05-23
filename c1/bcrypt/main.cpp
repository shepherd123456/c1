//
// Created by shepherd on 22.5.24.
//

#include <iostream>
#include <string>
#include "bcrypt.h"

int main(){
    std::string pass = "top_secret";
    std::string hash = bcrypt::generateHash(pass);
    std::cout << hash << std::endl;
    std::cout << "\"" << pass << "\" :" << bcrypt::validatePassword(pass, hash) << std::endl;
    std::cout << "\"wrong\": " << bcrypt::validatePassword("wrong", hash) << std::endl;
}

//
//  main.cpp
//  Parcer
//
//  Created by Павел on 18.02.2023.
//
#include "Parcer.hpp"
#include <fstream>
#include <functional>
#include <numeric>
#include <list>
#include <vector>
#include <string>
#include <iostream>

int main(int argc, const char * argv[]) {
    Config config("X.ini");

        for (const auto& it : config.get_section("Example"))
        for (const auto& it : config["Example"])
        {
     std::cout << "`" << it.first << "` -> `" << it.second << "`\n";
        }

    
    return 0;
}

//
//  Parcer.hpp
//  Parcer
//
//  Created by Павел on 18.02.2023.
//

#ifndef Parcer_hpp
#define Parcer_hpp

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <map>

class Config{
    public:
        Config(std::string filename);

// std::map<std::string, std::string> get_section(std::string section_name);
 std::map<std::string, std::string> get_section(const std::string& section_name);

 std::map<std::string, std::string> operator[](const std::string& section_name);

        void dump(FILE* log_file);//Запись в выходной поток
    
    private:
        std::map<std::string, std::map<std::string, std::string> > sections;
        std::string read_header(const std::string& line);
        void read_configuration(const std::string& line, const std::string& header);
        // обрезка в начале
        void ltrim(std::string &s);
        // обрезка в конце
        void rtrim(std::string &s);
        // обрезка с обоих концов
        void trim(std::string &s);
        // обрезка в начале (копирование)
        std::string ltrim_copy(std::string s);
        // обрезка в конце(копирование)
        std::string rtrim_copy(std::string s);
        // обрезка с обоих концов(копирование)
        std::string trim_copy(std::string s);
};
#endif /* Parcer_hpp */

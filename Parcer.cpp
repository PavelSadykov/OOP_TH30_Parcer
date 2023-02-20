//
//  Parcer.cpp
//  Parcer
//
//  Created by Павел on 18.02.2023.
//

#include "Parcer.hpp"
#include <cctype>
#include <cstdint>
#include <fstream>
#include <limits>
#include <vector>
#include <sstream>

Config::Config(std::string filename)
{
    std::ifstream fin(filename);
    if (fin.good())
    {
        std::string line;
        std::string current_header = "";
        while (std::getline(fin, line))
        {
            trim(line);
            // Пропуск пустых строк
            if (line.size() == 0)
                continue;
            switch (line[0])
            {
                case '#':
                case ';':
                    // Игнор комментариев
                    break;
                case '[':
                    // Заголовок раздела
                    current_header = read_header(line);
                    break;
                default:
                    read_configuration(line, current_header);
            }
        }
        fin.close();
    }
    else
    {
        throw std::runtime_error("File `" + filename + "` does not exist");
    }
}

//std::map<std::string, std::string> Config::get_section(std::string section_name)
std::map<std::string, std::string> Config::get_section(const std::string& section_name){
    return sections[section_name];
    if (sections.count(section_name) == 0)
    {
 std::string error = "No such key: `" + section_name + "`";
        throw std::out_of_range(error);
    }
    return sections.at(section_name);
}

std::map<std::string, std::string> Config::operator[](const std::string& section_name)
{
    return get_section(section_name);
}

void Config::dump(FILE* log_file)
{
    // Итераторы
    std::map<std::string, std::string>::iterator itr1;
    std::map<std::string, std::map<std::string, std::string> >::iterator itr2;
    for(itr2 = sections.begin(); itr2 != sections.end(); itr2++)
    {
        fprintf(log_file, "[%s]\n", itr2->first.c_str());//выводим в поток значения аргументов
        for(itr1 = itr2->second.begin(); itr1 != itr2->second.end(); itr1++)
        {
            fprintf(log_file, "%s=%s\n", itr1->first.c_str(), itr1->second.c_str());
        }
    }
}
std::string Config::read_header(const std::string& line)
{
    if (line[line.size() - 1] != ']')
        throw std::runtime_error("Invalid section header: `" + line + "`");
    return trim_copy(line.substr(1, line.size() - 2));
}
void Config::read_configuration(const std::string& line, const std::string& header)
{
    if (header == "")
    {
        std::string error = "No section provided for: `" + line + "`";
        throw std::runtime_error(error);
    }
    if (line.find('=') == std::string::npos)
    {
        std::string error = "Invalid configuration: `" + line + "`";
        throw std::runtime_error(error);
    }
    std::istringstream iss(line);
    std::string key;
    std::string val;
    std::getline(iss, key, '=');
    if (key.size()== 0)
    {
        std::string error = "No key found in configuration: `" + line + "`";
        throw std::runtime_error(error);
    }
    std::getline(iss, val);
    sections[header][trim_copy(key)] = trim_copy(val);
}
// обрезка в начале
void Config::ltrim(std::string &s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
                return !std::isspace(ch);
                }));
}
// обрезка в конце
void Config::rtrim(std::string &s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
                return !std::isspace(ch);
                }).base(), s.end());
}
// обрезка с обоих концов
void Config::trim(std::string &s)
{
    ltrim(s);
    rtrim(s);
}
// обрезка в начале (копирование)
std::string Config::ltrim_copy(std::string s)
{
    ltrim(s);
    return s;
}
// обрезка в конце (копирование)
std::string Config::rtrim_copy(std::string s)
{
    rtrim(s);
    return s;
}
// обрезка с обоих концов (копирование)
std::string Config::trim_copy(std::string s)
{
    trim(s);
    return s;
}

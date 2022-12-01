#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <filesystem>
#include "io.h"
#include "sort.h"

// static fns

template<typename _elem = char >
static auto split_lines(const std::basic_string<_elem>& str, const _elem& endl) noexcept
{
    std::vector<std::basic_string<_elem>> lines;
    {
        auto pos = str.begin(); // typename std::basic_string<_elem>::iterator
        for(auto it = str.begin(); it != str.end(); ++it)
        {
            if(*it == endl)
            {
                lines.emplace_back(pos, it);
                pos = it + 1;
            }
        }
        lines.emplace_back(pos, str.end());
    }
    return lines;
}

template<typename _type = std::string >
static std::vector<_type> split(const _type& str, const _type& str2, typename _type::const_iterator start_position) noexcept
{
    std::vector<_type> splited;
    if(str.empty() || str2.empty() || start_position == str.end())
    {
        return splited;
    }

    bool found = false;
    auto last_last = str.begin();
    auto it1 = start_position; //typename string_type::iterator
    auto it2 = str2.begin();
    auto first_found = start_position;

    while (true)
    {
        if(*it1 == *it2)
        {
            if(it2 != str2.end() -1)
            {
                ++it2;
            }
            else
            {
                splited.emplace_back(last_last, it1);
                last_last = it1 +1;
                found = false;
                ++it1;
                it2 = str2.begin();
                first_found = it1;
                continue;
            }

            if(found == false)
            {
                found = true;
                first_found = it1;
            }
        }
        else
        {
        if(found == true)
            {
                found = false;
                it1 = first_found + 1;
                it2 = str2.begin();
                first_found = start_position;
            }
        }

        if(it1 != str.end())
        {
            ++it1;
        }
        else
        {
            // not found
            break;
        }
    }
    splited.emplace_back(_type(last_last, str.end()));
    return splited;
}

namespace saheki::file
{
    namespace sfs = std::filesystem;

    // nome,supervisor,max_partipants,partipants
    auto options_file(sfs::path path_file)
    {
        using char_type = char;
        using string_type = std::basic_string<char_type>;

        const string_type separator = ",";
        const string_type separator2 = "|";
        const auto endl = '\n';

        // get file    
        string_type file = io::inputf<char_type>(path_file);
        
        // split lines
        auto lines = split_lines(file, endl);
        file.clear();

        // parsing
        std::vector<string_type> splitted;
        std::vector<saheki::sort::option<char_type>> options;
        
        std::basic_stringstream<char_type> ss;
        int temp;
        std::vector<string_type> temp_participants_vec;

        for(auto it = lines.begin(); it != lines.end(); ++it)
        {
            splitted = split((*it), separator, (*it).begin());
            if(splitted.size() != 4)
            {
                std::cout << "<ERROR | bad formating in file " << path_file << ">\n";
                exit(1);
            }

            temp_participants_vec =  split(splitted[3], separator2, (splitted[3]).begin());

            //convert args
            ss << splitted[2];
            ss >> temp;

            options.emplace_back(splitted[0],splitted[1],temp ,temp_participants_vec, distance(it, lines.begin()));
            
            ss.clear();
            ss.str(string_type());
            temp = 0;
            splitted.clear();
            temp_participants_vec.clear();
        }
        lines.clear();
        return options;
    }

    // NOME,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16
    auto forms_file(sfs::path path_file)
    {
        using char_type = char;
        using string_type = std::basic_string<char_type>;

        const string_type separator = ",";
        const auto endl = '\n';

        // get file    
        string_type file = io::inputf<char_type>(path_file);
        
        // split lines
        auto lines = split_lines(file, endl);
        file.clear();
        
        // parsing
        std::vector<string_type> splitted;
        std::vector<saheki::sort::partipant<char_type>> partipants;
        
        std::basic_stringstream<char_type> ss;
        
        std::vector<uint32_t> preferences;
        int temp;


        for(auto it = lines.begin(); it != lines.end(); ++it)
        {
            
            splitted = split((*it), separator, (*it).begin());
            if(splitted.size() != 17)
            {
                std::cout << "<ERROR | bad formating in file " << path_file << ">\n";
                exit(1);
            }
            //convert args
            for(auto a = splitted.begin() + 1; a != splitted.end(); ++a)
            {
                ss << *a;
                ss >> temp;
                
                preferences.emplace_back(temp);

                ss.clear();
                ss.str(string_type());
                temp = 0;
            }
            
            partipants.emplace_back(splitted[0], preferences);
            
            splitted.clear();
        }
        lines.clear();
        return partipants;
    }
}
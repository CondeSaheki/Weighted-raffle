#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <filesystem>

#include "io.h"
#include "sort.h"
#include "string_utils.h"


// static fns

namespace saheki::file
{
    namespace sfs = std::filesystem;

    // nome,supervisor,max_partipants,partipants
    auto options_file(sfs::path& path_file)
    {
        using char_type = char;
        using string_type = std::basic_string<char_type>;

        const string_type separator = ",";
        const string_type separator2 = "|";
        const char_type endl = '\n';

        // get file    
        string_type file = io::inputf<char_type>(path_file);
        
        // split lines
        auto lines = string_utils::split_lines(file, endl);
        file.clear();

        // parsing
        std::vector<string_type> splitted;
        std::vector<saheki::sort::option<char_type>> options;
        
        std::basic_stringstream<char_type> ss;
        int temp;
        std::vector<string_type> temp_participants_vec;

        for(auto it = lines.begin(); it != lines.end(); ++it)
        {
            splitted = string_utils::split((*it), separator, (*it).begin());
            if(splitted.size() != 4)
            {
                std::cout << "<ERROR | bad formating in file " << path_file << ">\n";
                exit(1);
            }

            temp_participants_vec = string_utils::split(splitted[3], separator2, (splitted[3]).begin());

            //convert args
            ss << splitted[2];
            ss >> temp;

            options.emplace_back(splitted[0],splitted[1],temp ,temp_participants_vec, std::distance(lines.begin(),it));
            
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
    auto forms_file(sfs::path& path_file)
    {
        using char_type = char;
        using string_type = std::basic_string<char_type>;

        const string_type separator = ",";
        const char_type endl = '\n';

        // get file    
        string_type file = io::inputf<char_type>(path_file);
        
        // split lines
        auto lines = string_utils::split_lines(file, endl);
        file.clear();
        
        // parsing
        std::vector<string_type> splitted;
        std::vector<saheki::sort::partipant<char_type>> partipants;
        
        std::basic_stringstream<char_type> ss;
        std::vector<uint64_t> preferences;
        int temp;


        for(auto it = lines.begin(); it != lines.end(); ++it)
        {
            
            splitted = string_utils::split((*it), separator, (*it).begin());
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
            
            preferences.clear();
            splitted.clear();
        }
        lines.clear();
        return partipants;
    }
}
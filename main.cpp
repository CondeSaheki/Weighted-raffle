#include <iostream>
#include "sort.h"
#include "file.h"

namespace sfs = std::filesystem;

int main(int argc, char **argv)
{
 
    using char_type = char;
    using string_type = std::basic_string<char_type>;
    using namespace saheki;

    // cli args
    /*
        // more or less args than needed
        if(argc != 2) 
        { 
            std::cout << "usage msg";
            exit(1);
        }

        auto path1 = argv[1];
        auto path2 = argv[2];
    */

    sfs::path options_file_path("options.csv");
    sfs::path forms_file_path("forms.csv");
    sfs::path output_file_path("output.csv");


    auto options = file::options_file(options_file_path);
    auto participants = file::forms_file(forms_file_path);

        
    // create references
    std::vector<sort::option<char_type>*> options_ptrs;
    std::vector<sort::partipant<char_type>*> partipants_ptrs;



    for(auto it = options.begin();it != options.end(); ++it)
    {
        options_ptrs.emplace_back(&(*it));
    }
    for(auto it = participants.begin();it != participants.end(); ++it)
    {
        partipants_ptrs.emplace_back(&(*it));
    }

    // check/remove unavalible options
    for(auto it = options_ptrs.begin(); it != options_ptrs.end(); ++it)
    {
        if((*(*it)).max_partipants < (*(*it)).partipants.size())
        {
            options_ptrs.erase(it);
            it = options_ptrs.begin();
        }
    }

    while(true)
    {
        if(options_ptrs.empty())
        {
            std::cout << "no avaliable options" << "\n";
            break;
        }
        if(partipants_ptrs.empty())
        {
            std::cout << "no avaliable participants" << "\n";
            break;
        }

        // print all options
        std::cout << "all options:\n\n";
        for(auto it = options.begin();it != options.end(); ++it)
        {
            std::cout << "name: " << (*it).name << "\n";
            std::cout << "slots: " << (*it).max_partipants << "\n";
            std::cout << "supervisor: " << (*it).supervisor << "\n";
            std::cout << "participants: ";
            for(auto it2 = ((*it).partipants).begin(); it2 != ((*it).partipants).end(); ++it2)    
            {
                std::cout << *it2 << " + ";
            }
            std::cout << " \n\n";
        }
        std::cout << "--------------------------------------------\n";

        // print all avaliable participants
        std::cout << "avaliable participants:\n\n";
        for(auto it = partipants_ptrs.begin();it != partipants_ptrs.end(); ++it)
        {
            std::cout << "name: " << (*(*it)).name << "\n";
        }
        std::cout << " \n\n";
        
        sort::sort(options_ptrs, partipants_ptrs);
    }
    
    // generate output file
    string_type result;
    for(auto it = options.begin();it != options.end(); ++it)
    {
        //Shingeki no Kyojin: The Final Season Part 2,Akaeboshi,2,
        (*it).max_partipants;
        result += (*it).name + "," + (*it).supervisor + ",";
        
        if(!(*it).partipants.empty())
        {
            for(auto it2 = (*it).partipants.begin(); it2 != (*it).partipants.end(); ++it2)
            {
                result += *it2;
                if(it2 + 1 != (*it).partipants.end())
                {
                    result += "|";
                }
            }
        }
        result += "\n";
    }
    io::outputf(output_file_path, result);
}
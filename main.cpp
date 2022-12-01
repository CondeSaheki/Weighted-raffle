#include <iostream>
#include "sort.h"
#include "file.h"


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


    auto options = file::options_file("options.csv");
    auto participants = file::forms_file("forms.csv");

    /*    
    // create references
    std::vector<std::unique_ptr<sort::option<char_type>>> options_references;
    std::vector<std::unique_ptr<sort::partipant<char_type>>> partipants_references;



    for(auto it = options.begin();it != options.end(); ++it)
    {
        options_references.emplace_back(std::make_unique<sort::option<char_type>>(*it));
    }
    for(auto it = participants.begin();it != participants.end(); ++it)
    {
        partipants_references.emplace_back(std::make_unique<sort::partipant<char_type>>(*it));
    }
    

    while(true)
    {
        sort::sort(options_references,partipants_references);
    }

    */
}
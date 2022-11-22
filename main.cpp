#include "sorteador.h"
#include "file.h"


int main(int argc, char **argv)
{
    std::vector<saheki::option<int>> options;
    std::vector<saheki::participant<int>> participants;

    // more or less args than needed
    if(argc != 2) 
    { 
        std::cout << "usage msg";
        exit;
    }



    std::cout << argv[1] << "\n";
    std::cout << argv[2] << "\n";



    std::string participants_path(argv[1]);
    std::string options_path(argv[2]);

    auto participants_file = file::inputfile(participants_path);
    auto options_file = file::inputfile(options_path);


    app.exe animes.txt participantes.txt



    {
        /*
            animepika 3
            animepika2 1
            animepika3 2
        */
        std::string line;
        auto awa = options_file.end();
        auto uwu = options_file.end();
        std::basic_stringstream<char> ss;

        auto temp1 = 1;
        auto temp2 = 1;

        for(auto it = options_file.begin(); it != options_file.end();++it)
        {
            ss << std::string(awa, uwu);
            ss >> temp1 >> temp2;
            options.emplace_back(temp1, temp2);
        }
        
    }


    {

        15
        1

        // 14/11/2022 16:05:02,conde.saheki@gmail.com,asdasd,asdasd,asdasdassa,Não,Não,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16
        // 14/11/2022 16:05:02,conde.saheki@gmail.com,asdasd,asdasd,asdasdassa,Não,Não,1,16,3,4,5,6,7,8,9,10,11,12,13,14,15,16
    }
    
    // populate ...

    
 
    
    
    participants.emplace_back(args);
}
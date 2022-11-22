#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <filesystem>

namespace file
{
    namespace sfs = std::filesystem;
    
    template<typename _Elem = char>
    [[nodiscard]] std::basic_string<_Elem> inputfile(const sfs::path& file_path) noexcept
    {
        std::basic_string<_Elem> file;
        std::basic_ifstream<_Elem> fs;
        fs.open(file_path);
        if (fs.is_open())
        {
            _Elem caracter = 0;
            std::streampos end;
            fs.seekg(0, std::ios_base::end);
            end = fs.tellg();
            fs.seekg(0);
            fs.clear();
            file.reserve(static_cast<int>(end)); // alloc
            benchmark::bench a;
            for (auto pos = 0; pos != static_cast<int>(end); ++pos) // fs.tellg() != end
            {
                //fs >> caracter
                if (caracter = fs.get())
                {
                    file += caracter;
                }
                else
                {
                    exit(1); // the end
                }
                caracter = 0;
            }
        }
        else
        {
            exit(1); // is not open
        }
        fs.close();
        fs.clear();
        return file;
    }
}
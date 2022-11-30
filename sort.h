#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <numbers>
#include <memory>
#include <math.h>

#include "file.h"

// static fns

template<typename type> static constexpr type sarandom(const type max, const type min) noexcept
{
    return 0;
}

template<typename from, typename to> static constexpr auto round_near(const from& value) noexcept
{
    auto casted = static_cast<to>(value);
    from decimals();
    if(casted >= 0)
    {
        decimals = value - casted;
    }
    else
    {
        decimals = value + casted;
    }
    

    if(decimals > 0.5)
    {
        return b + to(1);
    }
    else
    {
        b;
    }
    


}


    // defs
namespace saheki::sort
{
        // types

    // nome,supervisor,max_partipants,partipants
    template<typename _elem = char > class option
    {
    public: // types
        using elem = _elem;
    public: // data
        const std::basic_string<elem> name;
        const std::basic_string<elem> supervisor;
        const uint32_t max_partipants;
        std::vector<std::basic_string<elem>> partipants;
        const size_t position;
    public: // constructors
        constexpr option() 
            : name(std::basic_string<elem>()), 
            supervisor(std::basic_string<elem>()), 
            max_partipants(uint32_t()), 
            partipants(std::vector<std::basic_string<elem>>()), 
            position(size_t()) {}
        constexpr option(
            const std::basic_string<elem>& _name,
            const std::basic_string<elem>& _supervisor,
            const uint32_t& _max_partipants,
            std::vector<std::basic_string<elem>>& _partipants,
            const size_t& _position)
            : name(_name), 
            supervisor(_supervisor), 
            max_partipants(_max_partipants), 
            partipants(_partipants), 
            position(_position) {} 
    };

    auto optionf(std::filesystem::path path_file)
    {
        return saheki::file::options_file(path_file);
    }

    // NOME,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16
    template<typename _elem = char > class partipant
    {
    public: // types
        using elem = _elem;
    public: // data
        const std::basic_string<elem> name;
        std::vector<uint32_t> preferences;
    public:
        constexpr partipant() : name(std::basic_string<elem>()), preferences(std::vector<uint32_t>()) {}
        constexpr partipant(const std::basic_string<elem>& _name, std::vector<uint32_t>& _preferences) : name(_name), preferences(_preferences) {}
    };

    auto partipantf(std::filesystem::path path_file)
    {
        return saheki::file::forms_file(path_file);
    }

    template<typename _elem = char > class interval
    {
    public: // types
        using elem = _elem;
    public: // data
        std::unique_ptr<partipant<elem>> owner;
        uint32_t begin;
        uint32_t end;
    public: // construcotors
        constexpr interval() : owner(), begin(uint32_t()), end(uint32_t()) {}
        constexpr interval(std::unique_ptr<partipant<elem>>& owner, const uint32_t& _begin, const uint32_t& _end) : owner(_owner), begin(_begin), end(_end) {}
    };

        // fns

    void sort(std::vector<std::unique_ptr<sort::option<char>>>& options_references, std::vector<std::unique_ptr<sort::partipant<char>>>& partipants_references)
    {

        const auto e_const = std::numbers::e_v<long double>;
        using char_type = char;
        using string_type = std::basic_string<char_type>;

        //ramdomize music
        auto a = options_references.at(sarandom<int>(0, options_references.size()));
        
        //generate interavlals for participants
        for(auto it = partipant_references.begin(); it != partipant_references.end(); ++it)
        {
            (*it).at(a.position);
        }

        // auto sort = powl(e_const, 16 -x );

    }

}
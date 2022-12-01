#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <numbers>
#include <memory>
#include <chrono>
#include <thread>
#include <math.h>

// static fns

static inline const long double e_const = 2.718281828459045235360287471352662498L;

template<typename type> static constexpr type sarandom(const type max, const type min) noexcept
{
    return 0;
}

template<typename from, typename to> static constexpr auto round_near(const from& value) noexcept
{
/*
    auto casted = static_cast<to>(value);
    from decimals(0);
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
    
*/
}

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

    template<typename _elem = char > class interval
    {
    public: // types
        using elem = _elem;
    public: // data
        partipant<elem>* owner;
        uint32_t begin;
        uint32_t end;
        uint32_t power;
    public: // construcotors
        constexpr interval() : owner(), begin(uint32_t()), end(uint32_t()), power(uint32_t()) {}
        constexpr interval(partipant<elem>* _owner, const uint32_t& _begin, const uint32_t& _end, const uint32_t& _power) : owner(_owner), begin(_begin), end(_end), power(_power) {}
    };

        // fns
using _elem = char;
    void sort(std::vector<option<_elem>*>& options_ptrs, std::vector<partipant<_elem>*>& partipants_ptrs)
    {
        using char_type = char;
        using string_type = std::basic_string<char_type>;
        


        // ramdomize music
        auto random_option = options_ptrs.at(sarandom<int>(0, options_ptrs.size()));

        //display random music info
        std::cout << "name: " << (*random_option).name << "\n" ;
        std::cout << "slots: " << (*random_option).max_partipants << "\n" ;
        std::cout << "supervisor: " << (*random_option).supervisor << "\n";
        std::cout << "participants: ";
        for(auto it = ((*random_option).partipants).begin(); it != ((*random_option).partipants).end(); ++it)    
        {
            std::cout << *it << " " ;
        }
        std::cout << " \n" ;

        // generate intervals for participants
        std::vector<interval<char_type>> intervals;

        uint32_t max_number = 0;

        for(auto it = partipants_ptrs.begin(); it != partipants_ptrs.end(); ++it)
        {
            auto sort = powl(e_const, 16 -(*(*it)).preferences.at((*random_option).position) ); // need round closer 
            if(intervals.empty())
            {
                intervals.emplace_back(*(*it), 0, sort, sort);
            }
            else
            {
                intervals.emplace_back(*(*it), (*(intervals.end() -1)).begin + 1, (*(intervals.end() -1)).begin + 1 + sort, sort);
            }
        }
        
        // random
        max_number = (*(intervals.end() -1)).end;
        auto random_num = sarandom<int>(0, max_number);
        
        // find lucky number interval and calculate chances
        partipant<_elem>* winner;
        for(auto it = intervals.begin(); it != intervals.end(); ++it)
        {
            long double chance_for_participant = (     (static_cast<long double>((*it).power * 100000) / max_number)) / 1000; // need round closer 
            
            std::cout << "participant: " << (*((*it).owner)).name << "chance: " << chance_for_participant << "\n";

            if((*it).begin <= random_num && (*it).end >= random_num)
            {
                winner = (*it).owner;
            }
        }

        // suspense 3seg
        std::this_thread::sleep_for (std::chrono::seconds(3));


        std::cout << "congratulations participant: " << (*winner).name << "\n";

        // check if participant is ok

        if(true) // io::input<char_type, char_type>() == "yes"
        {
            // assing participant to option
            ((*random_option).partipants).emplace_back((*winner).name);
            
            // remove option if full
            if( ((*random_option).partipants).size() <= ((*random_option).max_partipants))
            {
                for(auto it = options_ptrs.begin(); it != options_ptrs.end(); ++it)
                {
                    if((*random_option).position == ((*(*it)).position))
                    {
                        options_ptrs.erase(it);
                        break;
                    }
                }
            }

            // remove participant from participant list
            for(auto it = partipants_ptrs.begin(); it != partipants_ptrs.end(); ++it)
            {
                if((*(*it)).name == (*winner).name)
                {
                    partipants_ptrs.erase(it);
                    break;
                }
            }
        }
        
    }

}
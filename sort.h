#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <numbers>
#include <memory>
#include <chrono>
#include <thread>
#include <math.h>
#include <algorithm>
#include "io.h"

// static fns

static inline const long double e_const = 2.718281828459045235360287471352662498L;

template<typename type> static constexpr type sarandom(const type max, const type min) noexcept
{
    return 0;
}

template< size_t num_decimals, typename from > static constexpr from round_near(const from& value) noexcept
{
    auto copy = value * powl(10, num_decimals);
    auto casted = static_cast<size_t>(copy);
    from decimals(0);
    if(value >= 0)
    {
        decimals = copy - casted;
        if(decimals >= 0.5)
        {
            casted = casted + 1;
        }
    }
    else
    {
        decimals = casted - copy;
        if(decimals <= 0.5)
        {
            casted = casted + 1;
        }
    }
    return static_cast<from>(casted) / powl(10, num_decimals);
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
        constexpr interval() : owner(nullptr), begin(uint32_t()), end(uint32_t()), power(uint32_t()) {}
        constexpr interval(partipant<elem>* _owner, const uint32_t& _begin, const uint32_t& _end, const uint32_t& _power) : owner(_owner), begin(_begin), end(_end), power(_power) {}
    };

        // fns
using _elem = char;
    void sort(std::vector<option<_elem>*>& options_ptrs, std::vector<partipant<_elem>*>& partipants_ptrs)
    {
        using char_type = char;
        using string_type = std::basic_string<char_type>;
        
        // suspense
        std::cout << "Are you ready ?\n"; 
        while((io::input<string_type, char_type>() != "yes"))
        {
            std::cout << "Are you ready ?\n"; 
        }
        
        // ramdomize music
        auto random_option = options_ptrs.at(sarandom<int>(0, options_ptrs.size()));

        //

        //display random music info
        
        std::cout << "randomized option: \n\n";
        std::cout << "name: " << (*random_option).name << "\n" ;
        std::cout << "slots: " << (*random_option).max_partipants << "\n" ;
        std::cout << "supervisor: " << (*random_option).supervisor << "\n";
        std::cout << "participants: ";
        
        for(auto it = ((*random_option).partipants).begin(); it != ((*random_option).partipants).end(); ++it)    
        {
            std::cout << *it << " ";
        }

        std::cout << "\n--------------------------------------------\n\n";
        

        // generate intervals for participants
        std::vector<interval<char_type>> intervals;

        uint32_t max_number = 0;
        uint32_t s;

        std::cout  << "\n\n\n" << ((*random_option).position) << "\n\n\n";

        for(auto it = partipants_ptrs.begin(); it != partipants_ptrs.end(); ++it)
        {
            s = round_near<0>(powl(e_const, 16 - ((*(*it)).preferences)[((*random_option).position)])); // need round closer 
            std::cout << "<" << s << ">\n";
            if(intervals.empty())
            {
                auto temp = 0;
                intervals.emplace_back((*it), temp, s, s);
            }
            else
            {
                intervals.emplace_back((*it), (*(intervals.end() -1)).end + 1, (*(intervals.end() -1)).end + 1 + s, s);
            }

            s = 0;
        }
        
        // random
        max_number = (*(intervals.end() -1)).end;

        std::cout << "<max num|" << max_number << ">\n";

        auto random_num = sarandom<int>(0, max_number);
        

        //sort intervals by power
        std::sort(intervals.begin(), intervals.end(), 
            [](const interval<char_type>& a, const interval<char_type>& b) {
                return a.power > b.power;
            });


        // find lucky number interval and calculate chances
        partipant<_elem>* winner;
        for(auto it = intervals.begin(); it != intervals.end(); ++it)
        {
            long double chance_for_participant = static_cast<long double>((*it).power * 100) / max_number; // need round closer 
            chance_for_participant = round_near<3>(chance_for_participant);

            if( 0.001 > chance_for_participant )
            {
                std::cout << "participant: " << (*((*it).owner)).name << "'s chance: " << " less than 0.001" <<  "%\n";    
            }
            else
            {
                std::cout << "participant: " << (*((*it).owner)).name << "'s chance: " << chance_for_participant <<  "%\n";
            }

            

            if((*it).begin <= random_num && (*it).end >= random_num)
            {
                winner = (*it).owner;
            }
        }

        


        std::cout << " \n\n";

        // suspense
        std::cout << "Are you ready ?\n"; 
        while((io::input<string_type, char_type>() != "yes"))
        {
            std::cout << "Are you ready ?\n"; 
        }


        std::cout << "\ncongratulations participant: " << (*winner).name << "\n";

        // check if participant is ok

        if(true) // io::input<char_type, char_type>() == "yes"
        {
            // assing participant to option
            ((*random_option).partipants).emplace_back((*winner).name);
            

            // remove option if full
            if( ((*random_option).partipants).size() >= ((*random_option).max_partipants))
            {
                for(auto it = options_ptrs.begin(); it != options_ptrs.end(); ++it)
                {
                    if((*random_option).position == ((*(*it)).position))
                    {
                        std::cout << "<removed option>\n";
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
                    std::cout << "<removed participant>\n";
                    partipants_ptrs.erase(it);
                    break;
                }
            }
        }
        
    }

}
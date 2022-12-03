#pragma once
#include <string>
#include <vector>
#include <algorithm>

#include "io.h"
#include "random.h"
#include "math_utils.h"

#define MAKE_QUESTIONS 0
#define QUESTIONS_CLEAR 1
#define RE_ROLL 0

static inline const long double e_const = 2.718281828459045235360287471352662498L;

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
        const uint64_t max_partipants;
        std::vector<std::basic_string<elem>> partipants;
        const size_t position;
    public: // constructors
        constexpr option() 
            : name(std::basic_string<elem>()), 
            supervisor(std::basic_string<elem>()), 
            max_partipants(uint64_t()), 
            partipants(std::vector<std::basic_string<elem>>()), 
            position(size_t()) {}
        constexpr option(
            const std::basic_string<elem>& _name,
            const std::basic_string<elem>& _supervisor,
            const uint64_t& _max_partipants,
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
        std::vector<uint64_t> preferences;
    public:
        constexpr partipant() : name(std::basic_string<elem>()), preferences(std::vector<uint64_t>()) {}
        constexpr partipant(const std::basic_string<elem>& _name, std::vector<uint64_t>& _preferences) : name(_name), preferences(_preferences) {}
    };

    template<typename _elem = char > class interval
    {
    public: // types
        using elem = _elem;
    public: // data
        partipant<elem>* owner;
        uint64_t begin;
        uint64_t end;
        uint64_t power;
        long double chance;
    public: // construcotors
        constexpr interval() : owner(nullptr), begin(uint64_t()), end(uint64_t()), power(uint64_t()), chance(0.0) {}
        constexpr interval(partipant<elem>* _owner, const uint64_t& _begin, const uint64_t& _end, const uint64_t& _power) : owner(_owner), begin(_begin), end(_end), power(_power), chance(0.0) {}
    };
    
        // fns

    void question1()
    {
        #if MAKE_QUESTIONS
            using char_type = char;
            std::cout << "--------------------------------------------\n";
            while(true)
            {
                std::cout << "Are you ready ?\n"; 
                if(io::input<std::basic_string<char_type>, char_type>() == "yes") { break; }
            }
        #endif
    }
    void question2()
    {
        question1();
        #if MAKE_QUESTIONS
        #if QUESTIONS_CLEAR
            system("clear");
        #endif
        #endif
    }
    bool question3()
    {
        #if RE_ROLL
            using char_type = char;
            std::basic_string<char_type> str;
            std::cout << "--------------------------------------------\n";
            while(true)
            {
                std::cout << "participant you want to reroll ?\n";
                str = io::input<std::basic_string<char_type>, char_type>();
                if(str == "yes") { return true; }
                if(str == "no") { return false; }
                str.clear();
            }
        #endif
        return false;
    }

    //print options
    template<typename _elem> void print_option(const option<_elem>& target)
    {
        std::cout << target.name << " | " << target.supervisor;
        if(!((target.partipants).empty()))
        {
            std::cout << " with ";
        }
        for(auto it = (target.partipants).begin(); it != (target.partipants).end(); ++it)
        {
            std::cout << *it;
            if(it + 1 != (target.partipants).end())
            {
                std::cout << " + ";
            }
        }
        //std::cout << "\n";
    }
    template<typename _elem> void print_option(const std::vector<option<_elem>>& target)
    {
        for(auto it = target.begin(); it != target.end(); ++it)
        {
            print_option<_elem>(*it);
            std::cout << std::endl;
        }
    }
    template<typename _elem> void print_option(const std::vector<option<_elem>*>& target)
    {
        for(auto it = target.begin(); it != target.end(); ++it)
        {
            print_option<_elem>(**it);
            std::cout << std::endl;
        }
    }

    //print participants
    template<typename _elem> void print_participant(const partipant<_elem>& target)
    {
        std::cout << target.name;
        /*
        for(auto it = (target.preferences).begin(); it != (target.preferences).end(); ++it)
        {
            std::cout << (*it) << std::endl;
        }
        */
    }
    template<typename _elem> void print_participant(const std::vector<partipant<_elem>>& target)
    {
        for(auto it = target.begin(); it != target.end() - 1; ++it)
        {
            print_participant<_elem>(*it);
            std::cout << ", ";
        }
        print_participant<_elem>(*(target.end() - 1));
        std::cout << std::endl;
    }
    template<typename _elem> void print_participant(const std::vector<partipant<_elem>*>& target)
    {
        for(auto it = target.begin(); it != target.end() - 1; ++it)
        {
            print_participant<_elem>(**it);
            std::cout << ", ";
        }
        print_participant<_elem>(**(target.end() - 1));
        std::cout << std::endl;
    }

    // print intervals
    template<typename _elem> void print_interval(const interval<_elem>& target)
    {
        print_participant(*(target.owner));
        if( 0.001 > target.chance)
        {
            std::cout << " | less than 0.001%\n";
        }
        else
        {
            std::cout << " | " << target.chance << "%\n";
        }
    }
    template<typename _elem> void print_interval(const std::vector<interval<_elem>>& target)
    {
        for(auto it = target.begin(); it != target.end(); ++it)
        {
            print_interval<_elem>(*it);
        }
    }
    template<typename _elem> void print_interval(const std::vector<interval<_elem>*>& target)
    {
        for(auto it = target.begin(); it != target.end(); ++it)
        {
            print_interval<_elem>(**it);
        }
    }
    
    // true gaming
    template<typename _elem = char > void sort(std::vector<option<_elem>*>& options_ptrs, std::vector<partipant<_elem>*>& partipants_ptrs)
    {
        using char_type = char;
        using string_type = std::basic_string<char_type>;
        
        // suspense
        question2();

        // ramdomize music
        auto random_option = options_ptrs.at(saheki::random_generator::number(options_ptrs.size() - 1));

        //display random music info
        std::cout << "--------------------------------------------\n";
        std::cout << "random music:\n";
        print_option<char_type>((*random_option));
        std::cout << std::endl;

        // generate intervals for participants
        std::vector<interval<char_type>> intervals;
        {
            uint64_t _power;
            auto temp = 0;
            for(auto it = partipants_ptrs.begin(); it != partipants_ptrs.end(); ++it)
            {   
                _power = math::round_near<0>(powl(e_const, 16 - ((*(*it)).preferences)[((*random_option).position)])); // need round closer 
                if(intervals.empty())
                {
                    intervals.emplace_back((*it), temp, _power, _power);
                }
                else
                {
                    intervals.emplace_back((*it), (*(intervals.end() -1)).end + 1, (*(intervals.end() -1)).end + 1 + _power, _power);
                }
                _power = 0;
            }
        }

        //get max number
        uint64_t max_number = (*(intervals.end() -1)).end;
        
        //sort intervals by power
        std::sort(intervals.begin(), intervals.end(), 
            [](const interval<char_type>& a, const interval<char_type>& b) {
                return a.power > b.power;
            });

        // random    
        auto random_num = saheki::random_generator::number(max_number);

        // find lucky number interval and calculate chances
        auto winner_interval = intervals.end();
        for(auto it = intervals.begin(); it != intervals.end(); ++it)
        {
            (*it).chance = math::round_near<3>((static_cast<long double>((*it).power * 100) / max_number));
            if((*it).begin <= random_num && (*it).end >= random_num)
            {
                winner_interval = it;
            }
        }
        
        //print all participants interval and chances
        std::cout << "--------------------------------------------\n";
        std::cout << "All participant chances: \n";
        print_interval(intervals);

        // suspense
        question1();

        // print winner
        std::cout << "--------------------------------------------\n";
        std::cout << "Congratulations!!!\n";
        print_interval(*winner_interval);
        
        // maybe check if participant is ok 
        if(!question3())
        {
            // assing participant to option
            ((*random_option).partipants).emplace_back((*((*winner_interval).owner)).name);
            
            // remove option if full
            if( ((*random_option).partipants).size() >= ((*random_option).max_partipants))
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
                if((*(*it)).name == (*((*winner_interval).owner)).name)
                {
                    partipants_ptrs.erase(it);
                    break;
                }
            }
        }

        // suspense
        question2();

    }

}

#undef MAKE_QUESTIONS
#undef QUESTIONS_CLEAR
#undef RE_ROLL
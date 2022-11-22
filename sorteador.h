#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

namespace saheki
{
        
        // types

    template<typename type = int> class value
    {
    public: // types
        using num_type = type;
    public: // data
        const num_type begin;
        const num_type end;
        typename std::vector<participant<num_type>>::iterator owner;
    public: // constructor
        constexpr value() : begin(1), end(1) {}
        template<typename type> constexpr value(const type& Begin, const type& End) : begin(static_cast<num_type>(Begin)), end(static_cast<num_type>(End)) {}
    };

    template<typename type = int> class participant
    {
    public: // types
        using num_type = type;
        using char_type = char;
        using string_type = std::basic_string<char_type>;
    public: // data
        string_type name;
        std::vector<num_type> preferences;
    public: // constructor
        constexpr participant() : name(string_type()), preferences(std::vector<num_type>()) {}
        template<typename type1, typename type2> constexpr participant(const type1& Name, const type2& Pref) : 
            name(static_cast<string_type>(Name)), 
            preferences(static_cast<std::vector<num_type>>(Pref)) {}
    };

    template<typename type = int> class option
    {
    public: // types
        using num_type = type;
        using char_type = char;
        using string_type = std::basic_string<char_type>;
    public: // data
        const string_type name;
        std::vector<typename participant<num_type>::iterator> chosen_ones;
        const num_type max_slots;
    public: // constructor

        constexpr option() : name(string_type()), slots(1), max_slots(1) {}
        template<typename type> constexpr option(const type& Start, const type& End) : start(static_cast<num>(Start)), end(static_cast<num>(End)) {}
    };

            // functions

    template<typename type1,typename type2> type1 random(const type1& max, const type2& min) {}
    bool user_input();

    void sort()
    {
            // types

        using num_type = int;
        using char_type = char;
        using string_type = std::basic_string<char_type>;

            // data

        const std::vector<participant<num_type>> participants; // temp dont modify 
        const std::vector<option<num_type>> options; // temp dont modify 

        std::vector<typename std::vector<option<num_type>>::iterator> options_its;
        std::vector<typename std::vector<participant<num_type>>::iterator> participants_its;
        std::vector<value<num_type>> values;
        values.reserve(participants.size());
        options_its.reserve(options.size());
        participants_its.reserve(participants.size());
        
        num_type rand_opt_num = -1;
        auto rand_opt_it = options_its.end();
        
        num_type random_part_num = -1;
        auto chosen_one = participants_its.end();
        num_type temp =-1;

            // logic

        // fill modifiable containers
        for(auto it = options.begin(); it != options.end(); ++it) { options_its.emplace_back(it); }        
        for(auto it = participants.begin(); it != participants.end(); ++it) { participants_its.emplace_back(it); }        
        
        while(!options_its.empty())
        {

            // random option 
            rand_opt_num = random(options_its.size() -1, 0);
            rand_opt_it = (options_its.begin() + random(options_its.size() -1, 0));

            // fill values container
            for(auto it = participants_its.begin(); it != participants_its.end(); ++it)
            {
                temp = options.size() - (*(*it)).preferences[rand_opt_num] + 1;
                if(temp == options.size())
                {
                    values.emplace_back(0, static_cast<num_type>(2.71828 * 2.71828 * temp));
                    continue;
                }
                values.emplace_back(0, static_cast<num_type>(2.71828 * temp));
            }

            // weighted random
            random_part_num = random(values.back().end, 0);

            //find chosen one
            for(auto it = values.begin(); it != values.end(); ++it)
            {
                if((*it).begin <= random_part_num && random_part_num < (*it).end)
                {
                    chosen_one = (*it).owner;
                    break;
                }
            }           
            
            // ask participant if he wants the option
            if(user_input()) // true
            {
                (*(*rand_opt_it)).chosen_ones.emplace_back(chosen_one);

                if((*(*rand_opt_it)).chosen_ones.size() == (*(*rand_opt_it)).max_slots)
                {
                    options_its.erase(rand_opt_it);
                }
                participants_its.erase(chosen_one);
            }

            values.clear();
        }
    }

}
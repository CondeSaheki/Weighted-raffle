#pragma once
#include <string>
#include <vector>

namespace saheki::string_utils
{
    template<typename _elem = char >
    static auto split_lines(const std::basic_string<_elem>& str, const _elem& endl) noexcept
    {
        std::vector<std::basic_string<_elem>> lines;
        {
            auto pos = str.begin(); // typename std::basic_string<_elem>::iterator
            for(auto it = str.begin(); it != str.end(); ++it)
            {
                if(*it == endl)
                {
                    lines.emplace_back(pos, it);
                    pos = it + 1;
                }
            }
            lines.emplace_back(pos, str.end());
        }
        return lines;
    }

    template<typename _type = std::string >
    static std::vector<_type> split(const _type& str, const _type& str2, typename _type::const_iterator start_position) noexcept
    {
        std::vector<_type> splited;
        if(str.empty() || str2.empty() || start_position == str.end())
        {
            return splited;
        }

        bool found = false;
        auto last_last = str.begin();
        auto it1 = start_position; //typename string_type::iterator
        auto it2 = str2.begin();
        auto first_found = start_position;

        while (true)
        {
            if(*it1 == *it2)
            {
                if(it2 != str2.end() -1)
                {
                    ++it2;
                }
                else
                {
                    splited.emplace_back(last_last, it1);
                    last_last = it1 +1;
                    found = false;
                    ++it1;
                    it2 = str2.begin();
                    first_found = it1;
                    continue;
                }

                if(found == false)
                {
                    found = true;
                    first_found = it1;
                }
            }
            else
            {
            if(found == true)
                {
                    found = false;
                    it1 = first_found + 1;
                    it2 = str2.begin();
                    first_found = start_position;
                }
            }

            if(it1 != str.end())
            {
                ++it1;
            }
            else
            {
                // not found
                break;
            }
        }
        splited.emplace_back(_type(last_last, str.end()));
        return splited;
    }
}
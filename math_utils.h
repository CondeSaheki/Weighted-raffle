#pragma once
#include <math.h>

namespace saheki::math
{
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
}
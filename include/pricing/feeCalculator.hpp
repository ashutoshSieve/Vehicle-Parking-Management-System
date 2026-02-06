#ifndef FEECAL_HPP
#define FEECAL_HPP
#include<ctime>
class FeeCalculator {
public:
    virtual double calculateFee(time_t in, time_t out) const = 0;
    virtual ~FeeCalculator() = default;
};

inline long secondsToCeilHours(time_t in, time_t out) {
    if (out < in) return 0;
    long secs = static_cast<long>(out - in);
    long hours = secs / 3600;
    if (secs % 3600 != 0) ++hours;
    if (hours == 0) hours = 1;
    return hours;
}
#endif
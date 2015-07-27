#include <lo/lo.h>
#include <string>
#include <iostream>

#pragma once

namespace spiralcore {

class status {
public:
    static void _update(std::string msg);
    static void update(const char *msg, ...);
    static lo_address m_address;
};

}

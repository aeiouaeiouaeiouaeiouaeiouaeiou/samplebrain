#include <lo/lo.h>
#include <string>
#include <iostream>

#pragma once

namespace spiralcore {

class status {
public:
    static void _update(const std::string &msg);
    static void update(const char *msg, ...);
    static void sound_item(const std::string &name, const std::string &colour);
    static void sound_item_refresh();
    static lo_address m_address;
};

}

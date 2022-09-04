#include "status.h"
#include <iostream>

using namespace spiralcore;
using namespace std;

lo_address status::m_address = lo_address_new_from_url("osc.udp://localhost:8890");

void status::_update(const std::string &msg) {
    lo_send(m_address,"/report","s",msg.c_str());
}

void status::sound_item(const std::string &name, const std::string &colour) {
  lo_send(m_address,"/sound-item","ss",name.c_str(),colour.c_str());
}

void status::sound_item_refresh() {
  lo_send(m_address,"/sound-item-refresh","");
}

void status::update(const char *msg, ...) {
    va_list args;
    va_start(args, msg);
    char s[4096];
    vsnprintf(s,4096,msg,args);
    status::_update(s);
    va_end(args);
}

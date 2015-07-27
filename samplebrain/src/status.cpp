#include "status.h"
#include <iostream>

using namespace spiralcore;
using namespace std;

lo_address status::m_address = lo_address_new_from_url("osc.udp://localhost:8890");

void status::_update(std::string msg) {
    cerr<<msg<<endl;
    lo_send(m_address,"/report","s",msg.c_str());
}

void status::update(const char *msg, ...) {
    va_list args;
    va_start(args, msg);
    char s[4096];
    vsnprintf(s,4096,msg,args);
    status::_update(s);
    va_end(args);
}

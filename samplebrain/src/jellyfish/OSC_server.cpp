// copyright (C) 2004 david griffiths <dave@pawfal.org>
//
// this program is free software; you can redistribute it and/or modify
// it under the terms of the GNU general public license as published by
// the free software foundation; either version 2 of the license, or
// (at your option) any later version.
//
// this program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  see the
// GNU general public license for more details.
//
// you should have received a copy of the GNU general public license
// along with this program; if not, write to the free software
// foundation, inc., 59 temple place - suite 330, boston, MA 02111-1307, USA.

#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <iostream>

#include "OSC_server.h"

using namespace std;

#ifdef NO_LO_ARG_SIZE_DECL
extern "C" {
  size_t lo_arg_size (lo_type type, void * data);
};
#endif

OSC_server::OSC_server(const string &port) :
m_port(port),
m_exit(false),
m_command_ring_buffer(262144)
{
        //cerr<<"using port: ["<<port<<"]"<<endl;
    m_server = lo_server_thread_new(port.c_str(), error_handler);
    lo_server_thread_add_method(m_server, NULL, NULL, default_handler, this);
}

OSC_server::~OSC_server()
{
    m_exit=true;
    lo_server_thread_stop(m_server);
}

void OSC_server::run()
{
    lo_server_thread_start(m_server);
//    while (!m_exit) usleep(1000);
}

void OSC_server::error_handler(int num, const char *msg, const char *path)
{
    //cerr<<"liblo server error "<<num<<" in path "<<path<<": "<<msg<<endl;
    cerr<<"liblo server error "<<num<<endl;
}

int OSC_server::default_handler(const char *path, const char *types, lo_arg **argv,
                    int argc, void *data, void *user_data)
{
        OSC_server *server = (OSC_server*)user_data;

        unsigned int size = 0;
        for (int i=0; i<argc; i++)
        {
                size+=lo_arg_size((lo_type)types[i],argv[i]);
                // add one for the null terminator
                if (types[i]=='s') size++;
        }

        char *newdata=new char[size];
        unsigned int pos=0;
        for (int i=0; i<argc; i++)
        {
                switch (types[i])
                {
                        case LO_INT32:
                        {
                                if (pos+4>COMMAND_DATA_SIZE)
                                {
                                        cerr<<"osc data too big for ringbuffer command"<<endl;
                                        delete[] newdata;
                                        return 1;
                                }

                                memcpy(newdata+pos,(char*)argv[i],4);
                                pos+=4;
                        }
                        break;
                        case LO_FLOAT:
                        {
                                if (pos+4>COMMAND_DATA_SIZE)
                                {
                                        cerr<<"osc data too big for ringbuffer command"<<endl;
                                        delete[] newdata;
                                        return 1;
                                }

                                memcpy(newdata+pos,(char*)argv[i],4);
                                pos+=4;
                        }
                        break;
                        case LO_STRING:
                        {
                                int size=strlen(&argv[i]->s);

                                if (pos+size+1>COMMAND_DATA_SIZE)
                                {
                                        cerr<<"osc data too big for ringbuffer command"<<endl;
                                        delete[] newdata;
                                        return 1;
                                }

                                memcpy(newdata+pos,&argv[i]->s,size);
                                newdata[pos+size]='\0';
                                pos+=size+1;
                        }
                        break;
                        default:
                        {
                                cerr<<"unsupported type: "<<types[i]<<endl;
                                delete[] newdata;
                                return 1;
                        }
                        break;
                }
        }

        if (1)//pos==size) hmm
        {
                command_ring_buffer::command command(path,types,newdata,pos);
                if (!server->m_command_ring_buffer.send(command))
                {
                        //cerr<<"OSC_server - ringbuffer full!"<<endl;
                }
        }
        else
        {
                cerr<<"OSC_server::default_handler: size mismatch ["<<pos<<":"<<size<<"], not sending message"<<endl;
        }

        delete[] newdata;
    return 1;
}

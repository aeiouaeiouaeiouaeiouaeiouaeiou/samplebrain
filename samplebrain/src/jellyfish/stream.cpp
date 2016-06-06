// Copyright (C) 2015 Dave Griffiths
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

#include <fstream>
#include "stream.h"
#include <iostream>
#include "types.h"

using namespace spiralcore;
using namespace std;

template<>ios &spiralcore::operator||(ios &s, string &v) {
    ofstream *pos=dynamic_cast<ofstream*>(&s);
    if (pos!=NULL) {
        ofstream &os = *pos;
        size_t len = v.length();
        os.write((char *)&len,sizeof(size_t));
        os.write((char*)(v.c_str()),v.length());
        return os;
    }
    else
    {
        ifstream *pis=dynamic_cast<ifstream*>(&s);
        assert(pis!=NULL);
        ifstream &is = *pis;
        size_t len=0;
        is.read((char *)&len,sizeof(size_t));
        if (len>0) {
            char *str = new char[len+1];
            is.read(str,len);
            str[len]='\0';
            v = string(str);
            delete[] str;
        }
        else {
            //v=string("");
        }
        return is;
    }
}


/*ios &operator||(ios &s, vector<U> &v) {
    ofstream *pos=dynamic_cast<ofstream*>(&s);
    if (pos!=NULL) {
        ofstream &os = *pos;
        size_t len = v.length();
        os.write((char *)&len,sizeof(size_t));
        return os.write((char*)(&v[0]),v.length()*sizeof(U));
    }
    else
    {
        ifstream *pis=dynamic_cast<ifstream*>(&s);
        assert(pis);
        ifstream &is = *pis;
        size_t len=0;
        is.read((char *)&len,sizeof(size_t));
        v.reserve(len);
        is.read((char*)&v[0],len);
        return is;
    }


    }*/
/*
template<class U>ios &operator||(ios &s, vector<U> &v) {
    ofstream *pos=dynamic_cast<ofstream*>(&s);
    if (pos!=NULL) {
        ofstream &os = *pos;
        size_t len = v.length();
        for (size_t i=0; i<len; ++i) {
            os||v[i];
        }
        return os;
    }
    else
    {
        ifstream *pis=dynamic_cast<ifstream*>(&s);
        assert(pis);
        ifstream &is = *pis;
        size_t len=0;
        is.read((char *)&len,sizeof(size_t));
        v.reserve(len);
        for (size_t i=0; i<len; ++i) {
            is||v[i];
        }
        return is;
    }


}
*/

void spiralcore::stream_unit_test() {

    ofstream of("test_data/streamtest.bin",ios::binary);
    int o_a(100);
    float o_b(0.2);
    string o_c("hello");
    string o_d("there");
    s32 size=10;
    int *o_e = new int[size];
    vector<int> o_f;

    for(s32 i=0; i<size; i++) {
        o_e[i]=i;
        o_f.push_back(i);
    }

    of||o_a||o_b||o_c||o_d;
//    o_e = stream_array(of,o_e,size);
    stream_vector(of,o_f);
    of.close();
    delete[] o_e;

    ifstream ifs("test_data/streamtest.bin",ios::binary);
    int i_a;
    float i_b;
    string i_c,i_d;
    ifs||i_a||i_b||i_c||i_d;
    int *i_e;
    vector<int> i_f;
//    i_e = stream_array(ifs,i_e,size);
    stream_vector(ifs,i_f);

    ifs.close();
    assert(i_a==100);
    assert(i_b>0.199f && i_b<0.20001);
    assert(i_c=="hello");
    assert(i_d=="there");

    for(s32 i=0; i<size; i++) {
//        assert(i_e[i]==i);
        assert(i_f[i]==i);
    }
    //delete[] i_e;
}

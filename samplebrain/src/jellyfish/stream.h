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
#include <string>
#include <vector>
#include <list>
#include <assert.h>
#include <iostream>

#pragma once

namespace spiralcore {

// hack to do both stream directions in one function
// saw this years ago at computer artworks, not seen it since...

template<typename T>std::ios &operator||(std::ios &s, T &v) {
    std::ofstream *pos=dynamic_cast<std::ofstream*>(&s);
    if (pos!=NULL) {
        std::ofstream &os = *pos;
        os.write((char*)(&v),sizeof(T));
        return os;
    }
    else
    {
        std::ifstream *pis=dynamic_cast<std::ifstream*>(&s);
        assert(pis);
        std::ifstream &is = *pis;
        is.read((char *)(&v),sizeof(T));
        return is;
    }
}

template<>std::ios &operator||(std::ios &s, std::string &v);

/*
template<typename T, typename U>T *stream_array(std::ios &s, T *v, U &len) {
    std::ofstream *pos=dynamic_cast<std::ofstream*>(&s);
    if (pos!=NULL) {
        std::ofstream &os = *pos;
        os||len;
        os.write((char*)v,sizeof(T)*len);
        return v;
    } else  {
        std::ifstream *pis=dynamic_cast<std::ifstream*>(&s);
        assert(pis);
        std::ifstream &is = *pis;
        is||len;
        if (v!=NULL) delete[] v;
        T* t = new T[len];
        is.read((char *)t,sizeof(T)*len);
        return t;
    }
}
*/

template<typename T>std::ios &stream_vector(std::ios &s, std::vector<T> &v) {
    std::ofstream *pos=dynamic_cast<std::ofstream*>(&s);
    if (pos!=NULL) {
        std::ofstream &os = *pos;
        size_t len = v.size();
        os||len;
        for (size_t i=0; i<len; ++i) {
            os||v[i];
        }
        return os;
    }
    else
    {
        std::ifstream *pis=dynamic_cast<std::ifstream*>(&s);
        assert(pis);
        std::ifstream &is = *pis;
        size_t len=0;
        is||len;
        //v.reserve(len);
        v.clear();
        for (size_t i=0; i<len; ++i) {
            T t;
            is||t;
            v.push_back(t);
        }
        return is;
    }
}

// skip a vector when loading
template<typename T>std::ios &skip_vector(std::ifstream &is) {
  size_t len=0;
  is||len;
  for (size_t i=0; i<len; ++i) {
    T t;
    is||t;
  }
  return is;
}


template<typename T>std::ios &stream_list(std::ios &s, std::list<T> &v) {
    std::ofstream *pos=dynamic_cast<std::ofstream*>(&s);
    if (pos!=NULL) {
        std::ofstream &os = *pos;
        size_t len = v.size();
        os||len;
        for (typename std::list<T>::iterator i=v.begin(); i!=v.end(); ++i) {
            os||*i;
        }
        return os;
    }
    else
    {
        std::ifstream *pis=dynamic_cast<std::ifstream*>(&s);
        assert(pis);
        std::ifstream &is = *pis;
        size_t len=0;
        is||len;
        for (size_t i=0; i<len; ++i) {
            T t;
            is||t;
            v.push_back(t);
        }
        return is;
    }
}

template<typename T>std::ios &skip_list(std::istream &is) {
  size_t len=0;
  is||len;
  for (size_t i=0; i<len; ++i) {
    T t;
    is||t;
  }
  return is;
}

void stream_unit_test();

}

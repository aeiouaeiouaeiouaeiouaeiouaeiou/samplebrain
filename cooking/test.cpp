#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <cmath>

#include <fstream>


using namespace std;

class desc {
public:
    desc() {
        randomise();
    }

    void randomise() {
        for (unsigned int i=0; i<13; ++i) {
            m_data[i]=rand()%1000/1000.0f;
        }
    }
    float m_data[13];
};

class test {
public:
    test(int brain_size) {
        for (int i=0; i<brain_size; i++) {
            m_brain.push_back(new desc());
        }
    }


    vector<desc*> m_brain;

    float dist(const desc &a, const desc &b) {
        float ret = 0;
        for(unsigned int i=0; i<13; ++i) {
            ret += abs(a.m_data[i]-b.m_data[i]);
        }
    }

    int find_closest(const desc &a) {
        float closest = 999999999999;
        unsigned int closest_index = 0;
        unsigned int index = 0;
        for (vector<desc*>::iterator i=m_brain.begin(); i!=m_brain.end(); ++i) {
            float d = dist(a,**i);
            if (d<closest) {
                closest = d;
                closest_index = index;
            }
            index++;
        }
        return closest_index;
    }
};



template<typename T>ios &operator||(ios &s, T &v) {
    ofstream *pos=dynamic_cast<ofstream*>(&s);
    if (pos!=NULL) {
        ofstream &os = *pos;
        return os.write((char*)(&v),sizeof(T));
    }
    else
    {
        ifstream *pis=dynamic_cast<ifstream*>(&s);
        assert(pis);
        ifstream &is = *pis;
        return is.read((char *)(&v),sizeof(T));
    }
}

template<typename T>ios &stream_array(ios &s, T *v, size_t &len) {
    ofstream *pos=dynamic_cast<ofstream*>(&s);
    if (pos!=NULL) {
        ofstream &os = *pos;
        os||len;
        return os.write((char*)v,sizeof(T)*len);
    }
    else
    {
        ifstream *pis=dynamic_cast<ifstream*>(&s);
        assert(pis);
        ifstream &is = *pis;
        is||len;
        return is.read((char *)v,sizeof(T)*len);
    }
}




class sertest {
public:
    sertest() {
        size = 100;
        buf = new float[size];
    }

    void build() {
        for (unsigned int n=0; n<size; n++) {
            buf[n]=n;
        }
    }

    float a;
    int c;
    float *buf;
    size_t size;
};

bool operator||(ios &s, sertest &v) {
    s||v.a||v.c;
    stream_array(s,v.buf,v.size);
}


int main() {

    sertest ss;
    ss.a=100;
    ss.c=230;
    ss.build();

    ofstream of("test.bin", ios::binary);
    of||ss;
    of.close();

    sertest sb;
    ifstream inf("test.bin", ios::binary);
    inf||sb;
    inf.close();

    cerr<<sb.a<<" "<<sb.c<<" "<<sb.buf[50]<<endl;


//    auto func = [] () { cout << "Hello world"; };
    //   func(); // now call the function

/*    test t=test(999);
    desc d;
    for (unsigned int i=0; i<99999; i++) {
        t.find_closest(d);
        d.randomise();
    }
*/
    return 0;
}

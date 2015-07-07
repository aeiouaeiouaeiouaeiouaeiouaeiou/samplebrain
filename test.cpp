#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <cmath>

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

int main() {
    auto func = [] () { cout << "Hello world"; };
    func(); // now call the function

/*    test t=test(999);
    desc d;
    for (unsigned int i=0; i<99999; i++) {
        t.find_closest(d);
        d.randomise();
    }
*/
    return 0;
}

#include <string>
#include <vector>
#include "jellyfish/fluxa/sample.h"
#include "jellyfish/core/types.h"

#ifndef WINDOW
#define WINDOW

namespace spiralcore {

class window {
public:
    window();
    void init(u32 length);

    enum type {
        DODGY = 0,
        BARTLETT,
        BLACKMAN,
        FLAT_TOP,
        GAUSSIAN,
        HAMMING,
        HANN,
        RECTANGLE,
        MAX_TYPES
    };

    void set_current_type(type t) { m_current_type=t; }
    void run(const sample &sample) const;

private:
    void clear();

    type m_current_type;

    std::vector<sample*> m_windows;

};

}

#endif

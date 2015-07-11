#ifndef SEARCH_PARAMS
#define SEARCH_PARAMS

namespace spiralcore {

class search_params {
public:
search_params(float ratio, int s1, int e1, int s2, int e2) :
    m_ratio(ratio),
        m_fft1_start(s1),
        m_fft1_end(e1),
        m_fft2_start(s2),
        m_fft2_end(e2) {}


    float m_ratio;
    int m_fft1_start;
    int m_fft1_end;
    int m_fft2_start;
    int m_fft2_end;

};

}

#endif

#include <fftw3.h>

#ifndef SPIRALCORE_FFT
#define SPIRALCORE_FFT

//#define __FFTWFLOAT__

namespace spiralcore {

class FFT
{
public:
    FFT(int length);
    ~FFT();
	void impulse2freq(float *imp, float *out);
    void raw_impulse2freq();

#ifndef __FFTWFLOAT__
	fftw_plan m_plan;
	unsigned int m_length;
	double *m_in;
	fftw_complex *m_spectrum;
#else
	fftwf_plan m_plan;
	unsigned int m_length;
	float *m_in;
	fftwf_complex *m_spectrum;
#endif
};

}

#endif

#include <fft.h>

using namespace spiralcore;

static const int MAX_FFT_LENGTH = 4096;

FFT::FFT(int length) :
    m_length(length),
#ifndef __FFTWFLOAT__
    m_in(new double[length]),
#else
    m_in(new float[length]),
#endif

#ifndef __FFTWFLOAT__
    m_spectrum(new fftw_complex[length])
{
	m_plan = fftw_plan_dft_r2c_1d(m_length, m_in, m_spectrum, FFTW_ESTIMATE);
}
#else
m_spectrum(new fftwf_complex[length])
{
	m_plan = fftwf_plan_dft_r2c_1d(m_length, m_in, m_spectrum, FFTW_ESTIMATE);
}
#endif

FFT::~FFT()
{
	delete[] m_in;
#ifndef __FFTWFLOAT__
	fftw_destroy_plan(m_plan);
#else
	fftwf_destroy_plan(m_plan);
#endif
}

void FFT::impulse2freq(float *imp, float *out)
{
    unsigned int i;

    for (i=0; i<m_length; i++)
    {
        m_in[i] = imp[i];
    }

#ifndef __FFTWFLOAT__
    fftw_execute(m_plan);
#else
    fftwf_execute(m_plan);
#endif

    for (i=0; i<m_length; i++)
    {
        out[i] = m_spectrum[i][0];
    }
}

void FFT::raw_impulse2freq()
{
    fftw_execute(m_plan);
}

#include <fft.h>
#include <jellyfish/core/types.h>

using namespace spiralcore;

static const int MAX_FFT_LENGTH = 4096;

FFT::FFT(int length) :
    m_length(length),
    m_in(new double[length]),
    m_spectrum(new fftw_complex[length])
{
	m_plan = fftw_plan_dft_r2c_1d(m_length, m_in, m_spectrum, FFTW_ESTIMATE);
}

FFT::~FFT()
{
	delete[] m_in;
	fftw_destroy_plan(m_plan);
}

void FFT::impulse2freq(float *imp)
{
    unsigned int i;

    for (i=0; i<m_length; i++)
    {
        m_in[i] = imp[i];
    }

    fftw_execute(m_plan);
}

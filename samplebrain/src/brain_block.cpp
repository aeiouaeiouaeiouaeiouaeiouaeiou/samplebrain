#include "brain_block.h"

FFT *brain_block::m_fftw;

brain_block::brain_block(const sample &pcm) :
    m_pcm(pcm),
    m_fft(pcm.get_length()),
    m_mfcc(13)
{
    init_fft(m_pcm.get_length());

}

void brain_block::init_fft(u32 block_size)
{
    if (m_fftw == NULL || m_fftw->m_length!=block_size) {
        if (m_fftw == NULL) delete m_fftw;
        m_fftw = new FFT(block_size);
    }
}

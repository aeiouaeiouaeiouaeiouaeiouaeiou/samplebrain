/**
 * @file Mfcc.cpp
 *
 * Calculation of MFCC signal features.
 *
 * This file is part of the Aquila DSP library.
 * Aquila is free software, licensed under the MIT/X11 License. A copy of
 * the license is provided with the library in the LICENSE file.
 *
 * @package Aquila
 * @version 3.0.0-dev
 * @author Zbigniew Siciarz
 * @date 2007-2014
 * @license http://www.opensource.org/licenses/mit-license.php MIT
 * @since 3.0.0
 */

#include "mfcc.h"
#include "aquila/transform/Dct.h"
#include "aquila/filter/MelFilterBank.h"

namespace Aquila
{
    std::vector<double> Mfcc::calculate(SpectrumType spectrum,
                                        std::size_t numFeatures)
    {
        //auto spectrum = m_fft->fft(source);

        Aquila::MelFilterBank bank(m_sampleRate, m_inputSize);
        auto filterOutput = bank.applyAll(spectrum);

        Aquila::Dct dct;
        return dct.dct(filterOutput, numFeatures);
    }
}

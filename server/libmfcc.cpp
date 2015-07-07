/*
 * libmfcc.c - Code implementation for libMFCC
 * Copyright (c) 2010 Jeremy Sawruk
 *
 * This code is released under the MIT License.
 * For conditions of distribution and use, see the license in LICENSE
 */

#include <math.h>
#include "libmfcc.h"

/*
 * Computes the specified (mth) MFCC
 *
 * spectralData - array of doubles containing the results of FFT computation. This data is already assumed to be purely real
 * samplingRate - the rate that the original time-series data was sampled at (i.e 44100)
 * NumFilters - the number of filters to use in the computation. Recommended value = 48
 * binSize - the size of the spectralData array, usually a power of 2
 * m - The mth MFCC coefficient to compute
 *
 */
double GetCoefficient(double* spectralData, unsigned int samplingRate, unsigned int NumFilters, unsigned int binSize, unsigned int m)
{
    double result = 0.0f;
    double outerSum = 0.0f;
    double innerSum = 0.0f;
    unsigned int k, l;

    // 0 <= m < L
    if(m >= NumFilters)
    {
        // This represents an error condition - the specified coefficient is greater than or equal to the number of filters. The behavior in this case is undefined.
        return 0.0f;
    }

    result = NormalizationFactor(NumFilters, m);


    for(l = 1; l <= NumFilters; l++)
    {
        // Compute inner sum
        innerSum = 0.0f;
        for(k = 0; k < binSize - 1; k++)
        {
            innerSum += fabs(spectralData[k] * GetFilterParameter(samplingRate, binSize, k, l));
        }

        if(innerSum > 0.0f)
        {
            innerSum = log(innerSum); // The log of 0 is undefined, so don't use it
        }

        innerSum = innerSum * cos(((m * PI) / NumFilters) * (l - 0.5f));

        outerSum += innerSum;
    }

    result *= outerSum;

    return result;
}

/*
 * Computes the Normalization Factor (Equation 6)
 * Used for internal computation only - not to be called directly
 */
double NormalizationFactor(int NumFilters, int m)
{
    double normalizationFactor = 0.0f;

    if(m == 0)
    {
        normalizationFactor = sqrt(1.0f / NumFilters);
    }
    else
    {
        normalizationFactor = sqrt(2.0f / NumFilters);
    }

    return normalizationFactor;
}

/*
 * Compute the filter parameter for the specified frequency and filter bands (Eq. 2)
 * Used for internal computation only - not the be called directly
 */
double GetFilterParameter(unsigned int samplingRate, unsigned int binSize, unsigned int frequencyBand, unsigned int filterBand)
{
    double filterParameter = 0.0f;

    double boundary = (frequencyBand * samplingRate) / binSize;             // k * Fs / N
    double prevCenterFrequency = GetCenterFrequency(filterBand - 1);                // fc(l - 1) etc.
    double thisCenterFrequency = GetCenterFrequency(filterBand);
    double nextCenterFrequency = GetCenterFrequency(filterBand + 1);

    if(boundary >= 0 && boundary < prevCenterFrequency)
    {
        filterParameter = 0.0f;
    }
    else if(boundary >= prevCenterFrequency && boundary < thisCenterFrequency)
    {
        filterParameter = (boundary - prevCenterFrequency) / (thisCenterFrequency - prevCenterFrequency);
        filterParameter *= GetMagnitudeFactor(filterBand);
    }
    else if(boundary >= thisCenterFrequency && boundary < nextCenterFrequency)
    {
        filterParameter = (boundary - nextCenterFrequency) / (thisCenterFrequency - nextCenterFrequency);
        filterParameter *= GetMagnitudeFactor(filterBand);
    }
    else if(boundary >= nextCenterFrequency && boundary < samplingRate)
    {
        filterParameter = 0.0f;
    }

    return filterParameter;
}

/*
 * Compute the band-dependent magnitude factor for the given filter band (Eq. 3)
 * Used for internal computation only - not the be called directly
 */
double GetMagnitudeFactor(unsigned int filterBand)
{
    double magnitudeFactor = 0.0f;

    if(filterBand >= 1 && filterBand <= 14)
    {
        magnitudeFactor = 0.015;
    }
    else if(filterBand >= 15 && filterBand <= 48)
    {
        magnitudeFactor = 2.0f / (GetCenterFrequency(filterBand + 1) - GetCenterFrequency(filterBand -1));
    }

    return magnitudeFactor;
}

/*
 * Compute the center frequency (fc) of the specified filter band (l) (Eq. 4)
 * This where the mel-frequency scaling occurs. Filters are specified so that their
 * center frequencies are equally spaced on the mel scale
 * Used for internal computation only - not the be called directly
 */
double GetCenterFrequency(unsigned int filterBand)
{
    double centerFrequency = 0.0f;
    double exponent;

    if(filterBand == 0)
    {
        centerFrequency = 0;
    }
    else if(filterBand >= 1 && filterBand <= 14)
    {
        centerFrequency = (200.0f * filterBand) / 3.0f;
    }
    else
    {
        exponent = filterBand - 14.0f;
        centerFrequency = pow(1.0711703, exponent);
        centerFrequency *= 1073.4;
    }

    return centerFrequency;
}

/*  complex.h    CCMATH mathematics library source code.
 *
 *  Copyright (C)  2000   Daniel A. Atkinson    All rights reserved.
 *  This code may be redistributed under the terms of the GNU library
 *  public license (LGPL). ( See the lgpl.license file for details.)
 * ------------------------------------------------------------------------
 */
#ifndef FFT_H

#ifdef __cplusplus
extern "C"
{
#endif

    struct complex
    {
        double re;
        double im;
    };

    extern void fft2(struct complex *ff, int k, int j);
    extern void fft2_d(struct complex *a, int m, int n, int f);

#ifdef __cplusplus
}
#endif
#endif

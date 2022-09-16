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

    // Compute, in place, the radix-2 FFT of a complex input series.
    //  void fft2(Cpx *ft,int m,int inv)
    //     ft = pointer to input/output complex structure array
    //         ( dimension=2^m )
    //     m = dimension parameter ( series length = 2^m )
    //     inv = control flag, with:
    //             inv='d' -> direct Fourier transform
    //             inv!='d' -> inverse transform

    extern void fft2(struct complex *ff, int k, int j);

    // Compute a two-dimensional radix-2 FFT transformation.
    //     void fft2_d(Cpx *a,int m,int n,int f)
    //     a = pointer to complex input/output structure array
    //             ( dimension= 2^m * 2^n )
    //     m = first dimension parameter
    //     n = second dimension parameter
    //     f = control flag, with:
    //             f='d' -> direct Fourier transform
    //             f='i' -> inverse transform
    //     The input array contains complex matrix elements
    //     a[k,j] = a[k*2^m+j]  ,  with 0 <= k <= 2^m -1 and
    //                                 0 <= j <= 2^n -1 .
    //     The output array is
    //         at[r,s] = { Sum(k=0 to 2^m -1){ Sum(j=0 to 2^n -1)
    //                     a[k,j]*exp(-i*(w[r]*k+w[s]*k))} }/N
    //     with  N = 2^(m+n) , for the direct transform, and
    //     a[r,s] = { Sum(k=0 to 2^m -1){ Sum(j=0 to 2^n -1)
    //             at[k,j]*exp(i*(w[r]*k+w[s]*j))} }
    //     for the inverse transform.
extern void fft2_d(struct complex *a, int m, int n, int f);

#ifdef __cplusplus
}
#endif
#endif

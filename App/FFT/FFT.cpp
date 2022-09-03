// ======================================================================
// \title  FFT.cpp
// \author ThibFrgsGmz
// \brief  cpp file for FFT component implementation class
// ======================================================================

#include <math.h>
#include <App/FFT/FFT.hpp>
#include "Fw/Types/BasicTypes.hpp"

namespace App {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  FFT ::
    FFT(
        const char *const compName
    ) : FFTComponentBase(compName)
  {

  }

  void FFT ::
    init(
        const NATIVE_INT_TYPE queueDepth,
        const NATIVE_INT_TYPE instance
    )
  {
    FFTComponentBase::init(queueDepth, instance);
  }

  FFT ::
    ~FFT()
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  void FFT ::
    schedIn_handler(
        const NATIVE_INT_TYPE portNum,
        NATIVE_UINT_TYPE context
    )
  {
    if (m_enable) {
      F32 elapsed_fft_time;
      elapsed_fft_time = FFT::do_fft_bench(FFT::m_fft_power);
      tlmWrite_ELAPSED_TIME(elapsed_fft_time);
    }
  }

  // ----------------------------------------------------------------------
  // Command handler implementations
  // ----------------------------------------------------------------------

  void FFT ::
    ENABLE_cmdHandler(
        const FwOpcodeType opCode,
        const U32 cmdSeq,
        App::FFTEnabled enable
    )
  {
    m_enable = (enable == FFTEnabled::ENABLED);
    this->cmdResponse_out(opCode,cmdSeq,Fw::CmdResponse::OK);
  }

  void FFT ::
    UPDATE_POWER_cmdHandler(
        const FwOpcodeType opCode,
        const U32 cmdSeq,
        U32 power
    )
  {
    m_fft_power = power;
    this->cmdResponse_out(opCode,cmdSeq,Fw::CmdResponse::OK);
  }

  struct complex { F32 re; F32 im; };
  complex operator*(complex a, complex b) {
    complex r;
    r.re = a.re * b.re - a.im * b.im;
    r.im = a.re * b.im + b.re * a.im;
    return r;
  }

  void FFT ::fft2(struct complex *ft, int m, int inv)
  {
    int n, i, j, k, mm, mp;
    F32 s, t, ang, tpi = 6.283185307179586;
    struct complex u, w, *p, *q, *pf;
    n = 1; n <<= m; pf = ft + n - 1;
    for (j = 0, p = ft; p < pf; ++p) {
      q = ft + j;
      if (p < q) {
        t = p->re;
        p->re = q->re;
        q->re = t;
        t = p->im;
        p->im = q->im;
        q->im = t;
      }
      for (mm = n / 2; mm <= j; mm /= 2)
        j -= mm; j += mm;
    }
    if (inv == 'd') for (p = ft, s = 1. / n; p <= pf;) {
        p->re *= s; (p++)->im *= s;
    }
    for (i = mp = 1; i <= m; ++i) {
      mm = mp; mp *= 2; ang = tpi / mp; if (inv == 'd') ang = -ang;
      w.re = cos(ang); w.im = sin(ang);
      for (j = 0; j < n; j += mp) {
        p = ft + j;
        u.re = 1.; u.im = 0.;
        for (k = 0; k < mm; ++k, ++p) {
          q = p + mm;
          t = q->re*u.re - q->im*u.im;
          s = q->im*u.re + q->re*u.im;
          q->re = p->re - t; q->im = p->im - s;
          p->re += t; p->im += s;
          t = u.re*w.re - u.im*w.im;
          u.im = u.im*w.re + u.re*w.im; u.re = t;
        }
      }
    }
  }

  void FFT ::fft2_d(struct complex *a, int m, int n, int f)
  {
    register int md, nd, i, j; struct complex *p, *q;
    register struct complex *r, *s;
    md = 1 << m; nd = 1 << n;
    for (i = 0, p = a; i < md; ++i) {
          fft2(p, n, f); p += nd;
    }
    q = (struct complex *)calloc(sizeof(*q), md);
    for (i = 0, p = a - nd; i < nd; ++i) {
      for (r = q, s = p, j = 0; j < md; ++j) *r++ = *(s += nd);
      fft2(q, m, f);
      for (r = q, s = p++, j = 0; j < md; ++j) *(s += nd) = *r++;
    }
    free(q);
  }

  F32 FFT ::do_fft_bench(int size) {
    /* variable init */
    clock_t start;
    clock_t end;
    int dim = size;
    int dim_out = pow(2,size); //(2^dim)
    size_t i = 0;

    complex * a = (complex*)malloc(sizeof(complex)*dim_out*dim_out);
    complex * b = (complex*)malloc(sizeof(complex)*dim_out*dim_out);
    complex * ab= (complex*)malloc(sizeof(complex)*dim_out*dim_out);

    memset(a, 0, sizeof(complex)*dim_out*dim_out);
    memset(b, 0, sizeof(complex)*dim_out*dim_out);
    memset(ab, 0, sizeof(complex)*dim_out*dim_out);
    
    for (i = 0; i < dim_out*dim_out; i++) {
      a[i].re =  rand() % 255;
      b[i].re =  rand() % 255;
    }

    start = clock();

    fft2_d(a, dim, dim, 'n');
    fft2_d(b, dim, dim, 'n');

    for (int li = 0; li < dim_out; li++) {
      for (int col = 0; col < dim_out; col++) {
      ab[col + li * dim_out] = a[col + li * dim_out] * b[col + li * dim_out];
      }
    }

    fft2_d(ab, dim, dim, 'd');
    end = clock();

    float seconds = (float)(end - start) / CLOCKS_PER_SEC;

    free(a);
    free(b);
    free(ab);

    printf("Elapsed time = %f sec\n", seconds);
    return seconds;
  }

} // end namespace App

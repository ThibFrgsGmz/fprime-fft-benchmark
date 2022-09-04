// ======================================================================
// \title  FFT.cpp
// \author ThibFrgsGmz
// \brief  cpp file for FFT component implementation class
// ======================================================================

#include "fft.h"
#include <App/FFT/FFT.hpp>
#include <Fw/Logger/Logger.hpp>
#include "Fw/Types/BasicTypes.hpp"
#include <math.h>

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
      F32 fft_duration;
      fft_duration = FFT::do_fft_bench(FFT::m_fft_power);
      Fw::Logger::logMsg("Elapsed time = %f sec\n", fft_duration);
      tlmWrite_ELAPSED_TIME(fft_duration);
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

  complex operator*(complex a, complex b) {
    complex r;
    r.re = a.re * b.re - a.im * b.im;
    r.im = a.re * b.im + b.re * a.im;
    return r;
  }

  F32 FFT
    ::do_fft_bench(int size) {
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

    return seconds;
  }

} // end namespace App

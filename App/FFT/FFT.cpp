// ======================================================================
// \title  FFT.cpp
// \author ThibFrgsGmz
// \brief  cpp file for FFT component implementation class
// ======================================================================

#include "FFT.hpp"
#include "ccmath/fft.h"
#include <Fw/Types/BasicTypes.hpp>
#include <Fw/Logger/Logger.hpp>
#include <math.h>

namespace App {

// ----------------------------------------------------------------------
// Construction, initialization, and destruction
// ----------------------------------------------------------------------

FFT ::FFT(const char *const compName) : FFTComponentBase(compName) {
    random_lower_bound = 0;
    random_upper_bound = 255;
}

void FFT ::init(const NATIVE_INT_TYPE queueDepth, const NATIVE_INT_TYPE instance) {
    FFTComponentBase::init(queueDepth, instance);
}

FFT ::~FFT() {
}

// ----------------------------------------------------------------------
// Handler implementations for user-defined typed input ports
// ----------------------------------------------------------------------

void FFT ::schedIn_handler(const NATIVE_INT_TYPE portNum, NATIVE_UINT_TYPE context) {
    if (m_enable) {
        F32 fft_duration;
        fft_duration = FFT::run_bench(FFT::m_fft_power);
        Fw::Logger::logMsg("Elapsed time = %f sec\n", fft_duration);
        tlmWrite_ELAPSED_TIME(fft_duration);
    }
}

// ----------------------------------------------------------------------
// Command handler implementations
// ----------------------------------------------------------------------

void FFT ::ENABLE_cmdHandler(const FwOpcodeType opCode, const U32 cmdSeq, App::FFTEnabled enable) {
    m_enable = (enable == FFTEnabled::ENABLED);
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
}

void FFT ::UPDATE_POWER_cmdHandler(const FwOpcodeType opCode, const U32 cmdSeq, U32 power) {
    m_fft_power = power;
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
}

complex operator*(complex a, complex b) {
    complex r;
    r.re = a.re * b.re - a.im * b.im;
    r.im = a.re * b.im + b.re * a.im;
    return r;
}

F32 FFT ::run_bench(U32 dim) {
    U32 dim_out = 1 << dim;
    U32 dim_out_square = pow(dim_out, 2);

    complex *a = (complex *)calloc(dim_out_square, sizeof(complex));
    complex *b = (complex *)calloc(dim_out_square, sizeof(complex));
    complex *ab = (complex *)calloc(dim_out_square, sizeof(complex));

    std::uniform_real_distribution<double> unif(random_lower_bound, random_upper_bound);

    for (U32 i = 0; i < dim_out_square; i++) {
        a[i].re = unif(re);
        b[i].re = unif(re);
    }

    start_bench = clock();

    fft2_d(a, dim, dim, 'd');
    fft2_d(b, dim, dim, 'd');

    for (U32 row = 0; row < dim_out; row++) {
        for (U32 column = 0; column < dim_out; column++) {
            ab[column + row * dim_out] = a[column + row * dim_out] * b[column + row * dim_out];
        }
    }

    fft2_d(ab, dim, dim, 'd');

    end_bench = clock();

    fft_duration = (F32)(end_bench - start_bench) / CLOCKS_PER_SEC;

    free(a);
    free(b);
    free(ab);

    return fft_duration;
}

} // end namespace App

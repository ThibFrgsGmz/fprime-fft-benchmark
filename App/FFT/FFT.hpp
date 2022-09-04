// ======================================================================
// \title  FFT.hpp
// \author ThibFrgsGmz
// \brief  hpp file for FFT component implementation class
// ======================================================================

#ifndef FFT_HPP
#define FFT_HPP

#include "App/FFT/FFTComponentAc.hpp"

namespace App {

  class FFT :
    public FFTComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object FFT
      //!
      FFT(
          const char *const compName /*!< The component name*/
      );

      //! Initialize object FFT
      //!
      void init(
          const NATIVE_INT_TYPE queueDepth, /*!< The queue depth*/
          const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
      );

      //! Destroy object FFT
      //!
      ~FFT();

    PRIVATE:

      // ----------------------------------------------------------------------
      // Handler implementations for user-defined typed input ports
      // ----------------------------------------------------------------------

      //! Handler implementation for schedIn
      //!
      void schedIn_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          NATIVE_UINT_TYPE context /*!< 
      The call order
      */
      );

    PRIVATE:

      U32 m_fft_power;
      bool m_enable;

      // ----------------------------------------------------------------------
      // Command handler implementations
      // ----------------------------------------------------------------------

      //! Implementation for ENABLE command handler
      //! A command to enable or disable system resource telemetry
      void ENABLE_cmdHandler(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq, /*!< The command sequence number*/
          App::FFTEnabled enable /*!< 
          Whether or not system resource telemetry is enabled
          */
      );

      //! Implementation for UPDATE_POWER command handler
      //! A command to enable or disable system resource telemetry
      void UPDATE_POWER_cmdHandler(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq, /*!< The command sequence number*/
          U32 power /*!< 
          Power applied to the FFT
          */
      );

      F32 run_bench(int size);

    };

} // end namespace App

#endif

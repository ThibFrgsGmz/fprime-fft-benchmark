module App {

  enum FFTEnabled {
    DISABLED = 0
    ENABLED = 1
  }

  active component FFT {

    @ Run port
    # guarded input port run: [1] Svc.Sched
    @ Schedule in port
    async input port schedIn: Svc.Sched
    
    # ----------------------------------------------------------------------
    # Special ports
    # ----------------------------------------------------------------------

    @ Time get port
    time get port Time

    @ Command registration port
    command reg port CmdReg

    @ Command received port
    command recv port CmdDisp

    @ Command response port
    command resp port CmdStatus

    @ Text event port
    text event port LogText

    @ Event port
    event port Log

    @ Telemetry port
    telemetry port Tlm

    @ A command to enable or disable system resource telemetry
    guarded command ENABLE(
                            enable: FFTEnabled @< Whether or not system resource telemetry is enabled
                          ) \
      opcode 0

    @ A command to enable or disable system resource telemetry
    guarded command UPDATE_POWER(
                            power: U32 @< Power applied to the FFT
                          ) \
      opcode 1
    
    @ Elapsed time for the FFT 
    telemetry ELAPSED_TIME: F32 id 0 format "{.6f} s"

  }
}

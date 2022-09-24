module App {

  enum FFTEnabled {
    DISABLED = 0
    ENABLED = 1
  }

  active component FFT {

    async input port schedIn: Svc.Sched
    
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
    command reg port CmdReg
    command recv port CmdDisp
    command resp port CmdStatus

    @ Elapsed time for the FFT 
    telemetry ELAPSED_TIME: F32 id 0 format "{.6f} s"
    time get port Time
    telemetry port Tlm
  }
}

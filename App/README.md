# `App` deployment

## Component(s)

### `FFT` (Fast Fourier Transform)

The `FFT` component is the main component of the benchmark.

It integrates the implementation of the FFT from the mathematical library `CCMATH` of Daniel A. Atkinson and under LGPL license.

See [here](./FFT/docs/sdd.md) for more details.

`FFT` is an active component so that we can easily assign an instance to a specific CPU.

This example deployment has two instances of `FFT` in its topology. If the user has a hardware platform with more cores, he is asked to instantiate as many FFT components as he has cores.

In `topology.fpp` you have to:

- instantiate the component

```
    # --------------------------------
    # Instances used in the topology |
    # --------------------------------
    ...
    instance fftx
```

- Connect the input of the component to an output port of a `RateGroup` component

```
# rateGroup1Comp.RateGroupMemberOut[y] -> fftx.schedIn
```

In `instances.fpp` you have to configure the component instance:

```
  instance fftx: App.FFT base id 0xF00 \
  queue size 20 \
  stack size Default.stackSize \
  priority 101 \
  cpu x
```


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

## In practice

By default, all FFT instances in the topology are not enabled, i.e., they do not run any FFT algorithm.

To run the benchmark with high CPU load and power consumption, the user has two commands per FFT instance.

First it shall configure the dimension fo the FFT, the value determine the size of the image on which the FFT is run.
For example, imagine you enter a dimension of 5 for the FFT instance ff1. fft1 will process an FFT on a square image of 2^5 x 2^5 = 32x32 = 1024 pixels.
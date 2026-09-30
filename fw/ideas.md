# Ideas

- Slew rate limiter so that we can control the delta of NM per loop
- Asymmetric rates using exponential function
- Backlash handling
- Oversampling using STM32 (L4, G4 and H7 chips)
- Median of 3 instead of (or before) the mean in `read_average_voltage()`. Rn the average samples are microseconds apart a spike is almost certainly noise and could trip
  - w/ EMA. Median for spike rejection then fed into EMA for the remaining.
  - It lwky delays the 100ms implausibility window, so keep in mind when implementing it that it needs to be fast enough to still trip. Mayb run implausibility early on just the median and if passed then feed into EMA for the torque calc.
  - Uses a median of sub-group medians over the batch instead of one flat average if DMA implemented.
- Drop the ADC clock to PCLK2 / 4. Mbed's `AnalogIn` uses PCLK2 / 2, and PCLK2 is 90 MHz on
  the VCU so ADC runs 45 MHz. F446 ADC rated 36 MHz, so probably double read same data if not.
- Fixed update rate for `update_state()`. Torque only leaves the board at 20 Hz, so the
  free-running while loop (probably ~10 kHz) is throwing away almost every iteration. That
  extra compute isn't needed at all.
  - The bottleneck is ADC. The float math in `update_state()` is a few
    dozen operations at 180 MHz. loop period is 16 blocking
    conversions (`SAMPLES_PER_READ` = 8 x 2 channels), each one 15 sampling + 12 conversion
    cycles = 27 ADC cycles at 22.5 MHz = ~1.2 us, 19 us of conversion per loop, and 
    Mbed's `read_voltage()` reconfigures the channel, starts the ADC and polls
    for completion on every single sample. Spends loop waiting on EOC
  - loop rate is an accident of ADC + HAL timing. The CAN thread runs
    at `osPriorityAboveNormal` and preempts, and the 2 Hz `printf` blocks for a long time.
  - EMA's time constant is set by the sample
    period, so with a variable dt the frequency and lag varies. Same for a median window changes with the loop rate. Max rate and dt becomes a constant and alpha becomes cutoff in hz and lag is what we determine. it no longer depends on CPU.
  - But we need a rate that will still catches an implausibility fast enough for T.4.2.5 and return extra time
  - Use the spare compute to sample constantly while no task is running (DMA oversampling
    into a buffer so a large batch of samples accumulates at a steady rate and is ready
    whenever `update_state()` runs). DMA also gets rid of the per-sample HAL overhead


# In-Helmet Audio — LV Onboarding (Hadi Mirza)

Driver radio audio: speakers + mic in the helmet, a breakaway connector to the
car, and a small car-side board that converts I2S (to/from telemetry) into
analog speaker drive and mic input.

- Schematic: `in-helmet-audio.kicad_sch` (PDF: `in-helmet-audio.pdf`)
- The helmet/harness parts (J3, J4, LS1, LS2, MK1) are on the schematic in the
  dashed "OFF-BOARD" box. They're set to *exclude from board*, so they appear in
  the BOM but don't go on the PCB.

## System overview

```
 telemetry MCU / radio            car-side board (this schematic)                  cockpit        helmet
 ─────────────────────   J1    ┌───────────────────────────────────┐   J2   harness    J3 ⇄ J4   pigtail
  I2S (BCLK/WCLK/DIN/DOUT) ───▶│ TLV320AIC3100 codec                │──────────────▶ magnetic ──▶ LS1+LS2 (series)
  I2C (config), RESET     ───▶│  class-D SPKP/SPKM → FB+1nF filter │   SPK±, MIC±,   breakaway    MK1 on chin bar
  +5V, GND                ───▶│  MICBIAS + PGA ← MIC±              │   shield, DET
                               └───────────────────────────────────┘
```

All electronics stay in the car. The helmet holds only passive transducers and
wire. That keeps the helmet light, means nothing in it needs power, and puts
only robust analog signals through the breakaway. Digital I2S/PDM clocks at
1–3 MHz over a magnetic pogo connector and 1–2 m of cable would be fragile.

## Components

| Ref | Part | Why |
|---|---|---|
| LS1, LS2 | **Same Sky CMS-28528N-L152** — Ø28 × 5.2 mm, 8 Ω, 2 W, 96 dB @ 1 W/0.1 m, f₀ 750 Hz, PET cone, wire leads | Thin enough to sit in a helmet ear pocket under the comfort liner |
| MK1 | **Same Sky CMR-2747PB-A** — noise-cancelling electret, Ø6 × 2.7 mm, −47 dB, 2 V bias, R_L 2.2 kΩ, 56 dB SNR | Close-talk, rejects wind and car noise, tiny |
| J3 (car) | **Mill-Max 878-22-006-00-011101** — Maxnetic 6-pin spring-pin, solder cup, 4 mm pitch (DigiKey 54-878-22-006-00-011101-ND, 57 in stock) | Magnetic, no latch, breaks away |
| J4 (helmet) | **Mill-Max 878-20-006-00-012000** — mating 6-pin target pad, solder cup (DigiKey, 76 in stock) | Flat targets on the side that gets knocked around |
| U1 | **TI TLV320AIC3100IRHBT** — I2S/I2C codec, mic PGA + MICBIAS + ADC, 1.3 W mono class-D (DigiKey 296-39265-1-ND, ~2.7k in stock; the IRHBR reel had only 3) | One chip for both directions |
| U2/U3 | AP2112K-3.3 / AP2112K-1.8 LDOs | 3.3 V AVDD/IOVDD/HPVDD, 1.8 V DVDD |
| D1 | TI TPD4E05U06DQAR 4-ch ESD | Protects the lines that leave the box toward the driver |
| J1 / J2 | Molex Micro-Fit 3.0 2×6 / 1×6 | Board-to-harness |

### Does the speaker need a big driver?

A bigger driver moves more air per mm of excursion. That buys more low-frequency
output and efficiency, a lower resonant frequency, and less distortion at a
given SPL. The example CSS-66668N (66 mm) is built for music bass. We don't need
that:

- **Bandwidth.** Radio voice is roughly 300 Hz–3.4 kHz, and intelligibility
  lives at 1–4 kHz. The 28 mm driver's 750 Hz f₀ rolls off the lows, which
  doubles as a free high-pass against rumble.
- **Distance.** The driver is about 1–2 cm from the ear in a semi-sealed
  pocket, not 10 cm away in free air. Near-field gain plus cavity loading give
  far more SPL than the 96 dB @ 1 W/0.1 m rating. We'll run well under 1 W and
  must **limit volume in firmware** to protect hearing (drivers usually also
  wear earplugs).
- **Packaging.** Helmet ear pockets are about 40–50 mm across and under 10 mm
  deep once the liner is in. A 5.2 mm-thick, 28 mm driver fits; a 66 mm one
  does not.

The two 8 Ω speakers are wired **in series (16 Ω)** across the codec's BTL
class-D output. That gives about 0.7 W max at 5 V, which is plenty, and lets
both ears share one pair of wires.

### Microphone challenges

- **Wind noise and turbulence** at the visor gap, plus tyre, motor, and inverter
  whine. Ambient noise in the helmet can exceed 90–100 dBA.
- **Breath pops and moisture** (sweat, humidity, condensation).
- **Vibration** and helmet movement.
- **EMI**: the inverter, the HV harness, and the team radio transmitter right
  next to the cable.

So the mic is a **noise-cancelling (pressure-gradient) electret**. Both faces
are open, so sound that hits both sides about equally (far-field noise) cancels.
The speaker's mouth, about 1 cm away, produces a large near-field pressure
gradient and comes through. It mounts on the inside of the chin bar with a foam
windscreen. On the board:

- R5 (2.2 kΩ) is the datasheet load.
- MICBIAS is programmed to 2.0 V, the mic's rated Vs.
- The mic is read pseudo-differentially (MIC1LP/MIC1LM), with the return taken
  to ground at a single point (R6).
- C20 is a 100 pF RF shunt.
- The codec's ADC high-pass should be enabled at about 150 Hz to cut wind
  rumble.

### Breakaway connector

Requirement: the driver must get out fast without unlatching anything.

- **Mill-Max Maxnetic** magnetic pogo connectors have no latch. They hold by
  polarized neodymium magnets, self-align, can't mate reversed (magnet
  polarity), and pull apart under load without damage. Rated for 1M cycles and
  −55 to +80 °C, with gold contacts.
- **Placement.** Mount J3 (car side, spring pins) to the chassis or headrest so
  that a pull in *any* exit direction separates the magnets. If J3 hangs loose,
  the driver ends up dragging the harness instead. The helmet keeps a ~30 cm
  pigtail ending in J4 (flat targets, which survive being dropped).
- **Pinout** (J2 = J3 = J4):

  | Pin | Signal |
  |---|---|
  | 1 | SPK+ |
  | 2 | SPK− |
  | 3 | MIC+ (bias) |
  | 4 | MIC− |
  | 5 | shield/GND |
  | 6 | HELMET_DET |

  In the helmet, J4 pin 6 is strapped to pin 5, so the codec's GPIO1 reads low
  when the helmet is connected.
- **Cable.** 4-conductor + drain, shielded, with the mic pair twisted. The
  shield is grounded at the board end only.

## Open questions / next steps

- **Breakaway force.** Mill-Max doesn't publish it. Measure the pull-off force,
  and check retention under vibration and head turns. Audio crackle on a bump is
  annoying but not dangerous.
- **Industry alternative.** Racing and aviation helmets often use Nexus
  TP-120/TJ-120 friction plugs. Compare cost and robustness.
- **Telemetry interface.** Confirm what the telemetry board provides (I2S
  slave/master, MCLK or not, 5 V available).
- **Firmware.** Configure the codec PLL, MICBIAS = 2.0 V, ADC HPF, class-D gain,
  and a volume ceiling.
- **ERC.** Shows one known false positive: the node between the two series
  speakers (`LS_SERIES`) has only "input" pins (KiCad's speaker symbol), so
  nothing "drives" it.

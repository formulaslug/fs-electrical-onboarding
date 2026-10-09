# Electrical LV onboarding research project

### How a Microphone Works

#### Setup
*same as speaker*

#### Process
*literally the inverse of a speaker*
1. Sound wave hits diaphragm (basically the cone)
    - connected to electromagnet
2. Electromagnet wiggles around
    - with the permanent magnet around it, it makes an electrical signal

--- 

### Key Terms (Vocabulary)
* **Diaphragm:** Basically the cone from a speaker

---

#### Challenges
1. Size constraints?
2. Lots of background noise (has to be cut out digitally or physically)
3. Gotta be sweat proof / moisture proof
4. Vibration proofing also (helmet shakes = mic shakes = bad audio)

#### Solutions
1. Has to be small enough to not smush against drivers face, but be close to the mouth to properly capture the sound (has to be )
2. Maybe have the sensitivity of the mic cut out all the bass (I expect alot of this from the wind and engine noise). Also the mic can be like one directional, only pointed at the drivers mouth
    - look for native dual port noise cancellation. how it works
        1. sound is let in through 2 holes
        2. the same sound entering from both holes cancel each other out when they meet on the diaphragm (pressure is equalized)
        3. since driver's voice comes in from one side only, it doesnt get canceled out
3. Cover it in Arcteryx jacket GORETEX material and call it a day
4. Surround the microphone in foam (not held up by anything but foam)

---

### Objective
1. Find a mic that fits the following criteria
    - One directional
    - Doesnt sense low enough frequencies (cut off ~200 Hz or something)
    - Small enough to not squish against driver's mouth and hear things properly (maybe 1-3cm away, around 1cm size max)
    - Records audio without clipping (~-45dB sensitivity)

### Candidates
1. TM141055, https://www.digikey.com/en/products/detail/top-shelf-acoustics-llc/TM141055/18666285
    - Pros:
        1. Unidirectional
        2. Good sensitivity (-42 dB)
    - Cons:
        1. Records low frequencies (50hz)
        2. kinda big (16mm diameter, 5mm height(height is pretty good))

2. TM141066, https://www.digikey.com/en/products/detail/top-shelf-acoustics-llc/TM141066/18666275
    - Pros:
        1. Unidirectional
        2. Good sensitivity (same as above)
        3. Very small (3.6mm height + 6mm diameter)
        4. Kinda cheap (1.99 per)
    - Cons:
        1. Records low freq like before


3. CMR-2747PB-A, https://www.digikey.com/es/products/detail/same-sky-formerly-cui-devices/CMR-2747PB-A/1869991
    - Pros:
        1. Unidirectional
        2. Records okay frequencies (100hz-20kHz)
        3. Good sensitivity (-47dB)
        4. Very small (6mm dia + 2.9mm height)
        5. Noise cancellation
    - Cons:
        1. slightly more expensive ($2.69)


4. FB-BW-30335-000, https://www.mouser.com/en/ProductDetail/Knowles/FB-BW-30335-000?qs=z%252BkirVhXFF5DOdKnwaqnmA%3D%3D
    - Pros:
        1. Noise cancellation
        2. Very good sensitivity (-59dB)
    - Cons:
        1. Expensive as frick boii ($70.17)
        2. Big as frick boii (237mm long)

5. CMR-4015-44-SP, https://www.mouser.com/en/ProductDetail/Same-Sky/CMR-4015-44-SP?qs=By6Nw2ByBD2qCg%252B7IBmoGA%3D%3D
    - Pros:
        1. Noise cancellation
        2. Decent sensitivity (-44dB)
        3. Small (4mm dia + 1.5mm height)
        4. Decent frequency (100hz-->10kHz)
    - Cons:
        1. slightly more expensive compared to some ($2.35)

---

## Final Verdict
### **CMR-4015-44-SP**
#### Why:
1. Noise cancellation
2. Decent sensitivity
3. Small(est)
4. Decent frequency
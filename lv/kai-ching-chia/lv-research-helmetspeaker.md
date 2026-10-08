# Electrical LV onboarding research project

### How a Speaker Works

#### Setup
1. Permanent magnet in center  
2. Electromagnet around it   
3. Wire connecting to electromagnet  
4. Cone attach to electromagnet  
5. Dust cap to cover inner workings (center of cone)  
   * Cone is usually squishy now (membrane)

#### Process
1. Electric signal thru wire  
   * This signal is based on what audio u wanna play  
2. Since electromagnet you can control electromagnet poles & strength with electricity, use that to move the magnet  
3. Magnet moves the cone, cone pushes air  
   * Im assuming that big cone means big air pushed  
   * Air push = sound wave  
4. Magnet moves / second is the hz

---

### Key Terms (Vocabulary)
* **Driver:** Actual component that converts signal --> sound
* **Voice coil:** The electromagnet
* **Impedance:** Measured in ohms, is the resistance for your speaker. less res --> more amplified (audio quality can degrade)
* **RMS (root mean square):** How much power a speaker can take in a day
* **Peak:** Max burst of power a speaker can handle 
* **Sensitivity:** Efficiency rating of speaker, usually in db output (from 1m away) given 1 watt of energy
* **Clipping:** When amplifier pushed past max capacity
* **Amplifier:** Amplifies bluetooth connection into actual electrical signals
* **Self resonance:** 

---

### Component Example: CSS-66668N
* **Power:** 3-4 Watts
* **Dimensions:** 66.00 mm x 66.00 mm
* **Height:** 29.00 mm
* **Type:** General Purpose
* **Frequency Range:** 160 Hz -> 15 kHz

#### Pros
1. Louder  
2. Higher range of sounds

#### Cons
1. Very large (will squish ears)  
   * Friction, heat, and pain

---

### Questions & Answers

#### Questions
1. What does general purpose mean? What other purposes are there besides from playing sound?
2. Why is this speaker bigger than the other ones?
3. What happens when u get a smaller speaker like is it more efficient?
4. What is considered "too big" of a speaker?

#### Answers
1. Some other purposes could be: 
   * **a. Waterproofing / weather proofing:** Gotta survive lots of dirt and dust. Use something like rubber seals. (Might have to look for something with this, cus imagine if the driver sweats hella).
   * **b. Temperature proofing:** CSS-66668N caps out at 55C (131F). Other speakers can cap out at liek 105C.
   * **c. Micro speaker:** Fit into small things like phones / earbuds.
   * **d. Medical grade audio:** Super precise frequency needed. Used for like machinery (idk maybe zap a patient with it).
2. Bigger surface area = more air to push, better bass. Better bass makes audio sound cleaner (Does NOT cover background noise i think)
3. Less weight, much easier packaging. 
4. Diameter ranges from 35 --> 45mm. Thickness ranges from 6 --> 12mm
---

### Challenges & Solutions

#### Challenges
1. **Vibration:** Might distort audio? Speaker might come loose or something.
2. **Very Noisy (wind and stuff hitting car):** Hard to hear whats being played in the speaker. I think all the low freq played by speaker will be hella unhearable because the speaker probably needs to be loud enough because it can't seal.

#### Solutions That I Can Think Of
1. Vibration not doing anything lol
2. Louder speaker to overpower the noise. 
   - OR  use an ear molded earbud like the F1 drivers (no cus too expensive and not worth it)

### Objective
1. Find a speaker that fits the following criteria
   - Slim enough to not smush driver's ears (6-8mm)
   - Able to hear comms well (300hz -> 4,000 hz cus human speak thru that range)
   - Plays the audio loud enough to overpower the background noise (2-3W and ~100 db at 100mm range)
   - Cheapest if possible (might have to sacrifice price)
   - Sends sound in one direction (to ears not into helmet and others)

### Candidates:
1. HPD-50N25PR00-32, https://www.digikey.com/en/products/detail/peerless-by-tymphany/HPD-50N25PR00-32/6211129
   - Pros: 
      1. Sensitivity is decent (78.4DB)
      2. lots of frequencies can be played (60 --> 20kHz)
   - Cons:
      1. Big as hell (50mm)
      2. Thick too (10mm thickness)
      3. Lower power ceiling (10 mW)

2. SP-3605, https://www.digikey.com/en/products/detail/soberton-inc/SP-3605/6562949?s=N4IgTCBcDaICwGYEFoCMqCsAGZA5AIiALoC%2BQA
   - Pros:
      1. 300 --> 5kHz, perfectly ranged for voice
      2. Very small (36mm dia + 5mm height)
   - Cons: 
      1. 1W power, 1.5 peak (kinda low)

3. SP-1511S-1, https://www.digikey.com/en/products/detail/soberton-inc/SP-1511S-1/6099099
   - Pros:
      1. 400 --> 5kHz, pretty good for voice
      2. extremely small (15x11mm, 3.5mm height)
   - Cons: 
      1. low volume (83 db)
      2. low power, 800mW max

4. CMS-3652-28SP, https://www.mouser.com/en/ProductDetail/Same-Sky/CMS-3652-28SP?qs=eG9znyypUbuM3kNcIYHSjg%3D%3D
   - Pros: 
      1. small and flat (36mm diameter with 5.2mm height)
      2. Good power  (2W)
      3. Loud max too (100 dB)
      4. $1.87 per (cheap cheap)
   Cons:
      1. 550 hZ resonance frequency, which is slightly high (does it even matter cus do voices get that low)

5. SP-4005, https://www.digikey.com/en/products/detail/soberton-inc/SP-4005/6562950
   - Pros: 
      1. kinda small and pretty flat (40mm dia + 5.5mm height)
      2. Good power peak (2W)
      3. Loud max too (92 dB)
      4. 300 --> 8kHz (decent range)
   - Cons: 
      1. 550Hz resonance



### Final Verdict:
### **CMS-3652-28SP**
#### Why:
1. Cheap
2. Very small
3. Good power & volume
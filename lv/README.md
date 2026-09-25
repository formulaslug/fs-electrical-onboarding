**Welcome to Formula Slug LV Onboarding**

In order to get to know you and your passions better, we are asking you to complete
an open ended racecar-related project in one of a few formats. Our goal is not
to evaluate any of your skills, but rather to learn about how you approach difficult
and uncertian things.

For the purposes of whichever LV project you choose to do, **I (Luca) am available to help you!**
(and would appreciate getting to know you better)
I will be in BE-49 (or sometimes Jacks Lounge) at the times published in the electrical leads
office hours calendar, and you can always shoot me a slack message.

# What does LV do?
LV team designs all the PCBs and electrical wiring on the car. There's lots of
interesting safety features which are rules required to be implemented in hardware,
and we also try to pack more and more sensors onto the car each year.

As part of LV, you should expect to face challenges like:
- Design a circuit to detect a high-current output from the battery at the same time
as high brake pressure (see: BSPD)
- Design a circuit to measure small resistance changes of a circuit in a high-noise
enviornment (see: Strain Gauges)
- Select parts (sheathing, wire, crimps) with which to wire the car
- Debug startup transient conditions causing fault lights to flash when the car
is turned on
- Layout components on a PCB to obey mechanical, thermal, and safety constraints
- Source and implement sensors
- Debug communication busses on the car like CAN, analog signals, Serial, an PWM

You can find exmaples of the work LV has done all over the car, as well as in
the [schematics repository](https://github.com/formulaslug/fs-4-schematics). You
can also see some awesome sensor data collected on LV PCBs in our [grafana
dashboard](https://graf.telemetry.formulaslug.com/d/lyffkrd/library-dashboard?orgId=1&from=1970-01-01T00:00:00.011Z&to=1970-01-01T00:04:08.856Z&timezone=utc&var-srcfile=FS-4%2Fttt%2Fcandump-2026-06-11_155420.parquet).


# Project Options
Reminder: These are big bites, we know that most poeple can't produce a car-ready
outcome for any of these... that's okay :). We just want to see how you'll go at
it. Aim to spend less than 5 hours on these, and try to involve as much of your
own thinking as possible. Your personal effort will be noticed. Chose one of these
projects, create a branch of this repository, and create a subfolder of /lv containing
your work/research. You can also propose literally anything else you'd like to do
as an onboarding project.

> [!CAUTION]
> **Don't get overwhelmed. Come talk to me. I want to help you. This is supposed to be hard. You're not supposed to do a good job.**

## Air pressure / temperature / humidity
Our racecar has two main applications for aerometric sensors: monitoring the
cooling of the battery, and validating simulations of the aerodynamic elements
on the car. Do some research to determine what parameters (accuracy, resolution,
range) are needed for these applications and source a sensor (on digikey or mouser).
You can also describe how you'd make your own sensor (or sensor array) for this applciation
(and I'd love to hear it).

One example of such a sensor is the [BMP180](https://www.digikey.com/en/products/detail/bosch-sensortec/BMP180/2688259).
It's a MEMS (micro electro mechanical system) which measures pressure. It has great software
support because lots of Arduino modules use it, but it's no longer manufactured, and has
decent resolution, but since it communicates with I2C and has no address pins (inputs which allow I2C address configuration), it would be
difficult to use several of them together with one microcontroller.

Try to find a sensor which has at least the resolution of the BMP180, but has a communication
or output interface which allows it to be banked with several others on the same PCB. I
recommend reading briefly about common sensor output interfaces (analog, I2C, SPI, oneWire),
so you can understand which are easiest to use with multiple of the same sensor.

Identify some key parameters, and compile your questions/thoughts, and then **check in with me.**

## FPC suspension strain gauge
We order our PCBs from [JLC](https://jlcpcb.com). JLC can also make something called
an [FPC](https://jlcpcb.com/pcb-fabrication/flexible-pcb). Read about how [strain gauges](https://en.wikipedia.org/wiki/Strain_gauge) 
work, do some research about how other FSAE teams have
implemented strain gauges on their suspension members, and attempt to design your own
strain gauge to be manufactured as an FPC. I have not seen other teams do this before, but
it has some benefits and drawbacks... try to find those. 

Once you've put some thought into it and have an idea of how these things work, I want you to
do a teeny bit of math. Use an online calculator, relevant equations and constants, or the
calculator built into Kicad to compute the necessary length of minimum width copper trace ([here are jlc's minimums](https://jlcpcb.com/capabilities/flex-pcb-capabilities))
needed to equal 350 Ohm's of resistance. Take this a step farther, and determine the size of
rectangle needed to fit those traces according to JLC's published minimum trace width and
trace clearance (width between traces).

At this point or if you get stuck, **come check in with me.**

This project will be a PCB, so
instead of creating a blank folder with markdown or text files documenting your research,
create a copy of the kicad template folder (see below). You can still include any research
as text files. This is one project we are very excited about as a team, and which will make
a big impact on DAQ (Data Aquisition).

## Design a BSPD circuit
Every FSAE EV car is required to have a device called the "Brake system plausibility device".
Read about it in EV8.7 of the [2027 rules](https://fsaeonline.com/cdsweb/gen/DownloadDocument.aspx?DocumentID=9574fa97-c13e-4b90-9c75-044e30348cab).
We use the following sensors for this device, but you can choose others for the purpose of this project if you prefer:
- [Brake Pressure](https://www.summitracing.com/parts/aag-s0050?srsltid=AU7gw4WvwmFzL4ESdIDoUFAQyi38mjfxpO6NWv7JNG3hZhB_v7D9QLCm)
- [Current Sensor](https://www.lem.com/sites/default/files/products_datasheets/hass-50_600-s-v22.pdf)
This project will be a schematic, so instead of creating a blank folder with markdown or 
text files documenting your research, create a copy of the kicad template folder 
(see below). You can still include any research as text files.

Hint: You'll need to use Op-Amps to compare and scale voltages.

You do not need to start immediately with Kicad. It can be a bit much. Start by creating a
schematic for an Op-Amp based comparator (google that). Capture it somehow (on paper, in Kicad, whatever).
**Then come and check in with me to talk it through.**

I expect many of you will be overwhelmed trying to figure out how op-amps work. Find some resources (a video, article, etc),
and as you hear terms you do not understand, work your way backwards. You can learn much of the fundamentals of
~2 entire classes if you are intellectually responsible in teaching yourself this way. If you feel like giving up, come
find me.

## In-Helmet Audio
We want to add radio based driver communications to our telemetry system. This project
specifically relates to the speakers and microphone in the drivers (motorcycle) helmet,
and perhaps the driver circuitry to convert a convenient digital signal to and from the
interface to the microphone/speakers. Find speakers and microphone(s) sourceable on
digikey and propose how they can be packaged into the helmet without compromising ergonomics.
Think about how this system can connect to wiring on the car with a connector
that is both robust and breakaway--that is, the driver needs to be able to get out of the car
quickly in an emergency and won't have time to unlatch any extra electrical connections.

[Here's](https://www.digikey.com/en/products/detail/same-sky-formerly-cui-devices/CSS-66668N/6145945) 
an example of the type of speaker driver that would be in a pair of headphones.
This particular one is very large. Determine if a large driver is necessary in this application,
or rather what advantage a larger driver has, and find one which is appropriate. Similarly,
think about the challenges a microphone in this application faces, and try to find one which
is suitable.

As you select components, remember to focus on both their electrical/audio performance,
and their ergonomics/dimensions as they relate to this application. **Find me when you source
at least 2/3 components (microphone, speaker, connector).**

# General Notes

- Clone this repository recursively (`git clone --recursive`). If you didn't, be
  sure to initialize the submodule: `git submodule init` _and_ `git submodule
update`

# Kicad Projects

## Creating a project

1. Install our Template Project to your local computer.
   - Kicad requires templates to be installed locally, but our template is
     stored in the `template` folder in this repo, so you'll need to copy the
     `template` folder to where Kicad expects it. To see where that is, press
     Preferences -> Configure Paths, and look for the value of
     `KICAD_USER_TEMPLATE_DIR`. Copy the `template` folder there.
2. Create a new branch _from main_. Name your branch in-kebab-case
3. Create a new Kicad project from template. Under "User Templates" you should
   now see our Formula Slug template listed! Navigate to `fs-5-schematics` in
   the dialog and name your project the same as your branch name
   (in-kebab-case). This should create a new folder for your project inside of
   `fs-5-schematics`.
5. In the Schematic Editor, open File -> Schematic Setup -> Text Variables, and
   fill in the info for your board.
6. Create an initial commit and get to work!

## LV Standards

https://docs.google.com/document/d/1JF8Ld86JzdSsicxHTWAqBsUBFZuK-cVn7AItZKhkslQ/edit?usp=sharing


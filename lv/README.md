**Welcome to Formula Slug LV Onboarding**

In order to get to know you and your passions better, we are asking you to complete
an open ended racecar-related project in one of a few formats. Our goal is not
to evaluate any of your skills, but rather to learn about how you approach difficult
and uncertian things.

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
own thinking as possible. Your personal effort will be noticed.

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


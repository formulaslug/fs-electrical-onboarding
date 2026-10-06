Formula Slug Firmware Onboarding
===
Have you ever wondered how information gets sent all the way across the car without 
getting messed up? Have you ever wanted to see the code you write have physical
meaning and actions? Well, firmware deals with all aspects of those questions and
more! Firmware is the very interaction point between hardware on boards and software
that we write.

# Onboarding Project

The project to get onboarded will consist of three parts, each with a necessary goal
for the work you'll be doing in the future.

Part 1: Learning the basics of GitHub, MbedOS, and reading KiCad schematics.

Part 2: Learning CAN communication, data representation, and testing on the car.

Part 3: Learning and researching how to work with HAL commands rather than Mbed.

The actual job you're assigned to complete is to write a basic version of the VCU.
The VCU controls the vehicle's movement and checks for faults surrounding it. Your
task is to find the pedal's output, use it to calculate a torque on the motor to
spin it, then send that value over CAN so that the motor ACTUALLY spins. And, yes,
that means you'll get to properly spin the real motor on the car at the end of
part 2. After all of this, you'll research ways to implement your Mbed approach into
HAL commands, which are simpler and require less time and cycles to do tasks with.

Please note that a lot of this is super confusing at first, and that's why you can 
ask for help at ANY time. Along with this, the official onboarding document includes 
a whole glossary page dedicated to defining terms you may've not heard of before. 
So, if there's a weird acronym somewhere or term, look there first as it'll likely 
be included.

This is an exciting opportunity to not only learn more information about firmware and
concepts behind it, but to get real applications that'll carry over into your jobs
and the rest of your life. Firmware is everywhere, so learning how to write it and
knowing the important concepts backing it is almost necessary.

And, you'll have lots of fun while at it.

With that being said, click below to view the official firmware onboarding guide 
with tons of helpful information. This guide will get you well on your way towards 
completing onboarding and getting on the electrical team at Formula Slug.

[View the FS Firmware Onboarding Guide 26-27](https://docs.google.com/document/d/1gzXtD5qyJgARo-87Nuxqq9qUc0AAmL1TZiSR43iaq20/edit?usp=sharing)

---

Note: Clone this repository recursively (`git clone --recursive`). If you
didn't, be sure to initialize the submodule: `git submodule init` _and_ `git
submodule update`

**IMPORTANT:** To start your project, create a branch in this repo with your
first and last name. For example: `jack-nystrom`. Then submit your work to that
branch!

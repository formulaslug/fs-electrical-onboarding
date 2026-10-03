**Formula Slug Power Electronics Onboarding**

Welcome to Formula Slug's Power Eletronics onboarding project! Refer to this
Google Doc for all information regarding this project:

[View the FS Power Electronics Onboarding Guide 26-27](https://docs.google.com/document/d/1htf_bj8dCnWR_2gC1TFTzJU0MFP1d0OxF1IBO_kqalM/edit?usp=sharing)

---

Note: Clone this repository recursively (`git clone --recursive`). If you
didn't, be sure to initialize the submodule: `git submodule init` _and_ `git
submodule update`

**IMPORTANT:** To start your project, create a branch in this repo with your
first and last name. For example: `jack-nystrom`. Then do your work in that
branch!

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

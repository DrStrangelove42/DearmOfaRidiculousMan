# DreamOfaRidiculousMan

Welcome to the Dream of a Ridiculous Man !

It's a rogue-like game based on the novel by Fyodor M. Dostoyevsky, and inspired by the inspired Movie directed by Aleksandr Petrov:

https://m.youtube.com/watch?v=jIr7cs6eEAs

## Requirements

Supported OS : macOS & Linux & Windows

Required library : SDL2 (see below to install dependencies and build the game).

## Currently under development:

- [x] Map generating, see the HowItWorks.txt in '/Source/MapCreating'
- [x] Room functions(door, keys, creates,etc)
- [x] Player and Monster basic features and movements
- [x] Fighting and Exp gaining
- [x] Not-So-Intelligent Monster
- [x] Entry menu

### Glimpses of the future 
#### About the story
At the next stage, we'll generate more complex maps to meet the theme of the game:

- In the scenes of Heaven, there'll be battling, and the minions might be attacking the boss by transfered by the player.

- In the interlude scenes the player will explore alone in the map and find the way out.

- The little girl will guild you to your dream and be your way out of it ! 

#### More down-to-earth

Also there'll be more features, such as:

- Different texture packs to enrich the story.

- Save file.

- More objects, more map capacities, with a touch of sound effects.

## Build the Project

### Prerequisite : SDL 2
In this section you will read about ways to install the graphics library in order to run the game.
#### On Linux Debian :

`sudo apt install libsdl2-dev` \
`sudo apt install libsdl2-ttf-dev`\
`sudo apt install libsdl2-mixer-dev`

#### On MacOS with brew :

`brew install sdl2`\
`brew install sdl2_ttf`\ 
`brew install sdl2_mixer`

#### On Windows 
1) Download SDL and SDL_ttf from here:\
https://www.libsdl.org/download-2.0.php \
Go under *Development Libraries*\
If you are using Visual Studio, download the VC archive.\
If you are only using MinGW, only download the *\*-mingw* one\
Extract in a folder on your choice. From now on, we will refer to it by *SDL folder* (```SDL2-<version>/```).
To avoid the pain to have two norms of include directories in our sources, if you are using Visual Studio, 
create a subfolder in the include directory named ```SDL2``` and copy all headers in it. In fact at all times the headers
must be found under ```SDL folder/include/SDL2/```. Strangely enough, for Windows the header files were directly in ```include```, and
in other systems they are in the ```SDL2``` subfolder : by democracy we decided to take the latter standard.

2) Same work for SDL_ttf and SDL_Mixer :
https://www.libsdl.org/projects/SDL_ttf/ \
https://www.libsdl.org/projects/SDL_mixer/ \
For these ones, just take the ```SDL_ttf.h``` and ```SDL_Mixer.h``` files
 from the respective includes directories and copy them to *SDL folder* under ```\include\SDL2``` as before. \
 This way we gather everything in one place.
 
3) If you plan on using VisualStudio or MSBuild (see next section), just merge
 the two archives together in the same *SDL folder*. At the end you *must* have all headers under ```SDL_PATH/SDL2/```.
4) Merge the lib folder of both SDL_ttf and SDL_Mixer with the one in ```\lib\x64``` (you will need all .lib for VS and .dll files).\
Remark : with MinGW, the .lib files become the .a files.

5) Now you are ready for compilation.
#### References
https://wiki.libsdl.org/Installation

### Compilation
#### On UNIX-like systems
Go to the project root directory and type the following command in a terminal:\
```make release```

#### On Windows with Visual Studio

If you have Visual Studio installed (version 2019 tested, but the older vesions from 2015 should work),
just open the solution or the project file located in the ```/Windows``` folder.
1) If not already done, add an environment variable named SDLPATH in your system (user variable): either 
by going to windows settings, or from Windows Vista/Server 2008 you can type in CMD.EXE or
in the Run dialog the next command : \
```setx SDLPATH "<your SDL folder where lib and include are>"```

2) Build the project (F6)

3) Finally, copy-paste the SDL.dll and SDL_ttf.dll etc. in the output folder (like ```/x64/Debug/```), if it is not done automatically.

You can now run the executable file (F5 in Visual Studio). The output file will be copied in the root folder of the repository,
along with its .dll files, so you can launch it from there as well.

*If your system is older than Windows Vista (e.g. Windows XP or older), replace 
the ```/D WIN6``` macro definition in Project properties > C/C++ > Command line by
```/D WIN```. This will prevent problems about high DPI awareness, which is a feature 
that first appeared on Vista.*
 

 
#### On Windows with MSBUILD (from MS Build Tools, discontinued in the project)
1) Go to the ```/Windows``` subfolder, and edit the ```make.bat``` file with your paths (follow the instructions there).
2) Then you can launch the BAT script with a terminal or directly on double-clicking on it in the Windows Explorer.
 

#### On Windows with MinGW

Mosty the same as on UNIX-like systems.

## Optional installation
 

### Linux
 
 
Once compiled, you'll need sudo rights (if you have not these rights,
don't worry, only the last part will fail, but the copying of resources to HOME will
normally work), and the following command:\
```make install```\
Yes, no configure script for now. 

Then if you installed with sudo rights, you can type ```doarm``` in a console. If not,
```cd``` to the directory of the Makefile and type ```./doarm```.

Note : if you run Linux on WSL2, you must enable sounds (see https://discourse.ubuntu.com/t/getting-sound-to-work-on-wsl2/11869)

### macOS

*Work in progress*

### Windows
 
*Work in progress*

## Generate the documentation

On UNIX-like system you can generate HTML documentation with Doxygen with the command:\
```make doc```

Alternatively you can start Doxywizard and load the file located at ```Doc/Doxyfile```, then 
run the generator.

## Tests

The tests are done in a UNIX environment only, with the CPPUnit : ```libcppunit-dev``` package.
Once installed, type the following: \
```make test```
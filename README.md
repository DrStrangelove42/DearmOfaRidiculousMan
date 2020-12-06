# DreamOfaRidiculousMan

Welcome to the Dream of a Ridiculous Man !

It's a rogue-like game based on the novel by Fyodor M. Dostoyevsky, and inspired by the inspired Movie directed by Aleksandr Petrov:

https://m.youtube.com/watch?v=jIr7cs6eEAs

## Requirements

Supported OSes : macOS & Linux & Windows

Required library : SDL2 (see below to install dependencies and build the game).

## Currently under development:

- [x] Map generating, see the HowItWorks.txt in '/Source/MapCreating'
- [x] Room functions(door, keys, creates,etc)
- [x] Player and Monster basic features and movements
- [x] Fighting and Exp gaining
- [x] Not-So-Intelligent Monster
- [x] Entry menu

At the next stage, we'll generate more complex maps to meet the theme of the game:

- In the scenes of Heaven, there'll be battling, and the minions might be attacking the boss by transfered by the player.

- In the interlude scenes the player will explore alone in the map and find the way out.

- The little girl will guild you to your dream and be your way out of it ! 

Also there'll be more features, such as:

- Different texture packs to enrich the story.

- Save file.

## Build the Project

### Install SDL 2
#### On Linux Debian :

`sudo apt install libsdl2-dev` \
`sudo apt install libsdl2-ttf-dev`

#### On MacOS with brew :

`brew install sdl2`\
`brew install sdl2_ttf`

#### On Windows 
1) Download SDL and SDL_ttf from here:\
https://www.libsdl.org/download-2.0.php\
Go under *Development Libraries*\
If you are using Visual Studio, download the two archives.\
If you are only using MinGW, only download the *\*-mingw* one\
Extract in a folder on your choice. From now on, we will refer to it by *SDL folder* (```SDL2-<version>/```).

2) Same work for SDL_ttf :
https://www.libsdl.org/projects/SDL_ttf/ \
For this one, just take the ```SDL_ttf.h``` file
 from the include directory and move it to *SDL folder* under ```\x86_64-w64-mingw32\include\SDL2``` (yes even for VisualStudio).\
This last path is our include directory, remember it. 
3) If you plan on using VisualStudio or MSBuild (see next section), just merge
 the two archives together in the same *SDL folder*.
4) Merge the lib folder of SDL_ttf with the one in ```\lib\x64``` (you will need all .lib for VS and .dll files).\
Remark : with MinGW, the .lib files become the .a files.

5) Now you are ready for compilation.
#### References
https://wiki.libsdl.org/Installation

### Compilation
#### On UNIX-like systems
Go to the project root directory and type the following command in a terminal:\
```make```

#### On Windows with Visual Studio

If you have Visual Studio installed (version 2019 tested, but the older vesions from 2015 should work),
just open the solution or the project file located in the ```/Windows``` folder.
1) Go to **Project > properties of doarm > Build events > Pre-build** and fill the textbox with the following command:\
```set SDLPATH=<your SDL2-2.<version> root directory>```
(Change the path with *SDL folder*).

2) Build the project (F6)

3) Finally, copy-paste the SDL.dll and SDL_ttf.dll in the output folder (like ```/x64/Debug/```).\

You can now run the executable file (F5 in Visual Studio). The output file will be copied in the root folder of the repository,
along with its .dll files, so you can launch it from there as well.

*If your system is older than Windows Vista (e.g. Windows XP or older), replace 
the ```/D WIN6``` macro definition in Project properties > C/C++ > Command line by
```/D WIN```. This will prevent problems about high DPI awareness, which is a feature 
that first appeared on Vista.*

#### On Windows with MSBUILD (from MS Build Tools, not tested yet)
1) Go to the ```/Windows``` subfolder, and edit the ```make.bat``` file with your paths (follow the instructions there).
2) Then you can launch the BAT script with a terminal or directly on double-clicking on it in the Windows Explorer.

#### On Windows with MinGW

Coming soon.

## Generate the documentation

On UNIX-like system you can generate HTML documentation with Doxygen with the command:\
```make doc```

Alternatively you can start Doxywizard and load the file located at ```Doc/Doxyfile```, then 
run the generator.
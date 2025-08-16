# War Storm
![War Action](./Extras/LogoMedium.png)

## Project
War Storm is an open source implementation of Fireglow Games' [Sudden Strike II](https://en.wikipedia.org/wiki/Sudden_Strike_2) from 2002, with the 2.2 patch.

## Goals
There are multiple goals this project tries to achieve:
- [x] Learn how games were made in an era when things had to be done in the code, and not through fancy game engines like today.
- [ ] Have a fully playable game implemented end-to-end, including resource management, audio, and video rendering, as well as support of large screen resolutions.
- [ ] Eventually, to support 64-bit compilation for modern systems.

## Code
```
git clone --recurse-submodules https://github.com/americusmaximus/WarStorm
```

## Requirements & Dependencies
1. [Microsoft Visual Studio](https://visualstudio.microsoft.com/downloads/)
2. [OGG](https://github.com/xiph/ogg) and [Vorbis](https://github.com/xiph/vorbis)
3. [Yoink](https://github.com/americusmaximus/Yoink)
4. [ZLib](https://github.com/madler/zlib)
5. Intel JPEG library

## Notes
1. I used GOG.com's Sudden Strike 2 version [13718](https://www.google.com/search?q=setup_sudden_strike_2_2.2_(13718).exe) of the game.
2. The game is structured in a way where the executable is just a glue for separate menu and game modules, which are in their turn can use different renderer modules.
3. The GOG.com's version of the game uses Ogg Vorbis for the game's music. It looks like this was a recent change and a requirement for the game publishing, I believe original game shipped with mp3 files. In order to support Ogg Vorbis, the games has its own WinMM.dll library to support the file format, otherwise it is mostly a wrapper of the system library.
4. The original game used zlib version 1.1.3, which I upgraded to 1.3.1 for proper 64-bit support.
5. The original game uses RAD Game Tools' binkw32 library version 1.5G.

## Modules

### Launcher
The launcher module is the game's executable. Its purpose is to do initial setup, read some settings, load proper renderer module, and transition control to the menu module.

### Renderer
The game ships with 3 renderer modules. The renderers have, essentially, the same codebase, the only difference is the size of the game screen supported. Available options are: 640x480, 800x600, 1024x768.

### Menu
The menu module is responsible for guiding the user through all kinds of options and activities such as starting a new campaign, loading a game, or setting up a multiplayer game. Once done - it transfers  control to the game module, and the game module can transfer control back to the menu module. The game module transfers the control back as well to display statistics and transition between maps and missions.

### Game
The game module is responsible for the actual gameplay, associated resource management, game state, etc, and can pass the control back to the menu module for video playback, showing mission statistics, and so on.

## Similar & Related Projects
1. [War Action](https://github.com/americusmaximus/WarAction)
2. [War Motion](https://github.com/americusmaximus/WarMotion)
3. [War Tool Kit](https://github.com/americusmaximus/WarToolKit)

## Thanks
1. [Hifi](https://github.com/hifi-unmaintained/ogg-winmm) for the original implementation of WinMM.dll with the Ogg Vorbis support. Even though the game's version is very customized, access to the original code was very useful.
3. [elwray](https://github.com/elwray/N2CadX) for the initial research of the rendering modules.
4. [IvanishinV](https://github.com/IvanishinV/MultiCAD) for completing reverse engineering and re-engineering of 1024x768 renderer for [Sudden Strike](https://github.com/americusmaximus/WarAction).

## Legal
1. This is not a complete game. Please purchase software you like!
2. The source code in this repository is mostly produced by reverse engineering the original binaries. There are a couple of exceptions for reverse engineering under DMCA -- documentation, interoperability, fair use. See goals section for the interoperability and fair use cases. The documentation is needed to support those. Also please see an article about [software preservation](https://en.wikipedia.org/wiki/Digital_preservation).
3. Sudden Strike, Fireglow Games, CDV, RAD Game Tools, Bink, Ogg Vorbis, DirectX, OpenGL, Vulkan, and others are trademarks of their respective owners.

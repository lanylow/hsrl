# Honkai: Star Rail Lua - HSRL [![License](https://img.shields.io/badge/License-GPL3.0-green.svg)](https://github.com/lanylow/genshin-utility/blob/main/LICENSE) ![OS](https://img.shields.io/badge/OS-Windows-yellow.svg) [![Discord](https://img.shields.io/badge/chat-discord-informational)](https://discord.gg/MrtJvV5tKv)

Free and open-source tool for Honkai: Start Rail that allows you to execute your own Lua scripts inside the game's built-in XLua environment. The program is developed as an internal module that's being loaded into the game process. Compatible only with the global version of the game.

## FAQ

### How to load the tool?
I am not providing any builds of this program yet, so if you want to try it you will have to compile it yourself. Once you do that, you can use the loader from my other program, [Genshin Utility](https://github.com/lanylow/genshin-utility), to load this tool into the game.

### Why is my game crashing when trying to run a script?
You cannot run scripts while in the start screen. Make sure to be in the game world before trying to run any scripts.

### How do I open and close the menu?
When you have the game window focused, press the <kbd>INSERT</kbd> key.

### What do I do if the HSRL menu doesn't pop up?
The most common cause of this problem are third-party overlays. Make sure programs such as MSI Afterburner (RTSS) or Discord Game Overlay are not attached to the game, because they might interfere with the menu of this tool. Another possible cause is that you are not running the game through the launcher, this program will not work if you open the game's executable directly.

## Screenshots

![image](https://github.com/lanylow/hsrl/assets/31806776/fefeac86-e309-4be9-816d-98c0f86fd666)

## Utilized third-party libraries

* [ImGui](https://github.com/ocornut/imgui) - Graphical User interface for C++
* [MinHook](https://github.com/TsudaKageyu/minhook) - API Hooking Library for Windows
* [ImGuiColorTextEdit](https://github.com/BalazsJako/ImGuiColorTextEdit) - Colorizing text editor for ImGui 

## License

This project is licensed under the GPL-3.0 License - see the [LICENSE](https://github.com/lanylow/hsrl/blob/master/LICENSE) file for details.

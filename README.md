# Guitar Hero 1 Milo Conversion Tools

This project intends on converting files from Harmonix's various proprietary
formats found inside Guitar Hero 1's `.rnd_ps2` and `.gh` files (usually referred
to as "milo" files due to their similarities to the newer `.milo_platform` files)
into more standard filetypes, such as `.obj` and `.png`.

### Dependencies
- [spng](https://libspng.org/)
- [zlib](https://zlib.net/)

### Supported Conversions

|   Source      |   Destination |   Status                      |
|---------------|---------------|-------------------------------|
|   LE HMX milo |   "raw" milo  |   Mostly Complete             |
|   HMX .mesh   |   .obj        |   Partially Complete          |
|   HMX .tex    |   .pam        |   Partially Complete          |
|   HMX .tex    |   .png        |   Partially Complete          |
|   HMX .mat    |   .mtl        |   Partially Complete          |
|   HMX .tex    |   .dds        |   Not Yet Implemented (soon)  |
|  .rnd_ps2/.gh |   .gltf       |   Not Yet Implemented         |

## Building

### Linux/WSL

Make sure you have your distro's version of `spng` and `zlib`, spng's package names can be found [here,](https://libspng.org/download/) and zlib is either already installed or it's `zlib-devel`. Then, `make`, `make genclang` if you intend on doing things with the project, and `sudo make install` to install, and do a sanity `hxconv` (name of the program) to make sure everything installed properly.

### Native Windows (and, to an extent, MacOS)

you're on your own lmao, theoretically mingw gcc works but i'm not helping you if it dies
prolly should set up dll autobuilding at some point but eh. if you want it so bad, make a pr

### Usage

`hxconv <input_file> <output_file> [-i type] [-o type]`
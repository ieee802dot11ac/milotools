# Guitar Hero 1 Milo Conversion Tools

This project intends on converting files from Harmonix's various proprietary
formats found inside Guitar Hero 1's `.rnd_ps2` and `.gh` files (usually referred
to as "milo" files due to their similarities to the newer `.milo_platform` files)
into more standard filetypes, such as `.obj` and `.png`.

### Dependencies
- [spng](https://libspng.org/)

### Supported Conversions

|   Source      |   Destination |   Status                      |
|---------------|---------------|-------------------------------|
|   HMX .mesh   |   .obj        |   Partially Complete          |
|   HMX .tex    |   .pam        |   Partially Complete          |
|   HMX .tex    |   .dds        |   Partially Complete          |
|   HMX .mat    |   .mtl        |   Not Yet Implemented (soon)  |
|   HMX .tex    |   .png        |   Not Yet Implemented (soon)  |
|  .rnd_ps2/.gh |   .gltf       |   Not Yet Implemented         |

## Building

### Linux/WSL2

Make sure you have your distro's version of `spng`, names can be found [here.](https://libspng.org/download/) Then, `make`, `make genclang` if you intend on doing things with the project, and `sudo make install` to install, and do a sanity `hxconv` (name of the program) to make sure everything installed properly.

### Windows (no WSL)

you're on your own lmao
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
|   HMX .lbl    |   .txt        |   Not Yet Implemented (soon)
|   HMX .mat    |   .mtl        |   Not Yet Implemented (soon)  |
|   HMX .tex    |   .png        |   Not Yet Implemented (soon)  |
|  .rnd_ps2/.gh |   .gltf       |   Not Yet Implemented         |

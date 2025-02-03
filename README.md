# Image Pixelator

A simple image "downscaler" written in C.

## What It Does

- Loads an image file.
- Applies a simple pixelation effect by averaging colors in blocks.
- Saves the new pixelated image.

### Building the Project

Open your terminal and run:

```bash
cmake -S . -B build
cmake --build build
./build/pixelator
```

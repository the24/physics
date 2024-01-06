# Physics

Trying to recreate a physical engine, in C. Using [SDL](https://www.libsdl.org/) for rendering.

For now, there are only collisions of spherical rigid body.

## Setting up

The project is compiled using `gcc` and `make`.
To switch compiler, change `CC` variable in `Makefile` (not tested).

### For Windows

Download [`SDL2-devel`](https://github.com/libsdl-org/SDL/releases/tag/release-2.28.5) then add `bin` and `lib` folders to the root of projet.

### For Linux

Install `libsdl2-dev` package.
Or download [`SDL2-devel`](https://github.com/libsdl-org/SDL/releases/tag/release-2.28.5) then follow `INSTALL.txt` instructions.

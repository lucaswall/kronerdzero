
# Warriors of Kronerd #

A shoot 'em up game for the Raspberry Pi 3.

Warriors of Kronerd is a Raspberry Pi 3 game written using only low level interactions with the hardware, without using any operating system (replacing it). It's a bare metal programming example of a game.

It was written just for fun, as a learning experience and out of nostalgia.

The game is not yet finished.

What is done:

 - Framebuffer init and sprite system.
 - Offscreen plane and fast copy to framebuffer.
 - Sprite animations.
 - Sprite collisions.
 - Mersenne Twister pseudorandom number sequence generated.
 - Hardware random number access for MT seed initialization.
 - Access to 1Ghz system timer.
 - Basic bitmap font to blit text and numbers.
 - Scene support.

What to code next:

 - Controller support (probably original NES hooked to GPIO).
 - Sound and music support (on a separate CPY core?).
 - DMA offscreen plane copy to framebuffer?
 - Use another CPU core to copy to framebuffer?


## How to run

Check the Makefile.

You will need an ARM compiler installed on your system. Running a `make build` should generate the `kernel7.img` file. This file, along with the `config.txt` should be placed on the first FAT32 partition of your Raspberry Pi 3 booting SD card.

Once powered the game should start immediately.


## Sources

The following sources where consulted to build the base of the bare metal code.

**Baking Pi – Operating Systems Development, course by Alex Chadwick.**

https://www.cl.cam.ac.uk/projects/raspberrypi/tutorials/os/index.html

**Raspberry Pi, Raspberry Pi 2 & Raspberry Pi 3 Bare Metal Code by krom (Peter Lemon).**

https://github.com/PeterLemon/RaspberryPi

**Bare Metal Programming in C, by Brian Sidebotham**

http://www.valvers.com/open-software/raspberry-pi/step01-bare-metal-programming-in-cpt1/

**Circle, A C++ bare metal environment for Raspberry Pi with USB**

https://github.com/rsta2/circle


## Author

- Lucas Wall <wall.lucas@gmail.com>


## License

Copyright (c) 2016 Lucas Wall <wall.lucas@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

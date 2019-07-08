# Tetris
A Tetris app for Android (and Desktop) written with SFML

## Features
* Basic tetris mechanics
* Android and desktop app
* Touch, mouse or keyboard controls
* Scoreboard
* Music (with dynamic speed)
* No assets. All graphics, fonts, sounds are generated

## Dependencies
### SFML
https://github.com/SFML/sfml#install

#### For Android
Follow the instructions at https://github.com/SFML/SFML/wiki/Tutorial:-Building-SFML-for-Android to install sfml.
You will probably need to install Gradle 4.x instead of 5.x.

#### For desktop
Install SFML the regular way. E. g. with a package manager like pacman:
```
pacman -S sfml
```

## Building
### Linux
#### For Android
```
gradle build
```

#### For desktop
```
mkdir build && cd build
cmake ..
make
```
## Todo
* Fix crash when exiting
* Parallel music generation
* Button icons
* effects
* 
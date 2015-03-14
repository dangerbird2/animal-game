animal game for Tulane CMPS 1600
====

Author: Steven Shea <stevenlsjr@gmail.com>

compiling instructions:
----
this project has no preexisting dependencies aside from a modern 
C/C++ compiler, git, and cmake. Git can fetch the googletest as
a submodule, which cmake will compile along with the project itself

to build the project:
```
#clone project
git clone https://github.com/dangerbird2/animal-game.git animal-game
cd animal-game

# download submodules
git submodule init
git submodule update

#create cmake build directory
mkdir build && cd build

#build with cmake
cmake ..
make

```
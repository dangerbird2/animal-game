animal game for Tulane CMPS 1600
====

Author: Steven Shea <stevenlsjr@gmail.com>

compiling instructions:
----

The final project will be con

this project has no preexisting dependencies aside from a modern 
C/C++ compiler, git, and cmake. Git can fetch the googletest as
a submodule, which cmake will compile along with the project itself

to build the project:
```bash
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

Animal game algorithm pseudocode:
---

* Store node data as a struct with two fields -- a boolean field indicating whether the node
represents a specific species or a descriptor(eg. does it quack, is it green, etc.). The second field is the node's name
    * nodes that are species must be leaf nodes.
* Begin by calling a `ask_user` routine on the head node
* subroutine `ask_user(node)`:
    * ask "are you thinking of a [node description]?"
    * if node is a branch
        * if user responds "yes", call ask_user on left node
        * else, call `ask_user` on right node
    * if node is a leaf
        * if user responds "yes", end game
        * else, call `expand_node` on node
* subroutine `expand_node(node)`
    * create a new descriptor node (descriptor can be chosen randomly from list)
    * 


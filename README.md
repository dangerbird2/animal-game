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

to build documentation:
```
doxygen ./doxyfile.in
# open docs/html/index.html in browser
```

* [Documentation](http://dangerbird2.github.io/animal-game/docs/html/)

Animal game algorithm pseudocode:
---

* Store node data as a struct with two fields -- a boolean field indicating whether the node
represents a specific species or a descriptor(eg. does it quack, is it green, etc.). The second field is the node's name
    * nodes that are species must be leaf nodes.
* Begin by calling a `ask_user` routine on the head node
* subroutine `ask_user(node)`:
    * ask "are you thinking of a [node description]?"
    * if node is a leaf and user responds "yes", end game
    * else, call `traverse-node` on node and response and
    set current node to returned value

* subroutine `traverse-node`
    * match response YES with right node, NO with left node
    * if matching node is non-null, return matching node
    * else, if node is a category(branch), ask user for the
    animal the user is thinking of, and attach new node with
    user's animal to matching node
    * else, if node is an animal(leaf) ask what differentiates
    user's animal from given animal. replace animal node
    with new category node, and place the old animal node with the
    *non-matching* node.
    * return tree's head node (starting process over)


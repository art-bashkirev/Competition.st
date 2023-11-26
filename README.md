# Competition.st
A command-line utility to quickly generate problem files from stubs for competitions

## Installation
```zsh
$ git clone https://github.com/art-bashkirev/Competition.st.git
$ make
$ make install # or sudo make install
```

## Usage
```zsh
$ st [x] [lang]
x - the number of problems
lang - the language of the created stubs
```

```zsh
$ st 5 cpp # Creates 5 alphabetically numbered stubs in C++
$ st 3 py  # Creates 3 alphabetically numbered stubs in Python
```

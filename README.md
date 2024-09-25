# Competition.st

A command-line utility to quickly generate problem files from templates for competitive programming

## Installation

```zsh
git clone https://github.com/art-bashkirev/Competition.st.git
make
make install
```

## Usage

```zsh
$ cst [x] [lang]
x - the number of problems
lang - the language of the created problem files from templates
```

```zsh
cst 5 cpp # Creates 5 alphabetically "numbered" files from C++
cst 3 py  # Creates 3 alphabetically "numbered" files from Python
```

## Template creation

The templates are located in `~/cst/templates/template.{lang}`.

---

Pre-installed on [artbashkirev/codespace:competition](https://hub.docker.com/r/artbashkirev/codespace/tags?page=1&name=comp)

# Competition.st
A command-line utility to quickly generate problem files from stubs for competitions

## Installation
```zsh
git clone https://github.com/art-bashkirev/Competition.st.git
make
make install
```

## Usage
```zsh
$ st [x] [lang]
x - the number of problems
lang - the language of the created stubs
```

```zsh
st 5 cpp # Creates 5 alphabetically "numbered" stubs for C++
st 3 py  # Creates 3 alphabetically "numbered" stubs for Python
```

## Stub creation

Located by default on "~/st/stub.{lang}"

---

Pre-installed on [artbashkirev/codespace:comp](https://hub.docker.com/r/artbashkirev/codespace/tags?page=1&name=comp)

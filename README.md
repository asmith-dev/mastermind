# Mastermind

A CLI implementation of the classic board game. Syntax instructions given upon execution. Mastermind game instructions and strategies can be found online from an abundance of sources.

## Installation and Usage

Note: dependencies are `git` and `g++`.  
Clone repository and move into parent directory:
```
git clone https://github.com/asmith-dev/mastermind.git
cd mastermind
```

Build for your system:
```
g++ main.cpp -o mastermind
```

Then, execute the game binary:
```
# Linux and MacOS
./mastermind

# Windows
.\mastermind.exe
```

<br>

### Optional (Linux only, with root privileges)

Move the binary file to `/usr/bin`:
```
sudo mv mastermind /usr/bin
```

Thus, conveniently, you can start the game from anywhere in your filesystem using just:
```
mastermind
```
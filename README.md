<img src="https://i.imgur.com/y2bQtnZ.png" width="150" height="150" alt="Logo" />

# 42-Minishell
## Overview
The **minishell** project is a **basic shell program** created as part of **42 School**. It replicates essential features of a Unix shell, including executing commands, handling pipes and redirections, and managing environment variables. This project is an introduction to the world of system programming, process creation, and signal handling in C, giving students insight into how a shell operates internally.

## Getting started
To compile and execute minishell, you will need to install **readline** library.
> If you are on macOS, make sure you have installed **Xcode Command Line Tools** and **Homebrew**.
- Linux
```bash
sudo apt install libreadline-dev
```
- macOS
```bash
brew install readline
```
Once **readline** is installed, you can continue with the following steps.
1. Clone this repository
```bash
git clone https://github.com/extrymes/42-Minishell.git
cd 42-Minishell
```
2. Compile and launch the program
```bash
make
./minishell
```

## Features
- Running executables located in `PATH` environment variable.
- Running built-in commands like `echo`, `cd`, `pwd`, `export`, `unset`, `env`, and `exit`.
- Handling pipe (`|`), heredoc (`<<`) and redirections (`<`, `>`, `>>`).
- Handling environment variables like bash.
- Handling signals `CTRL-C`, `CTRL-D`, and `CTRL-\` like bash.

## Contributing
We welcome contributions from everyone! Whether you're fixing bugs, adding new features, improving documentation, or simply sharing your ideas, your input is greatly appreciated.

Thanks for visiting and happy coding!

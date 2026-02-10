# Minishell-42

A simple shell implementation inspired by Bash, developed as part of the 42 curriculum.

## Description

Minishell is a command-line interpreter that replicates the core functionality of a Unix shell. It handles command execution, environment variable management, and signal processing, providing a deep dive into process creation (`fork`, `execve`), file descriptor manipulation (`dup2`, `pipe`), and signal handling.

## Features

-   **Command Execution**: Run executables from absolute/relative paths or `PATH` environment.
-   **Built-in Commands**:
    -   `echo` (with `-n` option)
    -   `cd` (with relative/absolute paths)
    -   `pwd` (print working directory)
    -   `export` (manage environment variables)
    -   `unset` (remove environment variables)
    -   `env` (list environment variables)
    -   `exit` (terminate shell)
-   **Redirections**:
    -   `<`: Redirect input.
    -   `>`: Redirect output.
    -   `<<`: Heredoc (read input until delimiter).
    -   `>>`: Append output.
-   **Pipes**: `|` Connect command output to input.
-   **Environment Variables**: Expansion of `$VAR` and `exit status $?`.
-   **Signals**:
    -   `Ctrl-C`: Interrupt (new prompt).
    -   `Ctrl-D`: EOF (exit shell).
    -   `Ctrl-\`: Quit (do nothing).
-   **Quotes**: Handling of single `'` and double `"` quotes.

## Getting Started

### Prerequisites

-   `gcc` or `clang`
-   `make`
-   `readline` library

### Installation & Usage

1.  **Clone the repository:**
    ```bash
    git clone https://github.com/nelsonwm45/Minishell-42.git
    cd Minishell-42
    ```

2.  **Compile the program:**
    ```bash
    make
    ```

3.  **Run Minishell:**
    ```bash
    ./minishell
    ```

    **Example Usage:**
    ```bash
    minishell$ echo Hello World
    Hello World
    minishell$ ls -l | grep .c
    ...
    ```

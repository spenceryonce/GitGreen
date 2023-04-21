# Windows Git Commit Generator

This program generates Git commits for random days in the current year, up to and including the current day. The purpose of this program is to create a unique contribution history in your GitHub profile.

## Prerequisites

- Git command line tool installed and configured on your system.
- A Git repository to run the program in.

## Features

- Generates a random number of Git commits for each day of the year up to the current day.
- Adds a line to a `green.txt` file for each commit with a unique identifier.
- Commits are dated with the `--date` option to create a custom commit history.

## Building and Running

### Using Microsoft Visual Studio Compiler

1. Open the Visual Studio Developer Command Prompt.
2. Navigate to the directory containing the `main.c` file.
3. Compile the program using the following command:
`cl main.c`
4. Run the compiled program `main.exe` in a Git repository:
`main.exe`

### Using GCC (MinGW)

1. Open a terminal or command prompt.
2. Navigate to the directory containing the `main.c` file.
3. Compile the program using the following command:
`gcc main.c -o main.exe -lkernel32`
4. Run the compiled program `main.exe` in a Git repository:
`main.exe`

## Notes
- The program has been tested on Windows x64 systems. Compatibility with other operating systems is not guaranteed.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.






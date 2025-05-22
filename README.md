# ULS - Unix List Directory

A custom implementation of the Unix `ls` command written in C, providing file and directory listing functionality with various formatting options and flags.
The implementation closely follows the behavior of the standard Unix `ls` command while maintaining clean, modular code structure.

## Features

- **Multiple output formats**: Simple list, detailed info, and column-based display
- **Comprehensive flag support**: Compatible with standard `ls` flags
- **Recursive directory traversal** with `-R` flag
- **Sorting options**: Alphabetical, by size, and reverse sorting
- **Permission and ownership display** in long format
- **Hidden file handling** with `-a` and `-A` flags
- **Cross-platform compatibility** (macOS, Linux, Oracle)

## Supported Flags

| Flag | Description |
|------|-------------|
| `-1` | Force output to be one entry per line |
| `-A` | List all entries except `.` and `..` |
| `-a` | List all entries including hidden files (starting with `.`) |
| `-f` | Do not sort; list entries in directory order |
| `-l` | Use long listing format with detailed file information |
| `-o` | Like `-l` but omit group information |
| `-p` | Append `/` indicator to directories |
| `-R` | List subdirectories recursively |
| `-r` | Reverse the order of the sort |
| `-S` | Sort by file size (largest first) |

## Project Structure

```
uls/
├── Makefile           # Build configuration
├── inc/
│   └── uls.h         # Header file with function declarations
├── src/
│   ├── main.c                    # Main program entry point
│   ├── mx_dirs_and_files.c      # Directory and file handling
│   ├── mx_list.c                # Linked list operations
│   ├── mx_max_len_names.c       # Utility for name length calculation
│   ├── mx_parse_and_checks.c    # Argument parsing and validation
│   ├── mx_print_full.c          # Long format output (-l flag)
│   ├── mx_print_part.c          # Column-based output
│   └── mx_simple_print.c        # Simple list output (-1 flag)
└── libmx/            # External library dependency
```

## Building

### Prerequisites
- `clang` compiler
- `make` utility
- The `libmx` library (should be in the `libmx/` directory)

### Compilation
```bash
make
```

This will:
1. Compile the `libmx` library
2. Build the `uls` executable
3. Clean up object files

### Other Make Targets
```bash
make clean      # Remove object files and library files
make uninstall  # Remove object files and executable
make reinstall  # Clean rebuild (uninstall + build)
```

## Usage

```bash
./uls [flags] [files/directories...]
```

### Examples

```bash
# List current directory contents
./uls

# List with detailed information
./uls -l

# List all files including hidden ones
./uls -a

# List recursively with long format
./uls -lR

# List specific files and directories
./uls -l file1.txt /path/to/directory

# Sort by size in reverse order
./uls -lSr
```

## Implementation Details

### Data Structures
- Uses a custom linked list implementation (`List` struct) for managing file and directory entries
- Separates files and directories for different handling and display

### Key Functions
- **Parsing**: `mx_parse()` handles command-line argument processing
- **Directory Reading**: `mx_get_files_from_dir()` reads directory contents
- **Sorting**: Multiple sorting algorithms including by name, size, and reverse order
- **Display**: Three different output formats depending on flags used

### Memory Management
- Proper allocation and deallocation of dynamic memory
- Custom list clearing functions to prevent memory leaks

### Error Handling
- Handles permission denied errors
- Reports non-existent files and directories
- Validates command-line flags

## Compatibility Notes

The Makefile includes different compiler flag configurations:
- **macOS and Oracle**: Uses `-std=c11` flag
- **Linux**: Alternative configuration available (commented out)

## Dependencies

- **libmx**: Custom utility library providing string manipulation and other helper functions
- **Standard C libraries**: `dirent.h`, `sys/stat.h`, `pwd.h`, `grp.h`, `time.h`, etc.

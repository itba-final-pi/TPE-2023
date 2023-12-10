# TPE Programación Imperativa Dec/2023

<!-- Status badge, requires to be logged into Github with permission to view the repo -->
<!-- This badge shows the status of the latest automated testing -->

[![Compile & Test C](https://github.com/itba-final-pi/TPE-2023/actions/workflows/test-c.yml/badge.svg)](https://github.com/itba-final-pi/TPE-2023/actions/workflows/test-c.yml)

<!-- End Status badge -->

This repository oversees the development of the [TPE as described here](https://docs.google.com/document/d/1wUARmwvPXxHk7e4jIkVxDeeFW-MSZbRAa6W8VgzmrmE/edit?usp=sharing)

## Table of contents

- [TPE Programación Imperativa Dec/2023](#tpe-programación-imperativa-dec2023)
  - [Table of contents](#table-of-contents)
  - [Members](#members)
  - [Compilation](#compilation)
  - [File structure](#file-structure)
  - [Speed](#speed)
  - [Development, Testing, Continuous Integration](#development-testing-continuous-integration)
  - [Discussion](#discussion)
    - [Git](#git)
    - [Optimizations](#optimizations)
    - [Testing](#testing)
      - [Pampero](#pampero)


## Members

| Name                   | Student ID | Email                      |
|------------------------|------------|----------------------------|
| Luca Mancuso           | 64150      | lmancuso@itba.edu.ar       |
| Santiago Manuel Torres | 64563      | torres.kilmes@gmail.com    |
| Tomas Pietravallo      | 64288      | hello@tomaspietravallo.com |

## Compilation

In order to compile the program, a POSIX compliant operating system with GNU Make and GCC is required.

To compile into an executable, run the following shell command `make all CITY=$CITY`

Where `$CITY` can take any of the following values:

| City              | $CITY | Full command        |
|-------------------|-------|---------------------|
| New York City, US | `NYC` | `make all CITY=NYC` |
| Montreal, CA      | `MON` | `make all CITY=MON` |

```sh
# Creates an executable compatible with Montreal's data
make all CITY=MON

# New York City
make all CITY=NYC
```

## File structure

In order to maintain things tidy, files are kept in separate folders following the criteria:

| path                                  | Description                                   |
|---------------------------------------|-----------------------------------------------|
| [.git/](./git)                        | Git history                                   |
| [.github/](./github)                  | Github Actions configuration                  |
| [CTable/](./CTable/)                  | CTable library files                          |
| [src/](./src/)                        | Backend source files                          |
| [front/](./front)                     | Frontend source files                         |
| [helpers/](./helpers)                 | Helper functions, useful data structures, etc |
| [headers/](./headers)                 | Header files (src & helpers)                  |
| [main.c](main.c)                      | Main file                                     |
| [tests](./tests/)                     | Test files, outputs, configurations           |
| [Makefile](./Makefile)                | GNU Make file                                 |
| [CONTRIBUTING.md](./CONTRIBUTING.md)  | Style guides and notes on how to contribute   |
| [.gitignore](./gitignore)             | Specifies files not tracked by Git            |
| [README.md](./README.md)              | Project description                           |

## Speed

All the following speeds are benchmarked using the [Binary file for Montreal](#compilation), reading the 14.266.437 line `bikesMON.csv` and 997 line `stationsMON.csv` datasets

| Hardware                 | Speed                                                |
|--------------------------|------------------------------------------------------|
| Pampero                  | 24.642s **                                           |
| MacBook (ARM, M2)        | 5.301 s ±  0.058 s [User: 5.077 s, System: 0.202 s]  |
| Ubuntu Laptop (i5-1240P) | 12.062 s ± 0.046 s [User: 11.869 s, System: 0.192 s] |

> \*\* We found this number oscillates significantly, most likely due to server load.

## Development, Testing, Continuous Integration

In order to move fast and make sure things weren't broken while iterating, establishing a process around a central testing pipeline proved crucial.

## Discussion

### Git

We recognize the Git history may not be as clean as it could.

We strived to move fast and work asynchronously on different tasks at the same time, which in our case, meant working across branches and performing merges.

### Optimizations

strptime

### Testing

The testing pipeline proved itself to be incredibly useful in ensuring a common baseline, and helping catch bugs/memory leaks. However, there are quite a few ways it could be improved, most notably:

#### Pampero

All tests are ran on the same Pampero user, and the test runners could potentially crash with each other. This would result in a failed test.

Luckily it is quite easy to manually re-run failed tests on CI, and test runners never crashed throughout the development process, as the pipeline wasn't hit often enough for this to happen.


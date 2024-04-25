# **coreutils**

Welcome to the coreutils repository. This repository contains basic utility programs implemented in C, inspired by GNU coreutils.

### Repository Overview

- **src**: Contains the source code files for utility programs.
  - **cat.c**: Source code for the `cat` utility.
  - **tac.c**: Source code for the `tac` utility.
  - **head.c**: Source code for the `head` utility.
  - **tail.c**: Source code for the `tail` utility.
  - **cd.c**: Source code for the `cd` utility.
  - **echo.c**: Source code for the `echo` utility.
  - **touch.c**: Source code for the `touch` utility.
  - **false.c**: Source code for the `false` utility.
  - **pwd.c**: Source code for the `pwd` utility.
  - **sleep.c**: Source code for the `sleep` utility.
  - **true.c**: Source code for the `true` utility.
  - **wc.c**: Source code for the `wc` utility.
  - **nproc.c**: Source code for the `nproc` utility.
  - **yes.c**: Source code for the `yes` utility.
- **compile**: Compilation script.

### Usage

1. **Clone the Repository:**
   ```bash
   git clone https://git.x3ric.com/coreutils
   ```

2. **Compile the Utilities:**
   - Use the provided `compile` script to compile the utilities.
   ```bash
   ./compile
   ```

3. **Run the Utilities:**
   - After compilation, execute the desired utility in the created folder `./bin/`.
   ```bash
   cat
   tac
   head
   tail
   cd
   echo
   touch
   false
   pwd
   sleep
   true
   nproc
   wc
   yes
   ```

4. **Compile and Run Shortcut:**
   - Execute the following command in the root of the repository to compile and run a utility.
   ```bash
   ./compile <utility>
   ```

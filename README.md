# Real-Time Systems Experiments 🕒

This repository contains codes and experiments conducted during the Real-Time Systems course. Currently, we have the following program available:

## Programs

- [x] [Time](./src/time/);

### Running the Program Using the `bin/run` Script 🚀

1. **Navigate to the Repository Root Directory:**
  
  ```bash
  cd path/this/repo
  ```

2. **Make the `run` Script Executable:**
  Ensure that the script has the necessary execute permissions:
  ```bash
  chmod +x bin/run
  ```

3. **Execute the Program:**
  You can run the program directly with the following command:
  ```bash
  bin/run time
  ```
  - To force build the program before executing, use:
  ```bash
  bin/run time -b
  ```

### Manual Execution Programs Using CMake 🛠️

1. **Navigate to the Project Directory:**

  ```bash
  cd src/$PROJECT
  ```

2. **Create a Build Directory:**
  If it doesn't already exist, create a build directory:

  ```bash
  mkdir build
  cd build
  ```

3. **Run CMake to Configure the Project:**

  ```bash
  cmake ..
  ```

4. **Build the Project:**

  ```bash
  make
  ```

5. **Execute the Program:**

  ```bash
  ./main
  ```

## Additional Information

Ensure you have the necessary dependencies installed, such as CMake and any libraries required by the program.

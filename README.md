# Real-Time Systems Experiments 🕒

Repository with codes, experiments and possible annotations conducted during the Real-Time Systems study.

## Programs

- [x] [Time](./src/time/);
- [x] [Sleep](./src/sleep/);
- [x] [localtime](./src/localtime/);
- [x] [gmtime](./src/gmtime/);
- [x] [bdaytime](./src/bdaytime/);
- [x] [clock](./src/clock/);

## Running the Program Using the `bin/run` Script 🚀

```bash
cd path/this/repo # Navigate to the repository directory
chmod +x bin/run # Ensure that the script has the necessary execute permissions
bin/run time # use -b to force build the program before executing "bin/run time -b"
```

## Manual Execution Programs Using CMake 🛠️

```bash
cd path/this/repo
cp template/CMakeLists.txt.example src/project/CMakeLists.txt # copy and configure/edit CMakeLists.txt file
cd src/project
mkdir build
cd build
cmake ..
make
./main
```

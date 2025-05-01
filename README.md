## Linux Process Monitor 
A lightweight `top`-like process monitor written in C, featuring real-time process listing, resource monitoring, and interactive controls.

![Demo](assets/demo.gif)

## Build and Run
**Prerequisites**:
- **CMake** (version 3.1 or higher) 
- **C compiler** (e.g., GCC, Clang)
- Ncurses library

### Build Instructions
1. Clone the repository
	```sh 
	git clone https://github.com/<your-username>/LPM
	cd LPM
	```
 <br>
 
2. Run the build script
	`./build.sh`
> **Note:** If you get a "Permission denied" error, make the script executable first:
> ```bash
> chmod +x build.sh
<br>
  
3. Run the application.
	`./build/lpm`

## Testing
Run the test suite:
```sh
  cd build
  ctest --output-on-failure
```

## License

This project is licensed under the MIT License. See the [LICENSE](./LICENSE) file for more details.

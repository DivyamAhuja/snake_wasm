# Snake - WebAssembly

Implementation of basic snake game in using olcPixelGameEngine

https://divyamahuja.github.io/snake_wasm

## Building and Running

To Build and Run on Windows.

```
cmake -S . -B ./build -G "Unix Makefiles"

or

cmake -S . -B ./build
```

To Run on Web using WebAssembly

```
cmake -S . -B ./wasm -G "Unix Makefiles" -DBUILD_WASM=ON

or

cmake -S . -B ./wasm -DBUILD_WASM=ON
```

> or maybe just emconfigure cmake and run emmake. Maybe?

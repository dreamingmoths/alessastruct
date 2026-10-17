# alessastruct

Alessastruct is a tool that aims to translate C data types to [Kaitai Struct](https://kaitai.io/).

It converts an existing C project to binary parsers in over a dozen supported
languages. Once the data is parsed, it can be edited or written back out.

Built with decompilation projects in mind, it's intended to automate the process
of data migration from binary to C. (However, a tool for writing Kaitai back to
C is not yet included in this repository.)

## building

Alessastruct is a Clang frontend tool, so it requires the [LLVM project](https://github.com/llvm/llvm-project) to build.

Please follow step zero of the tutorial here for a full introduction:

https://clang.llvm.org/docs/LibASTMatchersTutorial.html

Clone this repository into `clang-tools-extra`, then run the build.

```sh
cd clang-tools-extra
git clone https://github.com/dreamingmoths/alessastruct
ninja
```

The executable should appear at `build/bin/alessastruct`.

## usage

Alessastruct takes in a C source or header file.

In order for struct layouts to be accurate, you need to pass the right arguments
to Clang for your target, for example:

```sh
alessastruct structs.h -- --target=x86_64
```

Any arguments past the `--` separator are for the Clang frontend, while those
before it go to Alessastruct.

Since this project was built for
[memory-of-alessa](https://github.com/dreamingmoths/memory-of-alessa), it
supports a PlayStation 2 target:

```sh
alessastruct --platform=ps2 silent-hill-3/src/sh3.h          \
    -- -Iinclude -Isilent-hill-3/include -Isilent-hill-3/src \
    -std=gnu89 -fshort-enums
```


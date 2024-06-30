# luatest

The purpose of this repository is for me to learn about developing
C/C++ in VSCode, and to use it to call LUAJIT.

I chose the [MIT LICENSE](LICENSE) because that's what LUAJIT uses.

## Setup

> NOTE: This is after writing 'test4', the README.md files in that
folder and earlier tests may have different instructions, but
these should work. 

This uses luajit as a submodule purely for convenience, to enable
relative paths for the builds for the include and library folders.
To include it, clone with `--recurse-submodules`, or after you
clone without that use `git submodule update --init`.  Sample:

    git clone --recurse-submodules https://github.com/JasonGoemaat/luatest.git

To build LUAJIT, open a `Developer Command Prompt for VS 2022`, this means
you should have some version of visual studio 2022 installed.  Change to the
`luajit/src` subdirectory and run this to build it for static linking:

    msvcbuild.bat static

This is what the line looks like in the developer command prompt
because I cloned the repository into `c:\git\luatest2`:

    C:\git\luatest2\luajit\src>msvcbuild.bat static

## Building/Running

1. Clone repository with `--recurse-submodules` option
    * If you've already cloned it without, run `git submodules --init update`
2. Have Visual Studio 2022 installed with C/C++ functionality
3. Start "Developer Command Prompt for VS 2022"
    * If you haven't once aleady, change to the `luajit/src` directory and run `msvcbuild.bat static`
4. Start vs code from the developer command prompt in the root directory with `code .`
5. Open one of the `.c` files, the `test1/main.c` for instance
6. Hit the 'play' button at the top-right of the source window to build and debug
    * The output should now be in a 'bin' subdirectory where the `.c` file is.

I use VSCode with the 'C/C++' extension from Microsoft.  While using a file such as `test1/main.c`
I saw the play button on the top-right of the editor.   This lets you build and run each c file
while editing it.  The first time it created `./vscode/c_cpp_properties.json` for
the extension and `.vscode/tasks.json` for the build.  I had to add these arguments to
`cl.exe` in `tasks.json` to add the `luajit/src`subdirectory for includes and libraries
and add the `.lib` files:

    "/I${workspaceFolder}/luajit/src",
    "/link \"/LIBPATH:${workspaceFolder}/luajit/src\" lua51.lib luajit.lib"

I also changed the `/Fe` option and added other options so output files would be created in the
`bin` subdirectory under the `.c` file (did this after the test4 commit, but after that
it should work for earlier ones also):

    "/Fe${fileDirname}\\bin\\${fileBasenameNoExtension}.exe",
    "/Fd${fileDirname}\\bin\\${fileBasenameNoExtension}.pdb",
    "/Fo${fileDirname}\\bin\\${fileBasenameNoExtension}.obj",
    "/Fe${fileDirname}\\bin\\${fileBasenameNoExtension}.exe",

To debug in visual studio, use your developer command prompt and change to the directory and run:

    DevEnv /debugexe main.exe

## Possible problems

1. You didn't clone the luajit submodule, run `git submodules --init update`
2. You didn't start VS Code from the developer command prompt to set compiler environment variables
3. ??? - let me know if you have other issues
4. Compiling 64-bit, use `x64 native tools Command Prompt for VS 2022` when opening VS Code
    * Make sure to include `<stdlib.h>` when doing malloc or it assumes the return value is int.
    * Same for ALL libraries I assume for functions that return anything other than 32 bit int in 64 bit mode...
5. May use 32 bit GC in lua, compile with `msvcbuild.bat nogc64 static` to compile a 64 bit binary but use 32 bit memory for the linux VM which makes it use 32 bit registers more and use less memory.
6. If it can't find 'main.lua', make sure it's in the right directory.  Running inside VS Code uses the same folder as main.c, while using the exe in the bin directory looks in the bin directory.

## Links

LuaJIT internals - VERY detailed information:  https://0xbigshaq.github.io/2022/08/23/lua-jit/ Can
find '\x1bLJ' which seems to be a vm bytecode definition, but not sure since there are some diffs.
But including size it contains constant strings I think.   When I get to the opcodes the offsets
are messed up I *think*.   At least they don't make sense with what follows.

## Notes

Possibly disable `-DLUAJIT_ENABLE_GC64` to get the 32 bit register usage in certain places?  Actually
the docs have changed, now use `-DLUAJIT_DISABLE_GC64` to disable this.   Let's try it...  Ah, build
like this:

    msvcbuild.bat nogc64 static

# Test 2

> NOTE: You have to copy 'lua51.dll' from your luajit build to the same
directory as main.exe for this to work, or add it somewhere in your path.

Now is where I usually fail.   I want to build against the 
LUAJIT libraries.  Currently I am working with this
directory structure:

* `c:\git\luajit` - where I cloned luajit from https://luajit.org/git/luajit.git
    * `c:\git\luajit\src` - where I ran `msvcbuild.bat` from, which ran like a charm and created libraries and exes
        * I could run 'luajit.exe' as a REPL and type `print('Hello, world!')` and it ran it as lua.
        * This also contains `luajit.h` and `luajit.lib` so I think I want to use this as an include folder and library folder
* `c:\git\luatest\test2` - this folder where I'm trying to build and include luajit

MANY thanks for [this post by Victor](https://stackoverflow.com/a/68772283/369792) on stack overflow,
I had to edit the `c:\git\luatest\.vscode\tasks.json` file to add an arg `/IC:/git/luajit/src`
to add the include path where luajit has it's `luajit.h` file.  This is in addition
to adding it to `.vscode/c_cpp_properties.json` for the extension.

```json
    "type": "cppbuild",
    "label": "C/C++: cl.exe build active file",
    "command": "cl.exe",
    "args": [
        "/Zi",
        "/EHsc",
        "/nologo",
        "/Fe${fileDirname}\\${fileBasenameNoExtension}.exe",
        "${file}",
        "/Ic:/git/luajit/src"
    ],
```

Ok, I'm going to try a super simple program than runs the first arg on the command line,
thanks to [this page](https://cellux.github.io/articles/introduction-to-luajit-part-1/)

Ok, no freaking help for a noob like me.   I know programming, but the build systems
are all just so complex, that's why I quit programming it.  It's hard to find help
or tutorials online on how to do just the simplest things.  I ended up adding
another arg in my tasks.json:

    "/link \"/LIBPATH:C:/git/luajit/src\" lua51.lib"

That got it to build, then I had to copy `lua51.dll` because I built it static.
Then it works!  I can build using 'CTRL+SHIFT+B' when I have `main.c` open.
Then from the command line I can run this from my git bash:

    /c/git/luatest/test2 (master)
    $ ./main.exe 'print("Hello from lua")'

And from powershell:

    PS C:\git\luatest\test2> ./main.exe 'print("Hello from lua")'
    App running!  
    Hello from lua

And from a command prompt:

    C:\git\luatest\test2>main.exe "print('Hello from lua')"
    App running!
    Hello from lua

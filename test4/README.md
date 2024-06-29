# Test 4 - luajit static and as submodule

For this I want to build lujit as a static library, and also include
it as a submodule in this project.  This means I will change the
include and library paths and no longer have to copy the dll to
the same folder as `main.exe`.  If using this build system with
previous commits, you will need to modify the json files in
the `.vscode` dirctory as here.

First, adding it as a submodule (run from root of this repo):

    git submodule add https://luajit.org/git/luajit.git luajit

Then open a `Developer Command Prompt for VS 2022` and go to
`luajit/src` and run this:

    msvcbuild.bat static

Now I think I can actually remove this line from `c_cpp_properties.json` because
all subdirectories of my workspace folder are included:

    "c:\\git\\luajit\\src"

And change these lines in `.vscode/tasks.json`:

    "/I${workspaceFolder}/luajit/src",
    "/link \"/LIBPATH:${workspaceFolder}/luajit/src\" lua51.lib luajit.lib"

Hey, that worked pretty smoothly!  After that I debug just fine,
but my `main.exe` is now 1329664 bytes instead of 502784 bytes, but that's
ok!


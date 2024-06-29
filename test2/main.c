#include <stdio.h>
#include <luajit.h>
#include <lauxlib.h>

int main(int argc, char **argv)
{
    printf("App running!\n");

    if (argc > 1)
    {
        lua_State *L = luaL_newstate();
        luaL_openlibs(L);
        luaL_dostring(L, argv[1]);
        lua_close(L);
    }
    else
    {
        fprintf(stderr, "Usage: %s [lua-code]\n", argv[0]);
    }
}

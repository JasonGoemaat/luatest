#include <stdio.h>
#include <luajit.h>
#include <lauxlib.h>

int main(int argc, char **argv)
{
    printf("test3/main.exe running!\r\n");
    // return 0;
    char *buffer = 0;
    long length;
    FILE *f = fopen("main.lua", "rb");
    if (f)
    {
        fseek(f, 0, SEEK_END);
        length = ftell(f);
        fseek(f, 0, SEEK_SET);
        buffer = (char *)malloc(length+2);
        if (buffer)
        {
            fread(buffer, 1, length, f);
            buffer[length] = '\0';
        }
        fclose(f);
    }
    if (buffer)
    {
        lua_State *L = luaL_newstate();
        luaL_openlibs(L);
        luaL_dostring(L, buffer);
        lua_close(L);
        return 0;
    } else {
        fprintf(stderr, "Unable to open 'main.lua'!");
        return -1;
    }
}

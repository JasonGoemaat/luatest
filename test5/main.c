#include <stdio.h>
#include <stdlib.h>
#include <luajit.h>
#include <lauxlib.h>

int main(int argc, char **argv)
{
    printf("test4/main.exe running!\r\n");
    // return 0;
    char *buffer = 0;
    long length;
    size_t buffer_size;
    FILE *f = fopen("main.lua", "rb");
    if (f)
    {
        fseek(f, 0, SEEK_END);
        length = ftell(f);
        fseek(f, 0, SEEK_SET);
        buffer_size = length;
        buffer_size += 2;
        buffer = (char *)malloc(buffer_size);
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
        do_repl(L);
        lua_close(L);
        return 0;
    } else {
        fprintf(stderr, "Unable to open 'main.lua'!");
        return -1;
    }
}

int do_repl(lua_State *L) {
    char buffer[500];
    while (1) {
        printf("Enter LUA command\r\n");
        printf("> ");
        fgets(buffer, 500, stdin);
        int len = strlen(buffer);
        printf("\r\nYou typed %d characters...\r\n", len);
        if (len <= 1) return 0; // 1 byte for null terminator
        luaL_dostring(L, buffer);
    }
}
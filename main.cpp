#include <iostream>

extern "C"
{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#include "functions.hpp"
#include "LuaPlayer.hpp"

void report_errors(lua_State* L, int status)
{
    if (status != 0)
    {
        std::cerr << "[ERROR] " << lua_tostring(L, -1) << std::endl;
        lua_pop(L, 1);
    }
}

int main()
{
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    // Functions
    lua_register(L, "info", lua_info);

    // Objets
    luaopen_Player(L);

    int status = luaL_loadfile(L, "ia.lua");
    if (status == 0)
    {
        status = lua_pcall(L, 0, LUA_MULTRET, 0);
    }
    report_errors(L, status);

    /*if (luaL_dofile(L, "ia.lua"))
        std::cout << lua_tostring(L, -1) << std::endl;*/

    lua_close(L);
}


find_package(Lua51)
if (LUA51_FOUND)
	include_directories(${LUA_INCLUDE_DIR})
	add_module(lua FunctionHooks lua_int NWNXLua plugin-lua)
	target_link_libraries(lua ${LUA_LIBRARIES})
else (LUA51_FOUND)
	message(WARNING "Cannot find lua5.1 libraries")
endif (LUA51_FOUND)

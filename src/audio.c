#include "allua/audio.h"
#include <allegro5/kcm_audio.h>
#include <stdio.h>

#define AUDIO_STRING "audio"

/* Methods
 * */
static int allua_audio_install(lua_State *L)
{
	int mode = luaL_checkint(L, 1);
	lua_pushboolean(L, al_install_audio(mode));
	return 1;
}

static int allua_audio_uninstall(lua_State *L)
{
	al_uninstall_audio();
	return 0;
}

static int allua_audio_reserve_samples(lua_State *L)
{
	int n = luaL_checkint(L, 1);
	lua_pushboolean(L, al_reserve_samples(n));
	return 1;
}

static const luaL_reg allua_audio_methods[] = {
	{"install", allua_audio_install},
	{"uninstall", allua_audio_uninstall},
	{"reserve_samples", allua_audio_reserve_samples},
	{0,0}
};

/* Other attributes
 * */
void allua_audio_set_attributes(lua_State *L)
{
	lua_pushinteger(L, ALLEGRO_AUDIO_DRIVER_AUTODETECT);
	lua_setfield(L, -2, "AUDIO_DRIVER_AUTODETECT");
	lua_pushinteger(L, ALLEGRO_AUDIO_DRIVER_OPENAL);
	lua_setfield(L, -2, "AUDIO_DRIVER_OPENAL");
	lua_pushinteger(L, ALLEGRO_AUDIO_DRIVER_ALSA);
	lua_setfield(L, -2, "AUDIO_DRIVER_ALSA");
	lua_pushinteger(L, ALLEGRO_AUDIO_DRIVER_DSOUND);
	lua_setfield(L, -2, "AUDIO_DRIVER_DSOUND");
	lua_pushinteger(L, ALLEGRO_AUDIO_DRIVER_OSS);
	lua_setfield(L, -2, "AUDIO_DRIVER_OSS");
}

/* Register
 * */
int allua_register_audio (lua_State *L)
{
	lua_newtable(L);
	luaL_register(L, NULL, allua_audio_methods);  /* create methods table,
												add it to the globals */

	allua_audio_set_attributes(L);

	lua_setfield(L, -2, AUDIO_STRING);
	return 0;                           /* return methods on the stack */
}

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

	lua_pushinteger(L, ALLEGRO_AUDIO_DEPTH_INT8);
	lua_setfield(L, -2, "AUDIO_DEPTH_INT8");
	lua_pushinteger(L, ALLEGRO_AUDIO_DEPTH_INT16);
	lua_setfield(L, -2, "AUDIO_DEPTH_INT16");
	lua_pushinteger(L, ALLEGRO_AUDIO_DEPTH_INT24);
	lua_setfield(L, -2, "AUDIO_DEPTH_INT24");
	lua_pushinteger(L, ALLEGRO_AUDIO_DEPTH_FLOAT32);
	lua_setfield(L, -2, "AUDIO_DEPTH_FLOAT32");
	lua_pushinteger(L, ALLEGRO_AUDIO_DEPTH_UNSIGNED);
	lua_setfield(L, -2, "AUDIO_DEPTH_UNSIGNED");
	lua_pushinteger(L, ALLEGRO_AUDIO_DEPTH_UINT8);
	lua_setfield(L, -2, "AUDIO_DEPTH_UINT8");
	lua_pushinteger(L, ALLEGRO_AUDIO_DEPTH_UINT16);
	lua_setfield(L, -2, "AUDIO_DEPTH_UINT16");
	lua_pushinteger(L, ALLEGRO_AUDIO_DEPTH_UINT24);
	lua_setfield(L, -2, "AUDIO_DEPTH_UINT24");

	lua_pushinteger(L, ALLEGRO_CHANNEL_CONF_1);
	lua_setfield(L, -2, "CHANNEL_CONF_1");
	lua_pushinteger(L, ALLEGRO_CHANNEL_CONF_2);
	lua_setfield(L, -2, "CHANNEL_CONF_2");
	lua_pushinteger(L, ALLEGRO_CHANNEL_CONF_3);
	lua_setfield(L, -2, "CHANNEL_CONF_3");
	lua_pushinteger(L, ALLEGRO_CHANNEL_CONF_4);
	lua_setfield(L, -2, "CHANNEL_CONF_4");
	lua_pushinteger(L, ALLEGRO_CHANNEL_CONF_5_1);
	lua_setfield(L, -2, "CHANNEL_CONF_5_1");
	lua_pushinteger(L, ALLEGRO_CHANNEL_CONF_6_1);
	lua_setfield(L, -2, "CHANNEL_CONF_6_1");
	lua_pushinteger(L, ALLEGRO_CHANNEL_CONF_7_1);
	lua_setfield(L, -2, "CHANNEL_CONF_7_1");

	lua_pushinteger(L, ALLEGRO_PLAYMODE_ONCE);
	lua_setfield(L, -2, "PLAYMODE_ONCE");
	lua_pushinteger(L, ALLEGRO_PLAYMODE_LOOP);
	lua_setfield(L, -2, "PLAYMODE_LOOP");
	lua_pushinteger(L, ALLEGRO_PLAYMODE_BIDIR);
	lua_setfield(L, -2, "PLAYMODE_BIDIR");

	lua_pushinteger(L, ALLEGRO_MIXER_QUALITY_POINT);
	lua_setfield(L, -2, "MIXER_QUALITY_POINT");
	lua_pushinteger(L, ALLEGRO_MIXER_QUALITY_LINEAR);
	lua_setfield(L, -2, "MIXER_QUALITY_LINEAR");
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

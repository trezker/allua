#include "primitives.h"
#include "color.h"
#include <allegro5/a5_primitives.h>
#include <stdio.h>

#define PRIMITIVES "Primitives"

/* Methods
 * */
static int al_lua_draw_line_ex(lua_State *L)
{
	float x1 = luaL_checknumber(L, 1);
	float y1 = luaL_checknumber(L, 2);
	float x2 = luaL_checknumber(L, 3);
	float y2 = luaL_checknumber(L, 4);
	AL_Color color = al_lua_check_color(L, 5);
	float thickness = luaL_checknumber(L, 6);
	al_draw_line_ex(x1, y1, x2, y2, color, thickness);
	return 0;
}

static void al_lua_draw_triangle_common(lua_State *L, bool filled)
{
	float x1 = luaL_checknumber(L, 1);
	float y1 = luaL_checknumber(L, 2);
	float x2 = luaL_checknumber(L, 3);
	float y2 = luaL_checknumber(L, 4);
	float x3 = luaL_checknumber(L, 5);
	float y3 = luaL_checknumber(L, 6);
	AL_Color color = al_lua_check_color(L, 7);

	if(!filled)
	{
		float thickness = luaL_checknumber(L, 8);
		al_draw_triangle(x1, y1, x2, y2, x3, y3, color, thickness);
	}
	else
	{
		al_draw_filled_triangle(x1, y1, x2, y2, x3, y3, color);
	}
}
static int al_lua_draw_triangle(lua_State *L)
{
	al_lua_draw_triangle_common(L, false);
	return 0;
}
static int al_lua_draw_filled_triangle(lua_State *L)
{
	al_lua_draw_triangle_common(L, true);
	return 0;
}

static void al_lua_draw_rectangle_common(lua_State *L, bool filled, bool ellipse)
{
	float x1 = luaL_checknumber(L, 1);
	float y1 = luaL_checknumber(L, 2);
	float x2 = luaL_checknumber(L, 3);
	float y2 = luaL_checknumber(L, 4);
	AL_Color color = al_lua_check_color(L, 5);

	if(!filled)
	{
		float thickness = luaL_checknumber(L, 6);
		if(ellipse)
			al_draw_ellipse(x1, y1, x2, y2, color, thickness);
		else
			al_draw_rectangle_ex(x1, y1, x2, y2, color, thickness);
	}
	else
	{
		if(ellipse)
			al_draw_filled_ellipse(x1, y1, x2, y2, color);
		else
			al_draw_filled_rectangle(x1, y1, x2, y2, color);
	}
}
static int al_lua_draw_rectangle_ex(lua_State *L)
{
	al_lua_draw_rectangle_common(L, false, false);
	return 0;
}
static int al_lua_draw_filled_rectangle(lua_State *L)
{
	al_lua_draw_rectangle_common(L, true, false);
	return 0;
}
static int al_lua_draw_ellipse(lua_State *L)
{
	al_lua_draw_rectangle_common(L, false, true);
	return 0;
}
static int al_lua_draw_filled_ellipse(lua_State *L)
{
	al_lua_draw_rectangle_common(L, true, true);
	return 0;
}

static void al_lua_draw_circle_common(lua_State *L, bool filled)
{
	float x1 = luaL_checknumber(L, 1);
	float y1 = luaL_checknumber(L, 2);
	float r = luaL_checknumber(L, 3);
	AL_Color color = al_lua_check_color(L, 4);

	if(!filled)
	{
		float thickness = luaL_checknumber(L, 5);
		al_draw_circle(x1, y1, r, color, thickness);
	}
	else
	{
		al_draw_filled_circle(x1, y1, r, color);
	}
}
static int al_lua_draw_circle(lua_State *L)
{
	al_lua_draw_circle_common(L, false);
	return 0;
}
static int al_lua_draw_filled_circle(lua_State *L)
{
	al_lua_draw_circle_common(L, true);
	return 0;
}

static const luaL_reg Primitives_methods[] = {
  {"draw_line_ex",           al_lua_draw_line_ex},
  {"draw_triangle",           al_lua_draw_triangle},
  {"draw_filled_triangle",           al_lua_draw_filled_triangle},
  {"draw_rectangle_ex",           al_lua_draw_rectangle_ex},
  {"draw_filled_rectangle",           al_lua_draw_filled_rectangle},
  {"draw_ellipse",           al_lua_draw_ellipse},
  {"draw_filled_ellipse",           al_lua_draw_filled_ellipse},
  {"draw_circle",           al_lua_draw_circle},
  {"draw_filled_circle",           al_lua_draw_filled_circle},
  {0,0}
};

/* Register
 * */
int al_lua_register_primitives (lua_State *L)
{
  lua_newtable(L);
  luaL_register(L, NULL, Primitives_methods);  /* create methods table,
                                                add it to the globals */

  lua_setfield(L, -2, PRIMITIVES);
  return 0;                           /* return methods on the stack */
}

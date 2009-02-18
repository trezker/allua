import glob
import sys
import os

files = glob.glob('src/*.c')
files = [x.replace("src", "obj") for x in files]

env = Environment(CPPPATH = ['include'])

def CheckLua(context):
	context.Message("Checking for Lua 5.1...")
	have_pkg = context.TryAction("pkg-config lua5.1")[0]
	if have_pkg:
		context.env.ParseConfig("pkg-config lua5.1 --cflags --libs")
	else:
		context.env.Append(LIBS = ["lua", "m"])
	result = context.TryRun("""
	#include <lua.h>
	int main(void) {
		lua_open();
		return 0;
	}
	""", ".c")[0]
	context.Result(result)
	return result

conf = Configure(env, custom_tests = {"CheckLua" : CheckLua})
if not conf.CheckLua():
	sys.stderr.write("Lua 5.1 not found, please get it from lua.org.\n")
	Exit(1)
env = conf.Finish()

debug = ARGUMENTS.get('debug', 0)
if int(debug):
	env.Append(CCFLAGS = '-g')
env.Append(CCFLAGS = '-Wall')

env.BuildDir('obj','src', duplicate = 0)
env.Append(LIBS=['allegro-4.9.9','a5_iio-4.9.9','a5_font-4.9.9','a5_ttf-4.9.9','a5_primitives-4.9.9'])
env.StaticLibrary('lib/al_lua',files)


env.Append(LINKFLAGS = '-Llib')

env.Append(LIBS = 'al_lua')
env.Program('test/test', 'test/test.c')

rebuild_docs = ARGUMENTS.get('rebuild_docs', 0)
if int(rebuild_docs):
	os.system("../NaturalDocs/NaturalDocs -i include -i src -i test -i docs/nd -o HTML docs/html -p nd -ro")
else:
	os.system("../NaturalDocs/NaturalDocs -i include -i src -i test -i docs/nd -o HTML docs/html -p nd")

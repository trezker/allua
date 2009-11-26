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

#conf = Configure(env, custom_tests = {"CheckLua" : CheckLua})
#if not conf.CheckLua():
#	sys.stderr.write("Lua 5.1 not found, please get it from lua.org.\n")
#	Exit(1)
#env = conf.Finish()

debug = ARGUMENTS.get('debug', 0)
if int(debug):
	env.Append(CCFLAGS = '-g')
env.Append(CCFLAGS = '-Wall')

env.BuildDir('obj','src', duplicate = 0)
env.Append(LIBS=['lua','allegro-4.9.16','allegro_image-4.9.16','allegro_font-4.9.16','allegro_ttf-4.9.16','allegro_primitives-4.9.16','allegro_audio-4.9.16','allegro_vorbis-4.9.16','allegro_dialog-4.9.16'])
#allua = env.StaticLibrary('lib/allua',files)
allua_shared = env.SharedLibrary('lib/allua',files)

#env.Append(LIBS = [allua_shared])
#test_exe = env.Program('test/test', 'test/test.c')

##### Install #####
env.Alias('install', '/usr/local')
#env.Install('/usr/local/lib', allua)
env.Install('/usr/local/lib', allua_shared)
include_files = glob.glob('include/allua/*.h')
env.Install('/usr/local/include/allua', include_files)
env.Install('/usr/local/lib/lua/5.1', allua_shared)


rebuild_docs = ARGUMENTS.get('rebuild_docs', 0)
if int(rebuild_docs):
	os.system("../NaturalDocs/NaturalDocs -i include -i src -i test -i docs/nd -o HTML docs/html -p nd -ro")
else:
	os.system("../NaturalDocs/NaturalDocs -i include -i src -i test -i docs/nd -o HTML docs/html -p nd")
	
# Unit tests

def runUnitTest(env,target,source):
	os.system("cp lib/liballua.so test/liballua.so")
	os.system("cd test && lua unittest_main.lua")

Command("test.passed",'test',runUnitTest)

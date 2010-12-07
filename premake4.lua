lib_name = "allua"
dependencies = { "allegro", "allegro_image", "allegro_font", "allegro_ttf", "allegro_primitives", "allegro_audio", "allegro_acodec", "allegro_dialog" }

solution (lib_name)
	configurations { "Debug", "Release" }

	project (lib_name)
		kind "SharedLib"
		language "C"
		location "build"
		files { "src/*.c" }
		targetdir "build/lib"
		includedirs { "../include" }
		links (dependencies)
		flags { "ExtraWarnings", "FatalWarnings" }
--		postbuildcommands { "cp lib/liballua.so ../test/liballua.so", "cd ../test && lua unittest_main.lua" }

		
newaction {
	trigger     = "test",
	description = "Run tests",

	execute = function ()
		os.execute ("cp lib/liballua.so ../test/liballua.so")
		if not _OPTIONS["test"] then
			tests = os.matchfiles("test/*.lua")
			for index, name in pairs(tests) do
				os.execute ("lua " .. name)
				cmd = io.stdin:read'*l'
				if cmd == "q" then
					break;
				end
			end
		else
			os.execute ("lua test/" .. _OPTIONS["test"] .. ".lua")
		end
	end
}

newoption {
   trigger     = "dir",
   value       = "path",
   description = "Choose a path to install dir",
}

newoption {
   trigger     = "test",
   value       = "suit",
   description = "Choose a testing suit to run",
}

newaction {
	trigger     = "install",
	description = "Install the software",
	execute = function ()
		-- copy files, etc. here
		os.mkdir(_OPTIONS["dir"].."lib/");
		files = os.matchfiles("build/lib/*")
		print ("Installing lib files to " .. _OPTIONS["dir"] .."lib/")
		for k, f in pairs(files) do
			print ("Copying " .. f)
			os.copyfile(f, _OPTIONS["dir"].."lib/")
			if _OPTIONS["dir"] == "/usr/local/" then
				os.copyfile(f, "/usr/local/lib/lua/5.1/")
			end
		end
		os.mkdir(_OPTIONS["dir"].."include/"..lib_name.."/");
		files = os.matchfiles(lib_name.."/*")
		print ("Installing header files to " .. _OPTIONS["dir"] .."include/")
		for k, f in pairs(files) do
			print ("Copying " .. f)
			os.copyfile(f, _OPTIONS["dir"].."include/"..lib_name.."/")
		end
	end
}

newaction {
	trigger     = "docs",
	description = "Build documentation",
	execute = function ()
		os.execute("../NaturalDocs/NaturalDocs -i include -i src -i test -i docs/nd -o HTML docs/html -p nd -ro")
	end
}

if not _OPTIONS["dir"] then
   _OPTIONS["dir"] = "/usr/local/"
end

if not ("/" == _OPTIONS["dir"]:sub(_OPTIONS["dir"]:len())) then
	_OPTIONS["dir"] = _OPTIONS["dir"] .. "/"
end

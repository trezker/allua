Allua Read Me
=============

Allua is a binding of the Allegro 5.x game programming library to the powerful,
light, fast programming language that is Lua.

Building
--------

Requirements:

* Allegro 5.0.3 <http://www.liballeg.org/>
* Lua 5.1 <http://www.lua.org/>
* Premake 4.3 <http://industriousone.com/premake> to build the project
* NaturalDocs <http://www.naturaldocs.org/> (only if you want to build reference
  manual)
* luaunit <http://luaforge.net/> (only for unit tests) 

Instructions:

* Open a terminal and get to the Allua folder
* Enter `premake4 --help` for a list of possible build environments
* Enter `premake4 _YourBuildEnvironment_`
* Build the program with your selected build envrionment (i.e. `gmake`)
* Enter `premake4 install` to install Allua on a system that supports the
  filesystem heirarchy standard (i.e. Linux, OpenSolaris, or the BSDs)

Using Allua
-----------

You can run a Lua script that uses Allua simply by running `lua myscript.lua` if
you have the library (`liballua.so`, `allua.dll`, etc.) in your Lua search path.
`premake4 install` will install Allua into the search path on certain systems
listed in the previous section. You can also store the library in the same
directory as the script itself and it should work.

See naturoids.lua in the test folder for an example of Allua usage.


Documentation
-------------

Allua only provides a simple reference manual, for full explanation of all the
functions you should read Allegro's documentation at
<http://docs.liballeg.org/>.

A prebuilt version of the documentation is available for download here:
<http://github.com/trezker/allua/downloads>

You may also get NaturalDocs and build the documentation yourself, but that is
really only for people who wish edit the documentation.

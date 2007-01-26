package.name = "md5mesh2a2m"
package.kind = "exe"
package.language = "c++"

package.target = "tools/bin/md5mesh2a2m"

package.files = {
	matchfiles("*.h", "*.cpp")
}

if (OS == "windows") then
	tinsert(package.defines, {"WIN32", "_CONSOLE"})
	tinsert(package.config["Debug"].defines, { "_DEBUG" })
	tinsert(package.config["Release"].defines, { "NDEBUG" })
	tinsert(package.links, {"opengl32", "glu32", "glaux", "odbc32", "odbccp32", "SDL", "SDLmain", "SDL_net", "SDL_image", "ftgl_dynamic_MTD", "ode", "a2e"})
else
	tinsert(package.includepaths, {"../../a2e/src", "/usr/include", "/usr/include/freetype2", "/usr/include/FTGL", "/usr/include/ode", "/usr/include/opcode", "/usr/include/opcode/ICE"})
	tinsert(package.libpaths, {"jpeglib", "zlib", "../lib", findlib("GL"), findlib("GLU"), findlib("SDL"), findlib("ftgl"), findlib("ode"), findlib("lua"), findlib("xml2")})
	package.buildoptions = { "`sdl-config --cflags` -Wall -fopenmp -pipe -floop-optimize" }
	package.config["Release"].buildoptions = { " -march=i686" }
	package.config["Release_AMD"].buildoptions = { "-march=athlon64 -ftracer -O3 -msse3 -frename-registers -fweb -finline-functions" }
	tinsert(package.linkoptions, "-fPic `sdl-config --libs`")
	tinsert(package.links, {"GL", "GLU", "z", "jpeg", "a2e", "SDL_net", "SDL_image", "ode", "freetype", "ftgl", "lua", "xml2"})
end

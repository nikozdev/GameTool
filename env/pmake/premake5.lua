--[==[variables]==]--
name = "gametool"
--[=[directories]=]--
root = ".."
--[==[workspace]==]--
workspace               (name)
    --[=[globals]=]--
    startproject        ("game")
    location            (root)
    architecture        ("x64")
	configurations      {"work","test","play"}
	rtti                ("off")
	characterset        ("ascii")
	removeflags         ("excludefrombuild")
    warnings            ("off")
    --[=[compile]=]--
    buildoptions        {"/permissive","/MDd","/w"}
    --[=[filters]=]--
	filter              ("system:windows")
		systemversion   ("latest")
		defines         {"_GLFW_WIN32","GLFW_EXPOSE_NATIVE_WIN32"}
	filter              ("configurations:work")
		symbols         ("on")
		defines         {"DEBUG","GT_WORK"}
    filter              ("configurations:test")
		symbols         ("on")
		defines         {"DEBUG","GT_TEST"}
	filter              ("configurations:play")
		optimize        ("on")
		defines         {"NDEBUG","GT_PLAY"}
--[==[variables]==]--
name = "game"
--[=[directories]=]--
root = "../.."
dsrc = root.."/src"
dobj = root.."/obj"
dbin = root.."/bin"
dlib = root.."/lib"
drsc = root.."/rsc"
--[=[projects]=]--
project             (name)
    --[[globals]]--
    kind            ("consoleapp")
    location        (root)
    staticruntime   ("on")
    language        ("c++")
    cppdialect      ("c++20")
    --[[compile]]--
    objdir          (dobj)
    --pchheader       ("")
    --pchsource       ("")
    files           (dsrc.."/**")
    includedirs     (dlib.."**/src")
    --[[linking]]--
    targetdir       (dbin)
    links           {"opengl32","gdi32","Dwmapi","lua","glad","glfw","imgui"}
    --[[filters]]--
    filter          ("kind:consoleapp")
        defines     {"GT_BUILD_EXE"}
    filter          ("kind:staticlib")
        defines     {"GT_BUILD_LIB"}
    filter          ("kind:sharedlib")
        defines     {"GT_BUILD_DLL"}
--[[libraries]]--
include(dlib .. "/lua/env/pmake")
include(dlib .. "/glad/env/pmake")
include(dlib .. "/glfw/env/pmake")
include(dlib .. "/imgui/env/pmake")
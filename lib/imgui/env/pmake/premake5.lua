--[=[variables]=]--
name = "imgui"
--[=[projects]=]--
project             (name)
    --[[globals]]--
    kind            ("staticlib")
    location        (root)
    language        ("c++")
    cppdialect      ("c++20")
    --[[compile]]--
    objdir          (dobj)
    files           {dsrc.."/**"}
    includedirs     {dsrc,root.."/../glfw/src"}
    --[[linkage]]--
    targetdir       (dbin)
    links           {"opengl32","gdi32","glfw","glad"}
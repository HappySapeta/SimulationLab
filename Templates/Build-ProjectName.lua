project "<PROJECT_NAME>"
kind "ConsoleApp"
language "C++"
cppdialect "C++20"
targetdir "Binaries/%{cfg.buildcfg}"
staticruntime "off"

files
{
    "Include/**.h",
    "Source/**.cpp"
}

includedirs
{
    "Include/",
    "../Common/",
    "../../ThirdParty/Raylib/Include/",
}

links
{
    "raylib",
    "WinMM"
}

libdirs
{
    "../../ThirdParty/Raylib"    
}

targetdir("../Binaries/" .. OutputDir .. "/%{prj.name}")
objdir("../Binaries/Intermediates/" .. OutputDir .. "/%{prj.name}")

filter "system:windows"
systemversion "latest"
defines { "WINDOWS", "WIN32" }

filter "configurations:Debug"
defines { "DEBUG" }
runtime "Debug"
symbols "On"

filter "configurations:Release"
defines { "RELEASE" }
runtime "Release"
optimize "On"
symbols "Off"
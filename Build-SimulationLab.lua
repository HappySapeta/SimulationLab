--premake5.lua

workspace "SimulationLab"
architecture "x64"
configurations 
{ 
    "Debug", 
    "Release" 
}

startproject "WelcomeProject"

files { "Projects/Common/**.h" }

--Workspace-wide build options for MSVC
filter "system:windows"
buildoptions 
{
    "/EHsc",
    "/Zc:preprocessor",
    "/Zc:__cplusplus",
    "/D_ITERATOR_DEBUG_LEVEL=0"
}

filter "configurations:Debug"
linkoptions
{
    "/NODEFAULTLIB:msvcrt"
}

OutputDir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"

include "Projects/WelcomeProject/Build-WelcomeProject.lua"
include "Projects/Alpha/Build-Alpha.lua"

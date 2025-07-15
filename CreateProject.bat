@echo off

:: Check if running in a console window
if "%cmdcmdline%"=="" exit /b

:: Set up project path
set "base_dir=Projects"
set "new_project_path=%base_dir%\%~1"
set "new_source_path=%base_dir%\%~1\Source"
set "build-template=Templates\Build-ProjectName.lua"
set "source-template=Templates\ProjectName.cpp"

if "%~1"=="" (
	echo Error: Missing argument.
	echo Usage: CreateProject.bat ProjectName
	exit /b 1
)

:: Check if the target directory exists
if exist %new_project_path% (
	echo Error: Folder "%new_project_path%" already exists.
   exit /b 1
) 

mkdir %new_project_path% || (
	echo Failed to create folder.
	exit /b 1
)

mkdir %new_source_path% || (
	echo Failed to create source folder.
	exit /b 1
)

set filename=Build-%~1.lua
set build_script_path=%new_project_path%\%filename%
type nul > %build_script_path%

copy %build-template% %build_script_path% > nul
set "search=<PROJECT_NAME>"
set "replace=%~1"
powershell -Command "(Get-Content '%build_script_path%') -replace '%search%', '%replace%' | Set-Content '%build_script_path%'"

set cppfilename=%~1.cpp
set cpp_path=%new_source_path%\%cppfilename%
type nul > %cpp_path%
copy %source-template% %cpp_path% > nul

set "main_build_script=Build-SimulationLab.lua"
>> %main_build_script% echo include "Projects/%~1/%filename%"
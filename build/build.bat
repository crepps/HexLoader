rem Ensure MSBuild and other necessary tools are in the PATH
call "%VS_PATH%\VC\Auxiliary\Build\vcvarsall.bat" x64

rem Specify include directories
SET INCLUDE=%INCLUDE%;..\include\core;..\include\gui

rem Define _CRT_SECURE_NO_WARNINGS preprocessor macro
set CL=/D_CRT_SECURE_NO_WARNINGS

rem Build HexLoader
msbuild ..\HexLoader.vcxproj /p:Configuration=Release /t:Build /p:Platform="x64";OutDir=build

rem Move project subdirectory with post-build event
move /y ..\HexLoader .
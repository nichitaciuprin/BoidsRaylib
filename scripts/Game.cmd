@echo off

set thisFileName=%~n0
set root=%~f0\..\..
set gcc=%root%\deps\mingw64\bin\gcc.exe
set srcFile=%root%\src\%thisFileName%.c
set exeFile=%root%\build\%thisFileName%.exe
set include=%root%\include
set libs=-lraylib -ldloadhelper -lglmf32 -lm -lopengl32 -lgdi32 -lwinmm
set cfiles=^
%root%\src\AABB.c ^
%root%\src\Boid.c ^
%root%\src\GameWorld.c ^
%root%\src\GameWorldWindow.c ^
%root%\src\Helper.c ^
%root%\src\MyMath.c ^
%root%\src\MyVector2.c ^
%root%\src\MyWindow.c ^
%root%\src\Subgen.c
set flags=-g3 -O3 -Wall -std=c99 -Wno-missing-braces -pthread -m64

if not exist %root%\build mkdir %root%\build

%gcc% %srcFile% %cfiles% -I%include%\ %libs% -o %exeFile% %flags%

@REM Stop cmd if build failed
if %errorlevel% neq 0 exit /b %errorlevel%

%exeFile%

if %errorlevel% neq 0 echo ERROR!!!
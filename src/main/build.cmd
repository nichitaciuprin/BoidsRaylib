@echo off
setlocal

set root=%~f0\..\..\..
set deps=%root%\deps

@REM set mingw=%deps%\mingw\bin
@REM set path=%mingw%;

set flags=-g3 -O0 -Wall -std=c++17 -Wno-missing-braces -pthread -m64

set dep1=-I%deps%\raylib\include  -L%deps%\raylib\lib  -lraylib
set dep2=-I%deps%\Base\include                         -ldloadhelper -lglmf32 -lm -lopengl32 -lgdi32 -lwinmm -ld3d11 -ld3dcompiler
set depsAll=%dep1% %dep2%

if not exist build mkdir build

gcc main.cpp -o build/main.exe %flags% %depsAll%
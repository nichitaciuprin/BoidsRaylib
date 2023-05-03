@echo off
set cmdFileName=%~n0
set filePath=GameWorldTest\GameWorldTest
@REM del %filePath%.exe
gcc -S %filePath%.c ^
-lraylib ^
-ldloadhelper ^
-lglmf32 ^
-lm ^
-lopengl32 ^
-lgdi32 ^
-lwinmm ^
-o %filePath%.asm -g3 -O3 -Wall -std=c99 -Wno-missing-braces -pthread
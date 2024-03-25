@echo off
setlocal

set root=%~f0\..\..\..
set deps=%root%\deps

@REM set mingw=%deps%\mingw\bin
@REM set path=%mingw%;

gdb -q -ex=run -ex=backtrace -ex=quit --args build\main.exe

@REM build\main.exe
@REM if %errorlevel% neq 0 echo === ERROR === %errorlevel%
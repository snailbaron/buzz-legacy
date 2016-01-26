@echo off

set "base_dir=%~dp0"

if exist "%base_dir%bin" rmdir /s /q "%base_dir%bin"
if exist "%base_dir%obj" rmdir /s /q "%base_dir%obj"


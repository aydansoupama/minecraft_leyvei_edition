@echo off
setlocal

echo === 🔨 Building Minecraft Leyvei Edition ===

REM Chemin vers MinGW (adapter si différent)
set PATH=C:\msys64\ucrt64\bin;%PATH%

REM Nettoyer l'ancien build
if exist cmake-build-debug (
    rmdir /s /q cmake-build-debug
)

mkdir cmake-build-debug
cd cmake-build-debug

echo Configuring project with CMake...
cmake -G "MinGW Makefiles" ..

echo Compiling...
mingw32-make

if %errorlevel% neq 0 (
    echo ❌ Build failed!
    pause
    exit /b %errorlevel%
)

echo ✅ Build succeeded!
echo Running the game...
minecraft_leyvei_edition.exe

endlocal
pause

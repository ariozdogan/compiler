$ErrorActionPreference = "Stop"
$root = $PSScriptRoot

cmake -S $root -B "$root\build"
cmake --build "$root\build"

& "$root\build\compiler.exe" @args

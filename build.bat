@echo off

call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x64

SET includes=/Isrc /IC:\SDL2\SDL2\include /IC:\SDL2\SDL2_ttf\include /IC:\SDL2\SDL_gpu\include
SET libpaths=/LIBPATH:C:\SDL2\SDL2\lib\x64 /LIBPATH:C:\SDL2\SDL2_ttf\lib\x64 /LIBPATH:C:\SDL2\SDL_gpu\lib
SET libs=SDL2main.lib SDL2.lib SDL2_gpu.lib SDL2_ttf.lib winmm.lib
SET debugFlags=/D /DEBUG:FULL /Zi
SET optimisationFlags=/O2 /Oi /fp:fast
SET filename=someThing.exe

IF NOT EXIST obj mkdir obj

cd obj
cl /nologo /std:c++17 /EHsc /W2 %debugFlags% %includes% ../src/*.cpp /Fe../%filename% /link -incremental:no %libpaths% %libs%

IF EXIST "..\someThing.pdb" del "..\someThing.pdb"

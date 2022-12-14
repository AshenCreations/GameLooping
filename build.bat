@echo off

call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x64

SET includes=/Isrc /IC:\SDL2\SDL2\include /IC:\SDL2\SDL2_ttf\include /IC:\SDL2\SDL_gpu\include /IC:\SDL2\SDL2_mixer\include
SET libpaths=/LIBPATH:C:\SDL2\SDL2\lib\x64 /LIBPATH:C:\SDL2\SDL2_ttf\lib\x64 /LIBPATH:C:\SDL2\SDL_gpu\lib /LIBPATH:C:\SDL2\SDL2_mixer\lib\x64
SET libs=SDL2main.lib SDL2.lib SDL2_gpu.lib SDL2_ttf.lib SDL2_mixer.lib winmm.lib

SET debugFlags=/D /DEBUG:FULL /Zi
SET optimisationFlags=/O2
SET filename=GameLooping.exe

IF NOT EXIST obj mkdir obj
cd obj

cl /nologo /std:c++17 -Oi /W3 %debugFlags% %includes% ../src/*.cpp /Fe../%filename% /link -opt:ref -incremental:no %libpaths% %libs%
REM cl /nologo /std:c++17 -Oi %optimisationFlags% %includes% ../src/*.cpp /Fe../%filename% /link -opt:ref -incremental:no %libpaths% %libs%

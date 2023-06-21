@echo off

call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x64

SET includes=/Isrc /ID:\DEV\SDL2\SDL2\include /ID:\DEV\SDL2\SDL2_ttf\include /ID:\DEV\SDL2\SDL_gpu\include /ID:\DEV\SDL2\SDL2_mixer\include
SET libpaths=/LIBPATH:D:\DEV\SDL2\SDL2\lib\x64 /LIBPATH:D:\DEV\SDL2\SDL2_ttf\lib\x64 /LIBPATH:D:\DEV\SDL2\SDL_gpu\lib /LIBPATH:D:\DEV\SDL2\SDL2_mixer\lib\x64
SET libs=SDL2main.lib SDL2.lib SDL2_gpu.lib SDL2_ttf.lib SDL2_mixer.lib winmm.lib

SET debugFlags=/DEBUG:FULL /Zi
SET optimisationFlags=/O2
SET filename=GameLooping.exe

IF NOT EXIST obj mkdir obj
cd obj

REM cl /nologo /std:c++17 -Oi /fp:fast /W3 %debugFlags% %includes% ../src/*.cpp ../src/*.c /Fe../%filename% /link -opt:ref -incremental:no %libpaths% %libs%
cl /nologo /std:c++17 -Oi /fp:fast %optimisationFlags% %includes% ../src/*.cpp ../src/*.c /Fe../%filename% /link -opt:ref -incremental:no %libpaths% %libs%

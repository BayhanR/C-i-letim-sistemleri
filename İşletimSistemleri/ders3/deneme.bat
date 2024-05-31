@echo on
SET FILENAME=ex6
SET MINGW=%ProgramFiles%\mingw-w64\i686-8.1.0-win32-dworf-re-v6-rev6\mingw32\bin\gcc.exe
SET OBJOUMP=--------------------------------------------------------------------\objdump.exe
SET CD=%cd%
START /B /W """%MINGW%""%CD%\%FILENAME%.c"-c
START /B /W """%MINGW%"-S"%CD%\%FILENAME%.c"-f verbase-asm"%CD%\%FILENAME%.s"
START /B /W """%MINGW%""%CD%\%FILENAME%.o" -O "%cd%\%FILENAME%.exe"
PAUSE
START /B /W """%OBJOUMP%" -x -t -T -D -M inter -S "%CD%\%FILENAME%.o"
PAUSE
START ""CDM /k "%CD%\%FILENAME%.exe"
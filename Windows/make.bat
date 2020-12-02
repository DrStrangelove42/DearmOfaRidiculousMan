SET SDLPATH=D:\Program Files\SDL2\SDL2-2.0.12

REM If VisualStudio is not installed, you must install MS Build Tools. Then a folder like the following will contain MSBUILD :
REM SET MSBUILDPATH=C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\MSBuild\Current\Bin

REM This one is when Visual Studio is installed. Just change it a bit to match your installation :
SET MSBUILDPATH=C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\MSBuild\Current\Bin

"%MSBUILDPATH%\MSBUILD" /property:Configuration=Release
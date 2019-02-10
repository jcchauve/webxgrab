del *.tds
del *.bak
del *.obj
del *.~??
del ..\webxsrc.zip
md compact
copy webxgrab.exe compact
start /w D:\develop\aspack21\aspack.exe compact\webxgrab.exe
pkzip25 -add -passw=claudiosoft  ..\webxsrc  *.* -excl=*.exe -excl=*.obj -excl=*.txt -excl=*.tds -excl=*.dcu -excl=*.chm -excl=*.bak
pkzip25 -add -passw=claudiosoft  ..\webxsrc  -direct -recurse graphics32\*.* -excl=*.exe -excl=*.obj -excl=*.txt -excl=*.tds -excl=*.dcu -excl=*.chm -excl=*.bak -excl=*.zip
del ..\webxexe.zip
pkzip25 -add ..\webxexe compact\webxgrab.exe
copy ..\webxexe.zip \\claudio2\d\apache\apache\htdocs\webxgrab
copy ..\webxsrc.zip \\claudio2\d\apache\apache\htdocs\webxgrab
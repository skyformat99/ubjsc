set CYGWIN_ROOT=C:/cygwin
set CYGWIN_CACHE=C:/cygwin/var/cache/setup

appveyor DownloadFile http://cygwin.com/setup-x86.exe -FileName setup.exe
setup.exe -dN -R "%CYGWIN_ROOT%" -l "%CYGWIN_CACHE%" -P make
%CYGWIN_ROOT%/bin/bash -lc "cygcheck -dc cygwin"

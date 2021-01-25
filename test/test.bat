@echo off
echo test
del *.svg

SET CTG_EXE=..\bin\csvToGraph.exe
SET VERBOSE=

for %%t in (test*.csv) do echo %%t & %CTG_EXE% %VERBOSE% -o %%~nt.svg %%t
echo.
echo nopt
for %%t in (test*.csv) do echo %%t & %CTG_EXE% %VERBOSE% -nopt -o %%~nt.nopt.svg %%t
echo.
echo nolin
for %%t in (test*.csv) do echo %%t & %CTG_EXE% %VERBOSE% -nolin -o %%~nt.nl.svg %%t
echo.
echo nopap
for %%t in (test*.csv) do echo %%t & %CTG_EXE% %VERBOSE% -nopap -o %%~nt.npap.svg %%t
echo.
echo noax
for %%t in (test*.csv) do echo %%t & %CTG_EXE% %VERBOSE% -noax -o %%~nt.noax.svg %%t
echo.
echo nohead
for %%t in (test*.csv) do echo %%t & %CTG_EXE% %VERBOSE% -nohead -o %%~nt.nohead.svg %%t
echo.
echo xaxis
for %%t in (test*.csv) do echo %%t & %CTG_EXE% %VERBOSE% -x0 -o %%~nt.x0.svg %%t
echo.
echo yaxis
for %%t in (test*.csv) do echo %%t & %CTG_EXE% %VERBOSE% -y0 -o %%~nt.y0.svg %%t
echo.
echo xaxis yaxis
for %%t in (test*.csv) do echo %%t & %CTG_EXE% %VERBOSE% -x0 -y0 -o %%~nt.x0y0.svg %%t
echo.
echo nokey
for %%t in (test*.csv) do echo %%t & %CTG_EXE% %VERBOSE% -nokey -o %%~nt.nokey.svg %%t
echo.
echo nojoin
for %%t in (test*.csv) do echo %%t & %CTG_EXE% %VERBOSE% -nojoin -o %%~nt.nojoin.svg %%t

SET CTG_EXE=..\bin\
SET VERBOSE=


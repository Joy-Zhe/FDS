:loop
tester.exe
zqy.exe
lyz.exe
fc zqy.out lyz.out 
if not errorlevel 1 goto loop
pause
:end
@echo off

timeout /t 12
taskkill /f /t /im "t1.exe"
timeout /t 2
cat file1.txt
timeout /t 1
matlab -nodesktop -r rctest
rem matlab -nodesktop -r theory
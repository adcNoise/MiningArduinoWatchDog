@echo off
REM ���������� ������ SendSymbol � COM-���� ��� ������� NumPort ��� � TickTime ������
REM �� ����� ������ �� ���������


SET SendSymbol=A
SET NumPort=4
SET TickTime=3
MODE COM%NumPort% BAUD=19200>nul 2>&1



:mainloop


SET /p tmp="%SendSymbol%"<nul>\\.\COM%NumPort%
rem SET /p tmp="%SendSymbol%"<nul>test.txt


timeout /t %TickTime% >nul 2>&1
GOTO mainloop



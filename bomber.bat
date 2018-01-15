@echo off
rem Simple .bat script to run Bomberman game
rem so user doesn't have to manually re-run the 
rem executable after every game.

echo To stop playing Bomberman, you will have to
echo hit Ctrl-Alt-Del and choose to end 
echo "bomber - BOMBER" without quotes.
echo.
echo To exit now, press Ctrl-C
echo (Hold Ctrl while pressing C)
echo.
pause

:start
call bomber.exe
goto start


:end
:quit
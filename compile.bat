@set TCC_PATH=%~dp0

@"%TCC_PATH%tcc.exe" -w -nostdlib -DDEBUG -D__WIN32__ "-I%TCC_PATH%include\level0" "-I%TCC_PATH%include\level1" "-I%TCC_PATH%include\level2" ^
	%* ^
	"%TCC_PATH%lib\kernel32.def" ^
	"%TCC_PATH%lib\winmm.def" ^
	"%TCC_PATH%lib\gdi32.def" ^
	"%TCC_PATH%lib\user32.def" ^
	"%TCC_PATH%lib\opengl32.def" ^
	"%TCC_PATH%lib\avicap32.def" ^
	"%TCC_PATH%lib\ws2_32.def" ^
	"%TCC_PATH%lib\dxva2.def" ^
	"%TCC_PATH%lib\shell32.def" ^
	"%TCC_PATH%lib\ole32.def" ^
	"%TCC_PATH%lib\msvcrt.def" ^
	"%TCC_PATH%lib\avformat.def" ^
	"%TCC_PATH%lib\avcodec.def" ^
	"%TCC_PATH%lib\avutil.def" ^
	"%TCC_PATH%lib\swscale.def" ^
	|| pause
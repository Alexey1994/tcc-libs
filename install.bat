@assoc .c=
@ftype runnable_c_application=
@rem reg delete HKCR\.c /f
@rem reg delete HKCR\runnable_c_application /f
@rem reg delete HKCU\Software\Microsoft\Windows\CurrentVersion\Explorer\FileExts\.c /f
@rem reg delete HKCR\*\shell\��������஢��� /f
@rem reg delete "HKCR\*\shell\��������஢��� DLL" /f

@set TCC_PATH=%~dp0

@ftype runnable_c_application="%TCC_PATH%run.bat" "%%1" %%*
@assoc .c=runnable_c_application
@reg add "HKCR\runnable_c_application\shell\��������஢���\command" /f /t REG_SZ /d "\"%TCC_PATH%compile.bat\" \"%%1\""
@reg add "HKCR\runnable_c_application\shell\��������஢��� DLL\command" /f /t REG_SZ /d "\"%TCC_PATH%compile_DLL.bat\" \"%%1\""
@reg add "HKCR\runnable_c_application\shell\�९����\command" /f /t REG_SZ /d "\"%TCC_PATH%preprocess.bat\" \"%%1\""
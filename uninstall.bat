@assoc .c=
@ftype runnable_c_application=
@reg delete HKCR\.c /f
@reg delete HKCU\Software\Microsoft\Windows\CurrentVersion\Explorer\FileExts\.c /f
@reg delete HKCR\*\shell\Скомпилировать /f
@reg delete "HKCR\*\shell\Скомпилировать DLL" /f
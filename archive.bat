rem archive.bat
rem targets.txt�̃t�@�C��/�t�H���_��zip�����܂�
@echo off
setlocal

set OUT="%USERPROFILE%\Desktop\a.zip"

for /f %%t in (targets.txt) do (
    if exist %%t (
        7za.exe a %OUT% %%t
    )
)

# visible_file-extension.ps1
#  「登録されている拡張子は表示しない」を無効にします

Set-ItemProperty HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Explorer\Advanced -name "HideFileExt" -value "0"

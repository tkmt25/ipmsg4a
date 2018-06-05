# install_guest-additions.ps1
#  VBoxGuestAdditionをインストールします

Get-ChildItem "E:\cert\vbox*.cer" | ForEach-Object {
	E:\cert\VBoxCertUtil.exe add-trusted-publisher $_.FullName --root $_.FullName
}

Start-Process 'E:\VBoxWindowsAdditions.exe' '/S' -Wait

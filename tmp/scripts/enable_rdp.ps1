# enable-rdp.ps1
# �����[�g�f�X�N�g�b�v��L���ɂ��܂�

Set-ItemProperty -Path 'HKLM:\System\CurrentControlSet\Control\Terminal Server\WinStations\RDP-Tcp' -Name "UserAuthentication" -Value 0
Set-ItemProperty -Path 'HKLM:\System\CurrentControlSet\Control\Terminal Server'                     -Name "fDenyTSConnections" -Value 0

Enable-NetFirewallRule -DisplayGroup 'Remote Desktop*'

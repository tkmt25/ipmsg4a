# setup_proxy.ps1
# �Г��v���L�V��ݒ肵�܂�

$server = "192.168.2.254"
$port   = "3128"

# winhttp�v���L�V
netsh winhttp set proxy proxy-server="${server}:${port}"

# IE�v���L�V
$reg = 'HKCU:\SOFTWARE\Microsoft\Windows\CurrentVersion\Internet Settings'
Set-ItemProperty $reg -name "ProxyEnable" -Value "1"
Set-ItemProperty $reg -name "ProxyServer" -Value "${server}:${port}"
Set-ItemProperty $reg -name "ProxyOverride" -Value "*.contoso.com;<local>"


# �u�ݒ�������I�Ɍ��o����v�𖳌���
$reg = "${reg}\Connections"
$conf = (Get-ItemProperty -Path $reg).DefaultConnectionSettings
$conf[8] = $conf[8] -band 7 # DefaultConnectionSettins[8]��4bit��(0x08)�̃t���O��OFF
Set-ItemProperty -Path $reg -Name DefaultConnectionSettings -Value $conf

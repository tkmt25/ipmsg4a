# setup_proxy.ps1
# 社内プロキシを設定します

$server = "192.168.2.254"
$port   = "3128"

# winhttpプロキシ
netsh winhttp set proxy proxy-server="${server}:${port}"

# IEプロキシ
$reg = 'HKCU:\SOFTWARE\Microsoft\Windows\CurrentVersion\Internet Settings'
Set-ItemProperty $reg -name "ProxyEnable" -Value "1"
Set-ItemProperty $reg -name "ProxyServer" -Value "${server}:${port}"
Set-ItemProperty $reg -name "ProxyOverride" -Value "*.contoso.com;<local>"


# 「設定を自動的に検出する」を無効化
$reg = "${reg}\Connections"
$conf = (Get-ItemProperty -Path $reg).DefaultConnectionSettings
$conf[8] = $conf[8] -band 7 # DefaultConnectionSettins[8]の4bit目(0x08)のフラグをOFF
Set-ItemProperty -Path $reg -Name DefaultConnectionSettings -Value $conf

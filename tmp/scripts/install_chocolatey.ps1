# install_chocolatey.ps1 
#  chocolateyをインストールします

iex ((new-object net.webclient).DownloadString('https://chocolatey.org/install.ps1'))

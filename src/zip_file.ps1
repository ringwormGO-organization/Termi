clear
cd ..\

$Folder = 'windows-release\Release'
$File = 'windows-release\Release\Release.zip'

if (Test-Path -Path $Folder) {
    Remove-Item 'windows-release\Release\' -Recurse
}

if (Test-Path -Path $File) {
    Remove-Item 'windows-release\Release.zip' -Recurse
}

mkdir windows-release\Release\

Copy-Item 'src\Termi-Main\build\Release\*' -Destination 'windows-release\Release\'
Compress-Archive -Path windows-release\Release -DestinationPath windows-release\Release.zip

cd src

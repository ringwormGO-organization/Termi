clear
cd ..\

$Folder = 'windows-release\Debug'
$File = 'windows-release\Debug\Debug.zip'

if (Test-Path -Path $Folder) {
    Remove-Item 'windows-release\Debug\' -Recurse
}

if (Test-Path -Path $File) {
    Remove-Item 'windows-release\Debug.zip' -Recurse
}

mkdir windows-release\Debug\

Copy-Item 'src\Termi-Main\build\Debug\*' -Destination 'windows-release\Debug\'
Compress-Archive -Path windows-release\Debug -DestinationPath windows-release\Debug.zip

cd src

::======================================================
::             JKU create install script
::
::------------------------------------------------------
:: Author:   Fnuki
:: Date:     2020-04-18 20:39
:: Version:  0.1
::------------------------------------------------------
::
:: First attempt to create an installer for this project
:: to no longer manually copy and paste files
::======================================================

setlocal

set JKU_BUILD_CONFIGURATION=Debug
set JKU_BUILD_DIRECTORY=..\

"C:\Program Files (x86)\Inno Setup 6\ISCC.exe" jku_installer.iss

endlocal
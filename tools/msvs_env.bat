@echo off
:: Copyright (c) 2013 The Chromium Embedded Framework Authors. All rights
:: reserved. Use of this source code is governed by a BSD-style license
:: that can be found in the LICENSE file.

:: Set up the environment for use with MSVS tools and then execute whatever
:: was specified on the command-line.

set RC=

:: Support !! syntax for delayed variable expansion.
setlocal enabledelayedexpansion

:: Require that platform is passed as the first argument.
if "%1" == "win32" (
  set bits=32
) else if "%1" == "win64" (
  set bits=64
) else (
  echo ERROR: Please specify a target platform: win32 or win64
  set ERRORLEVEL=1
  goto end
)

:: Check if vcvars is already provided via the environment.
set vcvars="%CEF_VCVARS%"
if %vcvars% == "none" goto found_vcvars
if exist %vcvars% goto found_vcvars

:: Search for the default VS2017 installation path.
for %%x in ("%PROGRAMFILES(X86)%" "%PROGRAMFILES%") do (
  for %%y in (Professional Enterprise Community) do (
    set vcvars="%%~x\Microsoft Visual Studio\2017\%%y\VC\Auxiliary\Build\vcvars%bits%.bat"
    if exist !vcvars! goto found_vcvars
  )
)

echo ERROR: Failed to find vcvars
set ERRORLEVEL=1
goto end

:found_vcvars
echo vcvars:
echo %vcvars%

if not %vcvars% == "none" (
  :: Set this variable to keep VS2017 < 15.5 from changing the current working directory.
  set "VSCMD_START_DIR=%CD%"
  call %vcvars%
)

echo PATH:
echo %PATH%

:: Remove the first argument and execute the command.
for /f "tokens=1,* delims= " %%a in ("%*") do set ALL_BUT_FIRST=%%b
echo command:
echo %ALL_BUT_FIRST%
%ALL_BUT_FIRST%

:end
endlocal & set RC=%ERRORLEVEL%
goto omega

:returncode
exit /B %RC%

:omega
call :returncode %RC%

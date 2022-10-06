![header](Assets/Readme-Image/header.png)

## 🤔What is this?
**This is a software** or tool to make it easier to configure Windows with just a few clicks. The currently available configurations are **disabling or activating or custom settings windows updates** so that you feel comfortable and not disturbed by sudden updates, **blocking software** from being able to access data out of the network, and being able to use **custom DNS** for your device that **can unblock websites or others**, set whether you want to run check disk when starting windows or **turn off check disk when starting windows**. this software is portable so it can be run directly even on a flash disk provided the operating system must be windows and a 32bit or 64bit cpu.

<p align="center">
    <a href="https://safefileku.com/download/krFtHUCRYFWiJwf">
        <img src="https://img.shields.io/badge/Download-32Bits-brightgreen?style=for-the-badge&logo=mediafire&logoColor=white">
    </a>
    <a href="https://safefileku.com/download/8opZ6FBWRWz2lFA">
        <img src="https://img.shields.io/badge/Download-64Bits-brightgreen?style=for-the-badge&logo=mediafire&logoColor=white">
    </a>
</p>

### 📷Screenshoot
<p align="center">
    <img src="Assets\Readme-Image\screenshot-1.png">
    <img src="Assets\Readme-Image\screenshot-2.png">
    <img src="Assets\Readme-Image\screenshot-3.png">
    <img src="Assets\Readme-Image\screenshot-4.png">
    <img src="Assets\Readme-Image\screenshot-5.png">
</p>

### 🛠️How to use
- make sure you are using windows xp or later and cpu 32bit or 64bit
- download software from the download button at the top of the page
- run as usual (double click)

### 📜Release History
|Date|Version|Codename|
|-----------|---------|----------|
|21 Sep 2022|[v2022](https://github.com/felisware/Easy-Win-Config/releases/tag/v2022)|[SADCAT](https://github.com/felisware/Easy-Win-Config/releases/tag/v2022)|
|10 Oct 2022|[v2022.10](https://github.com/felisware/Easy-Win-Config/releases/tag/v2022.10)|[HACKTOBER FEST 2022](https://github.com/felisware/Easy-Win-Config/releases/tag/v2022.10)|

### ⚙️How to build
1. what you need is Compiler, Vscode, and wxwidgets library (static or dynamic)
2. adjust the settings in the `.vscode\c_cpp_properties.json`
```shell
  {
    "configurations": [
        {
            "name": "Win32",
            "includePath": [
                //add your wxwidgets library include (manual)
                "${env:WXWIN}\\include",
                "${env:WXWIN}\\lib\\gcc_lib_64\\mswu",

                //this default (automatic)
                "${workspaceFolder}\\include",
                "${workspaceFolder}/**"
            ],
            "defines": [
                "_DEBUG",
                "UNICODE",
                "_UNICODE"
            ],
            //select your compiler & intellisense (manual)
            "compilerPath": "C:/Program Files/mingw64/bin/g++.exe",
            "cStandard": "gnu17",
            "cppStandard": "gnu++17",
            "intelliSenseMode": "windows-gcc-x64"
        }
    ],
    "version": 4
}
```
3. adjust the build task in the `.vscode\c_cpp_properties.json`, you have to link to some libraries from Wxwidgets and windows.

Wxwidgets: `wxmsw32u_core` `wxbase32u` `wxpng` `wxzlib`
**note**: the number 32 is adjusted to the version of wxwigets you have.

Windows: if you use Wxwidgets dynamic link to `iphlpapi` and if you use Wxwidgets static link list is `comdlg32` `gdi32` `comctl32` `ole32` `oleaut32` `dmoguids` `uuid` `winspool` `z` `uxtheme` `oleacc` `shlwapi` `version` `iphlpapi`
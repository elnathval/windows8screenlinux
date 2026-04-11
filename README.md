# Windows 8 Start Screen for Linux Systems
An application for Linux that behaves like the Windows 8 Start Screen.

# Building
Clone this same repository either downloading through GitHub or using '''git clone'''.

## VSCode Users 
*Note* You must have a compiler toolchain installed in addition to vscode.

1. Download the quickstart
2. Rename the folder to your game name
3. Open the folder in VSCode
4. Run the build task ( CTRL+SHIFT+B or F5 )
5. You are good to go

## Other users
* Rename the folder to your game name
* CD into the build folder
* run `./premake5 gmake`
* CD back to the root
* run `make`
* you are good to go

## Output files
The built code will be in the bin dir

## Building for other OpenGL targets
If you need to build for a different OpenGL version than the default (OpenGL 3.3) you can specify an OpenGL version in your premake command line. Just modify the bat file or add the following to your command line

### For OpenGL 1.1
`--graphics=opengl11`

### For OpenGL 2.1
`--graphics=opengl21`

### For OpenGL 4.3
`--graphics=opengl43`

### For OpenGLES 2.0
`--graphics=opengles2`

### For OpenGLES 3.0
`--graphics=opengles3`

### For Software Rendering
`--graphics=software`

## Adding External Libraries 

If you want to use extra libraries, you can add them to the `build/premake5.lua` file yourself using the links function.

You can find the documentation for the links function here https://premake.github.io/docs/links/


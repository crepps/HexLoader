# HexLoader

HexLoader is a utility for packing library files into a standalone executable.
<br/>
<br/>
<br/>
<img src="https://github.com/user-attachments/assets/e5e4ce28-27f0-4e9c-989b-1a965f3ce386" width="580">
<br/>
<br/>
<br/>
Your bin and DLLs are hex dumped and formatted into comma-separated bytes, then the data is
embedded into a source file along with loader/installer code, and compiled into a single executable.
<br/>
<br/>
This is intended for use with lightweight applications that don't really need an installer, but can't
statically link the required libraries.
<br/>
<br/>
<br/>
## Loader
Running the new executable will silently write your files to the specified temp directory, and launch
the original executable. If 'Cleanup Thread' is enabled, after launching, a process will run in the
background until your application closes, at which point the process will remove the files from the
temp directory and terminate.
<br/>
## Installer
Running the new executable will spawn a series of message boxes, prompting the user to confirm the
installation directory, whether to create a desktop shortcut, whether to automatically start the
application when Windows starts, and whether to run the application after installing.
<br/>
<br/>
<br/>
<br/>
![(interface)](https://kevincrepps.com/images/steps_hl.gif)

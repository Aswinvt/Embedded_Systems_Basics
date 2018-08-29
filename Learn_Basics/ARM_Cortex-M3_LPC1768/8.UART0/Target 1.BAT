SET PATH=C:\Program Files (x86)\Keil_v5\ARM\ARMCC\Bin;C:\Program Files (x86)\Common Files\Oracle\Java\javapath;C:\Program Files\SDCC\bin;C:\ProgramData\Oracle\Java\javapath;C:\WINDOWS\system32;C:\WINDOWS;C:\WINDOWS\System32\Wbem;C:\WINDOWS\System32\WindowsPowerShell\v1.0\;c:\Program Files\Intel\WiFi\bin\;c:\Program Files\Common Files\Intel\WirelessCommon\;C:\Program Files\MATLAB\R2016a\runtime\win64;C:\Program Files\MATLAB\R2016a\bin;C:\Program Files\MATLAB\R2016a\polyspace\bin;C:\Program Files (x86)\Microchip\MPLAB C32 Suite\bin;C:\Program Files (x86)\Microchip\MPLAB IDE\VDI;C:\Program Files\Java\jdk1.8.0_112\bin;C:\OrCAD\OrCAD_10.3\tools\fet\bin;C:\OrCAD\OrCAD_10.3\tools\pcb\bin;C:\OrCAD\OrCAD_10.3\tools\specctra\bin;C:\OrCAD\OrCAD_10.3\tools\PSpice\Library;C:\OrCAD\OrCAD_10.3\tools\bin;C:\OrCAD\OrCAD_10.3\tools\Capture;C:\Program Files (x86)\Intel\Intel(R) Management Engine Components\DAL;C:\Program Files\Intel\Intel(R) Management Engine Components\DAL;C:\Program Files (x86)\Intel\Intel(R) Management Engine Components\IPT;C:\UnxUtils\usr\local\wbin;C:\adb;C:\WINDOWS\system32;C:\WINDOWS;C:\WINDOWS\System32\Wbem;C:\WINDOWS\System32\WindowsPowerShell\v1.0\;C:\Users\ASWIN\AppData\Local\Programs\Python\Python35-32;C:\Users\ASWIN\AppData\Local\Programs\Python\Python35-32\Scripts;C:\WINDOWS\System32\OpenSSH\;C:\Program Files\Git\cmd;C:\Users\ASWIN\AppData\Local\Microsoft\WindowsApps;c:\Program Files\Intel\WiFi\bin\;c:\Program Files\Common Files\Intel\WirelessCommon\;c:\program files (x86)\Modeltech_6.3f\win32;C:\Program Files\SDCC\bin;
SET ARMCC5_ASMOPT=--diag_suppress=9931
SET ARMCC5_CCOPT=--diag_suppress=9931
SET ARMCC5_LINKOPT=--diag_suppress=9931
SET CPU_TYPE=LPC1768
SET CPU_VENDOR=NXP
SET UV2_TARGET=Target 1
SET CPU_CLOCK=0x00B71B00
"C:\Program Files (x86)\Keil_v5\ARM\ARMCC\Bin\ArmAsm" --Via ".\objects\startup_lpc17xx._ia"
"C:\Program Files (x86)\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\uartprog.__i"
"C:\Program Files (x86)\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\system_lpc17xx.__i"
"C:\Program Files (x86)\Keil_v5\ARM\ARMCC\Bin\ArmLink" --Via ".\Objects\UART.lnp"
"C:\Program Files (x86)\Keil_v5\ARM\ARMCC\Bin\fromelf.exe" ".\Objects\UART.axf" --i32combined --output ".\Objects\UART.hex"

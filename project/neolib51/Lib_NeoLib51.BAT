SET C51INC=D:\Keil_v5\C51\Inc;D:\Keil_v5\C51\Inc\Atmel
SET C51LIB=D:\Keil_v5\C51\Lib
SET CPU_TYPE=AT89C52
SET CPU_VENDOR=Microchip
SET UV2_TARGET=Lib_NeoLib51
SET CPU_XTAL=0x016E3600
"D:\Keil_v5\C51\BIN\C51.EXE" @".\Objects\btn.__i"
"D:\Keil_v5\C51\BIN\C51.EXE" @".\Objects\exti.__i"
"D:\Keil_v5\C51\BIN\C51.EXE" @".\Objects\led.__i"
"D:\Keil_v5\C51\BIN\C51.EXE" @".\Objects\tim.__i"
"D:\Keil_v5\C51\BIN\LIB51.EXE" @".\Objects\neolib51.__b"
cp Objects/neolib51.LIB lib/neolib51.lib

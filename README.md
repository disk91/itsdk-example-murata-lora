# LoRaWan example for MURATA CMWX1ZZABZ using ItSdk

This project is a demo project on how to use a Murata STM32-SX1276 CMWX1ZZABZ and communicate over LoRaWAN network (TTN). This example is based on [Disk91 IoT SDK repository](https://github.com/disk91/stm32-it-sdk) where the driver code is.

The project is used as a documentation for supporting a blog post. Check this blog post to understand how to use it.
See here : https://www.disk91.com/?p=3469 

The hardware configuration has been set with CubeMX and the project has been created for CubeIDE.

## Status
** Ready for use **

## Dependencies
* This example requires [Disk91 IoT SDK version >= 1.6](https://github.com/disk91/stm32-it-sdk/tree/Version-1.6)
* This example requires [ST CubeIDE](https://www.st.com/en/development-tools/stm32cubeide.html) the ST-Microelectronic free IDE based on Eclipse + GCC

## Installation
1. If you never start CubeIDE, do it to get your project's workspace created. Then open a terminal and go to this directory.
2. Clone this repository
	```sh
	[Workspace_CubeMx]# git clone https://github.com/disk91/itsdk-example-murata-lora.git
	```
3. Enter this repository
	```sh
	[Workspace_CubeMx]# cd itsdk-example-murata-lora
	```
4. Clone the ItSDK repository
	```sh
	[itsdk-example-sigfox-sx1276]# git clone -b Version-1.6 https://github.com/disk91/stm32-it-sdk.git
	``` 
5. In CubeIDE go to File >> Import >> Existing Projects into Workspace. Select the _itsdk-example-murata-lora_ directory and import the project.
6. Build the project in Release mode
7. You get a _itsdk-example-murata-lora.bin_ in the _Release_ folder
8. Connect the LRWAN ST board with USB
9. Open a serial tty on the _STM32 STLink_ USB Serial port with 9600bps configuration 
10. Copy the _itsdk-example-murata-lora.bin_ file on the automatically mounted drive (named *DIS_L072Z*)
11. The board programming led is blinking, then the program is running.

On the console, at this step you should see:
```
[INFO] S 0x10001001
Startup
Booting
- 
```
On the board, you should see:
 - LD1 blinking (this is part of the program) 
 - LD4 will be on once the device will be connected to the LoRaWan network.
 
If you want to better understand [how the LRWAN board led are mapped, take a look to this post](https://www.disk91.com/2019/technology/hardware/getting-started-with-st-murata-lorawan-board/)

## Configuration
The board is not yet configured for Sigfox: you need to setup different infromations:
- The Radio Zone
- The Device EUI
- The Application EUI
- The Application KEY
This order is important as device EUI is a trigger for this exemple.
To obtain LoRaWan credentials, you can take a look at TheThingsNetwork (TTN).

1. Test the console, typing ? on the serial port. You should get:
	```
	?
	--- Common
	?          : print help
	!          : print copyright
	v          : print version
	o          : print OK
	--- ConfigMng
	c          : print config
	C          : print shadow config
	```
2. Enter in admin mode by typing in the console _changeme_
	```
	changme
	OK
	```
3. Verify you are now in admin mode by typing _?_
	```
	-- Common
	?          : print help
	!          : print copyright
	v          : print version
	o          : print OK
	X          : exit console
	R          : reset device
	R!         : clear the whole eeprom
	l / L      : switch LowPower ON / OFF
	s          : print device state
	t          : print current time in S
	T          : print current cpu temperature in oC
	b          : print battery level
	B          : print VCC level
	r          : print last Reset Cause
	--- ErrorMng
	e          : print errors log
	E          : Clear the error logs
	--- SecureStore
	ss:R       : restore all SS to factory default
	SS:0:xxxx  : change the secure store dyn Key (12B)
	...
	```
4. configure Sigfox assuming
	- Device EUI like : 756404B9D784EF5A
	- App EUI : 52DF791129AC5AAC
	- App KEY : FB501096443B4FC8954949520C895889
	
These credentials can be use for your tests but you won't be able to register them as the PAC is invalid.
Now you can type in the console to setup your device (if you copy/paste, you need to add a delay >= 300ms between each char)
- Configure radio for Europe: _SC:R:0020_  or for USA _SC:R:0100_
- Save the configuration: type _S_
- Configure APP EUI: _SS:A:70B3D57EF0003B19_
- Configure APP KEY: _SS:B:56FF706487C92F4717EEF706AC000000_
- Configure Device EUI: _SS:9:00F86ABA56993000_
	

After setting up the Device EUI you should get:
```
 Init LoRawan Stack success
\ Connecting LoRaWAN success
- Fire a LoRaWAN message success
```

You can verify your Device EUI and App EUI with
```
ss:9
00F86ABA56993000
ss:A
70B3D57EF0003B19
```
The Device Key is not accessible once set, so you can't verify it.


A first LoRaWan transmission has been fired and you will get one new on every 1 minute.


## General Usage

* A console for debug is accessible on USART2 @ 9600
* A console for configuration is accessible on USART2 @ 9600 ; type "?" to access the command. "changeme" to access the private extension to modify the configuration.

## License

This code and ItSdk are under GPLv3. You can use it freely, you can modify, redistribute but *you must* to publish your source code. Other licenses can be obtained by contacting me on [disk91.com](https://www.disk91.com)

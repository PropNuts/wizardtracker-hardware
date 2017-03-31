EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:rx5808
LIBS:WizardView-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L +5V #PWR01
U 1 1 58DB4B84
P 1950 2750
F 0 "#PWR01" H 1950 2600 50  0001 C CNN
F 1 "+5V" H 1965 2923 50  0000 C CNN
F 2 "" H 1950 2750 50  0001 C CNN
F 3 "" H 1950 2750 50  0001 C CNN
	1    1950 2750
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR02
U 1 1 58DB4D32
P 1100 6250
F 0 "#PWR02" H 1100 6000 50  0001 C CNN
F 1 "GND" H 1105 6077 50  0000 C CNN
F 2 "" H 1100 6250 50  0001 C CNN
F 3 "" H 1100 6250 50  0001 C CNN
	1    1100 6250
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR03
U 1 1 58DB4D45
P 1500 6250
F 0 "#PWR03" H 1500 6100 50  0001 C CNN
F 1 "+5V" H 1515 6423 50  0000 C CNN
F 2 "" H 1500 6250 50  0001 C CNN
F 3 "" H 1500 6250 50  0001 C CNN
	1    1500 6250
	-1   0    0    1   
$EndComp
$Comp
L PWR_FLAG #FLG04
U 1 1 58DB4DA6
P 1100 6250
F 0 "#FLG04" H 1100 6325 50  0001 C CNN
F 1 "PWR_FLAG" H 1100 6424 50  0000 C CNN
F 2 "" H 1100 6250 50  0001 C CNN
F 3 "" H 1100 6250 50  0001 C CNN
	1    1100 6250
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG05
U 1 1 58DB4EFC
P 1500 6250
F 0 "#FLG05" H 1500 6325 50  0001 C CNN
F 1 "PWR_FLAG" H 1500 6424 50  0000 C CNN
F 2 "" H 1500 6250 50  0001 C CNN
F 3 "" H 1500 6250 50  0001 C CNN
	1    1500 6250
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X02 J1
U 1 1 58DB5154
P 1400 2800
F 0 "J1" H 1319 2525 50  0000 C CNN
F 1 "PWR_IN" H 1319 2616 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02_Pitch2.54mm" H 1400 2800 50  0001 C CNN
F 3 "" H 1400 2800 50  0001 C CNN
	1    1400 2800
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR06
U 1 1 58DB4D00
P 1950 3400
F 0 "#PWR06" H 1950 3150 50  0001 C CNN
F 1 "GND" H 1955 3227 50  0000 C CNN
F 2 "" H 1950 3400 50  0001 C CNN
F 3 "" H 1950 3400 50  0001 C CNN
	1    1950 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	1600 2750 2350 2750
$Comp
L C C1
U 1 1 58DB5327
P 1950 3050
F 0 "C1" H 2065 3096 50  0000 L CNN
F 1 "1uF" H 2065 3005 50  0000 L CNN
F 2 "Capacitors_THT:C_Disc_D5.0mm_W2.5mm_P2.50mm" H 1988 2900 50  0001 C CNN
F 3 "" H 1950 3050 50  0001 C CNN
	1    1950 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	1950 2750 1950 2900
Wire Wire Line
	1600 3400 1600 2850
Wire Wire Line
	1600 3400 2350 3400
Wire Wire Line
	1950 3400 1950 3200
$Comp
L LED D1
U 1 1 58DB634E
P 2350 3250
F 0 "D1" V 2295 3328 50  0000 L CNN
F 1 "LED" V 2386 3328 50  0000 L CNN
F 2 "LEDs:LED_D3.0mm" H 2350 3250 50  0001 C CNN
F 3 "" H 2350 3250 50  0001 C CNN
	1    2350 3250
	0    1    1    0   
$EndComp
$Comp
L R R1
U 1 1 58DB641F
P 2350 2900
F 0 "R1" H 2420 2946 50  0000 L CNN
F 1 "330" H 2420 2855 50  0000 L CNN
F 2 "Resistors_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 2280 2900 50  0001 C CNN
F 3 "" H 2350 2900 50  0001 C CNN
	1    2350 2900
	1    0    0    -1  
$EndComp
Connection ~ 1950 2750
Connection ~ 1950 3400
Wire Wire Line
	2350 3050 2350 3100
$EndSCHEMATC

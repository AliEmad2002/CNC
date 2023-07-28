# 1. Introduction 
This SW runs CNC milling and drilling machine by G-Code interfacing*.
(not all G-code methods are implemented, only the needed ones)

# 2. Target
Mainly targeted for STM32F103 MCU.

# 3. Main features:
 * Uses SD-Card for file loading. Hence does not need to be connected to a computer.
 * Auto leveling:
   - Not the whole file boundaries are scanned. SW parses the file first and scans only areas that would be engraved.
   - After scanning, level map is saved on SD-Card and could be easily restored.
 * Zero saving:
   - After manually adjusting the zero point, distance between this point and the limit switches is stored on the SD-Card. Hence, if a power loss happens, the zero point could be exaxtly returned to without errors.
 * Spindle soft starting:
   - To avoid startup electrical noises. 

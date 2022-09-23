# 1. Introduction
This SW runs CNC milling and drilling machine by G-Code interfacing*.
(not all G-code methods are implemented, only the needed ones)

# 2. Targets
Mainly targeted for STM32F401 MCU, anyways it can be easly ported into other
targets*. (target must have requirements mentioned in section 5)

# 3. Interfacing
It could be interfaced using any of the popular softwares that sends G-code*.
(one may use the interfacing SW implemented here: <$$$$$$$$$$>)

# 4. Highlighted features:
  - Auto Leveling*. (To obtain very accurate results in terms of milling depth)
  
  - Resume after power loss*. (configurations and depth-map are restored from
  EEPROM)
  
  - Spindle fault protection*. (even if spindle is of closed loop speed control,
    the SW requieres self HW speed measurement - if this feature is to be activated -
    to halt the operation if speed is out of a user configured protected band)
  
  # 5. Target requierements
    -
    -
    -
  
  # 6. Acknowledgement
  

Here's a video of this SW in action:

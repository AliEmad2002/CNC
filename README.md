# 1. Introduction
This SW runs CNC milling and drilling machine by G-Code interfacing*.
(not all G-code methods are implemented, only the needed ones)

# 2. Targets
Mainly targeted for STM32F401, STM32F103 MCU's (Black-pill, Blue-pill respectively), anyways it can be easily ported into other
targets. (see #7.)

# 3. Interfacing
It could be interfaced using any of the popular programs that sends G-code*.
(one may use the interfacing SW implemented in "G-Code generator" program available in this repo)

# 4. Highlighted features:
  - Auto Leveling*. (To obtain very accurate results in terms of milling depth, 
    and compensate minor mechanical error)
    
  - Messages stack*. (to avoid steppers' scatter when large chunk / small displacements is sent)
  
  - To be added: Spindle fault protection*. (even if spindle is of closed loop speed control,
    the SW requires self HW speed measurement - if this feature is to be activated -
    to halt the operation if speed is out of a user configured protected band)
  
   # 5. Doc

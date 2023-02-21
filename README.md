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
  
  # 5. Acknowledgement
  Even though it may not be the best program among likes - hahaha - but I've learned and gained a quantity that I
  myself am compensated with, hoping it would improve my skills, looking forward for the best and for never stopping
  the process of learning, trying, making mistakes, debugging, optimizing, and agile-ing over.

  Thanks to every single person helped me in this project, technically or emotionally, demonstrating principles,
  sharing previous experiences, providing hardware material, or much more that I may not even recall.
  -	Family.                 For their patience and taking over a lot off me.
  -	Assiut Robotics team.   For proving - nearly most of - hardware material and workspace.
  -	Ahmed Osama.            (technical demonstrator at electronics and communication department, faculty of
                            engineering, Assiut university). For his guidance, supervision, and most importantly:
                            encouragement.
  -	Eslam Wael.             (colleague student). Mechanical engineer.
  -	Mohammed Mahmoud Abdo.  (colleague student). For all the time we spent brainstorming and discussing methods.
  -	Tarek M. Medhat.        (colleague student). User interface designer.
  -	Ahmed Abdul-Baset.      (colleague student). PCB designer.
  -	Kareem Essam.           (SW engineer at Valeo Egypt). For sharing previous experiences in CNC machines.
  -	Mohammed G. Eleish.     (SW engineer at Valeo Egypt). For sharing previous experiences in AVR MCU interfacing.
   # 6. Doc
   Here's a video of this SW in action:
   
   # 7. * all used COTS are implemented and documented in COTS project on my github. https://github.com/AliEmad2002/STM32F401x_10x_COTS

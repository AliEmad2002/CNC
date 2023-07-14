(Acceleration settings)
M204 P144000 T144000

(Rapid speed)
G00 F2400.00

(Auto leveling map probing)
G29 L2 R109 F3 B100 N51 N46

(Acceleration settings)
M204 P36000 T36000

(Rapid speed)
G00 F1200.00

(Tool change)
M06

(Probing new tool)
G30

(Give chance for removing probing wires)
M06

(Zeroing Z-axis after probing)
G92 X0 Y0 Z0
(G-CODE GENERATED BY FLATCAM v8.991 - www.flatcam.org - Version Date: 2019/12/27)

(Name: drill_2mm_1.01)
(Type: G-code from Excellon)
(Units: MM)

(Created on Wednesday, 21 June 2023 at 11:11)

(Feedrate: 60.0 mm/min)
(Feedrate rapids 1500.0 mm/min)

(Z_Cut: -1.7 mm)
(Z_Move: 2.0 mm)
(Z Toolchange: 15.0 mm)
(X,Y Toolchange: 0.0000, 0.0000 mm)
(Z Start: None mm)
(Z End: 5.0 mm)
(Steps per circle: 64)
(Preprocessor Excellon: default)

(X range:   10.2110 ...   33.4265  mm)
(Y range:   15.0110 ...   27.1780  mm)

(Spindle Speed: 65535.0 RPM)
G21
G90
G94

(Tool change)
M06

(Probing new tool)
G30

(Give chance for removing probing wires)
M06

(Zeroing Z-axis after probing)
G92 X0 Y0 Z0


G01 F60.00
G00 Z2.0000

M03 S65535.0
G00 X22.8600 Y26.6700
G01 Z-1.7000
G01 Z0
G00 Z2.0000
G00 X25.4000 Y26.6700
G01 Z-1.7000
G01 Z0
G00 Z2.0000
G00 X17.2210 Y20.0410
G01 Z-1.7000
G01 Z0
G00 Z2.0000
G00 X17.2210 Y15.5190
G01 Z-1.7000
G01 Z0
G00 Z2.0000
G00 X10.7190 Y15.5190
G01 Z-1.7000
G01 Z0
G00 Z2.0000
G00 X10.7190 Y20.0410
G01 Z-1.7000
G01 Z0
G00 Z2.0000
M05
G00 Z5.00
G00 X0.0 Y0.0


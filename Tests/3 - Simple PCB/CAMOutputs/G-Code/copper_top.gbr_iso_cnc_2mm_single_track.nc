(G-CODE GENERATED BY FLATCAM v8.991 - www.flatcam.org - Version Date: 2019/12/27)

(Name: copper_top.gbr_iso_cnc_2mm_single_track)
(Type: G-code from Geometry)
(Units: MM)

(Created on Tuesday, 20 June 2023 at 11:47)

(TOOL DIAMETER: 0.4679 mm)
(Feedrate: 60.0 mm/min)
(Feedrate_Z: 60.0 mm/min)
(Feedrate rapids 1500.0 mm/min)

(Z_Cut: -0.5 mm)
(DepthPerCut: 0.09 mm <=>6 passes)
(Z_Move: 2.0 mm)
(Z Toolchange: 15.0 mm)
(X,Y Toolchange: 0.0000, 0.0000 mm)
(Z Start: None mm)
(Z End: 5.0 mm)
(Steps per circle: 64)
(Preprocessor Geometry: default)

(X range:    1.0475 ...    8.8563  mm)
(Y range:    0.8669 ...   10.4283  mm)

(Spindle Speed: 65535 RPM)
G21
G90
G94

(Acceleration settings)
M204 P36000 T36000

(Rapid speed)
G00 F1200.00

(Auto leveling map probing)
G29 L0 R10 F0 B11 N2 N2

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

M03 S65535
G00 X1.2757 Y2.7342
G01 F60.00
G01 Z-0.0900
G01 F60.00
G01 X1.2519 Y2.7021
G01 X1.2453 Y2.6927
G01 X1.2391 Y2.6830
G01 X1.1917 Y2.6039
G01 X1.1860 Y2.5939
G01 X1.1809 Y2.5836
G01 X1.1414 Y2.5003
G01 X1.1368 Y2.4898
G01 X1.1327 Y2.4791
G01 X1.1016 Y2.3922
G01 X1.0980 Y2.3813
G01 X1.0949 Y2.3703
G01 X1.0725 Y2.2808
G01 X1.0700 Y2.2696
G01 X1.0680 Y2.2583
G01 X1.0545 Y2.1670
G01 X1.0531 Y2.1556
G01 X1.0523 Y2.1442
G01 X1.0477 Y2.0521
G01 X1.0475 Y2.0406
G01 X1.0477 Y2.0291
G01 X1.0523 Y1.9370
G01 X1.0531 Y1.9256
G01 X1.0545 Y1.9142
G01 X1.0680 Y1.8229
G01 X1.0700 Y1.8116
G01 X1.0725 Y1.8004
G01 X1.0949 Y1.7109
G01 X1.0980 Y1.6999
G01 X1.1016 Y1.6890
G01 X1.1327 Y1.6021
G01 X1.1368 Y1.5914
G01 X1.1414 Y1.5809
G01 X1.1809 Y1.4976
G01 X1.1860 Y1.4873
G01 X1.1917 Y1.4773
G01 X1.2391 Y1.3982
G01 X1.2453 Y1.3885
G01 X1.2519 Y1.3791
G01 X1.3068 Y1.3050
G01 X1.3139 Y1.2960
G01 X1.3214 Y1.2873
G01 X1.3833 Y1.2189
G01 X1.3912 Y1.2106
G01 X1.3995 Y1.2027
G01 X1.4679 Y1.1408
G01 X1.4766 Y1.1333
G01 X1.4856 Y1.1262
G01 X1.5597 Y1.0713
G01 X1.5691 Y1.0647
G01 X1.5788 Y1.0585
G01 X1.6579 Y1.0111
G01 X1.6679 Y1.0054
G01 X1.6782 Y1.0003
G01 X1.7615 Y0.9608
G01 X1.7720 Y0.9562
G01 X1.7827 Y0.9521
G01 X1.8696 Y0.9210
G01 X1.8805 Y0.9174
G01 X1.8915 Y0.9143
G01 X1.9810 Y0.8919
G01 X1.9922 Y0.8894
G01 X2.0035 Y0.8874
G01 X2.0948 Y0.8739
G01 X2.1062 Y0.8725
G01 X2.1176 Y0.8717
G01 X2.2097 Y0.8671
G01 X2.2212 Y0.8669
G01 X2.2327 Y0.8671
G01 X2.3248 Y0.8717
G01 X2.3362 Y0.8725
G01 X2.3476 Y0.8739
G01 X2.4389 Y0.8874
G01 X2.4502 Y0.8894
G01 X2.4614 Y0.8919
G01 X2.5509 Y0.9143
G01 X2.5619 Y0.9174
G01 X2.5728 Y0.9210
G01 X2.6597 Y0.9521
G01 X2.6704 Y0.9562
G01 X2.6809 Y0.9608
G01 X2.7642 Y1.0003
G01 X2.7745 Y1.0054
G01 X2.7845 Y1.0111
G01 X2.8636 Y1.0585
G01 X2.8733 Y1.0647
G01 X2.8827 Y1.0713
G01 X2.9568 Y1.1262
G01 X2.9658 Y1.1333
G01 X2.9745 Y1.1408
G01 X3.0429 Y1.2027
G01 X3.0512 Y1.2106
G01 X3.0591 Y1.2189
G01 X3.1210 Y1.2873
G01 X3.1285 Y1.2960
G01 X3.1356 Y1.3050
G01 X3.1905 Y1.3791
G01 X3.1971 Y1.3885
G01 X3.2033 Y1.3982
G01 X3.2507 Y1.4773
G01 X3.2564 Y1.4873
G01 X3.2615 Y1.4976
G01 X3.3010 Y1.5809
G01 X3.3056 Y1.5914
G01 X3.3097 Y1.6021
G01 X3.3408 Y1.6890
G01 X3.3444 Y1.6999
G01 X3.3475 Y1.7109
G01 X3.3699 Y1.8004
G01 X3.3724 Y1.8116
G01 X3.3744 Y1.8229
G01 X3.3879 Y1.9142
G01 X3.3893 Y1.9256
G01 X3.3901 Y1.9370
G01 X3.3947 Y2.0291
G01 X3.3947 Y2.0521
G01 X3.3901 Y2.1442
G01 X3.3893 Y2.1556
G01 X3.3879 Y2.1670
G01 X3.3744 Y2.2583
G01 X3.3724 Y2.2696
G01 X3.3699 Y2.2808
G01 X3.3475 Y2.3703
G01 X3.3444 Y2.3813
G01 X3.3408 Y2.3922
G01 X3.3097 Y2.4791
G01 X3.3056 Y2.4898
G01 X3.2683 Y2.5692
G01 X3.2683 Y2.9233
G01 X7.3801 Y7.0351
G01 X7.3903 Y7.0293
G01 X7.4006 Y7.0242
G01 X7.4682 Y6.9922
G01 X7.4787 Y6.9875
G01 X7.4894 Y6.9834
G01 X7.5708 Y6.9546
G01 X7.6544 Y6.9333
G01 X7.6656 Y6.9308
G01 X7.6769 Y6.9288
G01 X7.7623 Y6.9165
G01 X7.7738 Y6.9156
G01 X7.8600 Y6.9117
G01 X7.9462 Y6.9156
G01 X7.9577 Y6.9165
G01 X8.0431 Y6.9288
G01 X8.0544 Y6.9308
G01 X8.0656 Y6.9333
G01 X8.1492 Y6.9546
G01 X8.1601 Y6.9582
G01 X8.2413 Y6.9875
G01 X8.3194 Y7.0242
G01 X8.3297 Y7.0293
G01 X8.3397 Y7.0350
G01 X8.4135 Y7.0796
G01 X8.4229 Y7.0862
G01 X8.4921 Y7.1378
G01 X8.5562 Y7.1956
G01 X8.5645 Y7.2035
G01 X8.5724 Y7.2118
G01 X8.6302 Y7.2759
G01 X8.6818 Y7.3451
G01 X8.6884 Y7.3545
G01 X8.6946 Y7.3642
G01 X8.7330 Y7.4283
G01 X8.7387 Y7.4383
G01 X8.7438 Y7.4486
G01 X8.7805 Y7.5267
G01 X8.8098 Y7.6079
G01 X8.8134 Y7.6188
G01 X8.8165 Y7.6298
G01 X8.8372 Y7.7136
G01 X8.8392 Y7.7249
G01 X8.8515 Y7.8103
G01 X8.8524 Y7.8218
G01 X8.8563 Y7.9080
G01 X8.8563 Y9.4320
G01 X8.8560 Y9.4435
G01 X8.8515 Y9.5297
G01 X8.8392 Y9.6151
G01 X8.8372 Y9.6264
G01 X8.8347 Y9.6376
G01 X8.8134 Y9.7212
G01 X8.8098 Y9.7321
G01 X8.7805 Y9.8133
G01 X8.7438 Y9.8914
G01 X8.7387 Y9.9017
G01 X8.7330 Y9.9117
G01 X8.6884 Y9.9855
G01 X8.6818 Y9.9949
G01 X8.6302 Y10.0641
G01 X8.5724 Y10.1282
G01 X8.5645 Y10.1365
G01 X8.5562 Y10.1444
G01 X8.4921 Y10.2022
G01 X8.4229 Y10.2538
G01 X8.4135 Y10.2604
G01 X8.3397 Y10.3050
G01 X8.3297 Y10.3107
G01 X8.3194 Y10.3158
G01 X8.2413 Y10.3525
G01 X8.1601 Y10.3818
G01 X8.1492 Y10.3854
G01 X8.0656 Y10.4067
G01 X8.0544 Y10.4092
G01 X8.0431 Y10.4112
G01 X7.9577 Y10.4235
G01 X7.9462 Y10.4244
G01 X7.8600 Y10.4283
G01 X7.7738 Y10.4244
G01 X7.7623 Y10.4235
G01 X7.6769 Y10.4112
G01 X7.6656 Y10.4092
G01 X7.6544 Y10.4067
G01 X7.5708 Y10.3854
G01 X7.5599 Y10.3818
G01 X7.4787 Y10.3525
G01 X7.4006 Y10.3158
G01 X7.3903 Y10.3107
G01 X7.3803 Y10.3050
G01 X7.3065 Y10.2604
G01 X7.2971 Y10.2538
G01 X7.2279 Y10.2022
G01 X7.1638 Y10.1444
G01 X7.1555 Y10.1365
G01 X7.1476 Y10.1282
G01 X7.0898 Y10.0641
G01 X7.0382 Y9.9949
G01 X7.0316 Y9.9855
G01 X7.0254 Y9.9758
G01 X6.9870 Y9.9117
G01 X6.9813 Y9.9017
G01 X6.9762 Y9.8914
G01 X6.9395 Y9.8133
G01 X6.9102 Y9.7321
G01 X6.9066 Y9.7212
G01 X6.9035 Y9.7102
G01 X6.8828 Y9.6264
G01 X6.8808 Y9.6151
G01 X6.8685 Y9.5297
G01 X6.8676 Y9.5182
G01 X6.8637 Y9.4377
G01 X6.8637 Y9.2838
G01 X6.8212 Y9.2592
G01 X6.7985 Y9.2444
G01 X6.7411 Y9.2031
G01 X6.7199 Y9.1862
G01 X6.6936 Y9.1627
G01 X6.6755 Y9.1471
G01 X6.6669 Y9.1394
G01 X6.6475 Y9.1205
G01 X1.5675 Y4.0405
G01 X1.5596 Y4.0322
G01 X1.5018 Y3.9681
G01 X1.4502 Y3.8989
G01 X1.4436 Y3.8895
G01 X1.3990 Y3.8157
G01 X1.3933 Y3.8057
G01 X1.3882 Y3.7954
G01 X1.3515 Y3.7173
G01 X1.3222 Y3.6361
G01 X1.3186 Y3.6252
G01 X1.3155 Y3.6142
G01 X1.2948 Y3.5304
G01 X1.2928 Y3.5191
G01 X1.2805 Y3.4337
G01 X1.2796 Y3.4222
G01 X1.2757 Y3.3417
G01 X1.2757 Y2.7342
G00 X1.2757 Y2.7342
G01 F60.00
G01 Z-0.1800
G01 F60.00
G01 X1.2519 Y2.7021
G01 X1.2453 Y2.6927
G01 X1.2391 Y2.6830
G01 X1.1917 Y2.6039
G01 X1.1860 Y2.5939
G01 X1.1809 Y2.5836
G01 X1.1414 Y2.5003
G01 X1.1368 Y2.4898
G01 X1.1327 Y2.4791
G01 X1.1016 Y2.3922
G01 X1.0980 Y2.3813
G01 X1.0949 Y2.3703
G01 X1.0725 Y2.2808
G01 X1.0700 Y2.2696
G01 X1.0680 Y2.2583
G01 X1.0545 Y2.1670
G01 X1.0531 Y2.1556
G01 X1.0523 Y2.1442
G01 X1.0477 Y2.0521
G01 X1.0475 Y2.0406
G01 X1.0477 Y2.0291
G01 X1.0523 Y1.9370
G01 X1.0531 Y1.9256
G01 X1.0545 Y1.9142
G01 X1.0680 Y1.8229
G01 X1.0700 Y1.8116
G01 X1.0725 Y1.8004
G01 X1.0949 Y1.7109
G01 X1.0980 Y1.6999
G01 X1.1016 Y1.6890
G01 X1.1327 Y1.6021
G01 X1.1368 Y1.5914
G01 X1.1414 Y1.5809
G01 X1.1809 Y1.4976
G01 X1.1860 Y1.4873
G01 X1.1917 Y1.4773
G01 X1.2391 Y1.3982
G01 X1.2453 Y1.3885
G01 X1.2519 Y1.3791
G01 X1.3068 Y1.3050
G01 X1.3139 Y1.2960
G01 X1.3214 Y1.2873
G01 X1.3833 Y1.2189
G01 X1.3912 Y1.2106
G01 X1.3995 Y1.2027
G01 X1.4679 Y1.1408
G01 X1.4766 Y1.1333
G01 X1.4856 Y1.1262
G01 X1.5597 Y1.0713
G01 X1.5691 Y1.0647
G01 X1.5788 Y1.0585
G01 X1.6579 Y1.0111
G01 X1.6679 Y1.0054
G01 X1.6782 Y1.0003
G01 X1.7615 Y0.9608
G01 X1.7720 Y0.9562
G01 X1.7827 Y0.9521
G01 X1.8696 Y0.9210
G01 X1.8805 Y0.9174
G01 X1.8915 Y0.9143
G01 X1.9810 Y0.8919
G01 X1.9922 Y0.8894
G01 X2.0035 Y0.8874
G01 X2.0948 Y0.8739
G01 X2.1062 Y0.8725
G01 X2.1176 Y0.8717
G01 X2.2097 Y0.8671
G01 X2.2212 Y0.8669
G01 X2.2327 Y0.8671
G01 X2.3248 Y0.8717
G01 X2.3362 Y0.8725
G01 X2.3476 Y0.8739
G01 X2.4389 Y0.8874
G01 X2.4502 Y0.8894
G01 X2.4614 Y0.8919
G01 X2.5509 Y0.9143
G01 X2.5619 Y0.9174
G01 X2.5728 Y0.9210
G01 X2.6597 Y0.9521
G01 X2.6704 Y0.9562
G01 X2.6809 Y0.9608
G01 X2.7642 Y1.0003
G01 X2.7745 Y1.0054
G01 X2.7845 Y1.0111
G01 X2.8636 Y1.0585
G01 X2.8733 Y1.0647
G01 X2.8827 Y1.0713
G01 X2.9568 Y1.1262
G01 X2.9658 Y1.1333
G01 X2.9745 Y1.1408
G01 X3.0429 Y1.2027
G01 X3.0512 Y1.2106
G01 X3.0591 Y1.2189
G01 X3.1210 Y1.2873
G01 X3.1285 Y1.2960
G01 X3.1356 Y1.3050
G01 X3.1905 Y1.3791
G01 X3.1971 Y1.3885
G01 X3.2033 Y1.3982
G01 X3.2507 Y1.4773
G01 X3.2564 Y1.4873
G01 X3.2615 Y1.4976
G01 X3.3010 Y1.5809
G01 X3.3056 Y1.5914
G01 X3.3097 Y1.6021
G01 X3.3408 Y1.6890
G01 X3.3444 Y1.6999
G01 X3.3475 Y1.7109
G01 X3.3699 Y1.8004
G01 X3.3724 Y1.8116
G01 X3.3744 Y1.8229
G01 X3.3879 Y1.9142
G01 X3.3893 Y1.9256
G01 X3.3901 Y1.9370
G01 X3.3947 Y2.0291
G01 X3.3947 Y2.0521
G01 X3.3901 Y2.1442
G01 X3.3893 Y2.1556
G01 X3.3879 Y2.1670
G01 X3.3744 Y2.2583
G01 X3.3724 Y2.2696
G01 X3.3699 Y2.2808
G01 X3.3475 Y2.3703
G01 X3.3444 Y2.3813
G01 X3.3408 Y2.3922
G01 X3.3097 Y2.4791
G01 X3.3056 Y2.4898
G01 X3.2683 Y2.5692
G01 X3.2683 Y2.9233
G01 X7.3801 Y7.0351
G01 X7.3903 Y7.0293
G01 X7.4006 Y7.0242
G01 X7.4682 Y6.9922
G01 X7.4787 Y6.9875
G01 X7.4894 Y6.9834
G01 X7.5708 Y6.9546
G01 X7.6544 Y6.9333
G01 X7.6656 Y6.9308
G01 X7.6769 Y6.9288
G01 X7.7623 Y6.9165
G01 X7.7738 Y6.9156
G01 X7.8600 Y6.9117
G01 X7.9462 Y6.9156
G01 X7.9577 Y6.9165
G01 X8.0431 Y6.9288
G01 X8.0544 Y6.9308
G01 X8.0656 Y6.9333
G01 X8.1492 Y6.9546
G01 X8.1601 Y6.9582
G01 X8.2413 Y6.9875
G01 X8.3194 Y7.0242
G01 X8.3297 Y7.0293
G01 X8.3397 Y7.0350
G01 X8.4135 Y7.0796
G01 X8.4229 Y7.0862
G01 X8.4921 Y7.1378
G01 X8.5562 Y7.1956
G01 X8.5645 Y7.2035
G01 X8.5724 Y7.2118
G01 X8.6302 Y7.2759
G01 X8.6818 Y7.3451
G01 X8.6884 Y7.3545
G01 X8.6946 Y7.3642
G01 X8.7330 Y7.4283
G01 X8.7387 Y7.4383
G01 X8.7438 Y7.4486
G01 X8.7805 Y7.5267
G01 X8.8098 Y7.6079
G01 X8.8134 Y7.6188
G01 X8.8165 Y7.6298
G01 X8.8372 Y7.7136
G01 X8.8392 Y7.7249
G01 X8.8515 Y7.8103
G01 X8.8524 Y7.8218
G01 X8.8563 Y7.9080
G01 X8.8563 Y9.4320
G01 X8.8560 Y9.4435
G01 X8.8515 Y9.5297
G01 X8.8392 Y9.6151
G01 X8.8372 Y9.6264
G01 X8.8347 Y9.6376
G01 X8.8134 Y9.7212
G01 X8.8098 Y9.7321
G01 X8.7805 Y9.8133
G01 X8.7438 Y9.8914
G01 X8.7387 Y9.9017
G01 X8.7330 Y9.9117
G01 X8.6884 Y9.9855
G01 X8.6818 Y9.9949
G01 X8.6302 Y10.0641
G01 X8.5724 Y10.1282
G01 X8.5645 Y10.1365
G01 X8.5562 Y10.1444
G01 X8.4921 Y10.2022
G01 X8.4229 Y10.2538
G01 X8.4135 Y10.2604
G01 X8.3397 Y10.3050
G01 X8.3297 Y10.3107
G01 X8.3194 Y10.3158
G01 X8.2413 Y10.3525
G01 X8.1601 Y10.3818
G01 X8.1492 Y10.3854
G01 X8.0656 Y10.4067
G01 X8.0544 Y10.4092
G01 X8.0431 Y10.4112
G01 X7.9577 Y10.4235
G01 X7.9462 Y10.4244
G01 X7.8600 Y10.4283
G01 X7.7738 Y10.4244
G01 X7.7623 Y10.4235
G01 X7.6769 Y10.4112
G01 X7.6656 Y10.4092
G01 X7.6544 Y10.4067
G01 X7.5708 Y10.3854
G01 X7.5599 Y10.3818
G01 X7.4787 Y10.3525
G01 X7.4006 Y10.3158
G01 X7.3903 Y10.3107
G01 X7.3803 Y10.3050
G01 X7.3065 Y10.2604
G01 X7.2971 Y10.2538
G01 X7.2279 Y10.2022
G01 X7.1638 Y10.1444
G01 X7.1555 Y10.1365
G01 X7.1476 Y10.1282
G01 X7.0898 Y10.0641
G01 X7.0382 Y9.9949
G01 X7.0316 Y9.9855
G01 X7.0254 Y9.9758
G01 X6.9870 Y9.9117
G01 X6.9813 Y9.9017
G01 X6.9762 Y9.8914
G01 X6.9395 Y9.8133
G01 X6.9102 Y9.7321
G01 X6.9066 Y9.7212
G01 X6.9035 Y9.7102
G01 X6.8828 Y9.6264
G01 X6.8808 Y9.6151
G01 X6.8685 Y9.5297
G01 X6.8676 Y9.5182
G01 X6.8637 Y9.4377
G01 X6.8637 Y9.2838
G01 X6.8212 Y9.2592
G01 X6.7985 Y9.2444
G01 X6.7411 Y9.2031
G01 X6.7199 Y9.1862
G01 X6.6936 Y9.1627
G01 X6.6755 Y9.1471
G01 X6.6669 Y9.1394
G01 X6.6475 Y9.1205
G01 X1.5675 Y4.0405
G01 X1.5596 Y4.0322
G01 X1.5018 Y3.9681
G01 X1.4502 Y3.8989
G01 X1.4436 Y3.8895
G01 X1.3990 Y3.8157
G01 X1.3933 Y3.8057
G01 X1.3882 Y3.7954
G01 X1.3515 Y3.7173
G01 X1.3222 Y3.6361
G01 X1.3186 Y3.6252
G01 X1.3155 Y3.6142
G01 X1.2948 Y3.5304
G01 X1.2928 Y3.5191
G01 X1.2805 Y3.4337
G01 X1.2796 Y3.4222
G01 X1.2757 Y3.3417
G01 X1.2757 Y2.7342
G00 X1.2757 Y2.7342
G01 F60.00
G01 Z-0.2700
G01 F60.00
G01 X1.2519 Y2.7021
G01 X1.2453 Y2.6927
G01 X1.2391 Y2.6830
G01 X1.1917 Y2.6039
G01 X1.1860 Y2.5939
G01 X1.1809 Y2.5836
G01 X1.1414 Y2.5003
G01 X1.1368 Y2.4898
G01 X1.1327 Y2.4791
G01 X1.1016 Y2.3922
G01 X1.0980 Y2.3813
G01 X1.0949 Y2.3703
G01 X1.0725 Y2.2808
G01 X1.0700 Y2.2696
G01 X1.0680 Y2.2583
G01 X1.0545 Y2.1670
G01 X1.0531 Y2.1556
G01 X1.0523 Y2.1442
G01 X1.0477 Y2.0521
G01 X1.0475 Y2.0406
G01 X1.0477 Y2.0291
G01 X1.0523 Y1.9370
G01 X1.0531 Y1.9256
G01 X1.0545 Y1.9142
G01 X1.0680 Y1.8229
G01 X1.0700 Y1.8116
G01 X1.0725 Y1.8004
G01 X1.0949 Y1.7109
G01 X1.0980 Y1.6999
G01 X1.1016 Y1.6890
G01 X1.1327 Y1.6021
G01 X1.1368 Y1.5914
G01 X1.1414 Y1.5809
G01 X1.1809 Y1.4976
G01 X1.1860 Y1.4873
G01 X1.1917 Y1.4773
G01 X1.2391 Y1.3982
G01 X1.2453 Y1.3885
G01 X1.2519 Y1.3791
G01 X1.3068 Y1.3050
G01 X1.3139 Y1.2960
G01 X1.3214 Y1.2873
G01 X1.3833 Y1.2189
G01 X1.3912 Y1.2106
G01 X1.3995 Y1.2027
G01 X1.4679 Y1.1408
G01 X1.4766 Y1.1333
G01 X1.4856 Y1.1262
G01 X1.5597 Y1.0713
G01 X1.5691 Y1.0647
G01 X1.5788 Y1.0585
G01 X1.6579 Y1.0111
G01 X1.6679 Y1.0054
G01 X1.6782 Y1.0003
G01 X1.7615 Y0.9608
G01 X1.7720 Y0.9562
G01 X1.7827 Y0.9521
G01 X1.8696 Y0.9210
G01 X1.8805 Y0.9174
G01 X1.8915 Y0.9143
G01 X1.9810 Y0.8919
G01 X1.9922 Y0.8894
G01 X2.0035 Y0.8874
G01 X2.0948 Y0.8739
G01 X2.1062 Y0.8725
G01 X2.1176 Y0.8717
G01 X2.2097 Y0.8671
G01 X2.2212 Y0.8669
G01 X2.2327 Y0.8671
G01 X2.3248 Y0.8717
G01 X2.3362 Y0.8725
G01 X2.3476 Y0.8739
G01 X2.4389 Y0.8874
G01 X2.4502 Y0.8894
G01 X2.4614 Y0.8919
G01 X2.5509 Y0.9143
G01 X2.5619 Y0.9174
G01 X2.5728 Y0.9210
G01 X2.6597 Y0.9521
G01 X2.6704 Y0.9562
G01 X2.6809 Y0.9608
G01 X2.7642 Y1.0003
G01 X2.7745 Y1.0054
G01 X2.7845 Y1.0111
G01 X2.8636 Y1.0585
G01 X2.8733 Y1.0647
G01 X2.8827 Y1.0713
G01 X2.9568 Y1.1262
G01 X2.9658 Y1.1333
G01 X2.9745 Y1.1408
G01 X3.0429 Y1.2027
G01 X3.0512 Y1.2106
G01 X3.0591 Y1.2189
G01 X3.1210 Y1.2873
G01 X3.1285 Y1.2960
G01 X3.1356 Y1.3050
G01 X3.1905 Y1.3791
G01 X3.1971 Y1.3885
G01 X3.2033 Y1.3982
G01 X3.2507 Y1.4773
G01 X3.2564 Y1.4873
G01 X3.2615 Y1.4976
G01 X3.3010 Y1.5809
G01 X3.3056 Y1.5914
G01 X3.3097 Y1.6021
G01 X3.3408 Y1.6890
G01 X3.3444 Y1.6999
G01 X3.3475 Y1.7109
G01 X3.3699 Y1.8004
G01 X3.3724 Y1.8116
G01 X3.3744 Y1.8229
G01 X3.3879 Y1.9142
G01 X3.3893 Y1.9256
G01 X3.3901 Y1.9370
G01 X3.3947 Y2.0291
G01 X3.3947 Y2.0521
G01 X3.3901 Y2.1442
G01 X3.3893 Y2.1556
G01 X3.3879 Y2.1670
G01 X3.3744 Y2.2583
G01 X3.3724 Y2.2696
G01 X3.3699 Y2.2808
G01 X3.3475 Y2.3703
G01 X3.3444 Y2.3813
G01 X3.3408 Y2.3922
G01 X3.3097 Y2.4791
G01 X3.3056 Y2.4898
G01 X3.2683 Y2.5692
G01 X3.2683 Y2.9233
G01 X7.3801 Y7.0351
G01 X7.3903 Y7.0293
G01 X7.4006 Y7.0242
G01 X7.4682 Y6.9922
G01 X7.4787 Y6.9875
G01 X7.4894 Y6.9834
G01 X7.5708 Y6.9546
G01 X7.6544 Y6.9333
G01 X7.6656 Y6.9308
G01 X7.6769 Y6.9288
G01 X7.7623 Y6.9165
G01 X7.7738 Y6.9156
G01 X7.8600 Y6.9117
G01 X7.9462 Y6.9156
G01 X7.9577 Y6.9165
G01 X8.0431 Y6.9288
G01 X8.0544 Y6.9308
G01 X8.0656 Y6.9333
G01 X8.1492 Y6.9546
G01 X8.1601 Y6.9582
G01 X8.2413 Y6.9875
G01 X8.3194 Y7.0242
G01 X8.3297 Y7.0293
G01 X8.3397 Y7.0350
G01 X8.4135 Y7.0796
G01 X8.4229 Y7.0862
G01 X8.4921 Y7.1378
G01 X8.5562 Y7.1956
G01 X8.5645 Y7.2035
G01 X8.5724 Y7.2118
G01 X8.6302 Y7.2759
G01 X8.6818 Y7.3451
G01 X8.6884 Y7.3545
G01 X8.6946 Y7.3642
G01 X8.7330 Y7.4283
G01 X8.7387 Y7.4383
G01 X8.7438 Y7.4486
G01 X8.7805 Y7.5267
G01 X8.8098 Y7.6079
G01 X8.8134 Y7.6188
G01 X8.8165 Y7.6298
G01 X8.8372 Y7.7136
G01 X8.8392 Y7.7249
G01 X8.8515 Y7.8103
G01 X8.8524 Y7.8218
G01 X8.8563 Y7.9080
G01 X8.8563 Y9.4320
G01 X8.8560 Y9.4435
G01 X8.8515 Y9.5297
G01 X8.8392 Y9.6151
G01 X8.8372 Y9.6264
G01 X8.8347 Y9.6376
G01 X8.8134 Y9.7212
G01 X8.8098 Y9.7321
G01 X8.7805 Y9.8133
G01 X8.7438 Y9.8914
G01 X8.7387 Y9.9017
G01 X8.7330 Y9.9117
G01 X8.6884 Y9.9855
G01 X8.6818 Y9.9949
G01 X8.6302 Y10.0641
G01 X8.5724 Y10.1282
G01 X8.5645 Y10.1365
G01 X8.5562 Y10.1444
G01 X8.4921 Y10.2022
G01 X8.4229 Y10.2538
G01 X8.4135 Y10.2604
G01 X8.3397 Y10.3050
G01 X8.3297 Y10.3107
G01 X8.3194 Y10.3158
G01 X8.2413 Y10.3525
G01 X8.1601 Y10.3818
G01 X8.1492 Y10.3854
G01 X8.0656 Y10.4067
G01 X8.0544 Y10.4092
G01 X8.0431 Y10.4112
G01 X7.9577 Y10.4235
G01 X7.9462 Y10.4244
G01 X7.8600 Y10.4283
G01 X7.7738 Y10.4244
G01 X7.7623 Y10.4235
G01 X7.6769 Y10.4112
G01 X7.6656 Y10.4092
G01 X7.6544 Y10.4067
G01 X7.5708 Y10.3854
G01 X7.5599 Y10.3818
G01 X7.4787 Y10.3525
G01 X7.4006 Y10.3158
G01 X7.3903 Y10.3107
G01 X7.3803 Y10.3050
G01 X7.3065 Y10.2604
G01 X7.2971 Y10.2538
G01 X7.2279 Y10.2022
G01 X7.1638 Y10.1444
G01 X7.1555 Y10.1365
G01 X7.1476 Y10.1282
G01 X7.0898 Y10.0641
G01 X7.0382 Y9.9949
G01 X7.0316 Y9.9855
G01 X7.0254 Y9.9758
G01 X6.9870 Y9.9117
G01 X6.9813 Y9.9017
G01 X6.9762 Y9.8914
G01 X6.9395 Y9.8133
G01 X6.9102 Y9.7321
G01 X6.9066 Y9.7212
G01 X6.9035 Y9.7102
G01 X6.8828 Y9.6264
G01 X6.8808 Y9.6151
G01 X6.8685 Y9.5297
G01 X6.8676 Y9.5182
G01 X6.8637 Y9.4377
G01 X6.8637 Y9.2838
G01 X6.8212 Y9.2592
G01 X6.7985 Y9.2444
G01 X6.7411 Y9.2031
G01 X6.7199 Y9.1862
G01 X6.6936 Y9.1627
G01 X6.6755 Y9.1471
G01 X6.6669 Y9.1394
G01 X6.6475 Y9.1205
G01 X1.5675 Y4.0405
G01 X1.5596 Y4.0322
G01 X1.5018 Y3.9681
G01 X1.4502 Y3.8989
G01 X1.4436 Y3.8895
G01 X1.3990 Y3.8157
G01 X1.3933 Y3.8057
G01 X1.3882 Y3.7954
G01 X1.3515 Y3.7173
G01 X1.3222 Y3.6361
G01 X1.3186 Y3.6252
G01 X1.3155 Y3.6142
G01 X1.2948 Y3.5304
G01 X1.2928 Y3.5191
G01 X1.2805 Y3.4337
G01 X1.2796 Y3.4222
G01 X1.2757 Y3.3417
G01 X1.2757 Y2.7342
G00 X1.2757 Y2.7342
G01 F60.00
G01 Z-0.3600
G01 F60.00
G01 X1.2519 Y2.7021
G01 X1.2453 Y2.6927
G01 X1.2391 Y2.6830
G01 X1.1917 Y2.6039
G01 X1.1860 Y2.5939
G01 X1.1809 Y2.5836
G01 X1.1414 Y2.5003
G01 X1.1368 Y2.4898
G01 X1.1327 Y2.4791
G01 X1.1016 Y2.3922
G01 X1.0980 Y2.3813
G01 X1.0949 Y2.3703
G01 X1.0725 Y2.2808
G01 X1.0700 Y2.2696
G01 X1.0680 Y2.2583
G01 X1.0545 Y2.1670
G01 X1.0531 Y2.1556
G01 X1.0523 Y2.1442
G01 X1.0477 Y2.0521
G01 X1.0475 Y2.0406
G01 X1.0477 Y2.0291
G01 X1.0523 Y1.9370
G01 X1.0531 Y1.9256
G01 X1.0545 Y1.9142
G01 X1.0680 Y1.8229
G01 X1.0700 Y1.8116
G01 X1.0725 Y1.8004
G01 X1.0949 Y1.7109
G01 X1.0980 Y1.6999
G01 X1.1016 Y1.6890
G01 X1.1327 Y1.6021
G01 X1.1368 Y1.5914
G01 X1.1414 Y1.5809
G01 X1.1809 Y1.4976
G01 X1.1860 Y1.4873
G01 X1.1917 Y1.4773
G01 X1.2391 Y1.3982
G01 X1.2453 Y1.3885
G01 X1.2519 Y1.3791
G01 X1.3068 Y1.3050
G01 X1.3139 Y1.2960
G01 X1.3214 Y1.2873
G01 X1.3833 Y1.2189
G01 X1.3912 Y1.2106
G01 X1.3995 Y1.2027
G01 X1.4679 Y1.1408
G01 X1.4766 Y1.1333
G01 X1.4856 Y1.1262
G01 X1.5597 Y1.0713
G01 X1.5691 Y1.0647
G01 X1.5788 Y1.0585
G01 X1.6579 Y1.0111
G01 X1.6679 Y1.0054
G01 X1.6782 Y1.0003
G01 X1.7615 Y0.9608
G01 X1.7720 Y0.9562
G01 X1.7827 Y0.9521
G01 X1.8696 Y0.9210
G01 X1.8805 Y0.9174
G01 X1.8915 Y0.9143
G01 X1.9810 Y0.8919
G01 X1.9922 Y0.8894
G01 X2.0035 Y0.8874
G01 X2.0948 Y0.8739
G01 X2.1062 Y0.8725
G01 X2.1176 Y0.8717
G01 X2.2097 Y0.8671
G01 X2.2212 Y0.8669
G01 X2.2327 Y0.8671
G01 X2.3248 Y0.8717
G01 X2.3362 Y0.8725
G01 X2.3476 Y0.8739
G01 X2.4389 Y0.8874
G01 X2.4502 Y0.8894
G01 X2.4614 Y0.8919
G01 X2.5509 Y0.9143
G01 X2.5619 Y0.9174
G01 X2.5728 Y0.9210
G01 X2.6597 Y0.9521
G01 X2.6704 Y0.9562
G01 X2.6809 Y0.9608
G01 X2.7642 Y1.0003
G01 X2.7745 Y1.0054
G01 X2.7845 Y1.0111
G01 X2.8636 Y1.0585
G01 X2.8733 Y1.0647
G01 X2.8827 Y1.0713
G01 X2.9568 Y1.1262
G01 X2.9658 Y1.1333
G01 X2.9745 Y1.1408
G01 X3.0429 Y1.2027
G01 X3.0512 Y1.2106
G01 X3.0591 Y1.2189
G01 X3.1210 Y1.2873
G01 X3.1285 Y1.2960
G01 X3.1356 Y1.3050
G01 X3.1905 Y1.3791
G01 X3.1971 Y1.3885
G01 X3.2033 Y1.3982
G01 X3.2507 Y1.4773
G01 X3.2564 Y1.4873
G01 X3.2615 Y1.4976
G01 X3.3010 Y1.5809
G01 X3.3056 Y1.5914
G01 X3.3097 Y1.6021
G01 X3.3408 Y1.6890
G01 X3.3444 Y1.6999
G01 X3.3475 Y1.7109
G01 X3.3699 Y1.8004
G01 X3.3724 Y1.8116
G01 X3.3744 Y1.8229
G01 X3.3879 Y1.9142
G01 X3.3893 Y1.9256
G01 X3.3901 Y1.9370
G01 X3.3947 Y2.0291
G01 X3.3947 Y2.0521
G01 X3.3901 Y2.1442
G01 X3.3893 Y2.1556
G01 X3.3879 Y2.1670
G01 X3.3744 Y2.2583
G01 X3.3724 Y2.2696
G01 X3.3699 Y2.2808
G01 X3.3475 Y2.3703
G01 X3.3444 Y2.3813
G01 X3.3408 Y2.3922
G01 X3.3097 Y2.4791
G01 X3.3056 Y2.4898
G01 X3.2683 Y2.5692
G01 X3.2683 Y2.9233
G01 X7.3801 Y7.0351
G01 X7.3903 Y7.0293
G01 X7.4006 Y7.0242
G01 X7.4682 Y6.9922
G01 X7.4787 Y6.9875
G01 X7.4894 Y6.9834
G01 X7.5708 Y6.9546
G01 X7.6544 Y6.9333
G01 X7.6656 Y6.9308
G01 X7.6769 Y6.9288
G01 X7.7623 Y6.9165
G01 X7.7738 Y6.9156
G01 X7.8600 Y6.9117
G01 X7.9462 Y6.9156
G01 X7.9577 Y6.9165
G01 X8.0431 Y6.9288
G01 X8.0544 Y6.9308
G01 X8.0656 Y6.9333
G01 X8.1492 Y6.9546
G01 X8.1601 Y6.9582
G01 X8.2413 Y6.9875
G01 X8.3194 Y7.0242
G01 X8.3297 Y7.0293
G01 X8.3397 Y7.0350
G01 X8.4135 Y7.0796
G01 X8.4229 Y7.0862
G01 X8.4921 Y7.1378
G01 X8.5562 Y7.1956
G01 X8.5645 Y7.2035
G01 X8.5724 Y7.2118
G01 X8.6302 Y7.2759
G01 X8.6818 Y7.3451
G01 X8.6884 Y7.3545
G01 X8.6946 Y7.3642
G01 X8.7330 Y7.4283
G01 X8.7387 Y7.4383
G01 X8.7438 Y7.4486
G01 X8.7805 Y7.5267
G01 X8.8098 Y7.6079
G01 X8.8134 Y7.6188
G01 X8.8165 Y7.6298
G01 X8.8372 Y7.7136
G01 X8.8392 Y7.7249
G01 X8.8515 Y7.8103
G01 X8.8524 Y7.8218
G01 X8.8563 Y7.9080
G01 X8.8563 Y9.4320
G01 X8.8560 Y9.4435
G01 X8.8515 Y9.5297
G01 X8.8392 Y9.6151
G01 X8.8372 Y9.6264
G01 X8.8347 Y9.6376
G01 X8.8134 Y9.7212
G01 X8.8098 Y9.7321
G01 X8.7805 Y9.8133
G01 X8.7438 Y9.8914
G01 X8.7387 Y9.9017
G01 X8.7330 Y9.9117
G01 X8.6884 Y9.9855
G01 X8.6818 Y9.9949
G01 X8.6302 Y10.0641
G01 X8.5724 Y10.1282
G01 X8.5645 Y10.1365
G01 X8.5562 Y10.1444
G01 X8.4921 Y10.2022
G01 X8.4229 Y10.2538
G01 X8.4135 Y10.2604
G01 X8.3397 Y10.3050
G01 X8.3297 Y10.3107
G01 X8.3194 Y10.3158
G01 X8.2413 Y10.3525
G01 X8.1601 Y10.3818
G01 X8.1492 Y10.3854
G01 X8.0656 Y10.4067
G01 X8.0544 Y10.4092
G01 X8.0431 Y10.4112
G01 X7.9577 Y10.4235
G01 X7.9462 Y10.4244
G01 X7.8600 Y10.4283
G01 X7.7738 Y10.4244
G01 X7.7623 Y10.4235
G01 X7.6769 Y10.4112
G01 X7.6656 Y10.4092
G01 X7.6544 Y10.4067
G01 X7.5708 Y10.3854
G01 X7.5599 Y10.3818
G01 X7.4787 Y10.3525
G01 X7.4006 Y10.3158
G01 X7.3903 Y10.3107
G01 X7.3803 Y10.3050
G01 X7.3065 Y10.2604
G01 X7.2971 Y10.2538
G01 X7.2279 Y10.2022
G01 X7.1638 Y10.1444
G01 X7.1555 Y10.1365
G01 X7.1476 Y10.1282
G01 X7.0898 Y10.0641
G01 X7.0382 Y9.9949
G01 X7.0316 Y9.9855
G01 X7.0254 Y9.9758
G01 X6.9870 Y9.9117
G01 X6.9813 Y9.9017
G01 X6.9762 Y9.8914
G01 X6.9395 Y9.8133
G01 X6.9102 Y9.7321
G01 X6.9066 Y9.7212
G01 X6.9035 Y9.7102
G01 X6.8828 Y9.6264
G01 X6.8808 Y9.6151
G01 X6.8685 Y9.5297
G01 X6.8676 Y9.5182
G01 X6.8637 Y9.4377
G01 X6.8637 Y9.2838
G01 X6.8212 Y9.2592
G01 X6.7985 Y9.2444
G01 X6.7411 Y9.2031
G01 X6.7199 Y9.1862
G01 X6.6936 Y9.1627
G01 X6.6755 Y9.1471
G01 X6.6669 Y9.1394
G01 X6.6475 Y9.1205
G01 X1.5675 Y4.0405
G01 X1.5596 Y4.0322
G01 X1.5018 Y3.9681
G01 X1.4502 Y3.8989
G01 X1.4436 Y3.8895
G01 X1.3990 Y3.8157
G01 X1.3933 Y3.8057
G01 X1.3882 Y3.7954
G01 X1.3515 Y3.7173
G01 X1.3222 Y3.6361
G01 X1.3186 Y3.6252
G01 X1.3155 Y3.6142
G01 X1.2948 Y3.5304
G01 X1.2928 Y3.5191
G01 X1.2805 Y3.4337
G01 X1.2796 Y3.4222
G01 X1.2757 Y3.3417
G01 X1.2757 Y2.7342
G00 X1.2757 Y2.7342
G01 F60.00
G01 Z-0.4500
G01 F60.00
G01 X1.2519 Y2.7021
G01 X1.2453 Y2.6927
G01 X1.2391 Y2.6830
G01 X1.1917 Y2.6039
G01 X1.1860 Y2.5939
G01 X1.1809 Y2.5836
G01 X1.1414 Y2.5003
G01 X1.1368 Y2.4898
G01 X1.1327 Y2.4791
G01 X1.1016 Y2.3922
G01 X1.0980 Y2.3813
G01 X1.0949 Y2.3703
G01 X1.0725 Y2.2808
G01 X1.0700 Y2.2696
G01 X1.0680 Y2.2583
G01 X1.0545 Y2.1670
G01 X1.0531 Y2.1556
G01 X1.0523 Y2.1442
G01 X1.0477 Y2.0521
G01 X1.0475 Y2.0406
G01 X1.0477 Y2.0291
G01 X1.0523 Y1.9370
G01 X1.0531 Y1.9256
G01 X1.0545 Y1.9142
G01 X1.0680 Y1.8229
G01 X1.0700 Y1.8116
G01 X1.0725 Y1.8004
G01 X1.0949 Y1.7109
G01 X1.0980 Y1.6999
G01 X1.1016 Y1.6890
G01 X1.1327 Y1.6021
G01 X1.1368 Y1.5914
G01 X1.1414 Y1.5809
G01 X1.1809 Y1.4976
G01 X1.1860 Y1.4873
G01 X1.1917 Y1.4773
G01 X1.2391 Y1.3982
G01 X1.2453 Y1.3885
G01 X1.2519 Y1.3791
G01 X1.3068 Y1.3050
G01 X1.3139 Y1.2960
G01 X1.3214 Y1.2873
G01 X1.3833 Y1.2189
G01 X1.3912 Y1.2106
G01 X1.3995 Y1.2027
G01 X1.4679 Y1.1408
G01 X1.4766 Y1.1333
G01 X1.4856 Y1.1262
G01 X1.5597 Y1.0713
G01 X1.5691 Y1.0647
G01 X1.5788 Y1.0585
G01 X1.6579 Y1.0111
G01 X1.6679 Y1.0054
G01 X1.6782 Y1.0003
G01 X1.7615 Y0.9608
G01 X1.7720 Y0.9562
G01 X1.7827 Y0.9521
G01 X1.8696 Y0.9210
G01 X1.8805 Y0.9174
G01 X1.8915 Y0.9143
G01 X1.9810 Y0.8919
G01 X1.9922 Y0.8894
G01 X2.0035 Y0.8874
G01 X2.0948 Y0.8739
G01 X2.1062 Y0.8725
G01 X2.1176 Y0.8717
G01 X2.2097 Y0.8671
G01 X2.2212 Y0.8669
G01 X2.2327 Y0.8671
G01 X2.3248 Y0.8717
G01 X2.3362 Y0.8725
G01 X2.3476 Y0.8739
G01 X2.4389 Y0.8874
G01 X2.4502 Y0.8894
G01 X2.4614 Y0.8919
G01 X2.5509 Y0.9143
G01 X2.5619 Y0.9174
G01 X2.5728 Y0.9210
G01 X2.6597 Y0.9521
G01 X2.6704 Y0.9562
G01 X2.6809 Y0.9608
G01 X2.7642 Y1.0003
G01 X2.7745 Y1.0054
G01 X2.7845 Y1.0111
G01 X2.8636 Y1.0585
G01 X2.8733 Y1.0647
G01 X2.8827 Y1.0713
G01 X2.9568 Y1.1262
G01 X2.9658 Y1.1333
G01 X2.9745 Y1.1408
G01 X3.0429 Y1.2027
G01 X3.0512 Y1.2106
G01 X3.0591 Y1.2189
G01 X3.1210 Y1.2873
G01 X3.1285 Y1.2960
G01 X3.1356 Y1.3050
G01 X3.1905 Y1.3791
G01 X3.1971 Y1.3885
G01 X3.2033 Y1.3982
G01 X3.2507 Y1.4773
G01 X3.2564 Y1.4873
G01 X3.2615 Y1.4976
G01 X3.3010 Y1.5809
G01 X3.3056 Y1.5914
G01 X3.3097 Y1.6021
G01 X3.3408 Y1.6890
G01 X3.3444 Y1.6999
G01 X3.3475 Y1.7109
G01 X3.3699 Y1.8004
G01 X3.3724 Y1.8116
G01 X3.3744 Y1.8229
G01 X3.3879 Y1.9142
G01 X3.3893 Y1.9256
G01 X3.3901 Y1.9370
G01 X3.3947 Y2.0291
G01 X3.3947 Y2.0521
G01 X3.3901 Y2.1442
G01 X3.3893 Y2.1556
G01 X3.3879 Y2.1670
G01 X3.3744 Y2.2583
G01 X3.3724 Y2.2696
G01 X3.3699 Y2.2808
G01 X3.3475 Y2.3703
G01 X3.3444 Y2.3813
G01 X3.3408 Y2.3922
G01 X3.3097 Y2.4791
G01 X3.3056 Y2.4898
G01 X3.2683 Y2.5692
G01 X3.2683 Y2.9233
G01 X7.3801 Y7.0351
G01 X7.3903 Y7.0293
G01 X7.4006 Y7.0242
G01 X7.4682 Y6.9922
G01 X7.4787 Y6.9875
G01 X7.4894 Y6.9834
G01 X7.5708 Y6.9546
G01 X7.6544 Y6.9333
G01 X7.6656 Y6.9308
G01 X7.6769 Y6.9288
G01 X7.7623 Y6.9165
G01 X7.7738 Y6.9156
G01 X7.8600 Y6.9117
G01 X7.9462 Y6.9156
G01 X7.9577 Y6.9165
G01 X8.0431 Y6.9288
G01 X8.0544 Y6.9308
G01 X8.0656 Y6.9333
G01 X8.1492 Y6.9546
G01 X8.1601 Y6.9582
G01 X8.2413 Y6.9875
G01 X8.3194 Y7.0242
G01 X8.3297 Y7.0293
G01 X8.3397 Y7.0350
G01 X8.4135 Y7.0796
G01 X8.4229 Y7.0862
G01 X8.4921 Y7.1378
G01 X8.5562 Y7.1956
G01 X8.5645 Y7.2035
G01 X8.5724 Y7.2118
G01 X8.6302 Y7.2759
G01 X8.6818 Y7.3451
G01 X8.6884 Y7.3545
G01 X8.6946 Y7.3642
G01 X8.7330 Y7.4283
G01 X8.7387 Y7.4383
G01 X8.7438 Y7.4486
G01 X8.7805 Y7.5267
G01 X8.8098 Y7.6079
G01 X8.8134 Y7.6188
G01 X8.8165 Y7.6298
G01 X8.8372 Y7.7136
G01 X8.8392 Y7.7249
G01 X8.8515 Y7.8103
G01 X8.8524 Y7.8218
G01 X8.8563 Y7.9080
G01 X8.8563 Y9.4320
G01 X8.8560 Y9.4435
G01 X8.8515 Y9.5297
G01 X8.8392 Y9.6151
G01 X8.8372 Y9.6264
G01 X8.8347 Y9.6376
G01 X8.8134 Y9.7212
G01 X8.8098 Y9.7321
G01 X8.7805 Y9.8133
G01 X8.7438 Y9.8914
G01 X8.7387 Y9.9017
G01 X8.7330 Y9.9117
G01 X8.6884 Y9.9855
G01 X8.6818 Y9.9949
G01 X8.6302 Y10.0641
G01 X8.5724 Y10.1282
G01 X8.5645 Y10.1365
G01 X8.5562 Y10.1444
G01 X8.4921 Y10.2022
G01 X8.4229 Y10.2538
G01 X8.4135 Y10.2604
G01 X8.3397 Y10.3050
G01 X8.3297 Y10.3107
G01 X8.3194 Y10.3158
G01 X8.2413 Y10.3525
G01 X8.1601 Y10.3818
G01 X8.1492 Y10.3854
G01 X8.0656 Y10.4067
G01 X8.0544 Y10.4092
G01 X8.0431 Y10.4112
G01 X7.9577 Y10.4235
G01 X7.9462 Y10.4244
G01 X7.8600 Y10.4283
G01 X7.7738 Y10.4244
G01 X7.7623 Y10.4235
G01 X7.6769 Y10.4112
G01 X7.6656 Y10.4092
G01 X7.6544 Y10.4067
G01 X7.5708 Y10.3854
G01 X7.5599 Y10.3818
G01 X7.4787 Y10.3525
G01 X7.4006 Y10.3158
G01 X7.3903 Y10.3107
G01 X7.3803 Y10.3050
G01 X7.3065 Y10.2604
G01 X7.2971 Y10.2538
G01 X7.2279 Y10.2022
G01 X7.1638 Y10.1444
G01 X7.1555 Y10.1365
G01 X7.1476 Y10.1282
G01 X7.0898 Y10.0641
G01 X7.0382 Y9.9949
G01 X7.0316 Y9.9855
G01 X7.0254 Y9.9758
G01 X6.9870 Y9.9117
G01 X6.9813 Y9.9017
G01 X6.9762 Y9.8914
G01 X6.9395 Y9.8133
G01 X6.9102 Y9.7321
G01 X6.9066 Y9.7212
G01 X6.9035 Y9.7102
G01 X6.8828 Y9.6264
G01 X6.8808 Y9.6151
G01 X6.8685 Y9.5297
G01 X6.8676 Y9.5182
G01 X6.8637 Y9.4377
G01 X6.8637 Y9.2838
G01 X6.8212 Y9.2592
G01 X6.7985 Y9.2444
G01 X6.7411 Y9.2031
G01 X6.7199 Y9.1862
G01 X6.6936 Y9.1627
G01 X6.6755 Y9.1471
G01 X6.6669 Y9.1394
G01 X6.6475 Y9.1205
G01 X1.5675 Y4.0405
G01 X1.5596 Y4.0322
G01 X1.5018 Y3.9681
G01 X1.4502 Y3.8989
G01 X1.4436 Y3.8895
G01 X1.3990 Y3.8157
G01 X1.3933 Y3.8057
G01 X1.3882 Y3.7954
G01 X1.3515 Y3.7173
G01 X1.3222 Y3.6361
G01 X1.3186 Y3.6252
G01 X1.3155 Y3.6142
G01 X1.2948 Y3.5304
G01 X1.2928 Y3.5191
G01 X1.2805 Y3.4337
G01 X1.2796 Y3.4222
G01 X1.2757 Y3.3417
G01 X1.2757 Y2.7342
G00 X1.2757 Y2.7342
G01 F60.00
G01 Z-0.5000
G01 F60.00
G01 X1.2519 Y2.7021
G01 X1.2453 Y2.6927
G01 X1.2391 Y2.6830
G01 X1.1917 Y2.6039
G01 X1.1860 Y2.5939
G01 X1.1809 Y2.5836
G01 X1.1414 Y2.5003
G01 X1.1368 Y2.4898
G01 X1.1327 Y2.4791
G01 X1.1016 Y2.3922
G01 X1.0980 Y2.3813
G01 X1.0949 Y2.3703
G01 X1.0725 Y2.2808
G01 X1.0700 Y2.2696
G01 X1.0680 Y2.2583
G01 X1.0545 Y2.1670
G01 X1.0531 Y2.1556
G01 X1.0523 Y2.1442
G01 X1.0477 Y2.0521
G01 X1.0475 Y2.0406
G01 X1.0477 Y2.0291
G01 X1.0523 Y1.9370
G01 X1.0531 Y1.9256
G01 X1.0545 Y1.9142
G01 X1.0680 Y1.8229
G01 X1.0700 Y1.8116
G01 X1.0725 Y1.8004
G01 X1.0949 Y1.7109
G01 X1.0980 Y1.6999
G01 X1.1016 Y1.6890
G01 X1.1327 Y1.6021
G01 X1.1368 Y1.5914
G01 X1.1414 Y1.5809
G01 X1.1809 Y1.4976
G01 X1.1860 Y1.4873
G01 X1.1917 Y1.4773
G01 X1.2391 Y1.3982
G01 X1.2453 Y1.3885
G01 X1.2519 Y1.3791
G01 X1.3068 Y1.3050
G01 X1.3139 Y1.2960
G01 X1.3214 Y1.2873
G01 X1.3833 Y1.2189
G01 X1.3912 Y1.2106
G01 X1.3995 Y1.2027
G01 X1.4679 Y1.1408
G01 X1.4766 Y1.1333
G01 X1.4856 Y1.1262
G01 X1.5597 Y1.0713
G01 X1.5691 Y1.0647
G01 X1.5788 Y1.0585
G01 X1.6579 Y1.0111
G01 X1.6679 Y1.0054
G01 X1.6782 Y1.0003
G01 X1.7615 Y0.9608
G01 X1.7720 Y0.9562
G01 X1.7827 Y0.9521
G01 X1.8696 Y0.9210
G01 X1.8805 Y0.9174
G01 X1.8915 Y0.9143
G01 X1.9810 Y0.8919
G01 X1.9922 Y0.8894
G01 X2.0035 Y0.8874
G01 X2.0948 Y0.8739
G01 X2.1062 Y0.8725
G01 X2.1176 Y0.8717
G01 X2.2097 Y0.8671
G01 X2.2212 Y0.8669
G01 X2.2327 Y0.8671
G01 X2.3248 Y0.8717
G01 X2.3362 Y0.8725
G01 X2.3476 Y0.8739
G01 X2.4389 Y0.8874
G01 X2.4502 Y0.8894
G01 X2.4614 Y0.8919
G01 X2.5509 Y0.9143
G01 X2.5619 Y0.9174
G01 X2.5728 Y0.9210
G01 X2.6597 Y0.9521
G01 X2.6704 Y0.9562
G01 X2.6809 Y0.9608
G01 X2.7642 Y1.0003
G01 X2.7745 Y1.0054
G01 X2.7845 Y1.0111
G01 X2.8636 Y1.0585
G01 X2.8733 Y1.0647
G01 X2.8827 Y1.0713
G01 X2.9568 Y1.1262
G01 X2.9658 Y1.1333
G01 X2.9745 Y1.1408
G01 X3.0429 Y1.2027
G01 X3.0512 Y1.2106
G01 X3.0591 Y1.2189
G01 X3.1210 Y1.2873
G01 X3.1285 Y1.2960
G01 X3.1356 Y1.3050
G01 X3.1905 Y1.3791
G01 X3.1971 Y1.3885
G01 X3.2033 Y1.3982
G01 X3.2507 Y1.4773
G01 X3.2564 Y1.4873
G01 X3.2615 Y1.4976
G01 X3.3010 Y1.5809
G01 X3.3056 Y1.5914
G01 X3.3097 Y1.6021
G01 X3.3408 Y1.6890
G01 X3.3444 Y1.6999
G01 X3.3475 Y1.7109
G01 X3.3699 Y1.8004
G01 X3.3724 Y1.8116
G01 X3.3744 Y1.8229
G01 X3.3879 Y1.9142
G01 X3.3893 Y1.9256
G01 X3.3901 Y1.9370
G01 X3.3947 Y2.0291
G01 X3.3947 Y2.0521
G01 X3.3901 Y2.1442
G01 X3.3893 Y2.1556
G01 X3.3879 Y2.1670
G01 X3.3744 Y2.2583
G01 X3.3724 Y2.2696
G01 X3.3699 Y2.2808
G01 X3.3475 Y2.3703
G01 X3.3444 Y2.3813
G01 X3.3408 Y2.3922
G01 X3.3097 Y2.4791
G01 X3.3056 Y2.4898
G01 X3.2683 Y2.5692
G01 X3.2683 Y2.9233
G01 X7.3801 Y7.0351
G01 X7.3903 Y7.0293
G01 X7.4006 Y7.0242
G01 X7.4682 Y6.9922
G01 X7.4787 Y6.9875
G01 X7.4894 Y6.9834
G01 X7.5708 Y6.9546
G01 X7.6544 Y6.9333
G01 X7.6656 Y6.9308
G01 X7.6769 Y6.9288
G01 X7.7623 Y6.9165
G01 X7.7738 Y6.9156
G01 X7.8600 Y6.9117
G01 X7.9462 Y6.9156
G01 X7.9577 Y6.9165
G01 X8.0431 Y6.9288
G01 X8.0544 Y6.9308
G01 X8.0656 Y6.9333
G01 X8.1492 Y6.9546
G01 X8.1601 Y6.9582
G01 X8.2413 Y6.9875
G01 X8.3194 Y7.0242
G01 X8.3297 Y7.0293
G01 X8.3397 Y7.0350
G01 X8.4135 Y7.0796
G01 X8.4229 Y7.0862
G01 X8.4921 Y7.1378
G01 X8.5562 Y7.1956
G01 X8.5645 Y7.2035
G01 X8.5724 Y7.2118
G01 X8.6302 Y7.2759
G01 X8.6818 Y7.3451
G01 X8.6884 Y7.3545
G01 X8.6946 Y7.3642
G01 X8.7330 Y7.4283
G01 X8.7387 Y7.4383
G01 X8.7438 Y7.4486
G01 X8.7805 Y7.5267
G01 X8.8098 Y7.6079
G01 X8.8134 Y7.6188
G01 X8.8165 Y7.6298
G01 X8.8372 Y7.7136
G01 X8.8392 Y7.7249
G01 X8.8515 Y7.8103
G01 X8.8524 Y7.8218
G01 X8.8563 Y7.9080
G01 X8.8563 Y9.4320
G01 X8.8560 Y9.4435
G01 X8.8515 Y9.5297
G01 X8.8392 Y9.6151
G01 X8.8372 Y9.6264
G01 X8.8347 Y9.6376
G01 X8.8134 Y9.7212
G01 X8.8098 Y9.7321
G01 X8.7805 Y9.8133
G01 X8.7438 Y9.8914
G01 X8.7387 Y9.9017
G01 X8.7330 Y9.9117
G01 X8.6884 Y9.9855
G01 X8.6818 Y9.9949
G01 X8.6302 Y10.0641
G01 X8.5724 Y10.1282
G01 X8.5645 Y10.1365
G01 X8.5562 Y10.1444
G01 X8.4921 Y10.2022
G01 X8.4229 Y10.2538
G01 X8.4135 Y10.2604
G01 X8.3397 Y10.3050
G01 X8.3297 Y10.3107
G01 X8.3194 Y10.3158
G01 X8.2413 Y10.3525
G01 X8.1601 Y10.3818
G01 X8.1492 Y10.3854
G01 X8.0656 Y10.4067
G01 X8.0544 Y10.4092
G01 X8.0431 Y10.4112
G01 X7.9577 Y10.4235
G01 X7.9462 Y10.4244
G01 X7.8600 Y10.4283
G01 X7.7738 Y10.4244
G01 X7.7623 Y10.4235
G01 X7.6769 Y10.4112
G01 X7.6656 Y10.4092
G01 X7.6544 Y10.4067
G01 X7.5708 Y10.3854
G01 X7.5599 Y10.3818
G01 X7.4787 Y10.3525
G01 X7.4006 Y10.3158
G01 X7.3903 Y10.3107
G01 X7.3803 Y10.3050
G01 X7.3065 Y10.2604
G01 X7.2971 Y10.2538
G01 X7.2279 Y10.2022
G01 X7.1638 Y10.1444
G01 X7.1555 Y10.1365
G01 X7.1476 Y10.1282
G01 X7.0898 Y10.0641
G01 X7.0382 Y9.9949
G01 X7.0316 Y9.9855
G01 X7.0254 Y9.9758
G01 X6.9870 Y9.9117
G01 X6.9813 Y9.9017
G01 X6.9762 Y9.8914
G01 X6.9395 Y9.8133
G01 X6.9102 Y9.7321
G01 X6.9066 Y9.7212
G01 X6.9035 Y9.7102
G01 X6.8828 Y9.6264
G01 X6.8808 Y9.6151
G01 X6.8685 Y9.5297
G01 X6.8676 Y9.5182
G01 X6.8637 Y9.4377
G01 X6.8637 Y9.2838
G01 X6.8212 Y9.2592
G01 X6.7985 Y9.2444
G01 X6.7411 Y9.2031
G01 X6.7199 Y9.1862
G01 X6.6936 Y9.1627
G01 X6.6755 Y9.1471
G01 X6.6669 Y9.1394
G01 X6.6475 Y9.1205
G01 X1.5675 Y4.0405
G01 X1.5596 Y4.0322
G01 X1.5018 Y3.9681
G01 X1.4502 Y3.8989
G01 X1.4436 Y3.8895
G01 X1.3990 Y3.8157
G01 X1.3933 Y3.8057
G01 X1.3882 Y3.7954
G01 X1.3515 Y3.7173
G01 X1.3222 Y3.6361
G01 X1.3186 Y3.6252
G01 X1.3155 Y3.6142
G01 X1.2948 Y3.5304
G01 X1.2928 Y3.5191
G01 X1.2805 Y3.4337
G01 X1.2796 Y3.4222
G01 X1.2757 Y3.3417
G01 X1.2757 Y2.7342
G00 Z2.0000
M05
G00 Z2.0000
G00 Z5.00
G00 X0.0 Y0.0


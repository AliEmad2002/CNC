<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="9.6.2">
<drawing>
<settings>
<setting alwaysvectorfont="no"/>
<setting verticaltext="up"/>
</settings>
<grid distance="0.1" unitdist="inch" unit="inch" style="lines" multiple="1" display="no" altdistance="0.01" altunitdist="inch" altunit="inch"/>
<layers>
<layer number="1" name="Top" color="4" fill="1" visible="no" active="no"/>
<layer number="16" name="Bottom" color="1" fill="1" visible="no" active="no"/>
<layer number="17" name="Pads" color="2" fill="1" visible="no" active="no"/>
<layer number="18" name="Vias" color="2" fill="1" visible="no" active="no"/>
<layer number="19" name="Unrouted" color="6" fill="1" visible="no" active="no"/>
<layer number="20" name="Dimension" color="24" fill="1" visible="no" active="no"/>
<layer number="21" name="tPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="22" name="bPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="23" name="tOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="24" name="bOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="25" name="tNames" color="7" fill="1" visible="no" active="no"/>
<layer number="26" name="bNames" color="7" fill="1" visible="no" active="no"/>
<layer number="27" name="tValues" color="7" fill="1" visible="no" active="no"/>
<layer number="28" name="bValues" color="7" fill="1" visible="no" active="no"/>
<layer number="29" name="tStop" color="7" fill="3" visible="no" active="no"/>
<layer number="30" name="bStop" color="7" fill="6" visible="no" active="no"/>
<layer number="31" name="tCream" color="7" fill="4" visible="no" active="no"/>
<layer number="32" name="bCream" color="7" fill="5" visible="no" active="no"/>
<layer number="33" name="tFinish" color="6" fill="3" visible="no" active="no"/>
<layer number="34" name="bFinish" color="6" fill="6" visible="no" active="no"/>
<layer number="35" name="tGlue" color="7" fill="4" visible="no" active="no"/>
<layer number="36" name="bGlue" color="7" fill="5" visible="no" active="no"/>
<layer number="37" name="tTest" color="7" fill="1" visible="no" active="no"/>
<layer number="38" name="bTest" color="7" fill="1" visible="no" active="no"/>
<layer number="39" name="tKeepout" color="4" fill="11" visible="no" active="no"/>
<layer number="40" name="bKeepout" color="1" fill="11" visible="no" active="no"/>
<layer number="41" name="tRestrict" color="4" fill="10" visible="no" active="no"/>
<layer number="42" name="bRestrict" color="1" fill="10" visible="no" active="no"/>
<layer number="43" name="vRestrict" color="2" fill="10" visible="no" active="no"/>
<layer number="44" name="Drills" color="7" fill="1" visible="no" active="no"/>
<layer number="45" name="Holes" color="7" fill="1" visible="no" active="no"/>
<layer number="46" name="Milling" color="3" fill="1" visible="no" active="no"/>
<layer number="47" name="Measures" color="7" fill="1" visible="no" active="no"/>
<layer number="48" name="Document" color="7" fill="1" visible="no" active="no"/>
<layer number="49" name="Reference" color="7" fill="1" visible="no" active="no"/>
<layer number="50" name="dxf" color="7" fill="1" visible="no" active="no"/>
<layer number="51" name="tDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="52" name="bDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="53" name="tGND_GNDA" color="7" fill="1" visible="no" active="no"/>
<layer number="54" name="bGND_GNDA" color="7" fill="1" visible="no" active="no"/>
<layer number="56" name="wert" color="7" fill="1" visible="no" active="no"/>
<layer number="57" name="tCAD" color="7" fill="1" visible="no" active="no"/>
<layer number="58" name="b3D" color="7" fill="4" visible="no" active="no"/>
<layer number="59" name="tCarbon" color="7" fill="1" visible="no" active="no"/>
<layer number="60" name="bCarbon" color="7" fill="1" visible="no" active="no"/>
<layer number="88" name="SimResults" color="9" fill="1" visible="yes" active="yes"/>
<layer number="89" name="SimProbes" color="9" fill="1" visible="yes" active="yes"/>
<layer number="90" name="Modules" color="5" fill="1" visible="yes" active="yes"/>
<layer number="91" name="Nets" color="2" fill="1" visible="yes" active="yes"/>
<layer number="92" name="Busses" color="1" fill="1" visible="yes" active="yes"/>
<layer number="93" name="Pins" color="2" fill="1" visible="no" active="yes"/>
<layer number="94" name="Symbols" color="4" fill="1" visible="yes" active="yes"/>
<layer number="95" name="Names" color="7" fill="1" visible="yes" active="yes"/>
<layer number="96" name="Values" color="7" fill="1" visible="yes" active="yes"/>
<layer number="97" name="Info" color="7" fill="1" visible="yes" active="yes"/>
<layer number="98" name="Guide" color="6" fill="1" visible="yes" active="yes"/>
<layer number="99" name="SpiceOrder" color="7" fill="1" visible="yes" active="yes"/>
<layer number="100" name="5V" color="7" fill="1" visible="yes" active="yes"/>
</layers>
<schematic xreflabel="%F%N/%S.%C%R" xrefpart="/%S.%C%R">
<libraries>
<library name="BluePill" urn="urn:adsk.wipprod:fs.file:vf.zv9c6spOQmC8O2Ukh5v0tg">
<packages>
<package name="BLUE_PILL">
<pad name="P$1" x="-7.62" y="15.24" drill="0.8" shape="long"/>
<pad name="P$2" x="-7.62" y="12.7" drill="0.8" shape="long"/>
<pad name="P$3" x="-7.62" y="10.16" drill="0.8" shape="long"/>
<pad name="P$4" x="-7.62" y="7.62" drill="0.8" shape="long"/>
<pad name="P$5" x="-7.62" y="5.08" drill="0.8" shape="long"/>
<pad name="P$6" x="-7.62" y="2.54" drill="0.8" shape="long"/>
<pad name="P$7" x="-7.62" y="0" drill="0.8" shape="long"/>
<pad name="P$8" x="-7.62" y="-2.54" drill="0.8" shape="long"/>
<pad name="P$9" x="-7.62" y="-5.08" drill="0.8" shape="long"/>
<pad name="P$10" x="-7.62" y="-7.62" drill="0.8" shape="long"/>
<pad name="P$11" x="-7.62" y="-10.16" drill="0.8" shape="long"/>
<pad name="P$12" x="-7.62" y="-12.7" drill="0.8" shape="long"/>
<pad name="P$13" x="-7.62" y="-15.24" drill="0.8" shape="long"/>
<pad name="P$14" x="-7.62" y="-17.78" drill="0.8" shape="long"/>
<pad name="P$15" x="-7.62" y="-20.32" drill="0.8" shape="long"/>
<pad name="P$16" x="-7.62" y="-22.86" drill="0.8" shape="long"/>
<pad name="P$17" x="-7.62" y="-25.4" drill="0.8" shape="long"/>
<pad name="P$18" x="-7.62" y="-27.94" drill="0.8" shape="long"/>
<pad name="P$19" x="-7.62" y="-30.48" drill="0.8" shape="long"/>
<pad name="P$20" x="-7.62" y="-33.02" drill="0.8" shape="long"/>
<pad name="P$21" x="7.62" y="15.24" drill="0.8" shape="long"/>
<pad name="P$22" x="7.62" y="12.7" drill="0.8" shape="long"/>
<pad name="P$23" x="7.62" y="10.16" drill="0.8" shape="long"/>
<pad name="P$24" x="7.62" y="7.62" drill="0.8" shape="long"/>
<pad name="P$25" x="7.62" y="5.08" drill="0.8" shape="long"/>
<pad name="P$26" x="7.62" y="2.54" drill="0.8" shape="long"/>
<pad name="P$27" x="7.62" y="0" drill="0.8" shape="long"/>
<pad name="P$28" x="7.62" y="-2.54" drill="0.8" shape="long"/>
<pad name="P$29" x="7.62" y="-5.08" drill="0.8" shape="long"/>
<pad name="P$30" x="7.62" y="-7.62" drill="0.8" shape="long"/>
<pad name="P$31" x="7.62" y="-10.16" drill="0.8" shape="long"/>
<pad name="P$32" x="7.62" y="-12.7" drill="0.8" shape="long"/>
<pad name="P$33" x="7.62" y="-15.24" drill="0.8" shape="long"/>
<pad name="P$34" x="7.62" y="-17.78" drill="0.8" shape="long"/>
<pad name="P$35" x="7.62" y="-20.32" drill="0.8" shape="long"/>
<pad name="P$36" x="7.62" y="-22.86" drill="0.8" shape="long"/>
<pad name="P$37" x="7.62" y="-25.4" drill="0.8" shape="long"/>
<pad name="P$38" x="7.62" y="-27.94" drill="0.8" shape="long"/>
<pad name="P$39" x="7.62" y="-30.48" drill="0.8" shape="long"/>
<pad name="P$40" x="7.62" y="-33.02" drill="0.8" shape="long"/>
<wire x1="-3.81" y1="17.78" x2="-2.54" y2="17.78" width="0.127" layer="21"/>
<wire x1="2.54" y1="17.78" x2="3.81" y2="17.78" width="0.127" layer="21"/>
<wire x1="-3.81" y1="17.78" x2="-3.81" y2="13.335" width="0.127" layer="21"/>
<wire x1="-3.81" y1="13.335" x2="-3.175" y2="13.335" width="0.127" layer="21"/>
<wire x1="-3.175" y1="13.335" x2="-2.54" y2="12.7" width="0.127" layer="21"/>
<wire x1="-2.54" y1="12.7" x2="2.54" y2="12.7" width="0.127" layer="21"/>
<wire x1="2.54" y1="12.7" x2="3.175" y2="13.335" width="0.127" layer="21"/>
<wire x1="3.175" y1="13.335" x2="3.81" y2="13.335" width="0.127" layer="21"/>
<wire x1="3.81" y1="13.335" x2="3.81" y2="17.78" width="0.127" layer="21"/>
<wire x1="-5.08" y1="-8.89" x2="-4.445" y2="-8.255" width="0.127" layer="21"/>
<wire x1="-4.445" y1="-8.255" x2="-3.81" y2="-7.62" width="0.127" layer="21"/>
<wire x1="-3.81" y1="-7.62" x2="-3.175" y2="-6.985" width="0.127" layer="21"/>
<wire x1="-3.175" y1="-6.985" x2="-2.54" y2="-6.35" width="0.127" layer="21"/>
<wire x1="-2.54" y1="-6.35" x2="-1.905" y2="-5.715" width="0.127" layer="21"/>
<wire x1="-1.905" y1="-5.715" x2="-1.27" y2="-5.08" width="0.127" layer="21"/>
<wire x1="-1.27" y1="-5.08" x2="-0.635" y2="-4.445" width="0.127" layer="21"/>
<wire x1="-0.635" y1="-4.445" x2="0" y2="-3.81" width="0.127" layer="21"/>
<wire x1="0" y1="-3.81" x2="0.635" y2="-4.445" width="0.127" layer="21"/>
<wire x1="0.635" y1="-4.445" x2="1.27" y2="-5.08" width="0.127" layer="21"/>
<wire x1="1.27" y1="-5.08" x2="1.905" y2="-5.715" width="0.127" layer="21"/>
<wire x1="1.905" y1="-5.715" x2="2.54" y2="-6.35" width="0.127" layer="21"/>
<wire x1="2.54" y1="-6.35" x2="3.175" y2="-6.985" width="0.127" layer="21"/>
<wire x1="3.175" y1="-6.985" x2="3.81" y2="-7.62" width="0.127" layer="21"/>
<wire x1="3.81" y1="-7.62" x2="4.445" y2="-8.255" width="0.127" layer="21"/>
<wire x1="4.445" y1="-8.255" x2="5.08" y2="-8.89" width="0.127" layer="21"/>
<wire x1="5.08" y1="-8.89" x2="4.445" y2="-9.525" width="0.127" layer="21"/>
<wire x1="4.445" y1="-9.525" x2="3.81" y2="-10.16" width="0.127" layer="21"/>
<wire x1="3.81" y1="-10.16" x2="3.175" y2="-10.795" width="0.127" layer="21"/>
<wire x1="3.175" y1="-10.795" x2="2.54" y2="-11.43" width="0.127" layer="21"/>
<wire x1="2.54" y1="-11.43" x2="1.905" y2="-12.065" width="0.127" layer="21"/>
<wire x1="1.905" y1="-12.065" x2="1.27" y2="-12.7" width="0.127" layer="21"/>
<wire x1="1.27" y1="-12.7" x2="0.635" y2="-13.335" width="0.127" layer="21"/>
<wire x1="0.635" y1="-13.335" x2="0" y2="-13.97" width="0.127" layer="21"/>
<wire x1="0" y1="-13.97" x2="-0.635" y2="-13.335" width="0.127" layer="21"/>
<wire x1="-0.635" y1="-13.335" x2="-1.27" y2="-12.7" width="0.127" layer="21"/>
<wire x1="-1.27" y1="-12.7" x2="-1.905" y2="-12.065" width="0.127" layer="21"/>
<wire x1="-1.905" y1="-12.065" x2="-2.54" y2="-11.43" width="0.127" layer="21"/>
<wire x1="-2.54" y1="-11.43" x2="-3.175" y2="-10.795" width="0.127" layer="21"/>
<wire x1="-3.175" y1="-10.795" x2="-3.81" y2="-10.16" width="0.127" layer="21"/>
<wire x1="-3.81" y1="-10.16" x2="-4.445" y2="-9.525" width="0.127" layer="21"/>
<wire x1="-4.445" y1="-9.525" x2="-5.08" y2="-8.89" width="0.127" layer="21"/>
<text x="-1.905" y="-11.43" size="1.27" layer="21" rot="R46.6">STM32</text>
<wire x1="4.445" y1="-9.525" x2="5.08" y2="-10.16" width="0.127" layer="21"/>
<wire x1="3.81" y1="-10.16" x2="4.445" y2="-10.795" width="0.127" layer="21"/>
<wire x1="3.175" y1="-10.795" x2="3.81" y2="-11.43" width="0.127" layer="21"/>
<wire x1="2.54" y1="-11.43" x2="3.175" y2="-12.065" width="0.127" layer="21"/>
<wire x1="1.905" y1="-12.065" x2="2.54" y2="-12.7" width="0.127" layer="21"/>
<wire x1="1.27" y1="-12.7" x2="1.905" y2="-13.335" width="0.127" layer="21"/>
<wire x1="0.635" y1="-13.335" x2="1.27" y2="-13.97" width="0.127" layer="21"/>
<wire x1="-0.635" y1="-13.335" x2="-1.27" y2="-13.97" width="0.127" layer="21"/>
<wire x1="-1.27" y1="-12.7" x2="-1.905" y2="-13.335" width="0.127" layer="21"/>
<wire x1="-1.905" y1="-12.065" x2="-2.54" y2="-12.7" width="0.127" layer="21"/>
<wire x1="-2.54" y1="-11.43" x2="-3.175" y2="-12.065" width="0.127" layer="21"/>
<wire x1="-3.175" y1="-10.795" x2="-3.81" y2="-11.43" width="0.127" layer="21"/>
<wire x1="-3.81" y1="-10.16" x2="-4.445" y2="-10.795" width="0.127" layer="21"/>
<wire x1="-4.445" y1="-6.985" x2="-3.81" y2="-7.62" width="0.127" layer="21"/>
<wire x1="-3.81" y1="-6.35" x2="-3.175" y2="-6.985" width="0.127" layer="21"/>
<wire x1="-3.175" y1="-5.715" x2="-2.54" y2="-6.35" width="0.127" layer="21"/>
<wire x1="-2.54" y1="-5.08" x2="-1.905" y2="-5.715" width="0.127" layer="21"/>
<wire x1="-1.905" y1="-4.445" x2="-1.27" y2="-5.08" width="0.127" layer="21"/>
<wire x1="-1.27" y1="-3.81" x2="-0.635" y2="-4.445" width="0.127" layer="21"/>
<wire x1="0.635" y1="-4.445" x2="1.27" y2="-3.81" width="0.127" layer="21"/>
<wire x1="1.27" y1="-5.08" x2="1.905" y2="-4.445" width="0.127" layer="21"/>
<wire x1="1.905" y1="-5.715" x2="2.54" y2="-5.08" width="0.127" layer="21"/>
<wire x1="2.54" y1="-6.35" x2="3.175" y2="-5.715" width="0.127" layer="21"/>
<wire x1="3.175" y1="-6.985" x2="3.81" y2="-6.35" width="0.127" layer="21"/>
<wire x1="3.81" y1="-7.62" x2="4.445" y2="-6.985" width="0.127" layer="21"/>
<wire x1="3.81" y1="17.78" x2="8.89" y2="17.78" width="0.127" layer="21"/>
<wire x1="8.89" y1="17.78" x2="10.16" y2="16.51" width="0.127" layer="21" curve="-90"/>
<wire x1="10.16" y1="16.51" x2="10.16" y2="-33.02" width="0.127" layer="21"/>
<wire x1="10.16" y1="-33.02" x2="8.89" y2="-34.29" width="0.127" layer="21" curve="-90"/>
<wire x1="8.89" y1="-34.29" x2="-8.89" y2="-34.29" width="0.127" layer="21"/>
<wire x1="-8.89" y1="-34.29" x2="-10.16" y2="-33.02" width="0.127" layer="21" curve="-90"/>
<wire x1="-10.16" y1="-33.02" x2="-10.16" y2="16.51" width="0.127" layer="21"/>
<wire x1="-10.16" y1="16.51" x2="-8.89" y2="17.78" width="0.127" layer="21" curve="-90"/>
<wire x1="-8.89" y1="17.78" x2="-3.81" y2="17.78" width="0.127" layer="21"/>
<wire x1="-3.81" y1="17.78" x2="-2.54" y2="17.78" width="0.127" layer="21" curve="90"/>
<wire x1="-2.54" y1="17.78" x2="2.54" y2="17.78" width="0.127" layer="21"/>
<wire x1="2.54" y1="17.78" x2="3.81" y2="17.78" width="0.127" layer="21" curve="90"/>
<wire x1="-2.54" y1="15.24" x2="-2.54" y2="13.97" width="0.127" layer="21"/>
<wire x1="-2.54" y1="13.97" x2="-1.27" y2="13.97" width="0.127" layer="21"/>
<wire x1="-1.27" y1="13.97" x2="-1.27" y2="15.24" width="0.127" layer="21"/>
<wire x1="1.27" y1="15.24" x2="1.27" y2="13.97" width="0.127" layer="21"/>
<wire x1="1.27" y1="13.97" x2="2.54" y2="13.97" width="0.127" layer="21"/>
<wire x1="2.54" y1="13.97" x2="2.54" y2="15.24" width="0.127" layer="21"/>
<wire x1="-2.54" y1="15.24" x2="-1.27" y2="15.24" width="0.127" layer="21"/>
<wire x1="1.27" y1="15.24" x2="2.54" y2="15.24" width="0.127" layer="21"/>
<wire x1="-4.445" y1="-9.525" x2="-5.08" y2="-10.16" width="0.127" layer="21"/>
<wire x1="-5.08" y1="-7.62" x2="-4.445" y2="-8.255" width="0.127" layer="21"/>
<wire x1="5.08" y1="-7.62" x2="4.445" y2="-8.255" width="0.127" layer="21"/>
<circle x="-3.81" y="-8.89" radius="0.635" width="0.127" layer="21"/>
<wire x1="-4.445" y1="-21.59" x2="-2.54" y2="-23.495" width="0.127" layer="21" curve="90"/>
<wire x1="-2.54" y1="-23.495" x2="2.54" y2="-23.495" width="0.127" layer="21"/>
<wire x1="2.54" y1="-23.495" x2="4.445" y2="-21.59" width="0.127" layer="21" curve="90"/>
<wire x1="4.445" y1="-21.59" x2="2.54" y2="-19.685" width="0.127" layer="21" curve="90"/>
<wire x1="2.54" y1="-19.685" x2="-2.54" y2="-19.685" width="0.127" layer="21"/>
<wire x1="-2.54" y1="-19.685" x2="-4.445" y2="-21.59" width="0.127" layer="21" curve="90"/>
<wire x1="1.27" y1="8.89" x2="2.54" y2="8.89" width="0.127" layer="21"/>
<wire x1="2.54" y1="8.89" x2="2.54" y2="5.08" width="0.127" layer="21"/>
<wire x1="2.54" y1="5.08" x2="1.27" y2="5.08" width="0.127" layer="21"/>
<wire x1="1.27" y1="5.08" x2="1.27" y2="6.35" width="0.127" layer="21"/>
<wire x1="1.27" y1="6.35" x2="1.27" y2="7.62" width="0.127" layer="21"/>
<wire x1="1.27" y1="7.62" x2="1.27" y2="8.89" width="0.127" layer="21"/>
<wire x1="2.54" y1="8.89" x2="3.81" y2="8.89" width="0.127" layer="21"/>
<wire x1="3.81" y1="8.89" x2="3.81" y2="7.62" width="0.127" layer="21"/>
<wire x1="3.81" y1="7.62" x2="3.81" y2="6.35" width="0.127" layer="21"/>
<wire x1="3.81" y1="6.35" x2="3.81" y2="5.08" width="0.127" layer="21"/>
<wire x1="3.81" y1="5.08" x2="2.54" y2="5.08" width="0.127" layer="21"/>
<circle x="-2.54" y="6.35" radius="0.635" width="0.127" layer="21"/>
<wire x1="-3.81" y1="7.62" x2="-3.175" y2="7.62" width="0.127" layer="21"/>
<wire x1="-3.175" y1="7.62" x2="-1.905" y2="7.62" width="0.127" layer="21"/>
<wire x1="-1.905" y1="7.62" x2="-1.27" y2="7.62" width="0.127" layer="21"/>
<wire x1="-1.27" y1="7.62" x2="-1.27" y2="5.08" width="0.127" layer="21"/>
<wire x1="-1.27" y1="5.08" x2="-1.905" y2="5.08" width="0.127" layer="21"/>
<wire x1="-1.905" y1="5.08" x2="-3.175" y2="5.08" width="0.127" layer="21"/>
<wire x1="-3.175" y1="5.08" x2="-3.81" y2="5.08" width="0.127" layer="21"/>
<wire x1="-3.81" y1="5.08" x2="-3.81" y2="7.62" width="0.127" layer="21"/>
<wire x1="-1.905" y1="5.08" x2="-1.905" y2="4.445" width="0.127" layer="21"/>
<wire x1="-3.175" y1="5.08" x2="-3.175" y2="4.445" width="0.127" layer="21"/>
<wire x1="-3.175" y1="7.62" x2="-3.175" y2="8.255" width="0.127" layer="21"/>
<wire x1="-1.905" y1="7.62" x2="-1.905" y2="8.255" width="0.127" layer="21"/>
<wire x1="1.27" y1="7.62" x2="3.81" y2="7.62" width="0.127" layer="21"/>
<wire x1="3.81" y1="6.35" x2="1.27" y2="6.35" width="0.127" layer="21"/>
</package>
<package name="BLUE_PILL_ADV">
<pad name="P$1" x="10.16" y="-30.48" drill="0.8" diameter="1.9304" shape="octagon" rot="R180"/>
<pad name="P$2" x="10.16" y="-27.94" drill="0.8" diameter="1.9304" shape="octagon" rot="R180"/>
<pad name="P$3" x="10.16" y="-25.4" drill="0.8" diameter="1.9304" shape="octagon" rot="R180"/>
<pad name="P$4" x="10.16" y="-22.86" drill="0.8" diameter="1.9304" shape="octagon" rot="R180"/>
<pad name="P$5" x="10.16" y="-20.32" drill="0.8" diameter="1.9304" shape="octagon" rot="R180"/>
<pad name="P$6" x="10.16" y="-17.78" drill="0.8" diameter="1.9304" shape="octagon" rot="R180"/>
<pad name="P$7" x="10.16" y="-15.24" drill="0.8" diameter="1.9304" shape="octagon" rot="R180"/>
<pad name="P$8" x="10.16" y="-12.7" drill="0.8" diameter="1.9304" shape="octagon" rot="R180"/>
<pad name="P$9" x="10.16" y="-10.16" drill="0.8" diameter="1.9304" shape="octagon" rot="R180"/>
<pad name="P$10" x="10.16" y="-7.62" drill="0.8" diameter="1.9304" shape="octagon" rot="R180"/>
<pad name="P$11" x="10.16" y="-5.08" drill="0.8" diameter="1.9304" shape="octagon" rot="R180"/>
<pad name="P$12" x="10.16" y="-2.54" drill="0.8" diameter="1.9304" shape="octagon" rot="R180"/>
<pad name="P$13" x="10.16" y="0" drill="0.8" diameter="1.9304" shape="octagon" rot="R180"/>
<pad name="P$14" x="10.16" y="2.54" drill="0.8" diameter="1.9304" shape="octagon" rot="R180"/>
<pad name="P$15" x="10.16" y="5.08" drill="0.8" diameter="1.9304" shape="octagon" rot="R180"/>
<pad name="P$16" x="10.16" y="7.62" drill="0.8" diameter="1.9304" shape="octagon" rot="R180"/>
<pad name="P$17" x="10.16" y="10.16" drill="0.8" diameter="1.9304" shape="octagon" rot="R180"/>
<pad name="P$18" x="10.16" y="12.7" drill="0.8" diameter="1.9304" shape="octagon" rot="R180"/>
<pad name="P$19" x="10.16" y="15.24" drill="0.8" diameter="1.9304" shape="octagon" rot="R180"/>
<pad name="P$20" x="10.16" y="17.78" drill="0.8" diameter="1.9304" shape="octagon" rot="R180"/>
<pad name="P$21" x="-5.08" y="-30.48" drill="0.8" diameter="1.9304" shape="octagon" rot="R180"/>
<pad name="P$22" x="-5.08" y="-27.94" drill="0.8" diameter="1.9304" shape="octagon" rot="R180"/>
<pad name="P$23" x="-5.08" y="-25.4" drill="0.8" diameter="1.9304" shape="octagon" rot="R180"/>
<pad name="P$24" x="-5.08" y="-22.86" drill="0.8" diameter="1.9304" shape="octagon" rot="R180"/>
<pad name="P$25" x="-5.08" y="-20.32" drill="0.8" diameter="1.9304" shape="octagon" rot="R180"/>
<pad name="P$26" x="-5.08" y="-17.78" drill="0.8" diameter="1.9304" shape="octagon" rot="R180"/>
<pad name="P$27" x="-5.08" y="-15.24" drill="0.8" diameter="1.9304" shape="octagon" rot="R180"/>
<pad name="P$28" x="-5.08" y="-12.7" drill="0.8" diameter="1.9304" shape="octagon" rot="R180"/>
<pad name="P$29" x="-5.08" y="-10.16" drill="0.8" diameter="1.9304" shape="octagon" rot="R180"/>
<pad name="P$30" x="-5.08" y="-7.62" drill="0.8" diameter="1.9304" shape="octagon" rot="R180"/>
<pad name="P$31" x="-5.08" y="-5.08" drill="0.8" diameter="1.9304" shape="octagon" rot="R180"/>
<pad name="P$32" x="-5.08" y="-2.54" drill="0.8" diameter="1.9304" shape="octagon" rot="R180"/>
<pad name="P$33" x="-5.08" y="0" drill="0.8" diameter="1.9304" shape="octagon" rot="R180"/>
<pad name="P$34" x="-5.08" y="2.54" drill="0.8" diameter="1.9304" shape="octagon" rot="R180"/>
<pad name="P$35" x="-5.08" y="5.08" drill="0.8" diameter="1.9304" shape="octagon" rot="R180"/>
<pad name="P$36" x="-5.08" y="7.62" drill="0.8" diameter="1.9304" shape="octagon" rot="R180"/>
<pad name="P$37" x="-5.08" y="10.16" drill="0.8" diameter="1.9304" shape="octagon" rot="R180"/>
<pad name="P$38" x="-5.08" y="12.7" drill="0.8" diameter="1.9304" shape="octagon" rot="R180"/>
<pad name="P$39" x="-5.08" y="15.24" drill="0.8" diameter="1.9304" shape="octagon" rot="R180"/>
<pad name="P$40" x="-5.08" y="17.78" drill="0.8" diameter="1.9304" shape="octagon" rot="R180"/>
<wire x1="6.35" y1="-33.02" x2="5.08" y2="-33.02" width="0.127" layer="21"/>
<wire x1="0" y1="-33.02" x2="-1.27" y2="-33.02" width="0.127" layer="21"/>
<wire x1="6.35" y1="-33.02" x2="6.35" y2="-28.575" width="0.127" layer="21"/>
<wire x1="6.35" y1="-28.575" x2="5.715" y2="-28.575" width="0.127" layer="21"/>
<wire x1="5.715" y1="-28.575" x2="5.08" y2="-27.94" width="0.127" layer="21"/>
<wire x1="5.08" y1="-27.94" x2="0" y2="-27.94" width="0.127" layer="21"/>
<wire x1="0" y1="-27.94" x2="-0.635" y2="-28.575" width="0.127" layer="21"/>
<wire x1="-0.635" y1="-28.575" x2="-1.27" y2="-28.575" width="0.127" layer="21"/>
<wire x1="-1.27" y1="-28.575" x2="-1.27" y2="-33.02" width="0.127" layer="21"/>
<wire x1="7.62" y1="-6.35" x2="6.985" y2="-6.985" width="0.127" layer="21"/>
<wire x1="6.985" y1="-6.985" x2="6.35" y2="-7.62" width="0.127" layer="21"/>
<wire x1="6.35" y1="-7.62" x2="5.715" y2="-8.255" width="0.127" layer="21"/>
<wire x1="5.715" y1="-8.255" x2="5.08" y2="-8.89" width="0.127" layer="21"/>
<wire x1="5.08" y1="-8.89" x2="4.445" y2="-9.525" width="0.127" layer="21"/>
<wire x1="4.445" y1="-9.525" x2="3.81" y2="-10.16" width="0.127" layer="21"/>
<wire x1="3.81" y1="-10.16" x2="3.175" y2="-10.795" width="0.127" layer="21"/>
<wire x1="3.175" y1="-10.795" x2="2.54" y2="-11.43" width="0.127" layer="21"/>
<wire x1="2.54" y1="-11.43" x2="1.905" y2="-10.795" width="0.127" layer="21"/>
<wire x1="1.905" y1="-10.795" x2="1.27" y2="-10.16" width="0.127" layer="21"/>
<wire x1="1.27" y1="-10.16" x2="0.635" y2="-9.525" width="0.127" layer="21"/>
<wire x1="0.635" y1="-9.525" x2="0" y2="-8.89" width="0.127" layer="21"/>
<wire x1="0" y1="-8.89" x2="-0.635" y2="-8.255" width="0.127" layer="21"/>
<wire x1="-0.635" y1="-8.255" x2="-1.27" y2="-7.62" width="0.127" layer="21"/>
<wire x1="-1.27" y1="-7.62" x2="-1.905" y2="-6.985" width="0.127" layer="21"/>
<wire x1="-1.905" y1="-6.985" x2="-2.54" y2="-6.35" width="0.127" layer="21"/>
<wire x1="-2.54" y1="-6.35" x2="-1.905" y2="-5.715" width="0.127" layer="21"/>
<wire x1="-1.905" y1="-5.715" x2="-1.27" y2="-5.08" width="0.127" layer="21"/>
<wire x1="-1.27" y1="-5.08" x2="-0.635" y2="-4.445" width="0.127" layer="21"/>
<wire x1="-0.635" y1="-4.445" x2="0" y2="-3.81" width="0.127" layer="21"/>
<wire x1="0" y1="-3.81" x2="0.635" y2="-3.175" width="0.127" layer="21"/>
<wire x1="0.635" y1="-3.175" x2="1.27" y2="-2.54" width="0.127" layer="21"/>
<wire x1="1.27" y1="-2.54" x2="1.905" y2="-1.905" width="0.127" layer="21"/>
<wire x1="1.905" y1="-1.905" x2="2.54" y2="-1.27" width="0.127" layer="21"/>
<wire x1="2.54" y1="-1.27" x2="3.175" y2="-1.905" width="0.127" layer="21"/>
<wire x1="3.175" y1="-1.905" x2="3.81" y2="-2.54" width="0.127" layer="21"/>
<wire x1="3.81" y1="-2.54" x2="4.445" y2="-3.175" width="0.127" layer="21"/>
<wire x1="4.445" y1="-3.175" x2="5.08" y2="-3.81" width="0.127" layer="21"/>
<wire x1="5.08" y1="-3.81" x2="5.715" y2="-4.445" width="0.127" layer="21"/>
<wire x1="5.715" y1="-4.445" x2="6.35" y2="-5.08" width="0.127" layer="21"/>
<wire x1="6.35" y1="-5.08" x2="6.985" y2="-5.715" width="0.127" layer="21"/>
<wire x1="6.985" y1="-5.715" x2="7.62" y2="-6.35" width="0.127" layer="21"/>
<text x="4.445" y="-3.81" size="1.27" layer="21" rot="R226.6">STM32</text>
<wire x1="-1.905" y1="-5.715" x2="-2.54" y2="-5.08" width="0.127" layer="21"/>
<wire x1="-1.27" y1="-5.08" x2="-1.905" y2="-4.445" width="0.127" layer="21"/>
<wire x1="-0.635" y1="-4.445" x2="-1.27" y2="-3.81" width="0.127" layer="21"/>
<wire x1="0" y1="-3.81" x2="-0.635" y2="-3.175" width="0.127" layer="21"/>
<wire x1="0.635" y1="-3.175" x2="0" y2="-2.54" width="0.127" layer="21"/>
<wire x1="1.27" y1="-2.54" x2="0.635" y2="-1.905" width="0.127" layer="21"/>
<wire x1="1.905" y1="-1.905" x2="1.27" y2="-1.27" width="0.127" layer="21"/>
<wire x1="3.175" y1="-1.905" x2="3.81" y2="-1.27" width="0.127" layer="21"/>
<wire x1="3.81" y1="-2.54" x2="4.445" y2="-1.905" width="0.127" layer="21"/>
<wire x1="4.445" y1="-3.175" x2="5.08" y2="-2.54" width="0.127" layer="21"/>
<wire x1="5.08" y1="-3.81" x2="5.715" y2="-3.175" width="0.127" layer="21"/>
<wire x1="5.715" y1="-4.445" x2="6.35" y2="-3.81" width="0.127" layer="21"/>
<wire x1="6.35" y1="-5.08" x2="6.985" y2="-4.445" width="0.127" layer="21"/>
<wire x1="6.985" y1="-8.255" x2="6.35" y2="-7.62" width="0.127" layer="21"/>
<wire x1="6.35" y1="-8.89" x2="5.715" y2="-8.255" width="0.127" layer="21"/>
<wire x1="5.715" y1="-9.525" x2="5.08" y2="-8.89" width="0.127" layer="21"/>
<wire x1="5.08" y1="-10.16" x2="4.445" y2="-9.525" width="0.127" layer="21"/>
<wire x1="4.445" y1="-10.795" x2="3.81" y2="-10.16" width="0.127" layer="21"/>
<wire x1="3.81" y1="-11.43" x2="3.175" y2="-10.795" width="0.127" layer="21"/>
<wire x1="1.905" y1="-10.795" x2="1.27" y2="-11.43" width="0.127" layer="21"/>
<wire x1="1.27" y1="-10.16" x2="0.635" y2="-10.795" width="0.127" layer="21"/>
<wire x1="0.635" y1="-9.525" x2="0" y2="-10.16" width="0.127" layer="21"/>
<wire x1="0" y1="-8.89" x2="-0.635" y2="-9.525" width="0.127" layer="21"/>
<wire x1="-0.635" y1="-8.255" x2="-1.27" y2="-8.89" width="0.127" layer="21"/>
<wire x1="-1.27" y1="-7.62" x2="-1.905" y2="-8.255" width="0.127" layer="21"/>
<wire x1="-1.27" y1="-33.02" x2="-6.35" y2="-33.02" width="0.127" layer="21"/>
<wire x1="-6.35" y1="-33.02" x2="-7.62" y2="-31.75" width="0.127" layer="21" curve="-90"/>
<wire x1="-7.62" y1="-31.75" x2="-7.62" y2="17.78" width="0.127" layer="21"/>
<wire x1="-7.62" y1="17.78" x2="-6.35" y2="19.05" width="0.127" layer="21" curve="-90"/>
<wire x1="-6.35" y1="19.05" x2="11.43" y2="19.05" width="0.127" layer="21"/>
<wire x1="11.43" y1="19.05" x2="12.7" y2="17.78" width="0.127" layer="21" curve="-90"/>
<wire x1="12.7" y1="17.78" x2="12.7" y2="-31.75" width="0.127" layer="21"/>
<wire x1="12.7" y1="-31.75" x2="11.43" y2="-33.02" width="0.127" layer="21" curve="-90"/>
<wire x1="11.43" y1="-33.02" x2="6.35" y2="-33.02" width="0.127" layer="21"/>
<wire x1="6.35" y1="-33.02" x2="5.08" y2="-33.02" width="0.127" layer="21" curve="90"/>
<wire x1="5.08" y1="-33.02" x2="0" y2="-33.02" width="0.127" layer="21"/>
<wire x1="0" y1="-33.02" x2="-1.27" y2="-33.02" width="0.127" layer="21" curve="90"/>
<wire x1="5.08" y1="-30.48" x2="5.08" y2="-29.21" width="0.127" layer="21"/>
<wire x1="5.08" y1="-29.21" x2="3.81" y2="-29.21" width="0.127" layer="21"/>
<wire x1="3.81" y1="-29.21" x2="3.81" y2="-30.48" width="0.127" layer="21"/>
<wire x1="1.27" y1="-30.48" x2="1.27" y2="-29.21" width="0.127" layer="21"/>
<wire x1="1.27" y1="-29.21" x2="0" y2="-29.21" width="0.127" layer="21"/>
<wire x1="0" y1="-29.21" x2="0" y2="-30.48" width="0.127" layer="21"/>
<wire x1="5.08" y1="-30.48" x2="3.81" y2="-30.48" width="0.127" layer="21"/>
<wire x1="1.27" y1="-30.48" x2="0" y2="-30.48" width="0.127" layer="21"/>
<wire x1="6.985" y1="-5.715" x2="7.62" y2="-5.08" width="0.127" layer="21"/>
<wire x1="7.62" y1="-7.62" x2="6.985" y2="-6.985" width="0.127" layer="21"/>
<wire x1="-2.54" y1="-7.62" x2="-1.905" y2="-6.985" width="0.127" layer="21"/>
<circle x="6.35" y="-6.35" radius="0.635" width="0.127" layer="21"/>
<wire x1="6.985" y1="6.35" x2="5.08" y2="8.255" width="0.127" layer="21" curve="90"/>
<wire x1="5.08" y1="8.255" x2="0" y2="8.255" width="0.127" layer="21"/>
<wire x1="0" y1="8.255" x2="-1.905" y2="6.35" width="0.127" layer="21" curve="90"/>
<wire x1="-1.905" y1="6.35" x2="0" y2="4.445" width="0.127" layer="21" curve="90"/>
<wire x1="0" y1="4.445" x2="5.08" y2="4.445" width="0.127" layer="21"/>
<wire x1="5.08" y1="4.445" x2="6.985" y2="6.35" width="0.127" layer="21" curve="90"/>
<pad name="P$42" x="-1.27" y="-20.32" drill="1.1" diameter="1.9304" shape="octagon" rot="R180"/>
<pad name="P$43" x="-1.27" y="-17.78" drill="1.1" diameter="1.9304" shape="octagon" rot="R180"/>
<pad name="P$44" x="-1.27" y="-15.24" drill="1.1" diameter="1.9304" shape="octagon" rot="R180"/>
<pad name="P$45" x="1.27" y="-15.24" drill="1.1" diameter="1.9304" shape="octagon" rot="R180"/>
<pad name="P$46" x="1.27" y="-17.78" drill="1.1" diameter="1.9304" shape="octagon" rot="R180"/>
<pad name="P$47" x="1.27" y="-20.32" drill="1.1" diameter="1.9304" shape="octagon" rot="R180"/>
<wire x1="1.27" y1="-21.59" x2="-1.27" y2="-21.59" width="0.127" layer="19"/>
<wire x1="-1.27" y1="-21.59" x2="-1.905" y2="-21.59" width="0.127" layer="19"/>
<wire x1="-1.905" y1="-21.59" x2="-2.54" y2="-20.955" width="0.127" layer="19"/>
<wire x1="-2.54" y1="-20.955" x2="-2.54" y2="-19.685" width="0.127" layer="19"/>
<wire x1="-2.54" y1="-19.685" x2="-1.905" y2="-19.05" width="0.127" layer="19"/>
<wire x1="-1.905" y1="-19.05" x2="-2.54" y2="-18.415" width="0.127" layer="19"/>
<wire x1="-2.54" y1="-18.415" x2="-2.54" y2="-17.145" width="0.127" layer="19"/>
<wire x1="-2.54" y1="-17.145" x2="-1.905" y2="-16.51" width="0.127" layer="19"/>
<wire x1="-1.905" y1="-16.51" x2="-2.54" y2="-15.875" width="0.127" layer="19"/>
<wire x1="-2.54" y1="-15.875" x2="-2.54" y2="-14.605" width="0.127" layer="19"/>
<wire x1="-2.54" y1="-14.605" x2="-1.905" y2="-13.97" width="0.127" layer="19"/>
<wire x1="-1.905" y1="-13.97" x2="1.905" y2="-13.97" width="0.127" layer="19"/>
<wire x1="1.905" y1="-13.97" x2="2.54" y2="-14.605" width="0.127" layer="19"/>
<wire x1="2.54" y1="-14.605" x2="2.54" y2="-15.875" width="0.127" layer="19"/>
<wire x1="2.54" y1="-15.875" x2="1.905" y2="-16.51" width="0.127" layer="19"/>
<wire x1="1.905" y1="-16.51" x2="2.54" y2="-17.145" width="0.127" layer="19"/>
<wire x1="2.54" y1="-17.145" x2="2.54" y2="-18.415" width="0.127" layer="19"/>
<wire x1="2.54" y1="-18.415" x2="1.905" y2="-19.05" width="0.127" layer="19"/>
<wire x1="1.905" y1="-19.05" x2="2.54" y2="-19.685" width="0.127" layer="19"/>
<wire x1="2.54" y1="-19.685" x2="2.54" y2="-20.955" width="0.127" layer="19"/>
<wire x1="2.54" y1="-20.955" x2="1.905" y2="-21.59" width="0.127" layer="19"/>
<wire x1="1.905" y1="-21.59" x2="1.27" y2="-21.59" width="0.127" layer="19"/>
<wire x1="10.795" y1="-26.67" x2="11.43" y2="-27.305" width="0.127" layer="19"/>
<wire x1="11.43" y1="-27.305" x2="11.43" y2="-28.575" width="0.127" layer="19"/>
<wire x1="11.43" y1="-28.575" x2="10.795" y2="-29.21" width="0.127" layer="19"/>
<wire x1="10.795" y1="-29.21" x2="11.43" y2="-29.845" width="0.127" layer="19"/>
<wire x1="11.43" y1="-29.845" x2="11.43" y2="-31.115" width="0.127" layer="19"/>
<wire x1="11.43" y1="-31.115" x2="10.795" y2="-31.75" width="0.127" layer="19"/>
<wire x1="10.795" y1="-19.05" x2="11.43" y2="-19.685" width="0.127" layer="19"/>
<wire x1="11.43" y1="-19.685" x2="11.43" y2="-20.955" width="0.127" layer="19"/>
<wire x1="11.43" y1="-20.955" x2="10.795" y2="-21.59" width="0.127" layer="19"/>
<wire x1="10.795" y1="-21.59" x2="11.43" y2="-22.225" width="0.127" layer="19"/>
<wire x1="11.43" y1="-22.225" x2="11.43" y2="-23.495" width="0.127" layer="19"/>
<wire x1="11.43" y1="-23.495" x2="10.795" y2="-24.13" width="0.127" layer="19"/>
<wire x1="10.795" y1="-24.13" x2="11.43" y2="-24.765" width="0.127" layer="19"/>
<wire x1="11.43" y1="-24.765" x2="11.43" y2="-26.035" width="0.127" layer="19"/>
<wire x1="11.43" y1="-26.035" x2="10.795" y2="-26.67" width="0.127" layer="19"/>
<wire x1="10.795" y1="-11.43" x2="11.43" y2="-12.065" width="0.127" layer="19"/>
<wire x1="11.43" y1="-12.065" x2="11.43" y2="-13.335" width="0.127" layer="19"/>
<wire x1="11.43" y1="-13.335" x2="10.795" y2="-13.97" width="0.127" layer="19"/>
<wire x1="10.795" y1="-13.97" x2="11.43" y2="-14.605" width="0.127" layer="19"/>
<wire x1="11.43" y1="-14.605" x2="11.43" y2="-15.875" width="0.127" layer="19"/>
<wire x1="11.43" y1="-15.875" x2="10.795" y2="-16.51" width="0.127" layer="19"/>
<wire x1="10.795" y1="-16.51" x2="11.43" y2="-17.145" width="0.127" layer="19"/>
<wire x1="11.43" y1="-17.145" x2="11.43" y2="-18.415" width="0.127" layer="19"/>
<wire x1="11.43" y1="-18.415" x2="10.795" y2="-19.05" width="0.127" layer="19"/>
<wire x1="10.795" y1="-3.81" x2="11.43" y2="-4.445" width="0.127" layer="19"/>
<wire x1="11.43" y1="-4.445" x2="11.43" y2="-5.715" width="0.127" layer="19"/>
<wire x1="11.43" y1="-5.715" x2="10.795" y2="-6.35" width="0.127" layer="19"/>
<wire x1="10.795" y1="-6.35" x2="11.43" y2="-6.985" width="0.127" layer="19"/>
<wire x1="11.43" y1="-6.985" x2="11.43" y2="-8.255" width="0.127" layer="19"/>
<wire x1="11.43" y1="-8.255" x2="10.795" y2="-8.89" width="0.127" layer="19"/>
<wire x1="10.795" y1="-8.89" x2="11.43" y2="-9.525" width="0.127" layer="19"/>
<wire x1="11.43" y1="-9.525" x2="11.43" y2="-10.795" width="0.127" layer="19"/>
<wire x1="11.43" y1="-10.795" x2="10.795" y2="-11.43" width="0.127" layer="19"/>
<wire x1="10.795" y1="3.81" x2="11.43" y2="3.175" width="0.127" layer="19"/>
<wire x1="11.43" y1="3.175" x2="11.43" y2="1.905" width="0.127" layer="19"/>
<wire x1="11.43" y1="1.905" x2="10.795" y2="1.27" width="0.127" layer="19"/>
<wire x1="10.795" y1="1.27" x2="11.43" y2="0.635" width="0.127" layer="19"/>
<wire x1="11.43" y1="0.635" x2="11.43" y2="-0.635" width="0.127" layer="19"/>
<wire x1="11.43" y1="-0.635" x2="10.795" y2="-1.27" width="0.127" layer="19"/>
<wire x1="10.795" y1="-1.27" x2="11.43" y2="-1.905" width="0.127" layer="19"/>
<wire x1="11.43" y1="-1.905" x2="11.43" y2="-3.175" width="0.127" layer="19"/>
<wire x1="11.43" y1="-3.175" x2="10.795" y2="-3.81" width="0.127" layer="19"/>
<wire x1="10.795" y1="11.43" x2="11.43" y2="10.795" width="0.127" layer="19"/>
<wire x1="11.43" y1="10.795" x2="11.43" y2="9.525" width="0.127" layer="19"/>
<wire x1="11.43" y1="9.525" x2="10.795" y2="8.89" width="0.127" layer="19"/>
<wire x1="10.795" y1="8.89" x2="11.43" y2="8.255" width="0.127" layer="19"/>
<wire x1="11.43" y1="8.255" x2="11.43" y2="6.985" width="0.127" layer="19"/>
<wire x1="11.43" y1="6.985" x2="10.795" y2="6.35" width="0.127" layer="19"/>
<wire x1="10.795" y1="6.35" x2="11.43" y2="5.715" width="0.127" layer="19"/>
<wire x1="11.43" y1="5.715" x2="11.43" y2="4.445" width="0.127" layer="19"/>
<wire x1="11.43" y1="4.445" x2="10.795" y2="3.81" width="0.127" layer="19"/>
<wire x1="10.795" y1="19.05" x2="11.43" y2="18.415" width="0.127" layer="19"/>
<wire x1="11.43" y1="18.415" x2="11.43" y2="17.145" width="0.127" layer="19"/>
<wire x1="11.43" y1="17.145" x2="10.795" y2="16.51" width="0.127" layer="19"/>
<wire x1="10.795" y1="16.51" x2="11.43" y2="15.875" width="0.127" layer="19"/>
<wire x1="11.43" y1="15.875" x2="11.43" y2="14.605" width="0.127" layer="19"/>
<wire x1="11.43" y1="14.605" x2="10.795" y2="13.97" width="0.127" layer="19"/>
<wire x1="10.795" y1="13.97" x2="11.43" y2="13.335" width="0.127" layer="19"/>
<wire x1="11.43" y1="13.335" x2="11.43" y2="12.065" width="0.127" layer="19"/>
<wire x1="11.43" y1="12.065" x2="10.795" y2="11.43" width="0.127" layer="19"/>
<wire x1="9.525" y1="-16.51" x2="8.89" y2="-15.875" width="0.127" layer="19"/>
<wire x1="8.89" y1="-15.875" x2="8.89" y2="-14.605" width="0.127" layer="19"/>
<wire x1="8.89" y1="-14.605" x2="9.525" y2="-13.97" width="0.127" layer="19"/>
<wire x1="9.525" y1="-13.97" x2="8.89" y2="-13.335" width="0.127" layer="19"/>
<wire x1="8.89" y1="-13.335" x2="8.89" y2="-12.065" width="0.127" layer="19"/>
<wire x1="8.89" y1="-12.065" x2="9.525" y2="-11.43" width="0.127" layer="19"/>
<wire x1="9.525" y1="-11.43" x2="8.89" y2="-10.795" width="0.127" layer="19"/>
<wire x1="8.89" y1="-10.795" x2="8.89" y2="-9.525" width="0.127" layer="19"/>
<wire x1="8.89" y1="-9.525" x2="9.525" y2="-8.89" width="0.127" layer="19"/>
<wire x1="9.525" y1="-24.13" x2="8.89" y2="-23.495" width="0.127" layer="19"/>
<wire x1="8.89" y1="-23.495" x2="8.89" y2="-22.225" width="0.127" layer="19"/>
<wire x1="8.89" y1="-22.225" x2="9.525" y2="-21.59" width="0.127" layer="19"/>
<wire x1="9.525" y1="-21.59" x2="8.89" y2="-20.955" width="0.127" layer="19"/>
<wire x1="8.89" y1="-20.955" x2="8.89" y2="-19.685" width="0.127" layer="19"/>
<wire x1="8.89" y1="-19.685" x2="9.525" y2="-19.05" width="0.127" layer="19"/>
<wire x1="9.525" y1="-19.05" x2="8.89" y2="-18.415" width="0.127" layer="19"/>
<wire x1="8.89" y1="-18.415" x2="8.89" y2="-17.145" width="0.127" layer="19"/>
<wire x1="8.89" y1="-17.145" x2="9.525" y2="-16.51" width="0.127" layer="19"/>
<wire x1="9.525" y1="-31.75" x2="8.89" y2="-31.115" width="0.127" layer="19"/>
<wire x1="8.89" y1="-31.115" x2="8.89" y2="-29.845" width="0.127" layer="19"/>
<wire x1="8.89" y1="-29.845" x2="9.525" y2="-29.21" width="0.127" layer="19"/>
<wire x1="9.525" y1="-29.21" x2="8.89" y2="-28.575" width="0.127" layer="19"/>
<wire x1="8.89" y1="-28.575" x2="8.89" y2="-27.305" width="0.127" layer="19"/>
<wire x1="8.89" y1="-27.305" x2="9.525" y2="-26.67" width="0.127" layer="19"/>
<wire x1="9.525" y1="-26.67" x2="8.89" y2="-26.035" width="0.127" layer="19"/>
<wire x1="8.89" y1="-26.035" x2="8.89" y2="-24.765" width="0.127" layer="19"/>
<wire x1="8.89" y1="-24.765" x2="9.525" y2="-24.13" width="0.127" layer="19"/>
<wire x1="9.525" y1="6.35" x2="8.89" y2="6.985" width="0.127" layer="19"/>
<wire x1="8.89" y1="6.985" x2="8.89" y2="8.255" width="0.127" layer="19"/>
<wire x1="8.89" y1="8.255" x2="9.525" y2="8.89" width="0.127" layer="19"/>
<wire x1="9.525" y1="8.89" x2="8.89" y2="9.525" width="0.127" layer="19"/>
<wire x1="8.89" y1="9.525" x2="8.89" y2="10.795" width="0.127" layer="19"/>
<wire x1="8.89" y1="10.795" x2="9.525" y2="11.43" width="0.127" layer="19"/>
<wire x1="9.525" y1="11.43" x2="8.89" y2="12.065" width="0.127" layer="19"/>
<wire x1="8.89" y1="12.065" x2="8.89" y2="13.335" width="0.127" layer="19"/>
<wire x1="8.89" y1="13.335" x2="9.525" y2="13.97" width="0.127" layer="19"/>
<wire x1="9.525" y1="-1.27" x2="8.89" y2="-0.635" width="0.127" layer="19"/>
<wire x1="8.89" y1="-0.635" x2="8.89" y2="0.635" width="0.127" layer="19"/>
<wire x1="8.89" y1="0.635" x2="9.525" y2="1.27" width="0.127" layer="19"/>
<wire x1="9.525" y1="1.27" x2="8.89" y2="1.905" width="0.127" layer="19"/>
<wire x1="8.89" y1="1.905" x2="8.89" y2="3.175" width="0.127" layer="19"/>
<wire x1="8.89" y1="3.175" x2="9.525" y2="3.81" width="0.127" layer="19"/>
<wire x1="9.525" y1="3.81" x2="8.89" y2="4.445" width="0.127" layer="19"/>
<wire x1="8.89" y1="4.445" x2="8.89" y2="5.715" width="0.127" layer="19"/>
<wire x1="8.89" y1="5.715" x2="9.525" y2="6.35" width="0.127" layer="19"/>
<wire x1="9.525" y1="-8.89" x2="8.89" y2="-8.255" width="0.127" layer="19"/>
<wire x1="8.89" y1="-8.255" x2="8.89" y2="-6.985" width="0.127" layer="19"/>
<wire x1="8.89" y1="-6.985" x2="9.525" y2="-6.35" width="0.127" layer="19"/>
<wire x1="9.525" y1="-6.35" x2="8.89" y2="-5.715" width="0.127" layer="19"/>
<wire x1="8.89" y1="-5.715" x2="8.89" y2="-4.445" width="0.127" layer="19"/>
<wire x1="8.89" y1="-4.445" x2="9.525" y2="-3.81" width="0.127" layer="19"/>
<wire x1="9.525" y1="-3.81" x2="8.89" y2="-3.175" width="0.127" layer="19"/>
<wire x1="8.89" y1="-3.175" x2="8.89" y2="-1.905" width="0.127" layer="19"/>
<wire x1="8.89" y1="-1.905" x2="9.525" y2="-1.27" width="0.127" layer="19"/>
<wire x1="9.525" y1="13.97" x2="8.89" y2="14.605" width="0.127" layer="19"/>
<wire x1="8.89" y1="14.605" x2="8.89" y2="15.875" width="0.127" layer="19"/>
<wire x1="8.89" y1="15.875" x2="9.525" y2="16.51" width="0.127" layer="19"/>
<wire x1="9.525" y1="16.51" x2="8.89" y2="17.145" width="0.127" layer="19"/>
<wire x1="8.89" y1="17.145" x2="8.89" y2="18.415" width="0.127" layer="19"/>
<wire x1="8.89" y1="18.415" x2="9.525" y2="19.05" width="0.127" layer="19"/>
<wire x1="-4.445" y1="-24.13" x2="-3.81" y2="-24.765" width="0.127" layer="19"/>
<wire x1="-3.81" y1="-24.765" x2="-3.81" y2="-26.035" width="0.127" layer="19"/>
<wire x1="-3.81" y1="-26.035" x2="-4.445" y2="-26.67" width="0.127" layer="19"/>
<wire x1="-4.445" y1="-26.67" x2="-3.81" y2="-27.305" width="0.127" layer="19"/>
<wire x1="-3.81" y1="-27.305" x2="-3.81" y2="-28.575" width="0.127" layer="19"/>
<wire x1="-3.81" y1="-28.575" x2="-4.445" y2="-29.21" width="0.127" layer="19"/>
<wire x1="-4.445" y1="-29.21" x2="-3.81" y2="-29.845" width="0.127" layer="19"/>
<wire x1="-3.81" y1="-29.845" x2="-3.81" y2="-31.115" width="0.127" layer="19"/>
<wire x1="-3.81" y1="-31.115" x2="-4.445" y2="-31.75" width="0.127" layer="19"/>
<wire x1="-4.445" y1="-16.51" x2="-3.81" y2="-17.145" width="0.127" layer="19"/>
<wire x1="-3.81" y1="-17.145" x2="-3.81" y2="-18.415" width="0.127" layer="19"/>
<wire x1="-3.81" y1="-18.415" x2="-4.445" y2="-19.05" width="0.127" layer="19"/>
<wire x1="-4.445" y1="-19.05" x2="-3.81" y2="-19.685" width="0.127" layer="19"/>
<wire x1="-3.81" y1="-19.685" x2="-3.81" y2="-20.955" width="0.127" layer="19"/>
<wire x1="-3.81" y1="-20.955" x2="-4.445" y2="-21.59" width="0.127" layer="19"/>
<wire x1="-4.445" y1="-21.59" x2="-3.81" y2="-22.225" width="0.127" layer="19"/>
<wire x1="-3.81" y1="-22.225" x2="-3.81" y2="-23.495" width="0.127" layer="19"/>
<wire x1="-3.81" y1="-23.495" x2="-4.445" y2="-24.13" width="0.127" layer="19"/>
<wire x1="-4.445" y1="-8.89" x2="-3.81" y2="-9.525" width="0.127" layer="19"/>
<wire x1="-3.81" y1="-9.525" x2="-3.81" y2="-10.795" width="0.127" layer="19"/>
<wire x1="-3.81" y1="-10.795" x2="-4.445" y2="-11.43" width="0.127" layer="19"/>
<wire x1="-4.445" y1="-11.43" x2="-3.81" y2="-12.065" width="0.127" layer="19"/>
<wire x1="-3.81" y1="-12.065" x2="-3.81" y2="-13.335" width="0.127" layer="19"/>
<wire x1="-3.81" y1="-13.335" x2="-4.445" y2="-13.97" width="0.127" layer="19"/>
<wire x1="-4.445" y1="-13.97" x2="-3.81" y2="-14.605" width="0.127" layer="19"/>
<wire x1="-3.81" y1="-14.605" x2="-3.81" y2="-15.875" width="0.127" layer="19"/>
<wire x1="-3.81" y1="-15.875" x2="-4.445" y2="-16.51" width="0.127" layer="19"/>
<wire x1="-4.445" y1="-1.27" x2="-3.81" y2="-1.905" width="0.127" layer="19"/>
<wire x1="-3.81" y1="-1.905" x2="-3.81" y2="-3.175" width="0.127" layer="19"/>
<wire x1="-3.81" y1="-3.175" x2="-4.445" y2="-3.81" width="0.127" layer="19"/>
<wire x1="-4.445" y1="-3.81" x2="-3.81" y2="-4.445" width="0.127" layer="19"/>
<wire x1="-3.81" y1="-4.445" x2="-3.81" y2="-5.715" width="0.127" layer="19"/>
<wire x1="-3.81" y1="-5.715" x2="-4.445" y2="-6.35" width="0.127" layer="19"/>
<wire x1="-4.445" y1="-6.35" x2="-3.81" y2="-6.985" width="0.127" layer="19"/>
<wire x1="-3.81" y1="-6.985" x2="-3.81" y2="-8.255" width="0.127" layer="19"/>
<wire x1="-3.81" y1="-8.255" x2="-4.445" y2="-8.89" width="0.127" layer="19"/>
<wire x1="-4.445" y1="6.35" x2="-3.81" y2="5.715" width="0.127" layer="19"/>
<wire x1="-3.81" y1="5.715" x2="-3.81" y2="4.445" width="0.127" layer="19"/>
<wire x1="-3.81" y1="4.445" x2="-4.445" y2="3.81" width="0.127" layer="19"/>
<wire x1="-4.445" y1="3.81" x2="-3.81" y2="3.175" width="0.127" layer="19"/>
<wire x1="-3.81" y1="3.175" x2="-3.81" y2="1.905" width="0.127" layer="19"/>
<wire x1="-3.81" y1="1.905" x2="-4.445" y2="1.27" width="0.127" layer="19"/>
<wire x1="-4.445" y1="1.27" x2="-3.81" y2="0.635" width="0.127" layer="19"/>
<wire x1="-3.81" y1="0.635" x2="-3.81" y2="-0.635" width="0.127" layer="19"/>
<wire x1="-3.81" y1="-0.635" x2="-4.445" y2="-1.27" width="0.127" layer="19"/>
<wire x1="-4.445" y1="13.97" x2="-3.81" y2="13.335" width="0.127" layer="19"/>
<wire x1="-3.81" y1="13.335" x2="-3.81" y2="12.065" width="0.127" layer="19"/>
<wire x1="-3.81" y1="12.065" x2="-4.445" y2="11.43" width="0.127" layer="19"/>
<wire x1="-4.445" y1="11.43" x2="-3.81" y2="10.795" width="0.127" layer="19"/>
<wire x1="-3.81" y1="10.795" x2="-3.81" y2="9.525" width="0.127" layer="19"/>
<wire x1="-3.81" y1="9.525" x2="-4.445" y2="8.89" width="0.127" layer="19"/>
<wire x1="-4.445" y1="8.89" x2="-3.81" y2="8.255" width="0.127" layer="19"/>
<wire x1="-3.81" y1="8.255" x2="-3.81" y2="6.985" width="0.127" layer="19"/>
<wire x1="-3.81" y1="6.985" x2="-4.445" y2="6.35" width="0.127" layer="19"/>
<wire x1="-4.445" y1="19.05" x2="-3.81" y2="18.415" width="0.127" layer="19"/>
<wire x1="-3.81" y1="18.415" x2="-3.81" y2="17.145" width="0.127" layer="19"/>
<wire x1="-3.81" y1="17.145" x2="-4.445" y2="16.51" width="0.127" layer="19"/>
<wire x1="-4.445" y1="16.51" x2="-3.81" y2="15.875" width="0.127" layer="19"/>
<wire x1="-3.81" y1="15.875" x2="-3.81" y2="14.605" width="0.127" layer="19"/>
<wire x1="-3.81" y1="14.605" x2="-4.445" y2="13.97" width="0.127" layer="19"/>
<wire x1="-5.715" y1="-16.51" x2="-6.35" y2="-15.875" width="0.127" layer="19"/>
<wire x1="-6.35" y1="-15.875" x2="-6.35" y2="-14.605" width="0.127" layer="19"/>
<wire x1="-6.35" y1="-14.605" x2="-5.715" y2="-13.97" width="0.127" layer="19"/>
<wire x1="-5.715" y1="-13.97" x2="-6.35" y2="-13.335" width="0.127" layer="19"/>
<wire x1="-6.35" y1="-13.335" x2="-6.35" y2="-12.065" width="0.127" layer="19"/>
<wire x1="-6.35" y1="-12.065" x2="-5.715" y2="-11.43" width="0.127" layer="19"/>
<wire x1="-5.715" y1="-11.43" x2="-6.35" y2="-10.795" width="0.127" layer="19"/>
<wire x1="-6.35" y1="-10.795" x2="-6.35" y2="-9.525" width="0.127" layer="19"/>
<wire x1="-6.35" y1="-9.525" x2="-5.715" y2="-8.89" width="0.127" layer="19"/>
<wire x1="-5.715" y1="-24.13" x2="-6.35" y2="-23.495" width="0.127" layer="19"/>
<wire x1="-6.35" y1="-23.495" x2="-6.35" y2="-22.225" width="0.127" layer="19"/>
<wire x1="-6.35" y1="-22.225" x2="-5.715" y2="-21.59" width="0.127" layer="19"/>
<wire x1="-5.715" y1="-21.59" x2="-6.35" y2="-20.955" width="0.127" layer="19"/>
<wire x1="-6.35" y1="-20.955" x2="-6.35" y2="-19.685" width="0.127" layer="19"/>
<wire x1="-6.35" y1="-19.685" x2="-5.715" y2="-19.05" width="0.127" layer="19"/>
<wire x1="-5.715" y1="-19.05" x2="-6.35" y2="-18.415" width="0.127" layer="19"/>
<wire x1="-6.35" y1="-18.415" x2="-6.35" y2="-17.145" width="0.127" layer="19"/>
<wire x1="-6.35" y1="-17.145" x2="-5.715" y2="-16.51" width="0.127" layer="19"/>
<wire x1="-5.715" y1="-31.75" x2="-6.35" y2="-31.115" width="0.127" layer="19"/>
<wire x1="-6.35" y1="-31.115" x2="-6.35" y2="-29.845" width="0.127" layer="19"/>
<wire x1="-6.35" y1="-29.845" x2="-5.715" y2="-29.21" width="0.127" layer="19"/>
<wire x1="-5.715" y1="-29.21" x2="-6.35" y2="-28.575" width="0.127" layer="19"/>
<wire x1="-6.35" y1="-28.575" x2="-6.35" y2="-27.305" width="0.127" layer="19"/>
<wire x1="-6.35" y1="-27.305" x2="-5.715" y2="-26.67" width="0.127" layer="19"/>
<wire x1="-5.715" y1="-26.67" x2="-6.35" y2="-26.035" width="0.127" layer="19"/>
<wire x1="-6.35" y1="-26.035" x2="-6.35" y2="-24.765" width="0.127" layer="19"/>
<wire x1="-6.35" y1="-24.765" x2="-5.715" y2="-24.13" width="0.127" layer="19"/>
<wire x1="-5.715" y1="6.35" x2="-6.35" y2="6.985" width="0.127" layer="19"/>
<wire x1="-6.35" y1="6.985" x2="-6.35" y2="8.255" width="0.127" layer="19"/>
<wire x1="-6.35" y1="8.255" x2="-5.715" y2="8.89" width="0.127" layer="19"/>
<wire x1="-5.715" y1="8.89" x2="-6.35" y2="9.525" width="0.127" layer="19"/>
<wire x1="-6.35" y1="9.525" x2="-6.35" y2="10.795" width="0.127" layer="19"/>
<wire x1="-6.35" y1="10.795" x2="-5.715" y2="11.43" width="0.127" layer="19"/>
<wire x1="-5.715" y1="11.43" x2="-6.35" y2="12.065" width="0.127" layer="19"/>
<wire x1="-6.35" y1="12.065" x2="-6.35" y2="13.335" width="0.127" layer="19"/>
<wire x1="-6.35" y1="13.335" x2="-5.715" y2="13.97" width="0.127" layer="19"/>
<wire x1="-5.715" y1="-1.27" x2="-6.35" y2="-0.635" width="0.127" layer="19"/>
<wire x1="-6.35" y1="-0.635" x2="-6.35" y2="0.635" width="0.127" layer="19"/>
<wire x1="-6.35" y1="0.635" x2="-5.715" y2="1.27" width="0.127" layer="19"/>
<wire x1="-5.715" y1="1.27" x2="-6.35" y2="1.905" width="0.127" layer="19"/>
<wire x1="-6.35" y1="1.905" x2="-6.35" y2="3.175" width="0.127" layer="19"/>
<wire x1="-6.35" y1="3.175" x2="-5.715" y2="3.81" width="0.127" layer="19"/>
<wire x1="-5.715" y1="3.81" x2="-6.35" y2="4.445" width="0.127" layer="19"/>
<wire x1="-6.35" y1="4.445" x2="-6.35" y2="5.715" width="0.127" layer="19"/>
<wire x1="-6.35" y1="5.715" x2="-5.715" y2="6.35" width="0.127" layer="19"/>
<wire x1="-5.715" y1="-8.89" x2="-6.35" y2="-8.255" width="0.127" layer="19"/>
<wire x1="-6.35" y1="-8.255" x2="-6.35" y2="-6.985" width="0.127" layer="19"/>
<wire x1="-6.35" y1="-6.985" x2="-5.715" y2="-6.35" width="0.127" layer="19"/>
<wire x1="-5.715" y1="-6.35" x2="-6.35" y2="-5.715" width="0.127" layer="19"/>
<wire x1="-6.35" y1="-5.715" x2="-6.35" y2="-4.445" width="0.127" layer="19"/>
<wire x1="-6.35" y1="-4.445" x2="-5.715" y2="-3.81" width="0.127" layer="19"/>
<wire x1="-5.715" y1="-3.81" x2="-6.35" y2="-3.175" width="0.127" layer="19"/>
<wire x1="-6.35" y1="-3.175" x2="-6.35" y2="-1.905" width="0.127" layer="19"/>
<wire x1="-6.35" y1="-1.905" x2="-5.715" y2="-1.27" width="0.127" layer="19"/>
<wire x1="-5.715" y1="13.97" x2="-6.35" y2="14.605" width="0.127" layer="19"/>
<wire x1="-6.35" y1="14.605" x2="-6.35" y2="15.875" width="0.127" layer="19"/>
<wire x1="-6.35" y1="15.875" x2="-5.715" y2="16.51" width="0.127" layer="19"/>
<wire x1="-5.715" y1="16.51" x2="-6.35" y2="17.145" width="0.127" layer="19"/>
<wire x1="-6.35" y1="17.145" x2="-6.35" y2="18.415" width="0.127" layer="19"/>
<wire x1="-6.35" y1="18.415" x2="-5.715" y2="19.05" width="0.127" layer="19"/>
<wire x1="10.795" y1="19.05" x2="9.525" y2="19.05" width="0.127" layer="19"/>
<wire x1="-4.445" y1="19.05" x2="-5.715" y2="19.05" width="0.127" layer="19"/>
<wire x1="10.795" y1="-31.75" x2="9.525" y2="-31.75" width="0.127" layer="19"/>
<wire x1="-4.445" y1="-31.75" x2="-5.715" y2="-31.75" width="0.127" layer="19"/>
<text x="-1.905" y="-22.225" size="1.016" layer="19" rot="R270">BOOT0</text>
<text x="0.635" y="-22.225" size="1.016" layer="19" rot="R270">BOOT1</text>
<text x="3.175" y="-20.32" size="1.016" layer="19" rot="R270">0</text>
<text x="3.175" y="-15.24" size="1.016" layer="19" rot="R270">1</text>
<circle x="10.16" y="10.16" radius="1.419903125" width="0.4064" layer="100"/>
<circle x="10.16" y="7.62" radius="1.419903125" width="0.4064" layer="100"/>
<circle x="10.16" y="5.08" radius="1.419903125" width="0.4064" layer="100"/>
<circle x="10.16" y="2.54" radius="1.419903125" width="0.4064" layer="100"/>
<circle x="10.16" y="-2.54" radius="1.419903125" width="0.4064" layer="100"/>
<circle x="10.16" y="-5.08" radius="1.419903125" width="0.4064" layer="100"/>
<circle x="10.16" y="-5.08" radius="1.419903125" width="0.4064" layer="100"/>
<circle x="10.16" y="-7.62" radius="1.419903125" width="0.4064" layer="100"/>
<circle x="10.16" y="-10.16" radius="1.419903125" width="0.4064" layer="100"/>
<circle x="10.16" y="-12.7" radius="1.419903125" width="0.4064" layer="100"/>
<circle x="10.16" y="-15.24" radius="1.419903125" width="0.4064" layer="100"/>
<circle x="10.16" y="-17.78" radius="1.419903125" width="0.4064" layer="100"/>
<circle x="10.16" y="-20.32" radius="1.419903125" width="0.4064" layer="100"/>
<circle x="10.16" y="-22.86" radius="1.419903125" width="0.4064" layer="100"/>
<circle x="10.16" y="-25.4" radius="1.419903125" width="0.4064" layer="100"/>
<circle x="10.16" y="-27.94" radius="1.419903125" width="0.4064" layer="100"/>
<circle x="10.16" y="-30.48" radius="1.419903125" width="0.4064" layer="100"/>
<circle x="-5.08" y="-20.32" radius="1.419903125" width="0.4064" layer="100"/>
<circle x="-5.08" y="-17.78" radius="1.419903125" width="0.4064" layer="100"/>
<wire x1="3.81" y1="15.24" x2="1.27" y2="16.51" width="0.4064" layer="19"/>
<wire x1="1.27" y1="16.51" x2="3.81" y2="17.78" width="0.4064" layer="19"/>
<wire x1="3.81" y1="17.78" x2="3.81" y2="16.51" width="0.4064" layer="19"/>
<wire x1="3.81" y1="16.51" x2="3.81" y2="15.24" width="0.4064" layer="19"/>
<wire x1="1.27" y1="15.24" x2="1.27" y2="16.51" width="0.4064" layer="19"/>
<wire x1="1.27" y1="16.51" x2="1.27" y2="17.78" width="0.4064" layer="19"/>
<wire x1="1.27" y1="16.51" x2="-1.27" y2="16.51" width="0.4064" layer="19"/>
<wire x1="3.81" y1="16.51" x2="6.35" y2="16.51" width="0.4064" layer="19"/>
<wire x1="-1.27" y1="16.51" x2="-2.54" y2="15.24" width="0.4064" layer="19"/>
<wire x1="-2.54" y1="15.24" x2="-5.08" y2="15.24" width="0.4064" layer="19"/>
<wire x1="10.16" y1="17.78" x2="7.62" y2="17.78" width="0.4064" layer="19"/>
<wire x1="7.62" y1="17.78" x2="6.35" y2="16.51" width="0.4064" layer="19"/>
<wire x1="1.27" y1="14.605" x2="0.635" y2="13.97" width="0.4064" layer="19"/>
<wire x1="0.635" y1="13.97" x2="0.635" y2="14.605" width="0.4064" layer="19"/>
<wire x1="0.635" y1="13.97" x2="1.27" y2="13.97" width="0.4064" layer="19"/>
<wire x1="2.54" y1="14.605" x2="1.905" y2="13.97" width="0.4064" layer="19"/>
<wire x1="1.905" y1="13.97" x2="1.905" y2="14.605" width="0.4064" layer="19"/>
<wire x1="1.905" y1="13.97" x2="2.54" y2="13.97" width="0.4064" layer="19"/>
</package>
</packages>
<symbols>
<symbol name="BLUE_PILL">
<pin name="PB12" x="-20.32" y="22.86" length="middle"/>
<pin name="PB13" x="-20.32" y="20.32" length="middle"/>
<pin name="PB14" x="-20.32" y="17.78" length="middle"/>
<pin name="PB15" x="-20.32" y="15.24" length="middle"/>
<pin name="PA8" x="-20.32" y="12.7" length="middle"/>
<pin name="PA9" x="-20.32" y="10.16" length="middle"/>
<pin name="PA10" x="-20.32" y="7.62" length="middle"/>
<pin name="PA11" x="-20.32" y="5.08" length="middle"/>
<pin name="PA12" x="-20.32" y="2.54" length="middle"/>
<pin name="PA15" x="-20.32" y="0" length="middle"/>
<pin name="PB3" x="-20.32" y="-2.54" length="middle"/>
<pin name="PB4" x="-20.32" y="-5.08" length="middle"/>
<pin name="PB5" x="-20.32" y="-7.62" length="middle"/>
<pin name="PB6" x="-20.32" y="-10.16" length="middle"/>
<pin name="PB7" x="-20.32" y="-12.7" length="middle"/>
<pin name="PB8" x="-20.32" y="-15.24" length="middle"/>
<pin name="PB9" x="-20.32" y="-17.78" length="middle"/>
<pin name="5V" x="-20.32" y="-20.32" length="middle"/>
<pin name="GND2" x="-20.32" y="-22.86" length="middle"/>
<pin name="3.3V1" x="-20.32" y="-25.4" length="middle"/>
<pin name="GND1" x="20.32" y="22.86" length="middle" direction="pwr" rot="R180"/>
<pin name="GND" x="20.32" y="20.32" length="middle" rot="R180"/>
<pin name="3.3V" x="20.32" y="17.78" length="middle" rot="R180"/>
<pin name="RESET" x="20.32" y="15.24" length="middle" rot="R180"/>
<pin name="PB11" x="20.32" y="12.7" length="middle" rot="R180"/>
<pin name="PB10" x="20.32" y="10.16" length="middle" rot="R180"/>
<pin name="PB1" x="20.32" y="7.62" length="middle" rot="R180"/>
<pin name="PB0" x="20.32" y="5.08" length="middle" rot="R180"/>
<pin name="PA7" x="20.32" y="2.54" length="middle" rot="R180"/>
<pin name="PA6" x="20.32" y="0" length="middle" rot="R180"/>
<pin name="PA5" x="20.32" y="-2.54" length="middle" rot="R180"/>
<pin name="PA4" x="20.32" y="-5.08" length="middle" rot="R180"/>
<pin name="PA3" x="20.32" y="-7.62" length="middle" rot="R180"/>
<pin name="PA2" x="20.32" y="-10.16" length="middle" rot="R180"/>
<pin name="PA1" x="20.32" y="-12.7" length="middle" rot="R180"/>
<pin name="PA0" x="20.32" y="-15.24" length="middle" rot="R180"/>
<pin name="PC15" x="20.32" y="-17.78" length="middle" rot="R180"/>
<pin name="PC14" x="20.32" y="-20.32" length="middle" rot="R180"/>
<pin name="PC13" x="20.32" y="-22.86" length="middle" rot="R180"/>
<pin name="VBAT" x="20.32" y="-25.4" length="middle" rot="R180"/>
<wire x1="-5.08" y1="25.4" x2="-13.803159375" y2="25.4" width="0.254" layer="94"/>
<wire x1="-13.803159375" y1="25.4" x2="-15.24" y2="23.963159375" width="0.254" layer="94" curve="90"/>
<wire x1="-15.24" y1="23.963159375" x2="-15.24" y2="-26.862371875" width="0.254" layer="94"/>
<wire x1="-15.24" y1="-26.862371875" x2="-14.162371875" y2="-27.94" width="0.254" layer="94" curve="90"/>
<wire x1="-14.162371875" y1="-27.94" x2="13.803159375" y2="-27.94" width="0.254" layer="94"/>
<wire x1="13.803159375" y1="-27.94" x2="15.24" y2="-26.503159375" width="0.254" layer="94" curve="90"/>
<wire x1="15.24" y1="-26.503159375" x2="15.24" y2="24.13" width="0.254" layer="94"/>
<wire x1="15.24" y1="24.13" x2="13.97" y2="25.4" width="0.254" layer="94" curve="90"/>
<wire x1="13.97" y1="25.4" x2="5.08" y2="25.4" width="0.254" layer="94"/>
<wire x1="5.08" y1="25.4" x2="5.08" y2="20.32" width="0.254" layer="94"/>
<wire x1="5.08" y1="20.32" x2="-5.08" y2="20.32" width="0.254" layer="94"/>
<wire x1="-5.08" y1="20.32" x2="-5.08" y2="25.4" width="0.254" layer="94"/>
<wire x1="-5.08" y1="25.4" x2="5.08" y2="25.4" width="0.254" layer="94"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="BLUE_PILL" uservalue="yes">
<gates>
<gate name="G$1" symbol="BLUE_PILL" x="0" y="0"/>
</gates>
<devices>
<device name="" package="BLUE_PILL">
<connects>
<connect gate="G$1" pin="3.3V" pad="P$23"/>
<connect gate="G$1" pin="3.3V1" pad="P$20"/>
<connect gate="G$1" pin="5V" pad="P$18"/>
<connect gate="G$1" pin="GND" pad="P$22"/>
<connect gate="G$1" pin="GND1" pad="P$21"/>
<connect gate="G$1" pin="GND2" pad="P$19"/>
<connect gate="G$1" pin="PA0" pad="P$36"/>
<connect gate="G$1" pin="PA1" pad="P$35"/>
<connect gate="G$1" pin="PA10" pad="P$7"/>
<connect gate="G$1" pin="PA11" pad="P$8"/>
<connect gate="G$1" pin="PA12" pad="P$9"/>
<connect gate="G$1" pin="PA15" pad="P$10"/>
<connect gate="G$1" pin="PA2" pad="P$34"/>
<connect gate="G$1" pin="PA3" pad="P$33"/>
<connect gate="G$1" pin="PA4" pad="P$32"/>
<connect gate="G$1" pin="PA5" pad="P$31"/>
<connect gate="G$1" pin="PA6" pad="P$30"/>
<connect gate="G$1" pin="PA7" pad="P$29"/>
<connect gate="G$1" pin="PA8" pad="P$5"/>
<connect gate="G$1" pin="PA9" pad="P$6"/>
<connect gate="G$1" pin="PB0" pad="P$28"/>
<connect gate="G$1" pin="PB1" pad="P$27"/>
<connect gate="G$1" pin="PB10" pad="P$26"/>
<connect gate="G$1" pin="PB11" pad="P$25"/>
<connect gate="G$1" pin="PB12" pad="P$1"/>
<connect gate="G$1" pin="PB13" pad="P$2"/>
<connect gate="G$1" pin="PB14" pad="P$3"/>
<connect gate="G$1" pin="PB15" pad="P$4"/>
<connect gate="G$1" pin="PB3" pad="P$11"/>
<connect gate="G$1" pin="PB4" pad="P$12"/>
<connect gate="G$1" pin="PB5" pad="P$13"/>
<connect gate="G$1" pin="PB6" pad="P$14"/>
<connect gate="G$1" pin="PB7" pad="P$15"/>
<connect gate="G$1" pin="PB8" pad="P$16"/>
<connect gate="G$1" pin="PB9" pad="P$17"/>
<connect gate="G$1" pin="PC13" pad="P$39"/>
<connect gate="G$1" pin="PC14" pad="P$38"/>
<connect gate="G$1" pin="PC15" pad="P$37"/>
<connect gate="G$1" pin="RESET" pad="P$24"/>
<connect gate="G$1" pin="VBAT" pad="P$40"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="ADVANCED" package="BLUE_PILL_ADV">
<connects>
<connect gate="G$1" pin="3.3V" pad="P$23"/>
<connect gate="G$1" pin="3.3V1" pad="P$20"/>
<connect gate="G$1" pin="5V" pad="P$18"/>
<connect gate="G$1" pin="GND" pad="P$22"/>
<connect gate="G$1" pin="GND1" pad="P$21"/>
<connect gate="G$1" pin="GND2" pad="P$19"/>
<connect gate="G$1" pin="PA0" pad="P$36"/>
<connect gate="G$1" pin="PA1" pad="P$35"/>
<connect gate="G$1" pin="PA10" pad="P$7"/>
<connect gate="G$1" pin="PA11" pad="P$8"/>
<connect gate="G$1" pin="PA12" pad="P$9"/>
<connect gate="G$1" pin="PA15" pad="P$10"/>
<connect gate="G$1" pin="PA2" pad="P$34"/>
<connect gate="G$1" pin="PA3" pad="P$33"/>
<connect gate="G$1" pin="PA4" pad="P$32"/>
<connect gate="G$1" pin="PA5" pad="P$31"/>
<connect gate="G$1" pin="PA6" pad="P$30"/>
<connect gate="G$1" pin="PA7" pad="P$29"/>
<connect gate="G$1" pin="PA8" pad="P$5"/>
<connect gate="G$1" pin="PA9" pad="P$6"/>
<connect gate="G$1" pin="PB0" pad="P$28"/>
<connect gate="G$1" pin="PB1" pad="P$27"/>
<connect gate="G$1" pin="PB10" pad="P$26"/>
<connect gate="G$1" pin="PB11" pad="P$25"/>
<connect gate="G$1" pin="PB12" pad="P$1"/>
<connect gate="G$1" pin="PB13" pad="P$2"/>
<connect gate="G$1" pin="PB14" pad="P$3"/>
<connect gate="G$1" pin="PB15" pad="P$4"/>
<connect gate="G$1" pin="PB3" pad="P$11"/>
<connect gate="G$1" pin="PB4" pad="P$12"/>
<connect gate="G$1" pin="PB5" pad="P$13"/>
<connect gate="G$1" pin="PB6" pad="P$14"/>
<connect gate="G$1" pin="PB7" pad="P$15"/>
<connect gate="G$1" pin="PB8" pad="P$16"/>
<connect gate="G$1" pin="PB9" pad="P$17"/>
<connect gate="G$1" pin="PC13" pad="P$39"/>
<connect gate="G$1" pin="PC14" pad="P$38"/>
<connect gate="G$1" pin="PC15" pad="P$37"/>
<connect gate="G$1" pin="RESET" pad="P$24"/>
<connect gate="G$1" pin="VBAT" pad="P$40"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="pololu-stepper-driver">
<description>&lt;b&gt;Pololu stepper motor driver&lt;/b&gt;&lt;p&gt;
&lt;author&gt;Created by Suzaku Lab. Ltd. support@suzakugiken.jp&lt;/author&gt;
&lt;p&gt;This is an unofficial library. If you notice a mistake, please contact the author.&lt;/p&gt;</description>
<packages>
<package name="A4988">
<description>&lt;b&gt;A4988 Stepper Motor Driver Carriers&lt;/b&gt;</description>
<pad name="1" x="-6.35" y="8.89" drill="1.016"/>
<pad name="2" x="-6.35" y="6.35" drill="1.016"/>
<pad name="3" x="-6.35" y="3.81" drill="1.016"/>
<pad name="4" x="-6.35" y="1.27" drill="1.016"/>
<pad name="5" x="-6.35" y="-1.27" drill="1.016"/>
<pad name="6" x="-6.35" y="-3.81" drill="1.016"/>
<pad name="7" x="-6.35" y="-6.35" drill="1.016"/>
<pad name="8" x="-6.35" y="-8.89" drill="1.016"/>
<pad name="9" x="6.35" y="-8.89" drill="1.016"/>
<pad name="10" x="6.35" y="-6.35" drill="1.016"/>
<pad name="11" x="6.35" y="-3.81" drill="1.016"/>
<pad name="12" x="6.35" y="-1.27" drill="1.016"/>
<pad name="13" x="6.35" y="1.27" drill="1.016"/>
<pad name="14" x="6.35" y="3.81" drill="1.016"/>
<pad name="15" x="6.35" y="6.35" drill="1.016"/>
<pad name="16" x="6.35" y="8.89" drill="1.016"/>
<wire x1="-7.6" y1="10.15" x2="7.6" y2="10.15" width="0.127" layer="21"/>
<wire x1="7.6" y1="10.15" x2="7.6" y2="-10.15" width="0.127" layer="21"/>
<wire x1="7.6" y1="-10.15" x2="-7.6" y2="-10.15" width="0.127" layer="21"/>
<wire x1="-7.6" y1="-10.15" x2="-7.6" y2="10.15" width="0.127" layer="21"/>
<text x="-5.08" y="8.89" size="1.27" layer="21" align="center-left">!EN</text>
<text x="-5.08" y="6.35" size="1.27" layer="21" align="center-left">MS1</text>
<text x="-5.08" y="3.81" size="1.27" layer="21" align="center-left">MS2</text>
<text x="-5.08" y="1.27" size="1.27" layer="21" align="center-left">MS3</text>
<text x="-5.08" y="-1.27" size="1.27" layer="21" align="center-left">!RST</text>
<text x="-5.08" y="-3.81" size="1.27" layer="21" align="center-left">!SLP</text>
<text x="-5.08" y="-6.35" size="1.27" layer="21" align="center-left">STEP</text>
<text x="-5.08" y="-8.89" size="1.27" layer="21" align="center-left">DIR</text>
<text x="5.08" y="8.89" size="1.27" layer="21" align="center-right">VMOT</text>
<text x="5.08" y="6.35" size="1.27" layer="21" align="center-right">GND</text>
<text x="5.08" y="3.81" size="1.27" layer="21" align="center-right">2B</text>
<text x="5.08" y="1.27" size="1.27" layer="21" align="center-right">2A</text>
<text x="5.08" y="-1.27" size="1.27" layer="21" align="center-right">1A</text>
<text x="5.08" y="-3.81" size="1.27" layer="21" align="center-right">1B</text>
<text x="5.08" y="-6.35" size="1.27" layer="21" align="center-right">VDD</text>
<text x="5.08" y="-8.89" size="1.27" layer="21" align="center-right">GND</text>
<text x="-5.08" y="-12.7" size="1.778" layer="25">&gt;NAME</text>
<text x="-5.715" y="10.795" size="1.778" layer="27">&gt;VALUE</text>
</package>
</packages>
<symbols>
<symbol name="A4988">
<description>A4988 stepper motor driver</description>
<pin name="!EN" x="-12.7" y="7.62" length="short" direction="pas"/>
<pin name="MS1" x="-12.7" y="5.08" length="short" direction="pas"/>
<pin name="MS2" x="-12.7" y="2.54" length="short" direction="pas"/>
<pin name="MS3" x="-12.7" y="0" length="short" direction="pas"/>
<pin name="!RST" x="-12.7" y="-2.54" length="short" direction="pas"/>
<pin name="!SLP" x="-12.7" y="-5.08" length="short" direction="pas"/>
<pin name="STEP" x="-12.7" y="-7.62" length="short" direction="in"/>
<pin name="DIR" x="-12.7" y="-10.16" length="short" direction="in"/>
<pin name="GND1" x="12.7" y="-10.16" length="short" direction="pwr" rot="R180"/>
<pin name="VDD" x="12.7" y="-7.62" length="short" direction="pwr" rot="R180"/>
<pin name="1B" x="12.7" y="-5.08" length="short" direction="out" rot="R180"/>
<pin name="1A" x="12.7" y="-2.54" length="short" direction="out" rot="R180"/>
<pin name="2A" x="12.7" y="0" length="short" direction="out" rot="R180"/>
<pin name="2B" x="12.7" y="2.54" length="short" direction="out" rot="R180"/>
<pin name="GND2" x="12.7" y="5.08" length="short" direction="pwr" rot="R180"/>
<pin name="VMOT" x="12.7" y="7.62" length="short" direction="pwr" rot="R180"/>
<wire x1="-10.16" y1="10.16" x2="10.16" y2="10.16" width="0.254" layer="94"/>
<wire x1="10.16" y1="10.16" x2="10.16" y2="-12.7" width="0.254" layer="94"/>
<wire x1="10.16" y1="-12.7" x2="-10.16" y2="-12.7" width="0.254" layer="94"/>
<wire x1="-10.16" y1="-12.7" x2="-10.16" y2="10.16" width="0.254" layer="94"/>
<text x="-5.08" y="10.795" size="1.778" layer="95">&gt;NAME</text>
<text x="-5.08" y="-15.24" size="1.778" layer="96">&gt;VALUE</text>
</symbol>
</symbols>
<devicesets>
<deviceset name="2986-A4988" prefix="IC">
<description>&lt;b&gt;A4988 Stepper Motor Driver Carrier; Black Edition (Bulk; Header Pins Soldered)&lt;/b&gt;

&lt;ul&gt;
&lt;li&gt;&lt;a href="https://www.pololu.com/product/2986"&gt;#2986 A4988 Stepper Motor Driver Carrier; Black Edition (Bulk; Header Pins Soldered)&lt;/a&gt;&lt;/li&gt;
&lt;/ul&gt;

&lt;p&gt;in Japan, &lt;a href="https://suzakugiken.jp/"&gt;Suzaku Lab. Ltd.&lt;/a&gt;&lt;/p&gt;
&lt;ul&gt;
&lt;li&gt;&lt;a href="https://szc.jp/po2986"&gt;#2986 A4988 ステッピングモータドライバボード Black Edition (バルク品 ピンヘッダ実装済み)&lt;/a&gt;&lt;/li&gt;
&lt;/ul&gt;</description>
<gates>
<gate name="G$1" symbol="A4988" x="0" y="0"/>
</gates>
<devices>
<device name="" package="A4988">
<connects>
<connect gate="G$1" pin="!EN" pad="1"/>
<connect gate="G$1" pin="!RST" pad="5"/>
<connect gate="G$1" pin="!SLP" pad="6"/>
<connect gate="G$1" pin="1A" pad="12"/>
<connect gate="G$1" pin="1B" pad="11"/>
<connect gate="G$1" pin="2A" pad="13"/>
<connect gate="G$1" pin="2B" pad="14"/>
<connect gate="G$1" pin="DIR" pad="8"/>
<connect gate="G$1" pin="GND1" pad="9"/>
<connect gate="G$1" pin="GND2" pad="15"/>
<connect gate="G$1" pin="MS1" pad="2"/>
<connect gate="G$1" pin="MS2" pad="3"/>
<connect gate="G$1" pin="MS3" pad="4"/>
<connect gate="G$1" pin="STEP" pad="7"/>
<connect gate="G$1" pin="VDD" pad="10"/>
<connect gate="G$1" pin="VMOT" pad="16"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="Power_Symbols">
<description>&lt;B&gt;Supply &amp; Ground symbols</description>
<packages>
</packages>
<symbols>
<symbol name="+3.3V" urn="urn:adsk.eagle:symbol:18498252/2">
<description>3.3 Volt (3V3) Bar</description>
<wire x1="1.905" y1="2.54" x2="-1.905" y2="2.54" width="0.254" layer="94"/>
<text x="-0.127" y="3.048" size="1.778" layer="96" align="bottom-center">&gt;VALUE</text>
<pin name="+3.3V" x="0" y="0" visible="off" length="short" direction="sup" rot="R90"/>
</symbol>
<symbol name="+5V" urn="urn:adsk.eagle:symbol:18498226/2">
<description>5 Volt (5V0) Bar</description>
<wire x1="1.905" y1="2.54" x2="-1.905" y2="2.54" width="0.254" layer="94"/>
<text x="-0.127" y="3.048" size="1.778" layer="96" align="bottom-center">&gt;VALUE</text>
<pin name="+5V" x="0" y="0" visible="off" length="short" direction="sup" rot="R90"/>
</symbol>
<symbol name="GND" urn="urn:adsk.eagle:symbol:16502380/2">
<description>Ground (GND) Arrow</description>
<wire x1="-1.27" y1="0" x2="1.27" y2="0" width="0.254" layer="94"/>
<wire x1="1.27" y1="0" x2="0" y2="-1.27" width="0.254" layer="94"/>
<wire x1="0" y1="-1.27" x2="-1.27" y2="0" width="0.254" layer="94"/>
<text x="0" y="-2.54" size="1.778" layer="96" align="center">&gt;VALUE</text>
<pin name="GND" x="0" y="2.54" visible="off" length="short" direction="sup" rot="R270"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="+3.3V" urn="urn:adsk.eagle:component:16502431/7" prefix="SUPPLY" uservalue="yes">
<description>&lt;b&gt;SUPPLY SYMBOL&lt;/b&gt;  3.3 Volt (3V3) Bar</description>
<gates>
<gate name="G$1" symbol="+3.3V" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name="">
<attribute name="CATEGORY" value="Supply" constant="no"/>
<attribute name="VALUE" value="+3.3V" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="+5V" urn="urn:adsk.eagle:component:16502432/7" prefix="SUPPLY" uservalue="yes">
<description>&lt;b&gt;SUPPLY SYMBOL&lt;/b&gt;  5 Volt (5V0) Bar</description>
<gates>
<gate name="G$1" symbol="+5V" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name="">
<attribute name="CATEGORY" value="Supply" constant="no"/>
<attribute name="VALUE" value="+5V" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="GND" urn="urn:adsk.eagle:component:16502425/5" prefix="SUPPLY" uservalue="yes">
<description>&lt;b&gt;SUPPLY SYMBOL&lt;/b&gt; - Ground (GND) Arrow</description>
<gates>
<gate name="G$1" symbol="GND" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name="">
<attribute name="CATEGORY" value="Supply" constant="no"/>
<attribute name="VALUE" value="GND" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="Capacitor">
<description>&lt;B&gt;Capacitors - Fixed, Variable, Trimmers</description>
<packages>
<package name="CAPMP3216X180N" urn="urn:adsk.eagle:footprint:16290838/1">
<description>Molded Body, 3.20 X 1.60 X 1.80 mm body
&lt;p&gt;Molded Body package with body size 3.20 X 1.60 X 1.80 mm&lt;/p&gt;</description>
<wire x1="1.7" y1="0.9084" x2="-2.5217" y2="0.9084" width="0.12" layer="21"/>
<wire x1="-2.5217" y1="0.9084" x2="-2.5217" y2="-0.9084" width="0.12" layer="21"/>
<wire x1="-2.5217" y1="-0.9084" x2="1.7" y2="-0.9084" width="0.12" layer="21"/>
<wire x1="1.7" y1="-0.9" x2="-1.7" y2="-0.9" width="0.12" layer="51"/>
<wire x1="-1.7" y1="-0.9" x2="-1.7" y2="0.9" width="0.12" layer="51"/>
<wire x1="-1.7" y1="0.9" x2="1.7" y2="0.9" width="0.12" layer="51"/>
<wire x1="1.7" y1="0.9" x2="1.7" y2="-0.9" width="0.12" layer="51"/>
<smd name="1" x="-1.3099" y="0" dx="1.7955" dy="1.1887" layer="1"/>
<smd name="2" x="1.3099" y="0" dx="1.7955" dy="1.1887" layer="1"/>
<text x="0" y="1.5434" size="1.27" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-1.5434" size="1.27" layer="27" align="top-center">&gt;VALUE</text>
</package>
<package name="CAPMP3528X210N" urn="urn:adsk.eagle:footprint:16290842/1">
<description>Molded Body, 3.50 X 2.80 X 2.10 mm body
&lt;p&gt;Molded Body package with body size 3.50 X 2.80 X 2.10 mm&lt;/p&gt;</description>
<wire x1="1.85" y1="1.5" x2="-2.6717" y2="1.5" width="0.12" layer="21"/>
<wire x1="-2.6717" y1="1.5" x2="-2.6717" y2="-1.5" width="0.12" layer="21"/>
<wire x1="-2.6717" y1="-1.5" x2="1.85" y2="-1.5" width="0.12" layer="21"/>
<wire x1="1.85" y1="-1.5" x2="-1.85" y2="-1.5" width="0.12" layer="51"/>
<wire x1="-1.85" y1="-1.5" x2="-1.85" y2="1.5" width="0.12" layer="51"/>
<wire x1="-1.85" y1="1.5" x2="1.85" y2="1.5" width="0.12" layer="51"/>
<wire x1="1.85" y1="1.5" x2="1.85" y2="-1.5" width="0.12" layer="51"/>
<smd name="1" x="-1.4599" y="0" dx="1.7955" dy="2.2036" layer="1"/>
<smd name="2" x="1.4599" y="0" dx="1.7955" dy="2.2036" layer="1"/>
<text x="0" y="2.135" size="1.27" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-2.135" size="1.27" layer="27" align="top-center">&gt;VALUE</text>
</package>
<package name="CAPMP6032X280N" urn="urn:adsk.eagle:footprint:16290825/1">
<description>Molded Body, 6.00 X 3.20 X 2.80 mm body
&lt;p&gt;Molded Body package with body size 6.00 X 3.20 X 2.80 mm&lt;/p&gt;</description>
<wire x1="3.15" y1="1.75" x2="-3.9692" y2="1.75" width="0.12" layer="21"/>
<wire x1="-3.9692" y1="1.75" x2="-3.9692" y2="-1.75" width="0.12" layer="21"/>
<wire x1="-3.9692" y1="-1.75" x2="3.15" y2="-1.75" width="0.12" layer="21"/>
<wire x1="3.15" y1="-1.75" x2="-3.15" y2="-1.75" width="0.12" layer="51"/>
<wire x1="-3.15" y1="-1.75" x2="-3.15" y2="1.75" width="0.12" layer="51"/>
<wire x1="-3.15" y1="1.75" x2="3.15" y2="1.75" width="0.12" layer="51"/>
<wire x1="3.15" y1="1.75" x2="3.15" y2="-1.75" width="0.12" layer="51"/>
<smd name="1" x="-2.4712" y="0" dx="2.368" dy="2.2036" layer="1"/>
<smd name="2" x="2.4712" y="0" dx="2.368" dy="2.2036" layer="1"/>
<text x="0" y="2.385" size="1.27" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-2.385" size="1.27" layer="27" align="top-center">&gt;VALUE</text>
</package>
<package name="CAPMP7343X310N" urn="urn:adsk.eagle:footprint:16290846/1">
<description>Molded Body, 7.30 X 4.30 X 3.10 mm body
&lt;p&gt;Molded Body package with body size 7.30 X 4.30 X 3.10 mm&lt;/p&gt;</description>
<wire x1="3.8" y1="2.3" x2="-4.6192" y2="2.3" width="0.12" layer="21"/>
<wire x1="-4.6192" y1="2.3" x2="-4.6192" y2="-2.3" width="0.12" layer="21"/>
<wire x1="-4.6192" y1="-2.3" x2="3.8" y2="-2.3" width="0.12" layer="21"/>
<wire x1="3.8" y1="-2.3" x2="-3.8" y2="-2.3" width="0.12" layer="51"/>
<wire x1="-3.8" y1="-2.3" x2="-3.8" y2="2.3" width="0.12" layer="51"/>
<wire x1="-3.8" y1="2.3" x2="3.8" y2="2.3" width="0.12" layer="51"/>
<wire x1="3.8" y1="2.3" x2="3.8" y2="-2.3" width="0.12" layer="51"/>
<smd name="1" x="-3.1212" y="0" dx="2.368" dy="2.4036" layer="1"/>
<smd name="2" x="3.1212" y="0" dx="2.368" dy="2.4036" layer="1"/>
<text x="0" y="2.935" size="1.27" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-2.935" size="1.27" layer="27" align="top-center">&gt;VALUE</text>
</package>
<package name="CAPPRD508W65D1000H1100B" urn="urn:adsk.eagle:footprint:16290830/1">
<description>Radial Polarized Capacitor, 5.08 mm pitch, 10.00 mm body diameter, 11.00 mm body height
&lt;p&gt;Radial Polarized Capacitor package with 5.08 mm pitch (lead spacing), 0.65 mm lead diameter, 10.00 mm body diameter and 11.00 mm body height&lt;/p&gt;</description>
<circle x="0" y="0" radius="5" width="0.12" layer="21"/>
<circle x="0" y="0" radius="5" width="0.12" layer="51"/>
<wire x1="-4.1325" y1="4.1326" x2="-3.3825" y2="4.1326" width="0.12" layer="21"/>
<wire x1="-3.7575" y1="4.5076" x2="-3.7575" y2="3.7576" width="0.12" layer="21"/>
<pad name="1" x="-2.54" y="0" drill="0.85" diameter="1.45"/>
<pad name="2" x="2.54" y="0" drill="0.85" diameter="1.45"/>
<text x="0" y="5.635" size="1.27" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-5.635" size="1.27" layer="27" align="top-center">&gt;VALUE</text>
</package>
<package name="CAPAE1030X1050N" urn="urn:adsk.eagle:footprint:16290833/1">
<description>ECAP (Aluminum Electrolytic Capacitor), 10.30 X 10.50 mm body
&lt;p&gt;ECAP (Aluminum Electrolytic Capacitor) package with body size 10.30 X 10.50 mm&lt;/p&gt;</description>
<wire x1="-5.25" y1="1.3117" x2="-5.25" y2="3.1538" width="0.12" layer="21"/>
<wire x1="-5.25" y1="3.1538" x2="-3.1538" y2="5.25" width="0.12" layer="21"/>
<wire x1="-3.1538" y1="5.25" x2="5.25" y2="5.25" width="0.12" layer="21"/>
<wire x1="5.25" y1="5.25" x2="5.25" y2="1.3117" width="0.12" layer="21"/>
<wire x1="-5.25" y1="-1.3117" x2="-5.25" y2="-3.1538" width="0.12" layer="21"/>
<wire x1="-5.25" y1="-3.1538" x2="-3.1538" y2="-5.25" width="0.12" layer="21"/>
<wire x1="-3.1538" y1="-5.25" x2="5.25" y2="-5.25" width="0.12" layer="21"/>
<wire x1="5.25" y1="-5.25" x2="5.25" y2="-1.3117" width="0.12" layer="21"/>
<wire x1="5.25" y1="-5.25" x2="-5.25" y2="-5.25" width="0.12" layer="51"/>
<wire x1="-5.25" y1="-5.25" x2="-5.25" y2="5.25" width="0.12" layer="51"/>
<wire x1="-5.25" y1="5.25" x2="5.25" y2="5.25" width="0.12" layer="51"/>
<wire x1="5.25" y1="5.25" x2="5.25" y2="-5.25" width="0.12" layer="51"/>
<smd name="1" x="-4.3527" y="0" dx="4.4157" dy="2.1153" layer="1"/>
<smd name="2" x="4.3527" y="0" dx="4.4157" dy="2.1153" layer="1"/>
<text x="0" y="5.885" size="1.27" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-5.885" size="1.27" layer="27" align="top-center">&gt;VALUE</text>
</package>
<package name="CAPAE830X1050N" urn="urn:adsk.eagle:footprint:16290826/1">
<description>ECAP (Aluminum Electrolytic Capacitor), 8.30 X 10.50 mm body
&lt;p&gt;ECAP (Aluminum Electrolytic Capacitor) package with body size 8.30 X 10.50 mm&lt;/p&gt;</description>
<wire x1="-4.25" y1="1.3117" x2="-4.25" y2="2.6538" width="0.12" layer="21"/>
<wire x1="-4.25" y1="2.6538" x2="-2.6538" y2="4.25" width="0.12" layer="21"/>
<wire x1="-2.6538" y1="4.25" x2="4.25" y2="4.25" width="0.12" layer="21"/>
<wire x1="4.25" y1="4.25" x2="4.25" y2="1.3117" width="0.12" layer="21"/>
<wire x1="-4.25" y1="-1.3117" x2="-4.25" y2="-2.6538" width="0.12" layer="21"/>
<wire x1="-4.25" y1="-2.6538" x2="-2.6538" y2="-4.25" width="0.12" layer="21"/>
<wire x1="-2.6538" y1="-4.25" x2="4.25" y2="-4.25" width="0.12" layer="21"/>
<wire x1="4.25" y1="-4.25" x2="4.25" y2="-1.3117" width="0.12" layer="21"/>
<wire x1="4.25" y1="-4.25" x2="-4.25" y2="-4.25" width="0.12" layer="51"/>
<wire x1="-4.25" y1="-4.25" x2="-4.25" y2="4.25" width="0.12" layer="51"/>
<wire x1="-4.25" y1="4.25" x2="4.25" y2="4.25" width="0.12" layer="51"/>
<wire x1="4.25" y1="4.25" x2="4.25" y2="-4.25" width="0.12" layer="51"/>
<smd name="1" x="-3.4259" y="0" dx="3.7636" dy="2.1153" layer="1"/>
<smd name="2" x="3.4259" y="0" dx="3.7636" dy="2.1153" layer="1"/>
<text x="0" y="4.885" size="1.27" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-4.885" size="1.27" layer="27" align="top-center">&gt;VALUE</text>
</package>
<package name="CAPPRD1000W100D2275H3200B" urn="urn:adsk.eagle:footprint:16290828/1">
<description>Radial Polarized Capacitor, 10.00 mm pitch, 22.75 mm body diameter, 32.00 mm body height
&lt;p&gt;Radial Polarized Capacitor package with 10.00 mm pitch (lead spacing), 1.00 mm lead diameter, 22.75 mm body diameter and 32.00 mm body height&lt;/p&gt;</description>
<circle x="0" y="0" radius="11.75" width="0.12" layer="21"/>
<circle x="0" y="0" radius="11.75" width="0.12" layer="51"/>
<wire x1="-8.9055" y1="8.9056" x2="-8.1555" y2="8.9056" width="0.12" layer="21"/>
<wire x1="-8.5305" y1="9.2806" x2="-8.5305" y2="8.5306" width="0.12" layer="21"/>
<pad name="1" x="-5" y="0" drill="1.2" diameter="1.8"/>
<pad name="2" x="5" y="0" drill="1.2" diameter="1.8"/>
<text x="0" y="12.385" size="1.27" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-12.385" size="1.27" layer="27" align="top-center">&gt;VALUE</text>
</package>
<package name="CAPAE1905X1660N" urn="urn:adsk.eagle:footprint:16290827/1">
<description>ECAP (Aluminum Electrolytic Capacitor), 19.05 X 16.60 mm body
&lt;p&gt;ECAP (Aluminum Electrolytic Capacitor) package with body size 19.05 X 16.60 mm&lt;/p&gt;</description>
<wire x1="-9.6" y1="1.4617" x2="-9.6" y2="5.4038" width="0.12" layer="21"/>
<wire x1="-9.6" y1="5.4038" x2="-5.4038" y2="9.6" width="0.12" layer="21"/>
<wire x1="-5.4038" y1="9.6" x2="9.6" y2="9.6" width="0.12" layer="21"/>
<wire x1="9.6" y1="9.6" x2="9.6" y2="1.4617" width="0.12" layer="21"/>
<wire x1="-9.6" y1="-1.4617" x2="-9.6" y2="-5.4038" width="0.12" layer="21"/>
<wire x1="-9.6" y1="-5.4038" x2="-5.4038" y2="-9.6" width="0.12" layer="21"/>
<wire x1="-5.4038" y1="-9.6" x2="9.6" y2="-9.6" width="0.12" layer="21"/>
<wire x1="9.6" y1="-9.6" x2="9.6" y2="-1.4617" width="0.12" layer="21"/>
<wire x1="9.6" y1="-9.6" x2="-9.6" y2="-9.6" width="0.12" layer="51"/>
<wire x1="-9.6" y1="-9.6" x2="-9.6" y2="9.6" width="0.12" layer="51"/>
<wire x1="-9.6" y1="9.6" x2="9.6" y2="9.6" width="0.12" layer="51"/>
<wire x1="9.6" y1="9.6" x2="9.6" y2="-9.6" width="0.12" layer="51"/>
<smd name="1" x="-6.9877" y="0" dx="7.6873" dy="2.4153" layer="1"/>
<smd name="2" x="6.9877" y="0" dx="7.6873" dy="2.4153" layer="1"/>
<text x="0" y="10.235" size="1.27" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-10.235" size="1.27" layer="27" align="top-center">&gt;VALUE</text>
</package>
<package name="CAPPRD550W110D1250H2500B" urn="urn:adsk.eagle:footprint:16290834/1">
<description>Radial Polarized Capacitor, 5.50 mm pitch, 12.50 mm body diameter, 25.00 mm body height
&lt;p&gt;Radial Polarized Capacitor package with 5.50 mm pitch (lead spacing), 1.10 mm lead diameter, 12.50 mm body diameter and 25.00 mm body height&lt;/p&gt;</description>
<circle x="0" y="0" radius="6.25" width="0.12" layer="21"/>
<circle x="0" y="0" radius="6.25" width="0.12" layer="51"/>
<wire x1="-5.0164" y1="5.0165" x2="-4.2664" y2="5.0165" width="0.12" layer="21"/>
<wire x1="-4.6414" y1="5.3915" x2="-4.6414" y2="4.6415" width="0.12" layer="21"/>
<pad name="1" x="-2.75" y="0" drill="1.3" diameter="1.95"/>
<pad name="2" x="2.75" y="0" drill="1.3" diameter="1.95"/>
<text x="0" y="6.885" size="1.27" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-6.885" size="1.27" layer="27" align="top-center">&gt;VALUE</text>
</package>
<package name="CAPPRD550W60D1200H2000B" urn="urn:adsk.eagle:footprint:16290832/1">
<description>Radial Polarized Capacitor, 5.50 mm pitch, 12.00 mm body diameter, 20.00 mm body height
&lt;p&gt;Radial Polarized Capacitor package with 5.50 mm pitch (lead spacing), 0.60 mm lead diameter, 12.00 mm body diameter and 20.00 mm body height&lt;/p&gt;</description>
<circle x="0" y="0" radius="6" width="0.12" layer="21"/>
<circle x="0" y="0" radius="6" width="0.12" layer="51"/>
<wire x1="-4.8397" y1="4.8397" x2="-4.0897" y2="4.8397" width="0.12" layer="21"/>
<wire x1="-4.4647" y1="5.2147" x2="-4.4647" y2="4.4647" width="0.12" layer="21"/>
<pad name="1" x="-2.75" y="0" drill="0.8" diameter="1.4"/>
<pad name="2" x="2.75" y="0" drill="0.8" diameter="1.4"/>
<text x="0" y="6.635" size="1.27" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-6.635" size="1.27" layer="27" align="top-center">&gt;VALUE</text>
</package>
<package name="CAPMP7443X430N" urn="urn:adsk.eagle:footprint:16290831/1">
<description>Molded Body, 7.42 X 4.35 X 4.30 mm body
&lt;p&gt;Molded Body package with body size 7.42 X 4.35 X 4.30 mm&lt;/p&gt;</description>
<wire x1="3.825" y1="2.25" x2="-4.6458" y2="2.25" width="0.12" layer="21"/>
<wire x1="-4.6458" y1="2.25" x2="-4.6458" y2="-2.25" width="0.12" layer="21"/>
<wire x1="-4.6458" y1="-2.25" x2="3.825" y2="-2.25" width="0.12" layer="21"/>
<wire x1="3.825" y1="-2.25" x2="-3.825" y2="-2.25" width="0.12" layer="51"/>
<wire x1="-3.825" y1="-2.25" x2="-3.825" y2="2.25" width="0.12" layer="51"/>
<wire x1="-3.825" y1="2.25" x2="3.825" y2="2.25" width="0.12" layer="51"/>
<wire x1="3.825" y1="2.25" x2="3.825" y2="-2.25" width="0.12" layer="51"/>
<smd name="1" x="-3.1655" y="0" dx="2.3326" dy="2.5153" layer="1"/>
<smd name="2" x="3.1655" y="0" dx="2.3326" dy="2.5153" layer="1"/>
<text x="0" y="2.885" size="1.27" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-2.885" size="1.27" layer="27" align="top-center">&gt;VALUE</text>
</package>
<package name="CAPPAD3410W80L3025D1825B" urn="urn:adsk.eagle:footprint:16290824/1">
<description>Axial Polarized Capacitor, 34.10 mm pitch, 30.25 mm body length, 18.25 mm body diameter
&lt;p&gt;Axial Polarized Capacitor package with 34.10 mm pitch (lead spacing), 0.80 mm lead diameter, 30.25 mm body length and 18.25 mm body diameter&lt;/p&gt;</description>
<wire x1="-15.25" y1="9.25" x2="-15.25" y2="-9.25" width="0.12" layer="21"/>
<wire x1="-15.25" y1="-9.25" x2="15.25" y2="-9.25" width="0.12" layer="21"/>
<wire x1="15.25" y1="-9.25" x2="15.25" y2="9.25" width="0.12" layer="21"/>
<wire x1="15.25" y1="9.25" x2="-15.25" y2="9.25" width="0.12" layer="21"/>
<wire x1="-11.4375" y1="9.25" x2="-11.4375" y2="-9.25" width="0.12" layer="21"/>
<wire x1="-15.25" y1="0" x2="-15.996" y2="0" width="0.12" layer="21"/>
<wire x1="15.25" y1="0" x2="15.996" y2="0" width="0.12" layer="21"/>
<wire x1="15.25" y1="-9.25" x2="-15.25" y2="-9.25" width="0.12" layer="51"/>
<wire x1="-15.25" y1="-9.25" x2="-15.25" y2="9.25" width="0.12" layer="51"/>
<wire x1="-15.25" y1="9.25" x2="15.25" y2="9.25" width="0.12" layer="51"/>
<wire x1="15.25" y1="9.25" x2="15.25" y2="-9.25" width="0.12" layer="51"/>
<pad name="1" x="-17.05" y="0" drill="1" diameter="1.6"/>
<pad name="2" x="17.05" y="0" drill="1" diameter="1.6"/>
<text x="0" y="9.885" size="1.27" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-9.885" size="1.27" layer="27" align="top-center">&gt;VALUE</text>
</package>
</packages>
<packages3d>
<package3d name="CAPMP3216X180N" urn="urn:adsk.eagle:package:16290884/1" type="model">
<description>Molded Body, 3.20 X 1.60 X 1.80 mm body
&lt;p&gt;Molded Body package with body size 3.20 X 1.60 X 1.80 mm&lt;/p&gt;</description>
<packageinstances>
<packageinstance name="CAPMP3216X180N"/>
</packageinstances>
</package3d>
<package3d name="CAPMP3528X210N" urn="urn:adsk.eagle:package:16290901/1" type="model">
<description>Molded Body, 3.50 X 2.80 X 2.10 mm body
&lt;p&gt;Molded Body package with body size 3.50 X 2.80 X 2.10 mm&lt;/p&gt;</description>
<packageinstances>
<packageinstance name="CAPMP3528X210N"/>
</packageinstances>
</package3d>
<package3d name="CAPMP6032X280N" urn="urn:adsk.eagle:package:16290892/1" type="model">
<description>Molded Body, 6.00 X 3.20 X 2.80 mm body
&lt;p&gt;Molded Body package with body size 6.00 X 3.20 X 2.80 mm&lt;/p&gt;</description>
<packageinstances>
<packageinstance name="CAPMP6032X280N"/>
</packageinstances>
</package3d>
<package3d name="CAPMP7343X310N" urn="urn:adsk.eagle:package:16290885/1" type="model">
<description>Molded Body, 7.30 X 4.30 X 3.10 mm body
&lt;p&gt;Molded Body package with body size 7.30 X 4.30 X 3.10 mm&lt;/p&gt;</description>
<packageinstances>
<packageinstance name="CAPMP7343X310N"/>
</packageinstances>
</package3d>
<package3d name="CAPPRD508W65D1000H1100B" urn="urn:adsk.eagle:package:16290899/1" type="model">
<description>Radial Polarized Capacitor, 5.08 mm pitch, 10.00 mm body diameter, 11.00 mm body height
&lt;p&gt;Radial Polarized Capacitor package with 5.08 mm pitch (lead spacing), 0.65 mm lead diameter, 10.00 mm body diameter and 11.00 mm body height&lt;/p&gt;</description>
<packageinstances>
<packageinstance name="CAPPRD508W65D1000H1100B"/>
</packageinstances>
</package3d>
<package3d name="CAPAE1030X1050N" urn="urn:adsk.eagle:package:16290882/1" type="model">
<description>ECAP (Aluminum Electrolytic Capacitor), 10.30 X 10.50 mm body
&lt;p&gt;ECAP (Aluminum Electrolytic Capacitor) package with body size 10.30 X 10.50 mm&lt;/p&gt;</description>
<packageinstances>
<packageinstance name="CAPAE1030X1050N"/>
</packageinstances>
</package3d>
<package3d name="CAPAE830X1050N" urn="urn:adsk.eagle:package:16290889/1" type="model">
<description>ECAP (Aluminum Electrolytic Capacitor), 8.30 X 10.50 mm body
&lt;p&gt;ECAP (Aluminum Electrolytic Capacitor) package with body size 8.30 X 10.50 mm&lt;/p&gt;</description>
<packageinstances>
<packageinstance name="CAPAE830X1050N"/>
</packageinstances>
</package3d>
<package3d name="CAPPRD1000W100D2275H3200B" urn="urn:adsk.eagle:package:16290888/1" type="model">
<description>Radial Polarized Capacitor, 10.00 mm pitch, 22.75 mm body diameter, 32.00 mm body height
&lt;p&gt;Radial Polarized Capacitor package with 10.00 mm pitch (lead spacing), 1.00 mm lead diameter, 22.75 mm body diameter and 32.00 mm body height&lt;/p&gt;</description>
<packageinstances>
<packageinstance name="CAPPRD1000W100D2275H3200B"/>
</packageinstances>
</package3d>
<package3d name="CAPAE1905X1660N" urn="urn:adsk.eagle:package:16290872/1" type="model">
<description>ECAP (Aluminum Electrolytic Capacitor), 19.05 X 16.60 mm body
&lt;p&gt;ECAP (Aluminum Electrolytic Capacitor) package with body size 19.05 X 16.60 mm&lt;/p&gt;</description>
<packageinstances>
<packageinstance name="CAPAE1905X1660N"/>
</packageinstances>
</package3d>
<package3d name="CAPPRD550W110D1250H2500B" urn="urn:adsk.eagle:package:16290890/1" type="model">
<description>Radial Polarized Capacitor, 5.50 mm pitch, 12.50 mm body diameter, 25.00 mm body height
&lt;p&gt;Radial Polarized Capacitor package with 5.50 mm pitch (lead spacing), 1.10 mm lead diameter, 12.50 mm body diameter and 25.00 mm body height&lt;/p&gt;</description>
<packageinstances>
<packageinstance name="CAPPRD550W110D1250H2500B"/>
</packageinstances>
</package3d>
<package3d name="CAPPRD550W60D1200H2000B" urn="urn:adsk.eagle:package:16290874/1" type="model">
<description>Radial Polarized Capacitor, 5.50 mm pitch, 12.00 mm body diameter, 20.00 mm body height
&lt;p&gt;Radial Polarized Capacitor package with 5.50 mm pitch (lead spacing), 0.60 mm lead diameter, 12.00 mm body diameter and 20.00 mm body height&lt;/p&gt;</description>
<packageinstances>
<packageinstance name="CAPPRD550W60D1200H2000B"/>
</packageinstances>
</package3d>
<package3d name="CAPMP7443X430N" urn="urn:adsk.eagle:package:16290866/1" type="model">
<description>Molded Body, 7.42 X 4.35 X 4.30 mm body
&lt;p&gt;Molded Body package with body size 7.42 X 4.35 X 4.30 mm&lt;/p&gt;</description>
<packageinstances>
<packageinstance name="CAPMP7443X430N"/>
</packageinstances>
</package3d>
<package3d name="CAPPAD3410W80L3025D1825B" urn="urn:adsk.eagle:package:16290868/1" type="model">
<description>Axial Polarized Capacitor, 34.10 mm pitch, 30.25 mm body length, 18.25 mm body diameter
&lt;p&gt;Axial Polarized Capacitor package with 34.10 mm pitch (lead spacing), 0.80 mm lead diameter, 30.25 mm body length and 18.25 mm body diameter&lt;/p&gt;</description>
<packageinstances>
<packageinstance name="CAPPAD3410W80L3025D1825B"/>
</packageinstances>
</package3d>
</packages3d>
<symbols>
<symbol name="CPOL-US" urn="urn:adsk.eagle:symbol:16290821/1">
<wire x1="-2.54" y1="0" x2="2.54" y2="0" width="0.254" layer="94"/>
<wire x1="0" y1="-1.016" x2="0" y2="-2.54" width="0.1524" layer="94"/>
<wire x1="0" y1="-1" x2="2.4892" y2="-1.8542" width="0.254" layer="94" curve="-37.878202"/>
<wire x1="-2.4669" y1="-1.8504" x2="0" y2="-1.0161" width="0.254" layer="94" curve="-37.376341"/>
<text x="1.016" y="0.635" size="1.778" layer="95">&gt;NAME</text>
<text x="1.016" y="-4.191" size="1.778" layer="96">&gt;VALUE</text>
<rectangle x1="-2.253" y1="0.668" x2="-1.364" y2="0.795" layer="94"/>
<rectangle x1="-1.872" y1="0.287" x2="-1.745" y2="1.176" layer="94"/>
<pin name="+" x="0" y="2.54" visible="off" length="short" direction="pas" swaplevel="1" rot="R270"/>
<pin name="-" x="0" y="-5.08" visible="off" length="short" direction="pas" swaplevel="1" rot="R90"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="C-POL-US" urn="urn:adsk.eagle:component:16290906/6" prefix="C" uservalue="yes">
<description>&lt;B&gt;Capacitor Polarised - ANSI</description>
<gates>
<gate name="G$1" symbol="CPOL-US" x="0" y="0"/>
</gates>
<devices>
<device name="TANTALUM-1206(3216-METRIC)" package="CAPMP3216X180N">
<connects>
<connect gate="G$1" pin="+" pad="1"/>
<connect gate="G$1" pin="-" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16290884/1"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Capacitor" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
<attribute name="VOLTAGE_RATING" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="TANTALUM-1411(3528-METRIC)" package="CAPMP3528X210N">
<connects>
<connect gate="G$1" pin="+" pad="1"/>
<connect gate="G$1" pin="-" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16290901/1"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Capacitor" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
<attribute name="VOLTAGE_RATING" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="TANTALUM-2412(6032-METRIC)" package="CAPMP6032X280N">
<connects>
<connect gate="G$1" pin="+" pad="1"/>
<connect gate="G$1" pin="-" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16290892/1"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Capacitor" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
<attribute name="VOLTAGE_RATING" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="TANTALUM-2917(7343-METRIC)" package="CAPMP7343X310N">
<connects>
<connect gate="G$1" pin="+" pad="1"/>
<connect gate="G$1" pin="-" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16290885/1"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Capacitor" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
<attribute name="VOLTAGE_RATING" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="RADIAL-11MM-DIA" package="CAPPRD508W65D1000H1100B">
<connects>
<connect gate="G$1" pin="+" pad="1"/>
<connect gate="G$1" pin="-" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16290899/1"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Capacitor" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
<attribute name="VOLTAGE_RATING" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="ECAP-10.5MM" package="CAPAE1030X1050N">
<connects>
<connect gate="G$1" pin="+" pad="1"/>
<connect gate="G$1" pin="-" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16290882/1"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Capacitor" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
<attribute name="VOLTAGE_RATING" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="ECAP-8.5MM" package="CAPAE830X1050N">
<connects>
<connect gate="G$1" pin="+" pad="1"/>
<connect gate="G$1" pin="-" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16290889/1"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Capacitor" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
<attribute name="VOLTAGE_RATING" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="RADIAL-32MM-DIA" package="CAPPRD1000W100D2275H3200B">
<connects>
<connect gate="G$1" pin="+" pad="1"/>
<connect gate="G$1" pin="-" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16290888/1"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Capacitor" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
<attribute name="VOLTAGE_RATING" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="ECAP-19.2MM" package="CAPAE1905X1660N">
<connects>
<connect gate="G$1" pin="+" pad="1"/>
<connect gate="G$1" pin="-" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16290872/1"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Capacitor" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
<attribute name="VOLTAGE_RATING" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="RADIAL-25MM-DIA" package="CAPPRD550W110D1250H2500B">
<connects>
<connect gate="G$1" pin="+" pad="1"/>
<connect gate="G$1" pin="-" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16290890/1"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Capacitor" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
<attribute name="VOLTAGE_RATING" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="RADIAL-20MM-DIA" package="CAPPRD550W60D1200H2000B">
<connects>
<connect gate="G$1" pin="+" pad="1"/>
<connect gate="G$1" pin="-" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16290874/1"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Capacitor" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
<attribute name="VOLTAGE_RATING" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="TANTALUM-2920(7443-METRIC)" package="CAPMP7443X430N">
<connects>
<connect gate="G$1" pin="+" pad="1"/>
<connect gate="G$1" pin="-" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16290866/1"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Capacitor" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
<attribute name="VOLTAGE_RATING" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="AXIAL-34.1MM-PITCH" package="CAPPAD3410W80L3025D1825B">
<connects>
<connect gate="G$1" pin="+" pad="1"/>
<connect gate="G$1" pin="-" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16290868/1"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Capacitor" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
<attribute name="VOLTAGE_RATING" value="" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="Connector">
<description>&lt;b&gt;Pin Headers,Terminal blocks, D-Sub, Backplane, FFC/FPC, Socket</description>
<packages>
<package name="B4B-XH-A" urn="urn:adsk.eagle:footprint:24957617/2">
<pad name="1" x="0" y="0" drill="0.84"/>
<pad name="2" x="2.5" y="0" drill="0.84"/>
<pad name="3" x="5" y="0" drill="0.84"/>
<pad name="4" x="7.5" y="0" drill="0.84"/>
<wire x1="-2.45" y1="3.45" x2="9.95" y2="3.45" width="0.1524" layer="21"/>
<wire x1="-2.45" y1="-2.3" x2="9.95" y2="-2.3" width="0.1524" layer="21"/>
<wire x1="-2.45" y1="3.45" x2="-2.45" y2="-2.3" width="0.1524" layer="21"/>
<wire x1="9.95" y1="3.45" x2="9.95" y2="-2.3" width="0.1524" layer="21"/>
<text x="2.54" y="5.08" size="1" layer="25" align="center">&gt;NAME</text>
<text x="2.54" y="-3.81" size="1" layer="27" align="center">&gt;VALUE</text>
</package>
<package name="B2B-XH-A" urn="urn:adsk.eagle:footprint:24957611/2">
<pad name="1" x="0" y="0" drill="0.84"/>
<pad name="2" x="2.5" y="0" drill="0.84"/>
<wire x1="-2.45" y1="2.35" x2="4.95" y2="2.35" width="0.1524" layer="21"/>
<wire x1="-2.45" y1="2.35" x2="-2.45" y2="-3.4" width="0.1524" layer="21"/>
<wire x1="4.95" y1="2.35" x2="4.95" y2="-3.4" width="0.1524" layer="21"/>
<wire x1="-2.45" y1="-3.4" x2="4.95" y2="-3.4" width="0.1524" layer="21"/>
<text x="1.27" y="3.81" size="1" layer="25" align="center">&gt;NAME</text>
<text x="1.27" y="-5.08" size="1" layer="27" align="center">&gt;VALUE</text>
</package>
<package name="1X08" urn="urn:adsk.eagle:footprint:22262/1">
<description>&lt;b&gt;PIN HEADER&lt;/b&gt;</description>
<wire x1="5.715" y1="1.27" x2="6.985" y2="1.27" width="0.1524" layer="21"/>
<wire x1="6.985" y1="1.27" x2="7.62" y2="0.635" width="0.1524" layer="21"/>
<wire x1="7.62" y1="0.635" x2="7.62" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="7.62" y1="-0.635" x2="6.985" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="2.54" y1="0.635" x2="3.175" y2="1.27" width="0.1524" layer="21"/>
<wire x1="3.175" y1="1.27" x2="4.445" y2="1.27" width="0.1524" layer="21"/>
<wire x1="4.445" y1="1.27" x2="5.08" y2="0.635" width="0.1524" layer="21"/>
<wire x1="5.08" y1="0.635" x2="5.08" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="5.08" y1="-0.635" x2="4.445" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="4.445" y1="-1.27" x2="3.175" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="3.175" y1="-1.27" x2="2.54" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="5.715" y1="1.27" x2="5.08" y2="0.635" width="0.1524" layer="21"/>
<wire x1="5.08" y1="-0.635" x2="5.715" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="6.985" y1="-1.27" x2="5.715" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-1.905" y1="1.27" x2="-0.635" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-0.635" y1="1.27" x2="0" y2="0.635" width="0.1524" layer="21"/>
<wire x1="0" y1="0.635" x2="0" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="0" y1="-0.635" x2="-0.635" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="0" y1="0.635" x2="0.635" y2="1.27" width="0.1524" layer="21"/>
<wire x1="0.635" y1="1.27" x2="1.905" y2="1.27" width="0.1524" layer="21"/>
<wire x1="1.905" y1="1.27" x2="2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="2.54" y1="0.635" x2="2.54" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="2.54" y1="-0.635" x2="1.905" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="1.905" y1="-1.27" x2="0.635" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="0.635" y1="-1.27" x2="0" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="0.635" x2="-4.445" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-4.445" y1="1.27" x2="-3.175" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-3.175" y1="1.27" x2="-2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="0.635" x2="-2.54" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="-0.635" x2="-3.175" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-3.175" y1="-1.27" x2="-4.445" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-4.445" y1="-1.27" x2="-5.08" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-1.905" y1="1.27" x2="-2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="-0.635" x2="-1.905" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-0.635" y1="-1.27" x2="-1.905" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-9.525" y1="1.27" x2="-8.255" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-8.255" y1="1.27" x2="-7.62" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-7.62" y1="0.635" x2="-7.62" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-7.62" y1="-0.635" x2="-8.255" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-7.62" y1="0.635" x2="-6.985" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-6.985" y1="1.27" x2="-5.715" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-5.715" y1="1.27" x2="-5.08" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="0.635" x2="-5.08" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="-0.635" x2="-5.715" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-5.715" y1="-1.27" x2="-6.985" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-6.985" y1="-1.27" x2="-7.62" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-10.16" y1="0.635" x2="-10.16" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-9.525" y1="1.27" x2="-10.16" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-10.16" y1="-0.635" x2="-9.525" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-8.255" y1="-1.27" x2="-9.525" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="8.255" y1="1.27" x2="9.525" y2="1.27" width="0.1524" layer="21"/>
<wire x1="9.525" y1="1.27" x2="10.16" y2="0.635" width="0.1524" layer="21"/>
<wire x1="10.16" y1="0.635" x2="10.16" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="10.16" y1="-0.635" x2="9.525" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="8.255" y1="1.27" x2="7.62" y2="0.635" width="0.1524" layer="21"/>
<wire x1="7.62" y1="-0.635" x2="8.255" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="9.525" y1="-1.27" x2="8.255" y2="-1.27" width="0.1524" layer="21"/>
<pad name="1" x="-8.89" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="2" x="-6.35" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="3" x="-3.81" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="4" x="-1.27" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="5" x="1.27" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="6" x="3.81" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="7" x="6.35" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="8" x="8.89" y="0" drill="1.016" shape="long" rot="R90"/>
<text x="-10.2362" y="1.8288" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-10.16" y="-3.175" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="6.096" y1="-0.254" x2="6.604" y2="0.254" layer="51"/>
<rectangle x1="3.556" y1="-0.254" x2="4.064" y2="0.254" layer="51"/>
<rectangle x1="1.016" y1="-0.254" x2="1.524" y2="0.254" layer="51"/>
<rectangle x1="-1.524" y1="-0.254" x2="-1.016" y2="0.254" layer="51"/>
<rectangle x1="-4.064" y1="-0.254" x2="-3.556" y2="0.254" layer="51"/>
<rectangle x1="-6.604" y1="-0.254" x2="-6.096" y2="0.254" layer="51"/>
<rectangle x1="-9.144" y1="-0.254" x2="-8.636" y2="0.254" layer="51"/>
<rectangle x1="8.636" y1="-0.254" x2="9.144" y2="0.254" layer="51"/>
</package>
<package name="1X08/90" urn="urn:adsk.eagle:footprint:22261/1">
<description>&lt;b&gt;PIN HEADER&lt;/b&gt;</description>
<wire x1="-10.16" y1="-1.905" x2="-7.62" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-7.62" y1="-1.905" x2="-7.62" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-7.62" y1="0.635" x2="-10.16" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-10.16" y1="0.635" x2="-10.16" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-8.89" y1="6.985" x2="-8.89" y2="1.27" width="0.762" layer="21"/>
<wire x1="-7.62" y1="-1.905" x2="-5.08" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="-1.905" x2="-5.08" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="0.635" x2="-7.62" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-6.35" y1="6.985" x2="-6.35" y2="1.27" width="0.762" layer="21"/>
<wire x1="-5.08" y1="-1.905" x2="-2.54" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="-1.905" x2="-2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="0.635" x2="-5.08" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-3.81" y1="6.985" x2="-3.81" y2="1.27" width="0.762" layer="21"/>
<wire x1="-2.54" y1="-1.905" x2="0" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="0" y1="-1.905" x2="0" y2="0.635" width="0.1524" layer="21"/>
<wire x1="0" y1="0.635" x2="-2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-1.27" y1="6.985" x2="-1.27" y2="1.27" width="0.762" layer="21"/>
<wire x1="0" y1="-1.905" x2="2.54" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="2.54" y1="-1.905" x2="2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="2.54" y1="0.635" x2="0" y2="0.635" width="0.1524" layer="21"/>
<wire x1="1.27" y1="6.985" x2="1.27" y2="1.27" width="0.762" layer="21"/>
<wire x1="2.54" y1="-1.905" x2="5.08" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="5.08" y1="-1.905" x2="5.08" y2="0.635" width="0.1524" layer="21"/>
<wire x1="5.08" y1="0.635" x2="2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="3.81" y1="6.985" x2="3.81" y2="1.27" width="0.762" layer="21"/>
<wire x1="5.08" y1="-1.905" x2="7.62" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="7.62" y1="-1.905" x2="7.62" y2="0.635" width="0.1524" layer="21"/>
<wire x1="7.62" y1="0.635" x2="5.08" y2="0.635" width="0.1524" layer="21"/>
<wire x1="6.35" y1="6.985" x2="6.35" y2="1.27" width="0.762" layer="21"/>
<wire x1="7.62" y1="-1.905" x2="10.16" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="10.16" y1="-1.905" x2="10.16" y2="0.635" width="0.1524" layer="21"/>
<wire x1="10.16" y1="0.635" x2="7.62" y2="0.635" width="0.1524" layer="21"/>
<wire x1="8.89" y1="6.985" x2="8.89" y2="1.27" width="0.762" layer="21"/>
<pad name="1" x="-8.89" y="-3.81" drill="1.016" shape="long" rot="R90"/>
<pad name="2" x="-6.35" y="-3.81" drill="1.016" shape="long" rot="R90"/>
<pad name="3" x="-3.81" y="-3.81" drill="1.016" shape="long" rot="R90"/>
<pad name="4" x="-1.27" y="-3.81" drill="1.016" shape="long" rot="R90"/>
<pad name="5" x="1.27" y="-3.81" drill="1.016" shape="long" rot="R90"/>
<pad name="6" x="3.81" y="-3.81" drill="1.016" shape="long" rot="R90"/>
<pad name="7" x="6.35" y="-3.81" drill="1.016" shape="long" rot="R90"/>
<pad name="8" x="8.89" y="-3.81" drill="1.016" shape="long" rot="R90"/>
<text x="-10.795" y="-3.81" size="1.27" layer="25" ratio="10" rot="R90">&gt;NAME</text>
<text x="12.065" y="-3.81" size="1.27" layer="27" rot="R90">&gt;VALUE</text>
<rectangle x1="-9.271" y1="0.635" x2="-8.509" y2="1.143" layer="21"/>
<rectangle x1="-6.731" y1="0.635" x2="-5.969" y2="1.143" layer="21"/>
<rectangle x1="-4.191" y1="0.635" x2="-3.429" y2="1.143" layer="21"/>
<rectangle x1="-1.651" y1="0.635" x2="-0.889" y2="1.143" layer="21"/>
<rectangle x1="0.889" y1="0.635" x2="1.651" y2="1.143" layer="21"/>
<rectangle x1="3.429" y1="0.635" x2="4.191" y2="1.143" layer="21"/>
<rectangle x1="5.969" y1="0.635" x2="6.731" y2="1.143" layer="21"/>
<rectangle x1="8.509" y1="0.635" x2="9.271" y2="1.143" layer="21"/>
<rectangle x1="-9.271" y1="-2.921" x2="-8.509" y2="-1.905" layer="21"/>
<rectangle x1="-6.731" y1="-2.921" x2="-5.969" y2="-1.905" layer="21"/>
<rectangle x1="-4.191" y1="-2.921" x2="-3.429" y2="-1.905" layer="21"/>
<rectangle x1="-1.651" y1="-2.921" x2="-0.889" y2="-1.905" layer="21"/>
<rectangle x1="0.889" y1="-2.921" x2="1.651" y2="-1.905" layer="21"/>
<rectangle x1="3.429" y1="-2.921" x2="4.191" y2="-1.905" layer="21"/>
<rectangle x1="5.969" y1="-2.921" x2="6.731" y2="-1.905" layer="21"/>
<rectangle x1="8.509" y1="-2.921" x2="9.271" y2="-1.905" layer="21"/>
</package>
<package name="1X04" urn="urn:adsk.eagle:footprint:22258/1">
<description>&lt;b&gt;PIN HEADER&lt;/b&gt;</description>
<wire x1="0" y1="0.635" x2="0.635" y2="1.27" width="0.1524" layer="21"/>
<wire x1="0.635" y1="1.27" x2="1.905" y2="1.27" width="0.1524" layer="21"/>
<wire x1="1.905" y1="1.27" x2="2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="2.54" y1="0.635" x2="2.54" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="2.54" y1="-0.635" x2="1.905" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="1.905" y1="-1.27" x2="0.635" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="0.635" y1="-1.27" x2="0" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-4.445" y1="1.27" x2="-3.175" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-3.175" y1="1.27" x2="-2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="0.635" x2="-2.54" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="-0.635" x2="-3.175" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="0.635" x2="-1.905" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-1.905" y1="1.27" x2="-0.635" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-0.635" y1="1.27" x2="0" y2="0.635" width="0.1524" layer="21"/>
<wire x1="0" y1="0.635" x2="0" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="0" y1="-0.635" x2="-0.635" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-0.635" y1="-1.27" x2="-1.905" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-1.905" y1="-1.27" x2="-2.54" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="0.635" x2="-5.08" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-4.445" y1="1.27" x2="-5.08" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="-0.635" x2="-4.445" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-3.175" y1="-1.27" x2="-4.445" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="3.175" y1="1.27" x2="4.445" y2="1.27" width="0.1524" layer="21"/>
<wire x1="4.445" y1="1.27" x2="5.08" y2="0.635" width="0.1524" layer="21"/>
<wire x1="5.08" y1="0.635" x2="5.08" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="5.08" y1="-0.635" x2="4.445" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="3.175" y1="1.27" x2="2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="2.54" y1="-0.635" x2="3.175" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="4.445" y1="-1.27" x2="3.175" y2="-1.27" width="0.1524" layer="21"/>
<pad name="1" x="-3.81" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="2" x="-1.27" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="3" x="1.27" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="4" x="3.81" y="0" drill="1.016" shape="long" rot="R90"/>
<text x="-5.1562" y="1.8288" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-5.08" y="-3.175" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="1.016" y1="-0.254" x2="1.524" y2="0.254" layer="51"/>
<rectangle x1="-1.524" y1="-0.254" x2="-1.016" y2="0.254" layer="51"/>
<rectangle x1="-4.064" y1="-0.254" x2="-3.556" y2="0.254" layer="51"/>
<rectangle x1="3.556" y1="-0.254" x2="4.064" y2="0.254" layer="51"/>
</package>
<package name="1X04/90" urn="urn:adsk.eagle:footprint:22259/1">
<description>&lt;b&gt;PIN HEADER&lt;/b&gt;</description>
<wire x1="-5.08" y1="-1.905" x2="-2.54" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="-1.905" x2="-2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="0.635" x2="-5.08" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="0.635" x2="-5.08" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-3.81" y1="6.985" x2="-3.81" y2="1.27" width="0.762" layer="21"/>
<wire x1="-2.54" y1="-1.905" x2="0" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="0" y1="-1.905" x2="0" y2="0.635" width="0.1524" layer="21"/>
<wire x1="0" y1="0.635" x2="-2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-1.27" y1="6.985" x2="-1.27" y2="1.27" width="0.762" layer="21"/>
<wire x1="0" y1="-1.905" x2="2.54" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="2.54" y1="-1.905" x2="2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="2.54" y1="0.635" x2="0" y2="0.635" width="0.1524" layer="21"/>
<wire x1="1.27" y1="6.985" x2="1.27" y2="1.27" width="0.762" layer="21"/>
<wire x1="2.54" y1="-1.905" x2="5.08" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="5.08" y1="-1.905" x2="5.08" y2="0.635" width="0.1524" layer="21"/>
<wire x1="5.08" y1="0.635" x2="2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="3.81" y1="6.985" x2="3.81" y2="1.27" width="0.762" layer="21"/>
<pad name="1" x="-3.81" y="-3.81" drill="1.016" shape="long" rot="R90"/>
<pad name="2" x="-1.27" y="-3.81" drill="1.016" shape="long" rot="R90"/>
<pad name="3" x="1.27" y="-3.81" drill="1.016" shape="long" rot="R90"/>
<pad name="4" x="3.81" y="-3.81" drill="1.016" shape="long" rot="R90"/>
<text x="-5.715" y="-3.81" size="1.27" layer="25" ratio="10" rot="R90">&gt;NAME</text>
<text x="6.985" y="-4.445" size="1.27" layer="27" rot="R90">&gt;VALUE</text>
<rectangle x1="-4.191" y1="0.635" x2="-3.429" y2="1.143" layer="21"/>
<rectangle x1="-1.651" y1="0.635" x2="-0.889" y2="1.143" layer="21"/>
<rectangle x1="0.889" y1="0.635" x2="1.651" y2="1.143" layer="21"/>
<rectangle x1="3.429" y1="0.635" x2="4.191" y2="1.143" layer="21"/>
<rectangle x1="-4.191" y1="-2.921" x2="-3.429" y2="-1.905" layer="21"/>
<rectangle x1="-1.651" y1="-2.921" x2="-0.889" y2="-1.905" layer="21"/>
<rectangle x1="0.889" y1="-2.921" x2="1.651" y2="-1.905" layer="21"/>
<rectangle x1="3.429" y1="-2.921" x2="4.191" y2="-1.905" layer="21"/>
</package>
</packages>
<packages3d>
<package3d name="B4B-XH-A" urn="urn:adsk.eagle:package:24957647/3" type="model">
<packageinstances>
<packageinstance name="B4B-XH-A"/>
</packageinstances>
</package3d>
<package3d name="B2B-XH-A" urn="urn:adsk.eagle:package:24957641/6" type="model">
<packageinstances>
<packageinstance name="B2B-XH-A"/>
</packageinstances>
</package3d>
<package3d name="1X08" urn="urn:adsk.eagle:package:22409/2" type="model">
<description>PIN HEADER</description>
<packageinstances>
<packageinstance name="1X08"/>
</packageinstances>
</package3d>
<package3d name="1X08/90" urn="urn:adsk.eagle:package:22413/2" type="model">
<description>PIN HEADER</description>
<packageinstances>
<packageinstance name="1X08/90"/>
</packageinstances>
</package3d>
<package3d name="1X04" urn="urn:adsk.eagle:package:22407/2" type="model">
<description>PIN HEADER</description>
<packageinstances>
<packageinstance name="1X04"/>
</packageinstances>
</package3d>
<package3d name="1X04/90" urn="urn:adsk.eagle:package:22404/2" type="model">
<description>PIN HEADER</description>
<packageinstances>
<packageinstance name="1X04/90"/>
</packageinstances>
</package3d>
</packages3d>
<symbols>
<symbol name="TERMBLK_4-1" urn="urn:adsk.eagle:symbol:24957596/4">
<wire x1="-2.54" y1="3.81" x2="2.54" y2="3.81" width="0.1524" layer="94"/>
<wire x1="2.54" y1="3.81" x2="2.54" y2="-6.35" width="0.1524" layer="94"/>
<wire x1="2.54" y1="-6.35" x2="-2.54" y2="-6.35" width="0.1524" layer="94"/>
<wire x1="-2.54" y1="-6.35" x2="-2.54" y2="3.81" width="0.1524" layer="94"/>
<pin name="1" x="-5.08" y="2.54" length="short"/>
<pin name="2" x="-5.08" y="0" length="short"/>
<pin name="3" x="-5.08" y="-2.54" length="short"/>
<pin name="4" x="-5.08" y="-5.08" length="short"/>
<text x="0" y="-6.604" size="1.778" layer="96" align="top-center">&gt;VALUE</text>
<text x="0" y="4.064" size="1.778" layer="95" align="bottom-center">&gt;NAME</text>
</symbol>
<symbol name="TERMBLK_2" urn="urn:adsk.eagle:symbol:24957587/3">
<pin name="1" x="-5.08" y="2.54" length="short"/>
<pin name="2" x="-5.08" y="0" length="short"/>
<text x="0" y="-2.794" size="1.778" layer="96" align="top-center">&gt;VALUE</text>
<text x="0" y="5.334" size="1.778" layer="95" align="bottom-center">&gt;NAME</text>
<wire x1="-2.54" y1="-2.54" x2="-2.54" y2="5.08" width="0.1524" layer="94"/>
<wire x1="-2.54" y1="5.08" x2="2.54" y2="5.08" width="0.1524" layer="94"/>
<wire x1="2.54" y1="5.08" x2="2.54" y2="-2.54" width="0.1524" layer="94"/>
<wire x1="2.54" y1="-2.54" x2="-2.54" y2="-2.54" width="0.1524" layer="94"/>
</symbol>
<symbol name="PINHD8" urn="urn:adsk.eagle:symbol:22260/1">
<wire x1="-6.35" y1="-10.16" x2="1.27" y2="-10.16" width="0.4064" layer="94"/>
<wire x1="1.27" y1="-10.16" x2="1.27" y2="12.7" width="0.4064" layer="94"/>
<wire x1="1.27" y1="12.7" x2="-6.35" y2="12.7" width="0.4064" layer="94"/>
<wire x1="-6.35" y1="12.7" x2="-6.35" y2="-10.16" width="0.4064" layer="94"/>
<text x="-6.35" y="13.335" size="1.778" layer="95">&gt;NAME</text>
<text x="-6.35" y="-12.7" size="1.778" layer="96">&gt;VALUE</text>
<pin name="1" x="-2.54" y="10.16" visible="pad" length="short" direction="pas" function="dot"/>
<pin name="2" x="-2.54" y="7.62" visible="pad" length="short" direction="pas" function="dot"/>
<pin name="3" x="-2.54" y="5.08" visible="pad" length="short" direction="pas" function="dot"/>
<pin name="4" x="-2.54" y="2.54" visible="pad" length="short" direction="pas" function="dot"/>
<pin name="5" x="-2.54" y="0" visible="pad" length="short" direction="pas" function="dot"/>
<pin name="6" x="-2.54" y="-2.54" visible="pad" length="short" direction="pas" function="dot"/>
<pin name="7" x="-2.54" y="-5.08" visible="pad" length="short" direction="pas" function="dot"/>
<pin name="8" x="-2.54" y="-7.62" visible="pad" length="short" direction="pas" function="dot"/>
</symbol>
<symbol name="PINHD4" urn="urn:adsk.eagle:symbol:22257/1">
<wire x1="-6.35" y1="-5.08" x2="1.27" y2="-5.08" width="0.4064" layer="94"/>
<wire x1="1.27" y1="-5.08" x2="1.27" y2="7.62" width="0.4064" layer="94"/>
<wire x1="1.27" y1="7.62" x2="-6.35" y2="7.62" width="0.4064" layer="94"/>
<wire x1="-6.35" y1="7.62" x2="-6.35" y2="-5.08" width="0.4064" layer="94"/>
<text x="-6.35" y="8.255" size="1.778" layer="95">&gt;NAME</text>
<text x="-6.35" y="-7.62" size="1.778" layer="96">&gt;VALUE</text>
<pin name="1" x="-2.54" y="5.08" visible="pad" length="short" direction="pas" function="dot"/>
<pin name="2" x="-2.54" y="2.54" visible="pad" length="short" direction="pas" function="dot"/>
<pin name="3" x="-2.54" y="0" visible="pad" length="short" direction="pas" function="dot"/>
<pin name="4" x="-2.54" y="-2.54" visible="pad" length="short" direction="pas" function="dot"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="B4B-XH-A" urn="urn:adsk.eagle:component:24957705/6" prefix="J">
<description>XH Connector Top Entry - 4POS
&lt;br&gt;Details see: &lt;a href="http://www.jst-mfg.com/product/pdf/eng/eXH.pdf"&gt;Datasheet&lt;/a&gt;&lt;p&gt;</description>
<gates>
<gate name="G$1" symbol="TERMBLK_4-1" x="0" y="0"/>
</gates>
<devices>
<device name="" package="B4B-XH-A">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
<connect gate="G$1" pin="4" pad="4"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:24957647/3"/>
</package3dinstances>
<technologies>
<technology name="">
<attribute name="CATEGORY" value="CONNECTOR" constant="no"/>
<attribute name="DSECRIPTION" value="2.5mm pitch/disconnctable crimp style connector" constant="no"/>
<attribute name="MANUFACTURER" value="JST (XH connector)" constant="no"/>
<attribute name="MPN" value="B4B-XH-A" constant="no"/>
<attribute name="OPERATING_TEMPERATURE" value="-25 C to 85 C" constant="no"/>
<attribute name="PART_STATUS" value="ACTIVE" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="COMPLAINT" constant="no"/>
<attribute name="SERIES" value="B4B-XH-A" constant="no"/>
<attribute name="SUB_CATEGORY" value="Through hole" constant="no"/>
<attribute name="TYPE" value="TOP ENTRY" constant="no"/>
<attribute name="VALUE" value="3A/250V" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="B2B-XH-A" urn="urn:adsk.eagle:component:24957700/6" prefix="J">
<description>XH Connector Top Entry - 2POS
&lt;br&gt;Details see: &lt;a href="http://www.jst-mfg.com/product/pdf/eng/eXH.pdf"&gt;Datasheet&lt;/a&gt;&lt;p&gt;</description>
<gates>
<gate name="G$1" symbol="TERMBLK_2" x="0" y="0"/>
</gates>
<devices>
<device name="" package="B2B-XH-A">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:24957641/6"/>
</package3dinstances>
<technologies>
<technology name="">
<attribute name="CATEGORY" value="CONNECTOR" constant="no"/>
<attribute name="DESCRIPTION" value="2.5mm pitch/disconnectable crimp style connector" constant="no"/>
<attribute name="MANUFACTURER" value="JST (XH CONNECTOR)" constant="no"/>
<attribute name="MPN" value="B2B-XH-A" constant="no"/>
<attribute name="OPERATING_TEMPERATURE" value="-25°C ~ 85°C" constant="no"/>
<attribute name="PART_STATUS" value="ACTIVE" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="COMPLIANT" constant="no"/>
<attribute name="SERIES" value="B_B-XH-A" constant="no"/>
<attribute name="SUB_CATEGORY" value="Through hole connector" constant="no"/>
<attribute name="TYPE" value="top entry" constant="no"/>
<attribute name="VALUE" value="3A/250V" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="PINHD-1X8" urn="urn:adsk.eagle:component:16494884/2" prefix="JP">
<description>&lt;b&gt;PIN HEADER&lt;/b&gt;</description>
<gates>
<gate name="A" symbol="PINHD8" x="0" y="0"/>
</gates>
<devices>
<device name="" package="1X08">
<connects>
<connect gate="A" pin="1" pad="1"/>
<connect gate="A" pin="2" pad="2"/>
<connect gate="A" pin="3" pad="3"/>
<connect gate="A" pin="4" pad="4"/>
<connect gate="A" pin="5" pad="5"/>
<connect gate="A" pin="6" pad="6"/>
<connect gate="A" pin="7" pad="7"/>
<connect gate="A" pin="8" pad="8"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:22409/2"/>
</package3dinstances>
<technologies>
<technology name="">
<attribute name="CATEGORY" value="CONNECTOR" constant="no"/>
<attribute name="DESCRIPTION" value="" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="PIN-HEADER" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="/90" package="1X08/90">
<connects>
<connect gate="A" pin="1" pad="1"/>
<connect gate="A" pin="2" pad="2"/>
<connect gate="A" pin="3" pad="3"/>
<connect gate="A" pin="4" pad="4"/>
<connect gate="A" pin="5" pad="5"/>
<connect gate="A" pin="6" pad="6"/>
<connect gate="A" pin="7" pad="7"/>
<connect gate="A" pin="8" pad="8"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:22413/2"/>
</package3dinstances>
<technologies>
<technology name="">
<attribute name="CATEGORY" value="CONNECTOR" constant="no"/>
<attribute name="DESCRIPTION" value="" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="PIN-HEADER" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="PINHD-1X4" urn="urn:adsk.eagle:component:16494870/2" prefix="JP">
<description>&lt;b&gt;PIN HEADER&lt;/b&gt;</description>
<gates>
<gate name="A" symbol="PINHD4" x="0" y="0"/>
</gates>
<devices>
<device name="" package="1X04">
<connects>
<connect gate="A" pin="1" pad="1"/>
<connect gate="A" pin="2" pad="2"/>
<connect gate="A" pin="3" pad="3"/>
<connect gate="A" pin="4" pad="4"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:22407/2"/>
</package3dinstances>
<technologies>
<technology name="">
<attribute name="CATEGORY" value="CONNECTOR" constant="no"/>
<attribute name="DESCRIPTION" value="" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="PIN-HEADER" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="/90" package="1X04/90">
<connects>
<connect gate="A" pin="1" pad="1"/>
<connect gate="A" pin="2" pad="2"/>
<connect gate="A" pin="3" pad="3"/>
<connect gate="A" pin="4" pad="4"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:22404/2"/>
</package3dinstances>
<technologies>
<technology name="">
<attribute name="CATEGORY" value="CONNECTOR" constant="no"/>
<attribute name="DESCRIPTION" value="" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="PIN-HEADER" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="Resistor">
<description>&lt;B&gt;Resistors, Potentiometers, TrimPot</description>
<packages>
<package name="RESC1005X40" urn="urn:adsk.eagle:footprint:16378540/2">
<description>Chip, 1.05 X 0.54 X 0.40 mm body
&lt;p&gt;Chip package with body size 1.05 X 0.54 X 0.40 mm&lt;/p&gt;</description>
<wire x1="0.55" y1="0.636" x2="-0.55" y2="0.636" width="0.127" layer="21"/>
<wire x1="0.55" y1="-0.636" x2="-0.55" y2="-0.636" width="0.127" layer="21"/>
<wire x1="0.55" y1="-0.3" x2="-0.55" y2="-0.3" width="0.12" layer="51"/>
<wire x1="-0.55" y1="-0.3" x2="-0.55" y2="0.3" width="0.12" layer="51"/>
<wire x1="-0.55" y1="0.3" x2="0.55" y2="0.3" width="0.12" layer="51"/>
<wire x1="0.55" y1="0.3" x2="0.55" y2="-0.3" width="0.12" layer="51"/>
<smd name="1" x="-0.5075" y="0" dx="0.5351" dy="0.644" layer="1"/>
<smd name="2" x="0.5075" y="0" dx="0.5351" dy="0.644" layer="1"/>
<text x="0" y="1.271" size="1.27" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-1.271" size="1.27" layer="27" align="top-center">&gt;VALUE</text>
</package>
<package name="RESC1608X60" urn="urn:adsk.eagle:footprint:16378537/2">
<description>Chip, 1.60 X 0.82 X 0.60 mm body
&lt;p&gt;Chip package with body size 1.60 X 0.82 X 0.60 mm&lt;/p&gt;</description>
<wire x1="0.85" y1="0.8009" x2="-0.85" y2="0.8009" width="0.127" layer="21"/>
<wire x1="0.85" y1="-0.8009" x2="-0.85" y2="-0.8009" width="0.127" layer="21"/>
<wire x1="0.85" y1="-0.475" x2="-0.85" y2="-0.475" width="0.12" layer="51"/>
<wire x1="-0.85" y1="-0.475" x2="-0.85" y2="0.475" width="0.12" layer="51"/>
<wire x1="-0.85" y1="0.475" x2="0.85" y2="0.475" width="0.12" layer="51"/>
<wire x1="0.85" y1="0.475" x2="0.85" y2="-0.475" width="0.12" layer="51"/>
<smd name="1" x="-0.8152" y="0" dx="0.7987" dy="0.9739" layer="1"/>
<smd name="2" x="0.8152" y="0" dx="0.7987" dy="0.9739" layer="1"/>
<text x="0" y="1.4359" size="1.27" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-1.4359" size="1.27" layer="27" align="top-center">&gt;VALUE</text>
</package>
<package name="RESC2012X65" urn="urn:adsk.eagle:footprint:16378532/2">
<description>Chip, 2.00 X 1.25 X 0.65 mm body
&lt;p&gt;Chip package with body size 2.00 X 1.25 X 0.65 mm&lt;/p&gt;</description>
<wire x1="1.075" y1="1.0241" x2="-1.075" y2="1.0241" width="0.127" layer="21"/>
<wire x1="1.075" y1="-1.0241" x2="-1.075" y2="-1.0241" width="0.127" layer="21"/>
<wire x1="1.075" y1="-0.7" x2="-1.075" y2="-0.7" width="0.12" layer="51"/>
<wire x1="-1.075" y1="-0.7" x2="-1.075" y2="0.7" width="0.12" layer="51"/>
<wire x1="-1.075" y1="0.7" x2="1.075" y2="0.7" width="0.12" layer="51"/>
<wire x1="1.075" y1="0.7" x2="1.075" y2="-0.7" width="0.12" layer="51"/>
<smd name="1" x="-0.9195" y="0" dx="1.0312" dy="1.4202" layer="1"/>
<smd name="2" x="0.9195" y="0" dx="1.0312" dy="1.4202" layer="1"/>
<text x="0" y="1.6591" size="1.27" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-1.6591" size="1.27" layer="27" align="top-center">&gt;VALUE</text>
</package>
<package name="RESC3216X70" urn="urn:adsk.eagle:footprint:16378539/2">
<description>Chip, 3.20 X 1.60 X 0.70 mm body
&lt;p&gt;Chip package with body size 3.20 X 1.60 X 0.70 mm&lt;/p&gt;</description>
<wire x1="1.7" y1="1.2217" x2="-1.7" y2="1.2217" width="0.127" layer="21"/>
<wire x1="1.7" y1="-1.2217" x2="-1.7" y2="-1.2217" width="0.127" layer="21"/>
<wire x1="1.7" y1="-0.9" x2="-1.7" y2="-0.9" width="0.12" layer="51"/>
<wire x1="-1.7" y1="-0.9" x2="-1.7" y2="0.9" width="0.12" layer="51"/>
<wire x1="-1.7" y1="0.9" x2="1.7" y2="0.9" width="0.12" layer="51"/>
<wire x1="1.7" y1="0.9" x2="1.7" y2="-0.9" width="0.12" layer="51"/>
<smd name="1" x="-1.4754" y="0" dx="1.1646" dy="1.8153" layer="1"/>
<smd name="2" x="1.4754" y="0" dx="1.1646" dy="1.8153" layer="1"/>
<text x="0" y="1.8567" size="1.27" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-1.8567" size="1.27" layer="27" align="top-center">&gt;VALUE</text>
</package>
<package name="RESC3224X71" urn="urn:adsk.eagle:footprint:16378536/2">
<description>Chip, 3.20 X 2.49 X 0.71 mm body
&lt;p&gt;Chip package with body size 3.20 X 2.49 X 0.71 mm&lt;/p&gt;</description>
<wire x1="1.675" y1="1.6441" x2="-1.675" y2="1.6441" width="0.127" layer="21"/>
<wire x1="1.675" y1="-1.6441" x2="-1.675" y2="-1.6441" width="0.127" layer="21"/>
<wire x1="1.675" y1="-1.32" x2="-1.675" y2="-1.32" width="0.12" layer="51"/>
<wire x1="-1.675" y1="-1.32" x2="-1.675" y2="1.32" width="0.12" layer="51"/>
<wire x1="-1.675" y1="1.32" x2="1.675" y2="1.32" width="0.12" layer="51"/>
<wire x1="1.675" y1="1.32" x2="1.675" y2="-1.32" width="0.12" layer="51"/>
<smd name="1" x="-1.4695" y="0" dx="1.1312" dy="2.6602" layer="1"/>
<smd name="2" x="1.4695" y="0" dx="1.1312" dy="2.6602" layer="1"/>
<text x="0" y="2.2791" size="1.27" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-2.2791" size="1.27" layer="27" align="top-center">&gt;VALUE</text>
</package>
<package name="RESC5025X71" urn="urn:adsk.eagle:footprint:16378538/2">
<description>Chip, 5.00 X 2.50 X 0.71 mm body
&lt;p&gt;Chip package with body size 5.00 X 2.50 X 0.71 mm&lt;/p&gt;</description>
<wire x1="2.575" y1="1.6491" x2="-2.575" y2="1.6491" width="0.127" layer="21"/>
<wire x1="2.575" y1="-1.6491" x2="-2.575" y2="-1.6491" width="0.127" layer="21"/>
<wire x1="2.575" y1="-1.325" x2="-2.575" y2="-1.325" width="0.12" layer="51"/>
<wire x1="-2.575" y1="-1.325" x2="-2.575" y2="1.325" width="0.12" layer="51"/>
<wire x1="-2.575" y1="1.325" x2="2.575" y2="1.325" width="0.12" layer="51"/>
<wire x1="2.575" y1="1.325" x2="2.575" y2="-1.325" width="0.12" layer="51"/>
<smd name="1" x="-2.3195" y="0" dx="1.2312" dy="2.6702" layer="1"/>
<smd name="2" x="2.3195" y="0" dx="1.2312" dy="2.6702" layer="1"/>
<text x="0" y="2.2841" size="1.27" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-2.2841" size="1.27" layer="27" align="top-center">&gt;VALUE</text>
</package>
<package name="RESC6332X71" urn="urn:adsk.eagle:footprint:16378533/2">
<description>Chip, 6.30 X 3.20 X 0.71 mm body
&lt;p&gt;Chip package with body size 6.30 X 3.20 X 0.71 mm&lt;/p&gt;</description>
<wire x1="3.225" y1="1.9991" x2="-3.225" y2="1.9991" width="0.127" layer="21"/>
<wire x1="3.225" y1="-1.9991" x2="-3.225" y2="-1.9991" width="0.127" layer="21"/>
<wire x1="3.225" y1="-1.675" x2="-3.225" y2="-1.675" width="0.12" layer="51"/>
<wire x1="-3.225" y1="-1.675" x2="-3.225" y2="1.675" width="0.12" layer="51"/>
<wire x1="-3.225" y1="1.675" x2="3.225" y2="1.675" width="0.12" layer="51"/>
<wire x1="3.225" y1="1.675" x2="3.225" y2="-1.675" width="0.12" layer="51"/>
<smd name="1" x="-2.9695" y="0" dx="1.2312" dy="3.3702" layer="1"/>
<smd name="2" x="2.9695" y="0" dx="1.2312" dy="3.3702" layer="1"/>
<text x="0" y="2.6341" size="1.27" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-2.6341" size="1.27" layer="27" align="top-center">&gt;VALUE</text>
</package>
<package name="RESAD1176W63L850D250B" urn="urn:adsk.eagle:footprint:16378542/2">
<description>AXIAL Resistor, 11.76 mm pitch, 8.5 mm body length, 2.5 mm body diameter
&lt;p&gt;AXIAL Resistor package with 11.76 mm pitch, 0.63 mm lead diameter, 8.5 mm body length and 2.5 mm body diameter&lt;/p&gt;</description>
<wire x1="-4.25" y1="1.25" x2="-4.25" y2="-1.25" width="0.127" layer="21"/>
<wire x1="-4.25" y1="-1.25" x2="4.25" y2="-1.25" width="0.127" layer="21"/>
<wire x1="4.25" y1="-1.25" x2="4.25" y2="1.25" width="0.127" layer="21"/>
<wire x1="4.25" y1="1.25" x2="-4.25" y2="1.25" width="0.127" layer="21"/>
<wire x1="-4.25" y1="0" x2="-4.911" y2="0" width="0.127" layer="21"/>
<wire x1="4.25" y1="0" x2="4.911" y2="0" width="0.127" layer="21"/>
<wire x1="4.25" y1="-1.25" x2="-4.25" y2="-1.25" width="0.12" layer="51"/>
<wire x1="-4.25" y1="-1.25" x2="-4.25" y2="1.25" width="0.12" layer="51"/>
<wire x1="-4.25" y1="1.25" x2="4.25" y2="1.25" width="0.12" layer="51"/>
<wire x1="4.25" y1="1.25" x2="4.25" y2="-1.25" width="0.12" layer="51"/>
<pad name="1" x="-5.88" y="0" drill="0.83" diameter="1.43"/>
<pad name="2" x="5.88" y="0" drill="0.83" diameter="1.43"/>
<text x="0" y="1.885" size="1.27" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-1.885" size="1.27" layer="27" align="top-center">&gt;VALUE</text>
</package>
<package name="RESMELF3515" urn="urn:adsk.eagle:footprint:16378534/2">
<description>MELF, 3.50 mm length, 1.52 mm diameter
&lt;p&gt;MELF Resistor package with 3.50 mm length and 1.52 mm diameter&lt;/p&gt;</description>
<wire x1="1.105" y1="1.1825" x2="-1.105" y2="1.1825" width="0.127" layer="21"/>
<wire x1="-1.105" y1="-1.1825" x2="1.105" y2="-1.1825" width="0.127" layer="21"/>
<wire x1="1.85" y1="-0.8" x2="-1.85" y2="-0.8" width="0.12" layer="51"/>
<wire x1="-1.85" y1="-0.8" x2="-1.85" y2="0.8" width="0.12" layer="51"/>
<wire x1="-1.85" y1="0.8" x2="1.85" y2="0.8" width="0.12" layer="51"/>
<wire x1="1.85" y1="0.8" x2="1.85" y2="-0.8" width="0.12" layer="51"/>
<smd name="1" x="-1.6813" y="0" dx="1.1527" dy="1.7371" layer="1"/>
<smd name="2" x="1.6813" y="0" dx="1.1527" dy="1.7371" layer="1"/>
<text x="0" y="1.8175" size="1.27" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-1.8175" size="1.27" layer="27" align="top-center">&gt;VALUE</text>
</package>
<package name="RESMELF2014" urn="urn:adsk.eagle:footprint:16378535/2">
<description>MELF, 2.00 mm length, 1.40 mm diameter
&lt;p&gt;MELF Resistor package with 2.00 mm length and 1.40 mm diameter&lt;/p&gt;</description>
<wire x1="0.5189" y1="1.114" x2="-0.5189" y2="1.114" width="0.127" layer="21"/>
<wire x1="-0.5189" y1="-1.114" x2="0.5189" y2="-1.114" width="0.127" layer="21"/>
<wire x1="1.05" y1="-0.725" x2="-1.05" y2="-0.725" width="0.12" layer="51"/>
<wire x1="-1.05" y1="-0.725" x2="-1.05" y2="0.725" width="0.12" layer="51"/>
<wire x1="-1.05" y1="0.725" x2="1.05" y2="0.725" width="0.12" layer="51"/>
<wire x1="1.05" y1="0.725" x2="1.05" y2="-0.725" width="0.12" layer="51"/>
<smd name="1" x="-0.9918" y="0" dx="0.9456" dy="1.6" layer="1"/>
<smd name="2" x="0.9918" y="0" dx="0.9456" dy="1.6" layer="1"/>
<text x="0" y="1.749" size="1.27" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-1.749" size="1.27" layer="27" align="top-center">&gt;VALUE</text>
</package>
<package name="RESMELF5924" urn="urn:adsk.eagle:footprint:16378541/2">
<description>MELF, 5.90 mm length, 2.45 mm diameter
&lt;p&gt;MELF Resistor package with 5.90 mm length and 2.45 mm diameter&lt;/p&gt;</description>
<wire x1="2.1315" y1="1.639" x2="-2.1315" y2="1.639" width="0.127" layer="21"/>
<wire x1="-2.1315" y1="-1.639" x2="2.1315" y2="-1.639" width="0.127" layer="21"/>
<wire x1="3.05" y1="-1.25" x2="-3.05" y2="-1.25" width="0.12" layer="51"/>
<wire x1="-3.05" y1="-1.25" x2="-3.05" y2="1.25" width="0.12" layer="51"/>
<wire x1="-3.05" y1="1.25" x2="3.05" y2="1.25" width="0.12" layer="51"/>
<wire x1="3.05" y1="1.25" x2="3.05" y2="-1.25" width="0.12" layer="51"/>
<smd name="1" x="-2.7946" y="0" dx="1.3261" dy="2.65" layer="1"/>
<smd name="2" x="2.7946" y="0" dx="1.3261" dy="2.65" layer="1"/>
<text x="0" y="2.274" size="1.27" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-2.274" size="1.27" layer="27" align="top-center">&gt;VALUE</text>
</package>
<package name="RESMELF3218" urn="urn:adsk.eagle:footprint:16378531/2">
<description>MELF, 3.20 mm length, 1.80 mm diameter
&lt;p&gt;MELF Resistor package with 3.20 mm length and 1.80 mm diameter&lt;/p&gt;</description>
<wire x1="0.8815" y1="1.314" x2="-0.8815" y2="1.314" width="0.127" layer="21"/>
<wire x1="-0.8815" y1="-1.314" x2="0.8815" y2="-1.314" width="0.127" layer="21"/>
<wire x1="1.7" y1="-0.925" x2="-1.7" y2="-0.925" width="0.12" layer="51"/>
<wire x1="-1.7" y1="-0.925" x2="-1.7" y2="0.925" width="0.12" layer="51"/>
<wire x1="-1.7" y1="0.925" x2="1.7" y2="0.925" width="0.12" layer="51"/>
<wire x1="1.7" y1="0.925" x2="1.7" y2="-0.925" width="0.12" layer="51"/>
<smd name="1" x="-1.4946" y="0" dx="1.2261" dy="2" layer="1"/>
<smd name="2" x="1.4946" y="0" dx="1.2261" dy="2" layer="1"/>
<text x="0" y="1.949" size="1.27" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-1.949" size="1.27" layer="27" align="top-center">&gt;VALUE</text>
</package>
<package name="RESAD724W46L381D178B" urn="urn:adsk.eagle:footprint:16378530/2">
<description>Axial Resistor, 7.24 mm pitch, 3.81 mm body length, 1.78 mm body diameter
&lt;p&gt;Axial Resistor package with 7.24 mm pitch (lead spacing), 0.46 mm lead diameter, 3.81 mm body length and 1.78 mm body diameter&lt;/p&gt;</description>
<wire x1="-2.16" y1="1.015" x2="-2.16" y2="-1.015" width="0.127" layer="21"/>
<wire x1="-2.16" y1="-1.015" x2="2.16" y2="-1.015" width="0.127" layer="21"/>
<wire x1="2.16" y1="-1.015" x2="2.16" y2="1.015" width="0.127" layer="21"/>
<wire x1="2.16" y1="1.015" x2="-2.16" y2="1.015" width="0.127" layer="21"/>
<wire x1="-2.16" y1="0" x2="-2.736" y2="0" width="0.127" layer="21"/>
<wire x1="2.16" y1="0" x2="2.736" y2="0" width="0.127" layer="21"/>
<wire x1="2.16" y1="-1.015" x2="-2.16" y2="-1.015" width="0.12" layer="51"/>
<wire x1="-2.16" y1="-1.015" x2="-2.16" y2="1.015" width="0.12" layer="51"/>
<wire x1="-2.16" y1="1.015" x2="2.16" y2="1.015" width="0.12" layer="51"/>
<wire x1="2.16" y1="1.015" x2="2.16" y2="-1.015" width="0.12" layer="51"/>
<pad name="1" x="-3.62" y="0" drill="0.66" diameter="1.26"/>
<pad name="2" x="3.62" y="0" drill="0.66" diameter="1.26"/>
<text x="0" y="1.65" size="1.27" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-1.65" size="1.27" layer="27" align="top-center">&gt;VALUE</text>
</package>
</packages>
<packages3d>
<package3d name="RESC1005X40" urn="urn:adsk.eagle:package:16378568/2" type="model">
<description>Chip, 1.05 X 0.54 X 0.40 mm body
&lt;p&gt;Chip package with body size 1.05 X 0.54 X 0.40 mm&lt;/p&gt;</description>
<packageinstances>
<packageinstance name="RESC1005X40"/>
</packageinstances>
</package3d>
<package3d name="RESC1608X60" urn="urn:adsk.eagle:package:16378565/2" type="model">
<description>Chip, 1.60 X 0.82 X 0.60 mm body
&lt;p&gt;Chip package with body size 1.60 X 0.82 X 0.60 mm&lt;/p&gt;</description>
<packageinstances>
<packageinstance name="RESC1608X60"/>
</packageinstances>
</package3d>
<package3d name="RESC2012X65" urn="urn:adsk.eagle:package:16378559/2" type="model">
<description>Chip, 2.00 X 1.25 X 0.65 mm body
&lt;p&gt;Chip package with body size 2.00 X 1.25 X 0.65 mm&lt;/p&gt;</description>
<packageinstances>
<packageinstance name="RESC2012X65"/>
</packageinstances>
</package3d>
<package3d name="RESC3216X70" urn="urn:adsk.eagle:package:16378566/2" type="model">
<description>Chip, 3.20 X 1.60 X 0.70 mm body
&lt;p&gt;Chip package with body size 3.20 X 1.60 X 0.70 mm&lt;/p&gt;</description>
<packageinstances>
<packageinstance name="RESC3216X70"/>
</packageinstances>
</package3d>
<package3d name="RESC3224X71" urn="urn:adsk.eagle:package:16378563/3" type="model">
<description>Chip, 3.20 X 2.49 X 0.71 mm body
&lt;p&gt;Chip package with body size 3.20 X 2.49 X 0.71 mm&lt;/p&gt;</description>
<packageinstances>
<packageinstance name="RESC3224X71"/>
</packageinstances>
</package3d>
<package3d name="RESC5025X71" urn="urn:adsk.eagle:package:16378564/2" type="model">
<description>Chip, 5.00 X 2.50 X 0.71 mm body
&lt;p&gt;Chip package with body size 5.00 X 2.50 X 0.71 mm&lt;/p&gt;</description>
<packageinstances>
<packageinstance name="RESC5025X71"/>
</packageinstances>
</package3d>
<package3d name="RESC6332X71L" urn="urn:adsk.eagle:package:16378557/3" type="model">
<description>Chip, 6.30 X 3.20 X 0.71 mm body
&lt;p&gt;Chip package with body size 6.30 X 3.20 X 0.71 mm&lt;/p&gt;</description>
<packageinstances>
<packageinstance name="RESC6332X71"/>
</packageinstances>
</package3d>
<package3d name="RESAD1176W63L850D250B" urn="urn:adsk.eagle:package:16378560/2" type="model">
<description>AXIAL Resistor, 11.76 mm pitch, 8.5 mm body length, 2.5 mm body diameter
&lt;p&gt;AXIAL Resistor package with 11.76 mm pitch, 0.63 mm lead diameter, 8.5 mm body length and 2.5 mm body diameter&lt;/p&gt;</description>
<packageinstances>
<packageinstance name="RESAD1176W63L850D250B"/>
</packageinstances>
</package3d>
<package3d name="RESMELF3515" urn="urn:adsk.eagle:package:16378562/2" type="model">
<description>MELF, 3.50 mm length, 1.52 mm diameter
&lt;p&gt;MELF Resistor package with 3.50 mm length and 1.52 mm diameter&lt;/p&gt;</description>
<packageinstances>
<packageinstance name="RESMELF3515"/>
</packageinstances>
</package3d>
<package3d name="RESMELF2014" urn="urn:adsk.eagle:package:16378558/2" type="model">
<description>MELF, 2.00 mm length, 1.40 mm diameter
&lt;p&gt;MELF Resistor package with 2.00 mm length and 1.40 mm diameter&lt;/p&gt;</description>
<packageinstances>
<packageinstance name="RESMELF2014"/>
</packageinstances>
</package3d>
<package3d name="RESMELF5924" urn="urn:adsk.eagle:package:16378567/3" type="model">
<description>MELF, 5.90 mm length, 2.45 mm diameter
&lt;p&gt;MELF Resistor package with 5.90 mm length and 2.45 mm diameter&lt;/p&gt;</description>
<packageinstances>
<packageinstance name="RESMELF5924"/>
</packageinstances>
</package3d>
<package3d name="RESMELF3218" urn="urn:adsk.eagle:package:16378556/2" type="model">
<description>MELF, 3.20 mm length, 1.80 mm diameter
&lt;p&gt;MELF Resistor package with 3.20 mm length and 1.80 mm diameter&lt;/p&gt;</description>
<packageinstances>
<packageinstance name="RESMELF3218"/>
</packageinstances>
</package3d>
<package3d name="RESAD724W46L381D178B" urn="urn:adsk.eagle:package:16378561/2" type="model">
<description>Axial Resistor, 7.24 mm pitch, 3.81 mm body length, 1.78 mm body diameter
&lt;p&gt;Axial Resistor package with 7.24 mm pitch (lead spacing), 0.46 mm lead diameter, 3.81 mm body length and 1.78 mm body diameter&lt;/p&gt;</description>
<packageinstances>
<packageinstance name="RESAD724W46L381D178B"/>
</packageinstances>
</package3d>
</packages3d>
<symbols>
<symbol name="R" urn="urn:adsk.eagle:symbol:16378529/3">
<description>RESISTOR</description>
<wire x1="-2.54" y1="-0.889" x2="2.54" y2="-0.889" width="0.254" layer="94"/>
<wire x1="2.54" y1="0.889" x2="-2.54" y2="0.889" width="0.254" layer="94"/>
<wire x1="2.54" y1="-0.889" x2="2.54" y2="0.889" width="0.254" layer="94"/>
<wire x1="-2.54" y1="-0.889" x2="-2.54" y2="0.889" width="0.254" layer="94"/>
<pin name="1" x="-5.08" y="0" visible="off" length="short" direction="pas" swaplevel="1"/>
<pin name="2" x="5.08" y="0" visible="off" length="short" direction="pas" swaplevel="1" rot="R180"/>
<text x="0" y="2.54" size="1.778" layer="95" align="center">&gt;NAME</text>
<text x="0" y="-5.08" size="1.778" layer="95" align="center">&gt;SPICEMODEL</text>
<text x="0" y="-2.54" size="1.778" layer="96" align="center">&gt;VALUE</text>
<text x="0" y="-7.62" size="1.778" layer="95" align="center">&gt;SPICEEXTRA</text>
</symbol>
</symbols>
<devicesets>
<deviceset name="R" urn="urn:adsk.eagle:component:16378570/8" prefix="R" uservalue="yes">
<description>&lt;b&gt;Resistor Fixed - Generic</description>
<gates>
<gate name="G$1" symbol="R" x="0" y="0"/>
</gates>
<devices>
<device name="CHIP-0402(1005-METRIC)" package="RESC1005X40">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16378568/2"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Resistor" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="RATING" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="Fixed" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TOLERANCE" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="CHIP-0603(1608-METRIC)" package="RESC1608X60">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16378565/2"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Resistor" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="RATING" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="Fixed" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TOLERANCE" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="CHIP-0805(2012-METRIC)" package="RESC2012X65">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16378559/2"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Resistor" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="RATING" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="Fixed" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TOLERANCE" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="CHIP-1206(3216-METRIC)" package="RESC3216X70">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16378566/2"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Resistor" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="RATING" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="Fixed" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TOLERANCE" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="CHIP-1210(3225-METRIC)" package="RESC3224X71">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16378563/3"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Resistor" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="RATING" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="Fixed" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TOLERANCE" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="CHIP-2010(5025-METRIC)" package="RESC5025X71">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16378564/2"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Resistor" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="RATING" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="Fixed" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TOLERANCE" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="CHIP-2512(6332-METRIC)" package="RESC6332X71">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16378557/3"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Resistor" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="RATING" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="Fixed" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TOLERANCE" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="AXIAL-11.7MM-PITCH" package="RESAD1176W63L850D250B">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16378560/2"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Resistor" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="RATING" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="Fixed" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TOLERANCE" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="MELF(3515-METRIC)" package="RESMELF3515">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16378562/2"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Resistor" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="RATING" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="Fixed" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TOLERANCE" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="MELF(2014-METRIC)" package="RESMELF2014">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16378558/2"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Resistor" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="RATING" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="Fixed" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TOLERANCE" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="MELF(5924-METRIC)" package="RESMELF5924">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16378567/3"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Resistor" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="RATING" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="Fixed" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TOLERANCE" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="MELF(3218-METRIC)" package="RESMELF3218">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16378556/2"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Resistor" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="RATING" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="Fixed" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TOLERANCE" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="AXIAL-7.2MM-PITCH" package="RESAD724W46L381D178B">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16378561/2"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Resistor" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="RATING" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="Fixed" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TOLERANCE" value="" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
</technology>
</technologies>
</device>
</devices>
<spice>
<pinmapping spiceprefix="R">
<pinmap gate="G$1" pin="1" pinorder="1"/>
<pinmap gate="G$1" pin="2" pinorder="2"/>
</pinmapping>
</spice>
</deviceset>
</devicesets>
</library>
<library name="diode">
<description>&lt;b&gt;Diodes&lt;/b&gt;&lt;p&gt;
Based on the following sources:
&lt;ul&gt;
&lt;li&gt;Motorola : www.onsemi.com
&lt;li&gt;Fairchild : www.fairchildsemi.com
&lt;li&gt;Philips : www.semiconductors.com
&lt;li&gt;Vishay : www.vishay.de
&lt;/ul&gt;
&lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
<package name="DO41-10">
<description>&lt;B&gt;DIODE&lt;/B&gt;&lt;p&gt;
diameter 2.54 mm, horizontal, grid 10.16 mm</description>
<wire x1="2.032" y1="-1.27" x2="-2.032" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="2.032" y1="-1.27" x2="2.032" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-2.032" y1="1.27" x2="2.032" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-2.032" y1="1.27" x2="-2.032" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="5.08" y1="0" x2="4.064" y2="0" width="0.762" layer="51"/>
<wire x1="-5.08" y1="0" x2="-4.064" y2="0" width="0.762" layer="51"/>
<wire x1="-0.635" y1="0" x2="0" y2="0" width="0.1524" layer="21"/>
<wire x1="1.016" y1="0.635" x2="1.016" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="1.016" y1="-0.635" x2="0" y2="0" width="0.1524" layer="21"/>
<wire x1="0" y1="0" x2="1.524" y2="0" width="0.1524" layer="21"/>
<wire x1="0" y1="0" x2="1.016" y2="0.635" width="0.1524" layer="21"/>
<wire x1="0" y1="0.635" x2="0" y2="0" width="0.1524" layer="21"/>
<wire x1="0" y1="0" x2="0" y2="-0.635" width="0.1524" layer="21"/>
<pad name="A" x="5.08" y="0" drill="1.1176"/>
<pad name="C" x="-5.08" y="0" drill="1.1176"/>
<text x="-2.032" y="1.651" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-2.032" y="-2.794" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-1.651" y1="-1.27" x2="-1.143" y2="1.27" layer="21"/>
<rectangle x1="2.032" y1="-0.381" x2="3.937" y2="0.381" layer="21"/>
<rectangle x1="-3.937" y1="-0.381" x2="-2.032" y2="0.381" layer="21"/>
</package>
</packages>
<symbols>
<symbol name="D">
<wire x1="-1.27" y1="-1.27" x2="1.27" y2="0" width="0.254" layer="94"/>
<wire x1="1.27" y1="0" x2="-1.27" y2="1.27" width="0.254" layer="94"/>
<wire x1="1.27" y1="1.27" x2="1.27" y2="0" width="0.254" layer="94"/>
<wire x1="-1.27" y1="1.27" x2="-1.27" y2="-1.27" width="0.254" layer="94"/>
<wire x1="1.27" y1="0" x2="1.27" y2="-1.27" width="0.254" layer="94"/>
<text x="2.54" y="0.4826" size="1.778" layer="95">&gt;NAME</text>
<text x="2.54" y="-2.3114" size="1.778" layer="96">&gt;VALUE</text>
<pin name="A" x="-2.54" y="0" visible="off" length="short" direction="pas"/>
<pin name="C" x="2.54" y="0" visible="off" length="short" direction="pas" rot="R180"/>
<text x="-2.54" y="0" size="0.4064" layer="99" align="center">SpiceOrder 1</text>
<text x="2.54" y="0" size="0.4064" layer="99" align="center">SpiceOrder 2</text>
</symbol>
</symbols>
<devicesets>
<deviceset name="1N4004" prefix="D">
<description>&lt;B&gt;DIODE&lt;/B&gt;&lt;p&gt;
general purpose rectifier, 1 A</description>
<gates>
<gate name="1" symbol="D" x="0" y="0"/>
</gates>
<devices>
<device name="" package="DO41-10">
<connects>
<connect gate="1" pin="A" pad="A"/>
<connect gate="1" pin="C" pad="C"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="Transistor">
<description>&lt;B&gt;BJT, JFET, MOSFET, UJT, Darlington</description>
<packages>
<package name="TO92" urn="urn:adsk.eagle:footprint:32629656/1">
<description>&lt;b&gt;TO-92&lt;/b&gt;</description>
<wire x1="-2.095" y1="-1.651" x2="-0.7869" y2="2.5484" width="0.1524" layer="21" curve="-111.097684"/>
<wire x1="0.7869" y1="2.5484" x2="2.095" y2="-1.651" width="0.1524" layer="21" curve="-111.097684"/>
<wire x1="-2.095" y1="-1.651" x2="2.095" y2="-1.651" width="0.1524" layer="21"/>
<wire x1="-2.254" y1="-0.254" x2="-0.286" y2="-0.254" width="0.1524" layer="51"/>
<wire x1="-2.655" y1="-0.254" x2="-2.254" y2="-0.254" width="0.1524" layer="21"/>
<wire x1="-0.286" y1="-0.254" x2="0.286" y2="-0.254" width="0.1524" layer="21"/>
<wire x1="2.254" y1="-0.254" x2="2.655" y2="-0.254" width="0.1524" layer="21"/>
<wire x1="0.286" y1="-0.254" x2="2.254" y2="-0.254" width="0.1524" layer="51"/>
<wire x1="-0.7864" y1="2.5484" x2="0.7864" y2="2.5484" width="0.1524" layer="51" curve="-34.298964"/>
<pad name="1" x="-1.27" y="0" drill="0.8128" shape="octagon"/>
<pad name="2" x="0" y="1.905" drill="0.8128" shape="octagon"/>
<pad name="3" x="1.27" y="0" drill="0.8128" shape="octagon"/>
<text x="2.413" y="1.651" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="2.921" y="-1.27" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
</package>
<package name="SOT95P237X112-3N" urn="urn:adsk.eagle:footprint:16378720/1">
<description>3-SOT23, 0.95 mm pitch, 2.37 mm span, 2.86 X 1.28 X 1.12 mm body
&lt;p&gt;3-pin SOT23 package with 0.95 mm pitch, 2.37 mm span with body size 2.86 X 1.28 X 1.12 mm&lt;/p&gt;</description>
<circle x="-1.204" y="1.7664" radius="0.25" width="0" layer="21"/>
<wire x1="-0.7" y1="1.5764" x2="0.7" y2="1.5764" width="0.12" layer="21"/>
<wire x1="0.7" y1="1.5764" x2="0.7" y2="0.5664" width="0.12" layer="21"/>
<wire x1="-0.7" y1="-1.5764" x2="0.7" y2="-1.5764" width="0.12" layer="21"/>
<wire x1="0.7" y1="-1.5764" x2="0.7" y2="-0.5664" width="0.12" layer="21"/>
<wire x1="0.7" y1="-1.525" x2="-0.7" y2="-1.525" width="0.12" layer="51"/>
<wire x1="-0.7" y1="-1.525" x2="-0.7" y2="1.525" width="0.12" layer="51"/>
<wire x1="-0.7" y1="1.525" x2="0.7" y2="1.525" width="0.12" layer="51"/>
<wire x1="0.7" y1="1.525" x2="0.7" y2="-1.525" width="0.12" layer="51"/>
<smd name="1" x="-1.064" y="0.95" dx="1.2235" dy="0.6248" layer="1"/>
<smd name="2" x="-1.064" y="-0.95" dx="1.2235" dy="0.6248" layer="1"/>
<smd name="3" x="1.064" y="0" dx="1.2235" dy="0.6248" layer="1"/>
<text x="0" y="2.6514" size="1.27" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-2.2114" size="1.27" layer="27" align="top-center">&gt;VALUE</text>
</package>
<package name="SC59" urn="urn:adsk.eagle:footprint:29647/1">
<description>&lt;b&gt;ROHM : SMT3 ; EIAJ : SC-59&lt;/b&gt;</description>
<wire x1="1.4224" y1="0.8604" x2="1.4224" y2="-0.8604" width="0.127" layer="51"/>
<wire x1="1.4224" y1="-0.8604" x2="-1.4224" y2="-0.8604" width="0.127" layer="51"/>
<wire x1="-1.4224" y1="-0.8604" x2="-1.4224" y2="0.8604" width="0.127" layer="51"/>
<wire x1="-1.4224" y1="0.8604" x2="1.4224" y2="0.8604" width="0.127" layer="51"/>
<smd name="C" x="0" y="1.2" dx="1" dy="1.4" layer="1"/>
<smd name="E" x="0.95" y="-1.2" dx="1" dy="1.4" layer="1"/>
<smd name="B" x="-0.95" y="-1.2" dx="1" dy="1.4" layer="1"/>
<text x="-1.905" y="1.905" size="1.27" layer="25">&gt;NAME</text>
<text x="-1.905" y="-3.175" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="-0.2286" y1="0.9112" x2="0.2286" y2="1.4954" layer="51"/>
<rectangle x1="0.7112" y1="-1.4954" x2="1.1684" y2="-0.9112" layer="51"/>
<rectangle x1="-1.1684" y1="-1.4954" x2="-0.7112" y2="-0.9112" layer="51"/>
</package>
<package name="SC70" urn="urn:adsk.eagle:footprint:29646/1">
<description>&lt;b&gt;SC70-3 Reflow soldering&lt;/b&gt;&lt;p&gt;
Philips SC01_Mounting_1996.pdf&lt;p&gt;
ROHM : UMT3 ; EIAJ : SC-70</description>
<wire x1="0.9224" y1="0.4604" x2="0.9224" y2="-0.4604" width="0.1524" layer="51"/>
<wire x1="0.9224" y1="-0.4604" x2="-0.9224" y2="-0.4604" width="0.1524" layer="51"/>
<wire x1="-0.9224" y1="-0.4604" x2="-0.9224" y2="0.4604" width="0.1524" layer="51"/>
<wire x1="-0.9224" y1="0.4604" x2="0.9224" y2="0.4604" width="0.1524" layer="51"/>
<wire x1="0.9224" y1="0.4604" x2="0.9224" y2="-0.4604" width="0.1524" layer="21"/>
<wire x1="0.9224" y1="-0.4604" x2="-0.9224" y2="-0.4604" width="0.1524" layer="21"/>
<wire x1="-0.9224" y1="-0.4604" x2="-0.9224" y2="0.4604" width="0.1524" layer="21"/>
<wire x1="-0.9224" y1="0.4604" x2="0.9224" y2="0.4604" width="0.1524" layer="21"/>
<smd name="1" x="-0.65" y="-0.925" dx="0.6" dy="0.55" layer="1"/>
<smd name="2" x="0.65" y="-0.925" dx="0.6" dy="0.55" layer="1"/>
<smd name="3" x="0" y="0.925" dx="0.6" dy="0.55" layer="1"/>
<text x="-1" y="1.3" size="1.27" layer="25">&gt;NAME</text>
<text x="-1" y="-2.6" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="-0.8" y1="-1.1" x2="-0.5" y2="-0.5" layer="51"/>
<rectangle x1="0.5" y1="-1.1" x2="0.8" y2="-0.5" layer="51"/>
<rectangle x1="-0.15" y1="0.5" x2="0.15" y2="1.1" layer="51"/>
</package>
<package name="TO18" urn="urn:adsk.eagle:footprint:28463/1">
<description>&lt;b&gt;TO 18&lt;/b&gt;</description>
<wire x1="0.9289" y1="2.227" x2="2.227" y2="0.9289" width="0.0508" layer="51" curve="-44.7172"/>
<wire x1="0.9289" y1="-2.227" x2="2.227" y2="-0.9289" width="0.0508" layer="51" curve="44.7172"/>
<wire x1="-3.937" y1="-0.508" x2="-3.937" y2="0.508" width="0.127" layer="21"/>
<wire x1="-2.227" y1="-0.9289" x2="0.929" y2="2.2271" width="0.0508" layer="21" curve="-135.281"/>
<wire x1="-2.227" y1="-0.9289" x2="-0.9289" y2="-2.227" width="0.0508" layer="51" curve="44.7172"/>
<wire x1="-3.937" y1="-0.508" x2="-2.8765" y2="-0.508" width="0.127" layer="21"/>
<wire x1="-0.9289" y1="-2.227" x2="0.9289" y2="-2.227" width="0.0508" layer="21" curve="45.2828"/>
<wire x1="-3.937" y1="0.508" x2="-2.8765" y2="0.508" width="0.127" layer="21"/>
<wire x1="2.227" y1="-0.9289" x2="2.227" y2="0.9289" width="0.0508" layer="21" curve="45.2828"/>
<circle x="0" y="0" radius="2.921" width="0.127" layer="21"/>
<pad name="1" x="-1.27" y="-1.27" drill="0.8128" shape="octagon"/>
<pad name="2" x="1.27" y="-1.27" drill="0.8128" shape="octagon"/>
<pad name="3" x="1.27" y="1.27" drill="0.8128" shape="octagon"/>
<text x="3.175" y="0" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="3.175" y="-1.905" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
<text x="-1.905" y="-1.27" size="1.27" layer="51" ratio="10">1</text>
<text x="0.635" y="-1.27" size="1.27" layer="51" ratio="10">2</text>
<text x="0" y="0.635" size="1.27" layer="51" ratio="10">3</text>
</package>
</packages>
<packages3d>
<package3d name="TO92" urn="urn:adsk.eagle:package:16378726/8" type="model">
<description>&lt;b&gt;TO-92&lt;/b&gt;</description>
<packageinstances>
<packageinstance name="TO92"/>
</packageinstances>
</package3d>
<package3d name="SOT95P237X112-3N" urn="urn:adsk.eagle:package:16378725/1" type="model">
<description>3-SOT23, 0.95 mm pitch, 2.37 mm span, 2.86 X 1.28 X 1.12 mm body
&lt;p&gt;3-pin SOT23 package with 0.95 mm pitch, 2.37 mm span with body size 2.86 X 1.28 X 1.12 mm&lt;/p&gt;</description>
<packageinstances>
<packageinstance name="SOT95P237X112-3N"/>
</packageinstances>
</package3d>
<package3d name="SC59" urn="urn:adsk.eagle:package:29756/2" type="model">
<description>ROHM : SMT3 ; EIAJ : SC-59</description>
<packageinstances>
<packageinstance name="SC59"/>
</packageinstances>
</package3d>
<package3d name="SC70" urn="urn:adsk.eagle:package:29755/2" type="model">
<description>SC70-3 Reflow soldering
Philips SC01_Mounting_1996.pdf
ROHM : UMT3 ; EIAJ : SC-70</description>
<packageinstances>
<packageinstance name="SC70"/>
</packageinstances>
</package3d>
<package3d name="TO18" urn="urn:adsk.eagle:package:16378727/2" type="model">
<description>TO 18</description>
<packageinstances>
<packageinstance name="TO18"/>
</packageinstances>
</package3d>
</packages3d>
<symbols>
<symbol name="NPN" urn="urn:adsk.eagle:symbol:16378719/1">
<wire x1="0" y1="2.54" x2="-2.032" y2="1.524" width="0.1524" layer="94"/>
<wire x1="-0.762" y1="-1.524" x2="0" y2="-2.54" width="0.1524" layer="94"/>
<wire x1="0" y1="-2.54" x2="-1.27" y2="-2.54" width="0.1524" layer="94"/>
<wire x1="-1.27" y1="-2.54" x2="-0.762" y2="-1.524" width="0.1524" layer="94"/>
<wire x1="-1" y1="-2.04" x2="-2.232" y2="-1.424" width="0.1524" layer="94"/>
<wire x1="-1.016" y1="-2.413" x2="-0.254" y2="-2.413" width="0.254" layer="94"/>
<wire x1="-0.254" y1="-2.413" x2="-0.762" y2="-1.778" width="0.254" layer="94"/>
<wire x1="-0.762" y1="-1.778" x2="-1.016" y2="-2.286" width="0.254" layer="94"/>
<wire x1="-1.016" y1="-2.286" x2="-0.635" y2="-2.286" width="0.254" layer="94"/>
<wire x1="-0.635" y1="-2.286" x2="-0.762" y2="-2.032" width="0.254" layer="94"/>
<text x="0.54" y="3" size="1.778" layer="95">&gt;NAME</text>
<text x="0.54" y="0.46" size="1.778" layer="96">&gt;VALUE</text>
<text x="0.54" y="-2.08" size="1.778" layer="97">&gt;SPICEMODEL</text>
<text x="0.54" y="-4.62" size="1.778" layer="97">&gt;SPICEEXTRA</text>
<rectangle x1="-2.794" y1="-2.54" x2="-2.032" y2="2.54" layer="94"/>
<pin name="B" x="-5.08" y="0" visible="off" length="short" direction="pas" swaplevel="1"/>
<pin name="E" x="0" y="-5.08" visible="off" length="short" direction="pas" swaplevel="3" rot="R90"/>
<pin name="C" x="0" y="5.08" visible="off" length="short" direction="pas" swaplevel="2" rot="R270"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="NPN" urn="urn:adsk.eagle:component:16378737/8" prefix="Q" uservalue="yes">
<description>&lt;B&gt;NPN - Generic</description>
<gates>
<gate name="G$1" symbol="NPN" x="0" y="0"/>
</gates>
<devices>
<device name="TO92-EBC" package="TO92">
<connects>
<connect gate="G$1" pin="B" pad="2"/>
<connect gate="G$1" pin="C" pad="3"/>
<connect gate="G$1" pin="E" pad="1"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16378726/8"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Transistor" constant="no"/>
<attribute name="DESCRIPTION" value="" constant="no"/>
<attribute name="IC_MAX" value="" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="BJT" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TYPE" value="NPN" constant="no"/>
<attribute name="VALUE" value="NPN" constant="no"/>
<attribute name="VCEO_MAX" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="SOT23-BEC" package="SOT95P237X112-3N">
<connects>
<connect gate="G$1" pin="B" pad="1"/>
<connect gate="G$1" pin="C" pad="3"/>
<connect gate="G$1" pin="E" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16378725/1"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Transistor" constant="no"/>
<attribute name="DESCRIPTION" value="" constant="no"/>
<attribute name="IC_MAX" value="" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="BJT" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TYPE" value="NPN" constant="no"/>
<attribute name="VALUE" value="NPN" constant="no"/>
<attribute name="VCEO_MAX" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="SC59-BEC" package="SC59">
<connects>
<connect gate="G$1" pin="B" pad="B"/>
<connect gate="G$1" pin="C" pad="C"/>
<connect gate="G$1" pin="E" pad="E"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:29756/2"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Transistor" constant="no"/>
<attribute name="DESCRIPTION" value="" constant="no"/>
<attribute name="IC_MAX" value="" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="BJT" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TYPE" value="NPN" constant="no"/>
<attribute name="VALUE" value="NPN" constant="no"/>
<attribute name="VCEO_MAX" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="SC70-BEC" package="SC70">
<connects>
<connect gate="G$1" pin="B" pad="1"/>
<connect gate="G$1" pin="C" pad="3"/>
<connect gate="G$1" pin="E" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:29755/2"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Transistor" constant="no"/>
<attribute name="DESCRIPTION" value="" constant="no"/>
<attribute name="IC_MAX" value="" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="BJT" constant="no"/>
<attribute name="THERMALLOSS" value="NPN" constant="no"/>
<attribute name="TYPE" value="" constant="no"/>
<attribute name="VALUE" value="NPN" constant="no"/>
<attribute name="VCEO_MAX" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="TO18-EBC" package="TO18">
<connects>
<connect gate="G$1" pin="B" pad="2"/>
<connect gate="G$1" pin="C" pad="3"/>
<connect gate="G$1" pin="E" pad="1"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:16378727/2"/>
</package3dinstances>
<technologies>
<technology name="_">
<attribute name="CATEGORY" value="Transistor" constant="no"/>
<attribute name="DESCRIPTION" value="" constant="no"/>
<attribute name="IC_MAX" value="" constant="no"/>
<attribute name="MANUFACTURER" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OPERATING_TEMP" value="" constant="no"/>
<attribute name="PART_STATUS" value="" constant="no"/>
<attribute name="ROHS_COMPLIANT" value="" constant="no"/>
<attribute name="SERIES" value="" constant="no"/>
<attribute name="SUB-CATEGORY" value="BJT" constant="no"/>
<attribute name="THERMALLOSS" value="" constant="no"/>
<attribute name="TYPE" value="NPN" constant="no"/>
<attribute name="VALUE" value="NPN" constant="no"/>
<attribute name="VCEO_MAX" value="" constant="no"/>
</technology>
</technologies>
</device>
</devices>
<spice>
<pinmapping spiceprefix="Q">
<pinmap gate="G$1" pin="B" pinorder="2"/>
<pinmap gate="G$1" pin="C" pinorder="1"/>
<pinmap gate="G$1" pin="E" pinorder="3"/>
</pinmapping>
<model name="QNPN">
**********************
* Autodesk EAGLE - Spice Model File
* Date: 9/17/17
* basic npn intrinsic model
**********************
.MODEL QNPN NPN</model>
</spice>
</deviceset>
</devicesets>
</library>
<library name="TIP42C">
<packages>
<package name="TO220AV">
<description>&lt;b&gt;Molded Package&lt;/b&gt;&lt;p&gt;
grid 2.54 mm</description>
<wire x1="5.08" y1="-1.143" x2="4.953" y2="-4.064" width="0.1524" layer="21"/>
<wire x1="4.699" y1="-4.318" x2="4.953" y2="-4.064" width="0.1524" layer="21"/>
<wire x1="4.699" y1="-4.318" x2="-4.699" y2="-4.318" width="0.1524" layer="21"/>
<wire x1="-4.953" y1="-4.064" x2="-4.699" y2="-4.318" width="0.1524" layer="21"/>
<wire x1="-4.953" y1="-4.064" x2="-5.08" y2="-1.143" width="0.1524" layer="21"/>
<circle x="-4.4958" y="-3.7084" radius="0.254" width="0.1524" layer="21"/>
<text x="-5.08181875" y="-6.047359375" size="1.27045" layer="25" ratio="10">&gt;NAME</text>
<text x="-5.08035" y="-7.62053125" size="1.270090625" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-5.3361" y1="-0.7623" x2="5.334" y2="0" layer="21"/>
<rectangle x1="-5.337259375" y1="-1.27078125" x2="-3.429" y2="-0.762" layer="21"/>
<rectangle x1="-1.652059375" y1="-1.270809375" x2="-0.889" y2="-0.762" layer="21"/>
<rectangle x1="-3.430259375" y1="-1.27046875" x2="-1.651" y2="-0.762" layer="51"/>
<rectangle x1="0.8898" y1="-1.271140625" x2="1.651" y2="-0.762" layer="21"/>
<rectangle x1="3.434790625" y1="-1.272140625" x2="5.334" y2="-0.762" layer="21"/>
<rectangle x1="-0.890253125" y1="-1.271790625" x2="0.889" y2="-0.762" layer="51"/>
<rectangle x1="1.65425" y1="-1.2725" x2="3.429" y2="-0.762" layer="51"/>
<pad name="B" x="-2.54" y="-2.54" drill="1.016" shape="long" rot="R90"/>
<pad name="C" x="0" y="-2.54" drill="1.016" shape="long" rot="R90"/>
<pad name="E" x="2.54" y="-2.54" drill="1.016" shape="long" rot="R90"/>
</package>
</packages>
<symbols>
<symbol name="PNP">
<wire x1="2.54" y1="-2.54" x2="0" y2="0" width="0.1524" layer="94"/>
<wire x1="0" y1="0" x2="1.016" y2="1.016" width="0.1524" layer="94"/>
<wire x1="2.413" y1="1.651" x2="1.016" y2="1.016" width="0.1524" layer="94"/>
<wire x1="1.016" y1="1.016" x2="1.143" y2="1.143" width="0.1524" layer="94"/>
<wire x1="1.905" y1="1.905" x2="2.54" y2="2.54" width="0.1524" layer="94"/>
<wire x1="1.016" y1="1.016" x2="1.651" y2="2.413" width="0.1524" layer="94"/>
<wire x1="1.651" y1="2.413" x2="2.413" y2="1.651" width="0.1524" layer="94"/>
<wire x1="1.143" y1="1.143" x2="2.159" y2="1.651" width="0.254" layer="94"/>
<wire x1="2.159" y1="1.651" x2="1.905" y2="1.905" width="0.254" layer="94"/>
<wire x1="1.905" y1="1.905" x2="1.651" y2="2.159" width="0.254" layer="94"/>
<wire x1="1.651" y1="2.159" x2="1.143" y2="1.143" width="0.254" layer="94"/>
<wire x1="1.143" y1="1.143" x2="1.905" y2="1.905" width="0.254" layer="94"/>
<wire x1="1.651" y1="1.905" x2="1.905" y2="1.651" width="0.254" layer="94"/>
<text x="5.08195" y="2.54098125" size="1.77868125" layer="95">&gt;NAME</text>
<text x="5.087840625" y="0" size="1.78075" layer="96">&gt;VALUE</text>
<rectangle x1="-0.381665625" y1="-2.54445" x2="0.381" y2="2.54" layer="94"/>
<pin name="B" x="-2.54" y="0" visible="off" length="short" direction="pas"/>
<pin name="E" x="2.54" y="5.08" visible="off" length="short" direction="pas" rot="R270"/>
<pin name="C" x="2.54" y="-5.08" visible="off" length="short" direction="pas" rot="R90"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="TIP42C" prefix="Q">
<description>&lt;b&gt;PNP TRANSISTOR&lt;/b&gt; &lt;a href="https://pricing.snapeda.com/parts/TIP42C/onsemi/view-part?ref=eda"&gt;Check availability&lt;/a&gt;</description>
<gates>
<gate name="1" symbol="PNP" x="0" y="0"/>
</gates>
<devices>
<device name="" package="TO220AV">
<connects>
<connect gate="1" pin="B" pad="B"/>
<connect gate="1" pin="C" pad="C"/>
<connect gate="1" pin="E" pad="E"/>
</connects>
<technologies>
<technology name="">
<attribute name="AVAILABILITY" value="In Stock"/>
<attribute name="DESCRIPTION" value=" Bipolar (BJT) Transistor PNP 100 V 6 A 3MHz 2 W Through Hole TO-220-3 "/>
<attribute name="MF" value="onsemi"/>
<attribute name="MP" value="TIP42C"/>
<attribute name="PACKAGE" value="TO-220-3 ON"/>
<attribute name="PRICE" value="None"/>
<attribute name="PURCHASE-URL" value="https://pricing.snapeda.com/search?q=TIP42C&amp;ref=eda"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
</libraries>
<attributes>
</attributes>
<variantdefs>
</variantdefs>
<classes>
<class number="0" name="default" width="0.0254" drill="0">
<clearance class="0" value="0.0508"/>
</class>
<class number="1" name="pow" width="0.0254" drill="0">
<clearance class="1" value="0.0508"/>
</class>
</classes>
<parts>
<part name="U$1" library="BluePill" library_urn="urn:adsk.wipprod:fs.file:vf.zv9c6spOQmC8O2Ukh5v0tg" deviceset="BLUE_PILL" device="ADVANCED"/>
<part name="Z_DRV" library="pololu-stepper-driver" deviceset="2986-A4988" device=""/>
<part name="Y_DRV" library="pololu-stepper-driver" deviceset="2986-A4988" device=""/>
<part name="X_DRV" library="pololu-stepper-driver" deviceset="2986-A4988" device=""/>
<part name="SUPPLY1" library="Power_Symbols" deviceset="+3.3V" device="" value="+3.3V"/>
<part name="SUPPLY2" library="Power_Symbols" deviceset="+5V" device="" value="+24V"/>
<part name="SUPPLY3" library="Power_Symbols" deviceset="+5V" device="" value="+24V"/>
<part name="SUPPLY4" library="Power_Symbols" deviceset="+5V" device="" value="+24V"/>
<part name="SUPPLY5" library="Power_Symbols" deviceset="+3.3V" device="" value="+3.3V"/>
<part name="SUPPLY6" library="Power_Symbols" deviceset="GND" device="" value="GND"/>
<part name="SUPPLY7" library="Power_Symbols" deviceset="+3.3V" device="" value="+3.3V"/>
<part name="SUPPLY9" library="Power_Symbols" deviceset="GND" device="" value="GND"/>
<part name="SUPPLY8" library="Power_Symbols" deviceset="+3.3V" device="" value="+3.3V"/>
<part name="SUPPLY10" library="Power_Symbols" deviceset="GND" device="" value="GND"/>
<part name="SUPPLY12" library="Power_Symbols" deviceset="GND" device="" value="GND"/>
<part name="SUPPLY14" library="Power_Symbols" deviceset="GND" device="" value="GND"/>
<part name="SUPPLY16" library="Power_Symbols" deviceset="+3.3V" device="" value="+3.3V"/>
<part name="SUPPLY17" library="Power_Symbols" deviceset="GND" device="" value="GND"/>
<part name="SUPPLY18" library="Power_Symbols" deviceset="+3.3V" device="" value="+3.3V"/>
<part name="SUPPLY19" library="Power_Symbols" deviceset="+3.3V" device="" value="+24V"/>
<part name="SUPPLY20" library="Power_Symbols" deviceset="GND" device="" value="GND"/>
<part name="SUPPLY21" library="Power_Symbols" deviceset="GND" device="" value="GND"/>
<part name="C_PROBE" library="Capacitor" deviceset="C-POL-US" device="RADIAL-11MM-DIA" package3d_urn="urn:adsk.eagle:package:16290899/1" technology="_" value="10u"/>
<part name="SUPPLY23" library="Power_Symbols" deviceset="+3.3V" device="" value="+3.3V"/>
<part name="C_VDD" library="Capacitor" deviceset="C-POL-US" device="RADIAL-11MM-DIA" package3d_urn="urn:adsk.eagle:package:16290899/1" technology="_" value="100u"/>
<part name="X_JST" library="Connector" deviceset="B4B-XH-A" device="" package3d_urn="urn:adsk.eagle:package:24957647/3" value="3A/250V"/>
<part name="Y_JST" library="Connector" deviceset="B4B-XH-A" device="" package3d_urn="urn:adsk.eagle:package:24957647/3" value="3A/250V"/>
<part name="Z_JST" library="Connector" deviceset="B4B-XH-A" device="" package3d_urn="urn:adsk.eagle:package:24957647/3" value="3A/250V"/>
<part name="RB" library="Resistor" deviceset="R" device="AXIAL-7.2MM-PITCH" package3d_urn="urn:adsk.eagle:package:16378561/2" technology="_" value="12k"/>
<part name="SUPPLY13" library="Power_Symbols" deviceset="GND" device="" value="GND"/>
<part name="SUPPLY11" library="Power_Symbols" deviceset="+3.3V" device="" value="+3.3V"/>
<part name="SUPPLY15" library="Power_Symbols" deviceset="+3.3V" device="" value="+3.3V"/>
<part name="SUPPLY22" library="Power_Symbols" deviceset="GND" device="" value="GND"/>
<part name="C_VMOT" library="Capacitor" deviceset="C-POL-US" device="RADIAL-20MM-DIA" package3d_urn="urn:adsk.eagle:package:16290874/1" technology="_" value="4700u"/>
<part name="PROBE" library="Connector" deviceset="B2B-XH-A" device="" package3d_urn="urn:adsk.eagle:package:24957641/6" value="3A/250V"/>
<part name="24V" library="Connector" deviceset="B2B-XH-A" device="" package3d_urn="urn:adsk.eagle:package:24957641/6" value="3A/250V"/>
<part name="SUPPLY28" library="Power_Symbols" deviceset="+3.3V" device="" value="+3.3V"/>
<part name="SUPPLY29" library="Power_Symbols" deviceset="GND" device="" value="GND"/>
<part name="SPINDLE" library="Connector" deviceset="B2B-XH-A" device="" package3d_urn="urn:adsk.eagle:package:24957641/6" value="3A/250V"/>
<part name="D1" library="diode" deviceset="1N4004" device=""/>
<part name="R1" library="Resistor" deviceset="R" device="AXIAL-7.2MM-PITCH" package3d_urn="urn:adsk.eagle:package:16378561/2" technology="_" value="10"/>
<part name="Q1" library="Transistor" deviceset="NPN" device="TO92-EBC" package3d_urn="urn:adsk.eagle:package:16378726/8" technology="_" value="NPN"/>
<part name="SUPPLY25" library="Power_Symbols" deviceset="GND" device="" value="GND"/>
<part name="SUPPLY26" library="Power_Symbols" deviceset="+5V" device="" value="+24V"/>
<part name="RB1" library="Resistor" deviceset="R" device="AXIAL-7.2MM-PITCH" package3d_urn="urn:adsk.eagle:package:16378561/2" technology="_" value="1k"/>
<part name="Q2" library="TIP42C" deviceset="TIP42C" device=""/>
<part name="SUPPLY27" library="Power_Symbols" deviceset="+5V" device="" value="+24V"/>
<part name="SUPPLY30" library="Power_Symbols" deviceset="GND" device="" value="GND"/>
<part name="RB2" library="Resistor" deviceset="R" device="AXIAL-7.2MM-PITCH" package3d_urn="urn:adsk.eagle:package:16378561/2" technology="_" value="1k"/>
<part name="TFT_SD_2" library="Connector" deviceset="PINHD-1X8" device="" package3d_urn="urn:adsk.eagle:package:22409/2"/>
<part name="SUPPLY31" library="Power_Symbols" deviceset="GND" device="" value="GND"/>
<part name="SUPPLY32" library="Power_Symbols" deviceset="+3.3V" device="" value="+3.3V"/>
<part name="TFT_SD_1" library="Connector" deviceset="PINHD-1X4" device="/90" package3d_urn="urn:adsk.eagle:package:22404/2"/>
</parts>
<sheets>
<sheet>
<plain>
</plain>
<instances>
<instance part="U$1" gate="G$1" x="5.08" y="35.56" smashed="yes"/>
<instance part="Z_DRV" gate="G$1" x="71.12" y="-20.32" smashed="yes">
<attribute name="NAME" x="66.04" y="-9.525" size="1.778" layer="95"/>
<attribute name="VALUE" x="66.04" y="-35.56" size="1.778" layer="96"/>
</instance>
<instance part="Y_DRV" gate="G$1" x="71.12" y="15.24" smashed="yes">
<attribute name="NAME" x="66.04" y="26.035" size="1.778" layer="95"/>
<attribute name="VALUE" x="66.04" y="0" size="1.778" layer="96"/>
</instance>
<instance part="X_DRV" gate="G$1" x="71.12" y="50.8" smashed="yes">
<attribute name="NAME" x="66.04" y="61.595" size="1.778" layer="95"/>
<attribute name="VALUE" x="66.04" y="35.56" size="1.778" layer="96"/>
</instance>
<instance part="SUPPLY1" gate="G$1" x="48.26" y="60.96" smashed="yes">
<attribute name="VALUE" x="48.133" y="64.008" size="1.778" layer="96" align="bottom-center"/>
</instance>
<instance part="SUPPLY2" gate="G$1" x="88.9" y="58.42" smashed="yes">
<attribute name="VALUE" x="88.773" y="61.468" size="1.778" layer="96" align="bottom-center"/>
</instance>
<instance part="SUPPLY3" gate="G$1" x="88.9" y="22.86" smashed="yes">
<attribute name="VALUE" x="88.773" y="25.908" size="1.778" layer="96" align="bottom-center"/>
</instance>
<instance part="SUPPLY4" gate="G$1" x="88.9" y="-12.7" smashed="yes">
<attribute name="VALUE" x="88.773" y="-9.652" size="1.778" layer="96" align="bottom-center"/>
</instance>
<instance part="SUPPLY5" gate="G$1" x="91.44" y="38.1" smashed="yes">
<attribute name="VALUE" x="91.313" y="41.148" size="1.778" layer="96" align="bottom-center"/>
</instance>
<instance part="SUPPLY6" gate="G$1" x="96.52" y="33.02" smashed="yes">
<attribute name="VALUE" x="96.52" y="30.48" size="1.778" layer="96" align="center"/>
</instance>
<instance part="SUPPLY7" gate="G$1" x="91.44" y="2.54" smashed="yes">
<attribute name="VALUE" x="91.313" y="5.588" size="1.778" layer="96" align="bottom-center"/>
</instance>
<instance part="SUPPLY9" gate="G$1" x="96.52" y="-2.54" smashed="yes">
<attribute name="VALUE" x="96.52" y="-5.08" size="1.778" layer="96" align="center"/>
</instance>
<instance part="SUPPLY8" gate="G$1" x="91.44" y="-33.02" smashed="yes">
<attribute name="VALUE" x="91.313" y="-29.972" size="1.778" layer="96" align="bottom-center"/>
</instance>
<instance part="SUPPLY10" gate="G$1" x="96.52" y="-38.1" smashed="yes">
<attribute name="VALUE" x="96.52" y="-40.64" size="1.778" layer="96" align="center"/>
</instance>
<instance part="SUPPLY12" gate="G$1" x="96.52" y="58.42" smashed="yes">
<attribute name="VALUE" x="96.52" y="55.88" size="1.778" layer="96" align="center"/>
</instance>
<instance part="SUPPLY14" gate="G$1" x="96.52" y="-12.7" smashed="yes">
<attribute name="VALUE" x="96.52" y="-15.24" size="1.778" layer="96" align="center"/>
</instance>
<instance part="SUPPLY16" gate="G$1" x="38.1" y="58.42" smashed="yes">
<attribute name="VALUE" x="37.973" y="61.468" size="1.778" layer="96" align="bottom-center"/>
</instance>
<instance part="SUPPLY17" gate="G$1" x="33.02" y="58.42" smashed="yes">
<attribute name="VALUE" x="33.02" y="55.88" size="1.778" layer="96" align="center"/>
</instance>
<instance part="SUPPLY18" gate="G$1" x="10.16" y="-2.54" smashed="yes">
<attribute name="VALUE" x="10.033" y="0.508" size="1.778" layer="96" align="bottom-center"/>
</instance>
<instance part="SUPPLY19" gate="G$1" x="-7.62" y="-2.54" smashed="yes">
<attribute name="VALUE" x="-7.747" y="0.508" size="1.778" layer="96" align="bottom-center"/>
</instance>
<instance part="SUPPLY20" gate="G$1" x="-7.62" y="-12.7" smashed="yes">
<attribute name="VALUE" x="-7.62" y="-15.24" size="1.778" layer="96" align="center"/>
</instance>
<instance part="SUPPLY21" gate="G$1" x="10.16" y="-12.7" smashed="yes">
<attribute name="VALUE" x="10.16" y="-15.24" size="1.778" layer="96" align="center"/>
</instance>
<instance part="C_PROBE" gate="G$1" x="-17.78" y="71.12" smashed="yes">
<attribute name="NAME" x="-16.764" y="71.755" size="1.778" layer="95"/>
<attribute name="VALUE" x="-16.764" y="66.929" size="1.778" layer="96"/>
</instance>
<instance part="SUPPLY23" gate="G$1" x="-7.62" y="81.28" smashed="yes">
<attribute name="VALUE" x="-7.747" y="84.328" size="1.778" layer="96" align="bottom-center"/>
</instance>
<instance part="C_VDD" gate="G$1" x="10.16" y="-5.08" smashed="yes">
<attribute name="NAME" x="11.176" y="-4.445" size="1.778" layer="95"/>
<attribute name="VALUE" x="11.176" y="-9.271" size="1.778" layer="96"/>
</instance>
<instance part="X_JST" gate="G$1" x="106.68" y="50.8" smashed="yes">
<attribute name="VALUE" x="106.68" y="44.196" size="1.778" layer="96" align="top-center"/>
<attribute name="NAME" x="106.68" y="54.864" size="1.778" layer="95" align="bottom-center"/>
</instance>
<instance part="Y_JST" gate="G$1" x="106.68" y="15.24" smashed="yes">
<attribute name="VALUE" x="106.68" y="8.636" size="1.778" layer="96" align="top-center"/>
<attribute name="NAME" x="106.68" y="19.304" size="1.778" layer="95" align="bottom-center"/>
</instance>
<instance part="Z_JST" gate="G$1" x="106.68" y="-20.32" smashed="yes">
<attribute name="VALUE" x="106.68" y="-26.924" size="1.778" layer="96" align="top-center"/>
<attribute name="NAME" x="106.68" y="-16.256" size="1.778" layer="95" align="bottom-center"/>
</instance>
<instance part="RB" gate="G$1" x="-96.52" y="60.96" smashed="yes">
<attribute name="NAME" x="-96.52" y="63.5" size="1.778" layer="95" align="center"/>
<attribute name="VALUE" x="-96.52" y="58.42" size="1.778" layer="96" align="center"/>
</instance>
<instance part="SUPPLY13" gate="G$1" x="96.52" y="22.86" smashed="yes">
<attribute name="VALUE" x="96.52" y="20.32" size="1.778" layer="96" align="center"/>
</instance>
<instance part="SUPPLY11" gate="G$1" x="48.26" y="27.94" smashed="yes">
<attribute name="VALUE" x="48.133" y="30.988" size="1.778" layer="96" align="bottom-center"/>
</instance>
<instance part="SUPPLY15" gate="G$1" x="48.26" y="-10.16" smashed="yes">
<attribute name="VALUE" x="48.133" y="-7.112" size="1.778" layer="96" align="bottom-center"/>
</instance>
<instance part="SUPPLY22" gate="G$1" x="-17.78" y="63.5" smashed="yes">
<attribute name="VALUE" x="-17.78" y="60.96" size="1.778" layer="96" align="center"/>
</instance>
<instance part="C_VMOT" gate="G$1" x="-7.62" y="-5.08" smashed="yes">
<attribute name="NAME" x="-6.604" y="-4.445" size="1.778" layer="95"/>
<attribute name="VALUE" x="-6.604" y="-9.271" size="1.778" layer="96"/>
</instance>
<instance part="PROBE" gate="G$1" x="7.62" y="76.2" smashed="yes">
<attribute name="VALUE" x="7.62" y="73.406" size="1.778" layer="96" align="top-center"/>
<attribute name="NAME" x="7.62" y="81.534" size="1.778" layer="95" align="bottom-center"/>
</instance>
<instance part="24V" gate="G$1" x="-22.86" y="-5.08" smashed="yes" rot="R180">
<attribute name="VALUE" x="-22.86" y="-2.286" size="1.778" layer="96" rot="R180" align="top-center"/>
<attribute name="NAME" x="-22.86" y="-10.414" size="1.778" layer="95" rot="R180" align="bottom-center"/>
</instance>
<instance part="SUPPLY28" gate="G$1" x="-20.32" y="5.08" smashed="yes">
<attribute name="VALUE" x="-20.447" y="8.128" size="1.778" layer="96" align="bottom-center"/>
</instance>
<instance part="SUPPLY29" gate="G$1" x="-27.94" y="7.62" smashed="yes">
<attribute name="VALUE" x="-27.94" y="5.08" size="1.778" layer="96" align="center"/>
</instance>
<instance part="SPINDLE" gate="G$1" x="-55.88" y="58.42" smashed="yes" rot="MR180">
<attribute name="VALUE" x="-55.88" y="61.214" size="1.778" layer="96" rot="MR180" align="top-center"/>
<attribute name="NAME" x="-55.88" y="53.086" size="1.778" layer="95" rot="MR180" align="bottom-center"/>
</instance>
<instance part="D1" gate="1" x="-71.12" y="55.88" smashed="yes" rot="R90">
<attribute name="NAME" x="-74.1426" y="50.8" size="1.778" layer="95" rot="R90"/>
<attribute name="VALUE" x="-76.4286" y="50.8" size="1.778" layer="96" rot="R90"/>
</instance>
<instance part="R1" gate="G$1" x="-71.12" y="48.26" smashed="yes" rot="R90">
<attribute name="NAME" x="-73.66" y="48.26" size="1.778" layer="95" rot="R90" align="center"/>
<attribute name="VALUE" x="-68.58" y="48.26" size="1.778" layer="96" rot="R90" align="center"/>
</instance>
<instance part="Q1" gate="G$1" x="-86.36" y="60.96" smashed="yes">
<attribute name="NAME" x="-85.82" y="63.96" size="1.778" layer="95"/>
<attribute name="VALUE" x="-85.82" y="61.42" size="1.778" layer="96"/>
</instance>
<instance part="SUPPLY25" gate="G$1" x="-86.36" y="53.34" smashed="yes">
<attribute name="VALUE" x="-86.36" y="50.8" size="1.778" layer="96" align="center"/>
</instance>
<instance part="SUPPLY26" gate="G$1" x="-86.36" y="76.2" smashed="yes">
<attribute name="VALUE" x="-86.487" y="79.248" size="1.778" layer="96" align="bottom-center"/>
</instance>
<instance part="RB1" gate="G$1" x="-86.36" y="71.12" smashed="yes" rot="R90">
<attribute name="NAME" x="-88.9" y="71.12" size="1.778" layer="95" rot="R90" align="center"/>
<attribute name="VALUE" x="-83.82" y="71.12" size="1.778" layer="96" rot="R90" align="center"/>
</instance>
<instance part="Q2" gate="1" x="-66.04" y="66.04" smashed="yes">
<attribute name="NAME" x="-60.95805" y="68.58098125" size="1.77868125" layer="95"/>
<attribute name="VALUE" x="-60.952159375" y="66.04" size="1.78075" layer="96"/>
</instance>
<instance part="SUPPLY27" gate="G$1" x="-63.5" y="71.12" smashed="yes">
<attribute name="VALUE" x="-63.627" y="74.168" size="1.778" layer="96" align="bottom-center"/>
</instance>
<instance part="SUPPLY30" gate="G$1" x="-63.5" y="40.64" smashed="yes">
<attribute name="VALUE" x="-63.5" y="38.1" size="1.778" layer="96" align="center"/>
</instance>
<instance part="RB2" gate="G$1" x="-73.66" y="66.04" smashed="yes">
<attribute name="NAME" x="-73.66" y="68.58" size="1.778" layer="95" align="center"/>
<attribute name="VALUE" x="-73.66" y="63.5" size="1.778" layer="96" align="center"/>
</instance>
<instance part="TFT_SD_2" gate="A" x="-71.12" y="-38.1" smashed="yes">
<attribute name="NAME" x="-77.47" y="-24.765" size="1.778" layer="95"/>
<attribute name="VALUE" x="-77.47" y="-50.8" size="1.778" layer="96"/>
</instance>
<instance part="SUPPLY31" gate="G$1" x="-66.04" y="-45.72" smashed="yes">
<attribute name="VALUE" x="-66.04" y="-48.26" size="1.778" layer="96" align="center"/>
</instance>
<instance part="SUPPLY32" gate="G$1" x="-83.82" y="-45.72" smashed="yes">
<attribute name="VALUE" x="-83.947" y="-42.672" size="1.778" layer="96" align="bottom-center"/>
</instance>
<instance part="TFT_SD_1" gate="A" x="-40.64" y="-35.56" smashed="yes">
<attribute name="NAME" x="-46.99" y="-27.305" size="1.778" layer="95"/>
<attribute name="VALUE" x="-46.99" y="-43.18" size="1.778" layer="96"/>
</instance>
</instances>
<busses>
</busses>
<nets>
<net name="Z_EN" class="0">
<segment>
<pinref part="Z_DRV" gate="G$1" pin="!EN"/>
<wire x1="58.42" y1="-12.7" x2="55.88" y2="-12.7" width="0.1524" layer="91"/>
<label x="50.8" y="-12.7" size="1.778" layer="95"/>
</segment>
<segment>
<wire x1="-15.24" y1="43.18" x2="-17.78" y2="43.18" width="0.1524" layer="91"/>
<label x="-17.78" y="43.18" size="1.778" layer="95" rot="MR0"/>
<pinref part="U$1" gate="G$1" pin="PA10"/>
</segment>
</net>
<net name="Z_STEP" class="0">
<segment>
<pinref part="Z_DRV" gate="G$1" pin="STEP"/>
<wire x1="58.42" y1="-27.94" x2="55.88" y2="-27.94" width="0.1524" layer="91"/>
<label x="48.26" y="-27.94" size="1.778" layer="95"/>
</segment>
<segment>
<wire x1="-15.24" y1="45.72" x2="-17.78" y2="45.72" width="0.1524" layer="91"/>
<label x="-17.78" y="45.72" size="1.778" layer="95" rot="MR0"/>
<pinref part="U$1" gate="G$1" pin="PA9"/>
</segment>
</net>
<net name="Z_DIR" class="0">
<segment>
<pinref part="Z_DRV" gate="G$1" pin="DIR"/>
<wire x1="58.42" y1="-30.48" x2="55.88" y2="-30.48" width="0.1524" layer="91"/>
<label x="50.8" y="-30.48" size="1.778" layer="95"/>
</segment>
<segment>
<wire x1="-15.24" y1="48.26" x2="-17.78" y2="48.26" width="0.1524" layer="91"/>
<label x="-25.4" y="48.26" size="1.778" layer="95"/>
<pinref part="U$1" gate="G$1" pin="PA8"/>
</segment>
</net>
<net name="N$27" class="1">
<segment>
<pinref part="Z_DRV" gate="G$1" pin="1B"/>
<pinref part="Z_JST" gate="G$1" pin="4"/>
<wire x1="101.6" y1="-25.4" x2="83.82" y2="-25.4" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$28" class="1">
<segment>
<pinref part="Z_DRV" gate="G$1" pin="1A"/>
<wire x1="83.82" y1="-22.86" x2="101.6" y2="-22.86" width="0.1524" layer="91"/>
<pinref part="Z_JST" gate="G$1" pin="3"/>
</segment>
</net>
<net name="N$29" class="1">
<segment>
<pinref part="Z_DRV" gate="G$1" pin="2A"/>
<pinref part="Z_JST" gate="G$1" pin="2"/>
<wire x1="101.6" y1="-20.32" x2="83.82" y2="-20.32" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$30" class="1">
<segment>
<pinref part="Z_DRV" gate="G$1" pin="2B"/>
<pinref part="Z_JST" gate="G$1" pin="1"/>
<wire x1="101.6" y1="-17.78" x2="83.82" y2="-17.78" width="0.1524" layer="91"/>
</segment>
</net>
<net name="Y_EN" class="0">
<segment>
<pinref part="Y_DRV" gate="G$1" pin="!EN"/>
<wire x1="58.42" y1="22.86" x2="55.88" y2="22.86" width="0.1524" layer="91"/>
<label x="50.8" y="22.86" size="1.778" layer="95"/>
</segment>
<segment>
<wire x1="-15.24" y1="35.56" x2="-17.78" y2="35.56" width="0.1524" layer="91"/>
<label x="-17.78" y="35.56" size="1.778" layer="95" rot="MR0"/>
<pinref part="U$1" gate="G$1" pin="PA15"/>
</segment>
</net>
<net name="Y_STEP" class="0">
<segment>
<pinref part="Y_DRV" gate="G$1" pin="STEP"/>
<wire x1="58.42" y1="7.62" x2="55.88" y2="7.62" width="0.1524" layer="91"/>
<label x="48.26" y="7.62" size="1.778" layer="95"/>
</segment>
<segment>
<wire x1="-15.24" y1="38.1" x2="-17.78" y2="38.1" width="0.1524" layer="91"/>
<label x="-17.78" y="38.1" size="1.778" layer="95" rot="MR0"/>
<pinref part="U$1" gate="G$1" pin="PA12"/>
</segment>
</net>
<net name="Y_DIR" class="0">
<segment>
<pinref part="Y_DRV" gate="G$1" pin="DIR"/>
<wire x1="58.42" y1="5.08" x2="55.88" y2="5.08" width="0.1524" layer="91"/>
<label x="50.8" y="5.08" size="1.778" layer="95"/>
</segment>
<segment>
<wire x1="-15.24" y1="40.64" x2="-17.78" y2="40.64" width="0.1524" layer="91"/>
<label x="-17.78" y="40.64" size="1.778" layer="95" rot="MR0"/>
<pinref part="U$1" gate="G$1" pin="PA11"/>
</segment>
</net>
<net name="N$11" class="1">
<segment>
<pinref part="Y_DRV" gate="G$1" pin="1B"/>
<wire x1="83.82" y1="10.16" x2="101.6" y2="10.16" width="0.1524" layer="91"/>
<pinref part="Y_JST" gate="G$1" pin="4"/>
</segment>
</net>
<net name="N$12" class="1">
<segment>
<pinref part="Y_DRV" gate="G$1" pin="1A"/>
<pinref part="Y_JST" gate="G$1" pin="3"/>
<wire x1="101.6" y1="12.7" x2="83.82" y2="12.7" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$13" class="1">
<segment>
<pinref part="Y_DRV" gate="G$1" pin="2A"/>
<wire x1="83.82" y1="15.24" x2="101.6" y2="15.24" width="0.1524" layer="91"/>
<pinref part="Y_JST" gate="G$1" pin="2"/>
</segment>
</net>
<net name="N$14" class="1">
<segment>
<pinref part="Y_DRV" gate="G$1" pin="2B"/>
<pinref part="Y_JST" gate="G$1" pin="1"/>
<wire x1="101.6" y1="17.78" x2="83.82" y2="17.78" width="0.1524" layer="91"/>
</segment>
</net>
<net name="X_STEP" class="0">
<segment>
<pinref part="X_DRV" gate="G$1" pin="STEP"/>
<wire x1="58.42" y1="43.18" x2="55.88" y2="43.18" width="0.1524" layer="91"/>
<label x="48.26" y="43.18" size="1.778" layer="95"/>
</segment>
<segment>
<wire x1="-15.24" y1="30.48" x2="-17.78" y2="30.48" width="0.1524" layer="91"/>
<label x="-17.78" y="30.48" size="1.778" layer="95" rot="MR0"/>
<pinref part="U$1" gate="G$1" pin="PB4"/>
</segment>
</net>
<net name="X_DIR" class="0">
<segment>
<pinref part="X_DRV" gate="G$1" pin="DIR"/>
<wire x1="58.42" y1="40.64" x2="55.88" y2="40.64" width="0.1524" layer="91"/>
<label x="50.8" y="40.64" size="1.778" layer="95"/>
</segment>
<segment>
<wire x1="-15.24" y1="33.02" x2="-17.78" y2="33.02" width="0.1524" layer="91"/>
<label x="-17.78" y="33.02" size="1.778" layer="95" rot="MR0"/>
<pinref part="U$1" gate="G$1" pin="PB3"/>
</segment>
</net>
<net name="N$43" class="1">
<segment>
<pinref part="X_DRV" gate="G$1" pin="1B"/>
<wire x1="83.82" y1="45.72" x2="101.6" y2="45.72" width="0.1524" layer="91"/>
<pinref part="X_JST" gate="G$1" pin="4"/>
</segment>
</net>
<net name="N$44" class="1">
<segment>
<pinref part="X_DRV" gate="G$1" pin="1A"/>
<pinref part="X_JST" gate="G$1" pin="3"/>
<wire x1="101.6" y1="48.26" x2="83.82" y2="48.26" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$45" class="1">
<segment>
<pinref part="X_DRV" gate="G$1" pin="2A"/>
<pinref part="X_JST" gate="G$1" pin="2"/>
<wire x1="101.6" y1="50.8" x2="83.82" y2="50.8" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$46" class="1">
<segment>
<pinref part="X_DRV" gate="G$1" pin="2B"/>
<pinref part="X_JST" gate="G$1" pin="1"/>
<wire x1="101.6" y1="53.34" x2="83.82" y2="53.34" width="0.1524" layer="91"/>
</segment>
</net>
<net name="X_EN" class="0">
<segment>
<pinref part="X_DRV" gate="G$1" pin="!EN"/>
<wire x1="58.42" y1="58.42" x2="55.88" y2="58.42" width="0.1524" layer="91"/>
<label x="50.8" y="58.42" size="1.778" layer="95"/>
</segment>
<segment>
<wire x1="-15.24" y1="27.94" x2="-17.78" y2="27.94" width="0.1524" layer="91"/>
<label x="-17.78" y="27.94" size="1.778" layer="95" rot="MR0"/>
<pinref part="U$1" gate="G$1" pin="PB5"/>
</segment>
</net>
<net name="+3.3V" class="0">
<segment>
<pinref part="SUPPLY1" gate="G$1" pin="+3.3V"/>
<wire x1="48.26" y1="60.96" x2="48.26" y2="55.88" width="0.1524" layer="91"/>
<wire x1="48.26" y1="55.88" x2="55.88" y2="55.88" width="0.1524" layer="91"/>
<pinref part="X_DRV" gate="G$1" pin="MS1"/>
<pinref part="X_DRV" gate="G$1" pin="MS2"/>
<wire x1="55.88" y1="55.88" x2="58.42" y2="55.88" width="0.1524" layer="91"/>
<wire x1="58.42" y1="53.34" x2="55.88" y2="53.34" width="0.1524" layer="91"/>
<wire x1="55.88" y1="53.34" x2="55.88" y2="55.88" width="0.1524" layer="91"/>
<junction x="55.88" y="55.88"/>
<pinref part="X_DRV" gate="G$1" pin="MS3"/>
<wire x1="58.42" y1="50.8" x2="55.88" y2="50.8" width="0.1524" layer="91"/>
<wire x1="55.88" y1="50.8" x2="55.88" y2="53.34" width="0.1524" layer="91"/>
<junction x="55.88" y="53.34"/>
<pinref part="X_DRV" gate="G$1" pin="!RST"/>
<wire x1="58.42" y1="48.26" x2="55.88" y2="48.26" width="0.1524" layer="91"/>
<wire x1="55.88" y1="48.26" x2="55.88" y2="45.72" width="0.1524" layer="91"/>
<pinref part="X_DRV" gate="G$1" pin="!SLP"/>
<wire x1="58.42" y1="45.72" x2="55.88" y2="45.72" width="0.1524" layer="91"/>
<wire x1="55.88" y1="48.26" x2="55.88" y2="50.8" width="0.1524" layer="91"/>
<junction x="55.88" y="48.26"/>
<junction x="55.88" y="50.8"/>
</segment>
<segment>
<pinref part="X_DRV" gate="G$1" pin="VDD"/>
<wire x1="83.82" y1="43.18" x2="86.36" y2="43.18" width="0.1524" layer="91"/>
<wire x1="86.36" y1="43.18" x2="86.36" y2="38.1" width="0.1524" layer="91"/>
<wire x1="86.36" y1="38.1" x2="91.44" y2="38.1" width="0.1524" layer="91"/>
<pinref part="SUPPLY5" gate="G$1" pin="+3.3V"/>
</segment>
<segment>
<wire x1="83.82" y1="7.62" x2="86.36" y2="7.62" width="0.1524" layer="91"/>
<wire x1="86.36" y1="7.62" x2="86.36" y2="2.54" width="0.1524" layer="91"/>
<wire x1="86.36" y1="2.54" x2="91.44" y2="2.54" width="0.1524" layer="91"/>
<pinref part="SUPPLY7" gate="G$1" pin="+3.3V"/>
<pinref part="Y_DRV" gate="G$1" pin="VDD"/>
</segment>
<segment>
<wire x1="83.82" y1="-27.94" x2="86.36" y2="-27.94" width="0.1524" layer="91"/>
<wire x1="86.36" y1="-27.94" x2="86.36" y2="-33.02" width="0.1524" layer="91"/>
<wire x1="86.36" y1="-33.02" x2="91.44" y2="-33.02" width="0.1524" layer="91"/>
<pinref part="SUPPLY8" gate="G$1" pin="+3.3V"/>
<pinref part="Z_DRV" gate="G$1" pin="VDD"/>
</segment>
<segment>
<pinref part="SUPPLY16" gate="G$1" pin="+3.3V"/>
<wire x1="38.1" y1="58.42" x2="38.1" y2="53.34" width="0.1524" layer="91"/>
<wire x1="38.1" y1="53.34" x2="25.4" y2="53.34" width="0.1524" layer="91"/>
<pinref part="U$1" gate="G$1" pin="3.3V"/>
</segment>
<segment>
<wire x1="-7.62" y1="78.74" x2="-7.62" y2="81.28" width="0.1524" layer="91"/>
<pinref part="SUPPLY23" gate="G$1" pin="+3.3V"/>
<wire x1="2.54" y1="78.74" x2="-7.62" y2="78.74" width="0.1524" layer="91"/>
<pinref part="PROBE" gate="G$1" pin="1"/>
</segment>
<segment>
<pinref part="SUPPLY18" gate="G$1" pin="+3.3V"/>
<pinref part="C_VDD" gate="G$1" pin="+"/>
</segment>
<segment>
<pinref part="SUPPLY11" gate="G$1" pin="+3.3V"/>
<wire x1="48.26" y1="27.94" x2="48.26" y2="20.32" width="0.1524" layer="91"/>
<pinref part="Y_DRV" gate="G$1" pin="MS3"/>
<pinref part="Y_DRV" gate="G$1" pin="MS2"/>
<pinref part="Y_DRV" gate="G$1" pin="MS1"/>
<wire x1="48.26" y1="20.32" x2="55.88" y2="20.32" width="0.1524" layer="91"/>
<wire x1="55.88" y1="20.32" x2="58.42" y2="20.32" width="0.1524" layer="91"/>
<wire x1="58.42" y1="17.78" x2="55.88" y2="17.78" width="0.1524" layer="91"/>
<wire x1="55.88" y1="17.78" x2="55.88" y2="20.32" width="0.1524" layer="91"/>
<wire x1="58.42" y1="15.24" x2="55.88" y2="15.24" width="0.1524" layer="91"/>
<wire x1="55.88" y1="15.24" x2="55.88" y2="17.78" width="0.1524" layer="91"/>
<pinref part="Y_DRV" gate="G$1" pin="!RST"/>
<wire x1="55.88" y1="12.7" x2="55.88" y2="10.16" width="0.1524" layer="91"/>
<pinref part="Y_DRV" gate="G$1" pin="!SLP"/>
<wire x1="58.42" y1="10.16" x2="55.88" y2="10.16" width="0.1524" layer="91"/>
<wire x1="58.42" y1="12.7" x2="55.88" y2="12.7" width="0.1524" layer="91"/>
<wire x1="55.88" y1="12.7" x2="55.88" y2="15.24" width="0.1524" layer="91"/>
<junction x="55.88" y="20.32"/>
<junction x="55.88" y="17.78"/>
<junction x="55.88" y="15.24"/>
<junction x="55.88" y="12.7"/>
</segment>
<segment>
<pinref part="SUPPLY15" gate="G$1" pin="+3.3V"/>
<wire x1="48.26" y1="-10.16" x2="48.26" y2="-15.24" width="0.1524" layer="91"/>
<wire x1="48.26" y1="-15.24" x2="55.88" y2="-15.24" width="0.1524" layer="91"/>
<pinref part="Z_DRV" gate="G$1" pin="!SLP"/>
<wire x1="58.42" y1="-25.4" x2="55.88" y2="-25.4" width="0.1524" layer="91"/>
<wire x1="55.88" y1="-25.4" x2="55.88" y2="-22.86" width="0.1524" layer="91"/>
<pinref part="Z_DRV" gate="G$1" pin="!RST"/>
<wire x1="58.42" y1="-22.86" x2="55.88" y2="-22.86" width="0.1524" layer="91"/>
<wire x1="55.88" y1="-22.86" x2="55.88" y2="-20.32" width="0.1524" layer="91"/>
<pinref part="Z_DRV" gate="G$1" pin="MS3"/>
<wire x1="58.42" y1="-20.32" x2="55.88" y2="-20.32" width="0.1524" layer="91"/>
<wire x1="55.88" y1="-20.32" x2="55.88" y2="-17.78" width="0.1524" layer="91"/>
<pinref part="Z_DRV" gate="G$1" pin="MS1"/>
<wire x1="58.42" y1="-15.24" x2="55.88" y2="-15.24" width="0.1524" layer="91"/>
<wire x1="55.88" y1="-15.24" x2="55.88" y2="-17.78" width="0.1524" layer="91"/>
<pinref part="Z_DRV" gate="G$1" pin="MS2"/>
<wire x1="58.42" y1="-17.78" x2="55.88" y2="-17.78" width="0.1524" layer="91"/>
<junction x="55.88" y="-17.78"/>
<junction x="55.88" y="-20.32"/>
<junction x="55.88" y="-22.86"/>
<junction x="55.88" y="-15.24"/>
</segment>
<segment>
<pinref part="U$1" gate="G$1" pin="3.3V1"/>
<wire x1="-15.24" y1="10.16" x2="-15.24" y2="5.08" width="0.1524" layer="91"/>
<wire x1="-15.24" y1="5.08" x2="-20.32" y2="5.08" width="0.1524" layer="91"/>
<pinref part="SUPPLY28" gate="G$1" pin="+3.3V"/>
</segment>
<segment>
<wire x1="-73.66" y1="-45.72" x2="-83.82" y2="-45.72" width="0.1524" layer="91"/>
<pinref part="SUPPLY32" gate="G$1" pin="+3.3V"/>
<pinref part="TFT_SD_2" gate="A" pin="8"/>
</segment>
</net>
<net name="+24V" class="1">
<segment>
<pinref part="SUPPLY4" gate="G$1" pin="+5V"/>
<pinref part="Z_DRV" gate="G$1" pin="VMOT"/>
<wire x1="83.82" y1="-12.7" x2="88.9" y2="-12.7" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="SUPPLY3" gate="G$1" pin="+5V"/>
<pinref part="Y_DRV" gate="G$1" pin="VMOT"/>
<wire x1="83.82" y1="22.86" x2="88.9" y2="22.86" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="SUPPLY2" gate="G$1" pin="+5V"/>
<pinref part="X_DRV" gate="G$1" pin="VMOT"/>
<wire x1="83.82" y1="58.42" x2="88.9" y2="58.42" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="SUPPLY19" gate="G$1" pin="+3.3V"/>
<pinref part="C_VMOT" gate="G$1" pin="+"/>
<wire x1="-7.62" y1="-2.54" x2="-17.78" y2="-2.54" width="0.1524" layer="91"/>
<junction x="-7.62" y="-2.54"/>
<wire x1="-17.78" y1="-2.54" x2="-17.78" y2="-5.08" width="0.1524" layer="91"/>
<pinref part="24V" gate="G$1" pin="2"/>
</segment>
<segment>
<pinref part="RB1" gate="G$1" pin="2"/>
<pinref part="SUPPLY26" gate="G$1" pin="+5V"/>
</segment>
<segment>
<pinref part="SUPPLY27" gate="G$1" pin="+5V"/>
<pinref part="Q2" gate="1" pin="E"/>
</segment>
</net>
<net name="GND" class="0">
<segment>
<pinref part="X_DRV" gate="G$1" pin="GND1"/>
<wire x1="83.82" y1="40.64" x2="83.82" y2="35.56" width="0.1524" layer="91"/>
<wire x1="83.82" y1="35.56" x2="96.52" y2="35.56" width="0.1524" layer="91"/>
<pinref part="SUPPLY6" gate="G$1" pin="GND"/>
</segment>
<segment>
<wire x1="83.82" y1="5.08" x2="83.82" y2="0" width="0.1524" layer="91"/>
<wire x1="83.82" y1="0" x2="96.52" y2="0" width="0.1524" layer="91"/>
<pinref part="SUPPLY9" gate="G$1" pin="GND"/>
<pinref part="Y_DRV" gate="G$1" pin="GND1"/>
</segment>
<segment>
<wire x1="83.82" y1="-30.48" x2="83.82" y2="-35.56" width="0.1524" layer="91"/>
<wire x1="83.82" y1="-35.56" x2="96.52" y2="-35.56" width="0.1524" layer="91"/>
<pinref part="SUPPLY10" gate="G$1" pin="GND"/>
<pinref part="Z_DRV" gate="G$1" pin="GND1"/>
</segment>
<segment>
<pinref part="X_DRV" gate="G$1" pin="GND2"/>
<wire x1="83.82" y1="55.88" x2="93.98" y2="55.88" width="0.1524" layer="91"/>
<wire x1="93.98" y1="55.88" x2="93.98" y2="60.96" width="0.1524" layer="91"/>
<wire x1="93.98" y1="60.96" x2="96.52" y2="60.96" width="0.1524" layer="91"/>
<pinref part="SUPPLY12" gate="G$1" pin="GND"/>
</segment>
<segment>
<wire x1="83.82" y1="-15.24" x2="93.98" y2="-15.24" width="0.1524" layer="91"/>
<wire x1="93.98" y1="-15.24" x2="93.98" y2="-10.16" width="0.1524" layer="91"/>
<wire x1="93.98" y1="-10.16" x2="96.52" y2="-10.16" width="0.1524" layer="91"/>
<pinref part="SUPPLY14" gate="G$1" pin="GND"/>
<pinref part="Z_DRV" gate="G$1" pin="GND2"/>
</segment>
<segment>
<pinref part="U$1" gate="G$1" pin="GND"/>
<wire x1="25.4" y1="55.88" x2="30.48" y2="55.88" width="0.1524" layer="91"/>
<wire x1="30.48" y1="55.88" x2="30.48" y2="60.96" width="0.1524" layer="91"/>
<wire x1="30.48" y1="60.96" x2="33.02" y2="60.96" width="0.1524" layer="91"/>
<pinref part="SUPPLY17" gate="G$1" pin="GND"/>
<pinref part="U$1" gate="G$1" pin="GND1"/>
<wire x1="25.4" y1="58.42" x2="25.4" y2="55.88" width="0.1524" layer="91"/>
<junction x="25.4" y="55.88"/>
</segment>
<segment>
<pinref part="SUPPLY21" gate="G$1" pin="GND"/>
<pinref part="C_VDD" gate="G$1" pin="-"/>
</segment>
<segment>
<pinref part="Y_DRV" gate="G$1" pin="GND2"/>
<wire x1="83.82" y1="20.32" x2="93.98" y2="20.32" width="0.1524" layer="91"/>
<wire x1="93.98" y1="20.32" x2="93.98" y2="25.4" width="0.1524" layer="91"/>
<wire x1="93.98" y1="25.4" x2="96.52" y2="25.4" width="0.1524" layer="91"/>
<pinref part="SUPPLY13" gate="G$1" pin="GND"/>
</segment>
<segment>
<pinref part="C_PROBE" gate="G$1" pin="-"/>
<wire x1="-17.78" y1="66.04" x2="-17.78" y2="68.58" width="0.1524" layer="91"/>
<pinref part="SUPPLY22" gate="G$1" pin="GND"/>
<junction x="-17.78" y="66.04"/>
</segment>
<segment>
<pinref part="SUPPLY20" gate="G$1" pin="GND"/>
<pinref part="C_VMOT" gate="G$1" pin="-"/>
<pinref part="24V" gate="G$1" pin="1"/>
<wire x1="-17.78" y1="-7.62" x2="-17.78" y2="-10.16" width="0.1524" layer="91"/>
<wire x1="-17.78" y1="-10.16" x2="-7.62" y2="-10.16" width="0.1524" layer="91"/>
<junction x="-7.62" y="-10.16"/>
</segment>
<segment>
<pinref part="U$1" gate="G$1" pin="GND2"/>
<wire x1="-15.24" y1="12.7" x2="-27.94" y2="12.7" width="0.1524" layer="91"/>
<wire x1="-27.94" y1="12.7" x2="-27.94" y2="10.16" width="0.1524" layer="91"/>
<pinref part="SUPPLY29" gate="G$1" pin="GND"/>
</segment>
<segment>
<pinref part="Q1" gate="G$1" pin="E"/>
<pinref part="SUPPLY25" gate="G$1" pin="GND"/>
</segment>
<segment>
<pinref part="SPINDLE" gate="G$1" pin="1"/>
<wire x1="-60.96" y1="55.88" x2="-63.5" y2="55.88" width="0.1524" layer="91"/>
<wire x1="-63.5" y1="55.88" x2="-63.5" y2="43.18" width="0.1524" layer="91"/>
<pinref part="SUPPLY30" gate="G$1" pin="GND"/>
<pinref part="R1" gate="G$1" pin="1"/>
<wire x1="-71.12" y1="43.18" x2="-63.5" y2="43.18" width="0.1524" layer="91"/>
<junction x="-63.5" y="43.18"/>
</segment>
<segment>
<pinref part="SUPPLY31" gate="G$1" pin="GND"/>
<wire x1="-66.04" y1="-43.18" x2="-73.66" y2="-43.18" width="0.1524" layer="91"/>
<pinref part="TFT_SD_2" gate="A" pin="7"/>
</segment>
</net>
<net name="PROBE_IN" class="0">
<segment>
<wire x1="-17.78" y1="76.2" x2="-17.78" y2="73.66" width="0.1524" layer="91"/>
<pinref part="C_PROBE" gate="G$1" pin="+"/>
<label x="-25.4" y="76.2" size="1.778" layer="95"/>
<wire x1="2.54" y1="76.2" x2="-17.78" y2="76.2" width="0.1524" layer="91"/>
<pinref part="PROBE" gate="G$1" pin="2"/>
</segment>
<segment>
<wire x1="25.4" y1="17.78" x2="27.94" y2="17.78" width="0.1524" layer="91"/>
<label x="27.94" y="17.78" size="1.778" layer="95"/>
<pinref part="U$1" gate="G$1" pin="PC15"/>
</segment>
</net>
<net name="SPINDLE_PWM" class="0">
<segment>
<pinref part="RB" gate="G$1" pin="1"/>
<wire x1="-101.6" y1="60.96" x2="-104.14" y2="60.96" width="0.1524" layer="91"/>
<label x="-121.92" y="60.96" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="U$1" gate="G$1" pin="PB8"/>
<wire x1="-15.24" y1="20.32" x2="-22.86" y2="20.32" width="0.1524" layer="91"/>
<label x="-38.1" y="20.32" size="1.778" layer="95"/>
</segment>
</net>
<net name="SD_CS" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="PB0"/>
<wire x1="25.4" y1="40.64" x2="27.94" y2="40.64" width="0.1524" layer="91"/>
<label x="27.94" y="40.64" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="TFT_SD_1" gate="A" pin="1"/>
<wire x1="-43.18" y1="-30.48" x2="-35.56" y2="-30.48" width="0.1524" layer="91"/>
<label x="-35.56" y="-30.48" size="1.778" layer="95"/>
</segment>
</net>
<net name="SPI_MOSI" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="PA7"/>
<wire x1="25.4" y1="38.1" x2="27.94" y2="38.1" width="0.1524" layer="91"/>
<label x="27.94" y="38.1" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="TFT_SD_1" gate="A" pin="2"/>
<wire x1="-43.18" y1="-33.02" x2="-35.56" y2="-33.02" width="0.1524" layer="91"/>
<label x="-35.56" y="-33.02" size="1.778" layer="95"/>
</segment>
</net>
<net name="SPI_MISO" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="PA6"/>
<wire x1="25.4" y1="35.56" x2="27.94" y2="35.56" width="0.1524" layer="91"/>
<label x="27.94" y="35.56" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="TFT_SD_1" gate="A" pin="3"/>
<wire x1="-43.18" y1="-35.56" x2="-35.56" y2="-35.56" width="0.1524" layer="91"/>
<label x="-35.56" y="-35.56" size="1.778" layer="95"/>
</segment>
</net>
<net name="SPI_CLK" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="PA5"/>
<wire x1="25.4" y1="33.02" x2="27.94" y2="33.02" width="0.1524" layer="91"/>
<label x="27.94" y="33.02" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="TFT_SD_1" gate="A" pin="4"/>
<wire x1="-43.18" y1="-38.1" x2="-35.56" y2="-38.1" width="0.1524" layer="91"/>
<label x="-35.56" y="-38.1" size="1.778" layer="95"/>
</segment>
</net>
<net name="N$6" class="1">
<segment>
<pinref part="D1" gate="1" pin="A"/>
<pinref part="R1" gate="G$1" pin="2"/>
</segment>
</net>
<net name="N$4" class="0">
<segment>
<pinref part="RB" gate="G$1" pin="2"/>
<pinref part="Q1" gate="G$1" pin="B"/>
</segment>
</net>
<net name="N$5" class="0">
<segment>
<pinref part="Q1" gate="G$1" pin="C"/>
<pinref part="RB1" gate="G$1" pin="1"/>
<pinref part="RB2" gate="G$1" pin="1"/>
<wire x1="-78.74" y1="66.04" x2="-86.36" y2="66.04" width="0.1524" layer="91"/>
<junction x="-86.36" y="66.04"/>
</segment>
</net>
<net name="N$7" class="0">
<segment>
<pinref part="Q2" gate="1" pin="C"/>
<wire x1="-63.5" y1="60.96" x2="-63.5" y2="58.42" width="0.1524" layer="91"/>
<wire x1="-63.5" y1="58.42" x2="-60.96" y2="58.42" width="0.1524" layer="91"/>
<pinref part="SPINDLE" gate="G$1" pin="2"/>
<wire x1="-63.5" y1="58.42" x2="-71.12" y2="58.42" width="0.1524" layer="91"/>
<junction x="-63.5" y="58.42"/>
<pinref part="D1" gate="1" pin="C"/>
</segment>
</net>
<net name="N$8" class="0">
<segment>
<pinref part="Q2" gate="1" pin="B"/>
<pinref part="RB2" gate="G$1" pin="2"/>
</segment>
</net>
</nets>
</sheet>
</sheets>
</schematic>
</drawing>
<compatibility>
<note version="8.2" severity="warning">
Since Version 8.2, EAGLE supports online libraries. The ids
of those online libraries will not be understood (or retained)
with this version.
</note>
<note version="8.3" severity="warning">
Since Version 8.3, EAGLE supports URNs for individual library
assets (packages, symbols, and devices). The URNs of those assets
will not be understood (or retained) with this version.
</note>
<note version="8.3" severity="warning">
Since Version 8.3, EAGLE supports the association of 3D packages
with devices in libraries, schematics, and board files. Those 3D
packages will not be understood (or retained) with this version.
</note>
<note version="8.4" severity="warning">
Since Version 8.4, EAGLE supports properties for SPICE simulation. 
Probes in schematics and SPICE mapping objects found in parts and library devices
will not be understood with this version. Update EAGLE to the latest version
for full support of SPICE simulation. 
</note>
</compatibility>
</eagle>

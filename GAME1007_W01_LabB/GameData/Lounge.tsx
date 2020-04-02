<?xml version="1.0" encoding="UTF-8"?>
<tileset version="1.2" tiledversion="1.3.1" name="Lounge" tilewidth="32" tileheight="32" tilecount="64" columns="1" backgroundcolor="#000000">
 <editorsettings>
  <export target="Lounge.tsx" format="tsx"/>
 </editorsettings>
 <tile id="0" type="BackgroundTile">
  <properties>
   <property name="drag" type="float" value="0.95"/>
   <property name="force_x" type="float" value="0"/>
   <property name="force_y" type="float" value="0.5"/>
   <property name="jumpforce_x" type="float" value="0"/>
   <property name="jumpforce_y" type="float" value="-0.75"/>
   <property name="jumpforcemax" type="float" value="-10"/>
   <property name="maxdrag" type="float" value="0.5"/>
   <property name="maxspeed" type="float" value="25"/>
  </properties>
  <image width="32" height="32" source="../../Assets/Textures/BGTile3.png"/>
 </tile>
 <tile id="1" type="BackgroundTile">
  <properties>
   <property name="drag" type="float" value="0.95"/>
   <property name="force_x" type="float" value="0"/>
   <property name="force_y" type="float" value="0.5"/>
   <property name="jumpforce_x" type="float" value="0"/>
   <property name="jumpforce_y" type="float" value="-0.75"/>
   <property name="jumpforcemax" type="float" value="-10"/>
   <property name="maxdrag" type="float" value="0.5"/>
   <property name="maxspeed" type="float" value="25"/>
  </properties>
  <image width="32" height="32" source="../../Assets/Textures/Window.png"/>
 </tile>
 <tile id="2" type="InteractiveTile">
  <properties>
   <property name="interactiontype" type="int" value="1"/>
  </properties>
  <image width="32" height="32" source="../../Assets/Textures/DoorBottom_1.png"/>
  <objectgroup draworder="index" id="2">
   <object id="1" x="0" y="-32" width="32" height="64"/>
  </objectgroup>
 </tile>
 <tile id="3" type="InteractiveTile">
  <properties>
   <property name="interactiontype" type="int" value="2"/>
  </properties>
  <image width="32" height="32" source="../../Assets/Textures/DoorBottom_2.png"/>
  <objectgroup draworder="index" id="2">
   <object id="1" x="0" y="-32" width="32" height="64"/>
  </objectgroup>
 </tile>
 <tile id="4" type="InteractiveTile">
  <properties>
   <property name="interactiontype" type="int" value="0"/>
  </properties>
  <image width="32" height="32" source="../../Assets/Textures/DoorBottom_3.png"/>
  <objectgroup draworder="index" id="2">
   <object id="1" x="0" y="-32" width="32" height="64"/>
  </objectgroup>
 </tile>
 <tile id="5" type="InteractiveTile">
  <properties>
   <property name="interactiontype" type="int" value="0"/>
  </properties>
  <image width="32" height="32" source="../../Assets/Textures/DoorBottom_4.png"/>
  <objectgroup draworder="index" id="2">
   <object id="1" x="0" y="-32" width="32" height="64"/>
  </objectgroup>
 </tile>
 <tile id="6" type="InteractiveTile">
  <properties>
   <property name="animateoninteraction" type="bool" value="true"/>
   <property name="interactiontype" type="int" value="1"/>
  </properties>
  <image width="32" height="32" source="../../Assets/Textures/DoorBottom_1.png"/>
  <objectgroup draworder="index" id="2">
   <object id="1" x="0" y="-32" width="32" height="64"/>
  </objectgroup>
  <animation>
   <frame tileid="5" duration="500"/>
   <frame tileid="4" duration="500"/>
   <frame tileid="3" duration="500"/>
   <frame tileid="2" duration="0"/>
  </animation>
 </tile>
 <tile id="7" type="InteractiveTile">
  <properties>
   <property name="animateoninteraction" type="bool" value="true"/>
   <property name="interactiontype" type="int" value="2"/>
  </properties>
  <image width="32" height="32" source="../../Assets/Textures/DoorBottom_2.png"/>
  <objectgroup draworder="index" id="2">
   <object id="1" x="0" y="-32" width="32" height="64"/>
  </objectgroup>
  <animation>
   <frame tileid="3" duration="500"/>
   <frame tileid="4" duration="500"/>
   <frame tileid="5" duration="0"/>
  </animation>
 </tile>
 <tile id="8" type="InteractiveTile">
  <properties>
   <property name="interactiontype" type="int" value="0"/>
  </properties>
  <image width="32" height="32" source="../../Assets/Textures/DoorTop_1.png"/>
  <objectgroup draworder="index" id="2">
   <object id="1" x="0" y="0" width="32" height="32"/>
  </objectgroup>
 </tile>
 <tile id="9" type="InteractiveTile">
  <properties>
   <property name="interactiontype" type="int" value="0"/>
  </properties>
  <image width="32" height="32" source="../../Assets/Textures/DoorTop_2.png"/>
  <objectgroup draworder="index" id="2">
   <object id="1" x="0" y="0" width="32" height="32"/>
  </objectgroup>
 </tile>
 <tile id="10" type="InteractiveTile">
  <properties>
   <property name="interactiontype" type="int" value="0"/>
  </properties>
  <image width="32" height="32" source="../../Assets/Textures/DoorTop_3.png"/>
  <objectgroup draworder="index" id="2">
   <object id="1" x="0" y="0" width="32" height="32"/>
  </objectgroup>
 </tile>
 <tile id="11" type="InteractiveTile">
  <properties>
   <property name="interactiontype" type="int" value="0"/>
  </properties>
  <image width="32" height="32" source="../../Assets/Textures/DoorTop_4.png"/>
  <objectgroup draworder="index" id="2">
   <object id="1" x="0" y="0" width="32" height="32"/>
  </objectgroup>
 </tile>
 <tile id="12" type="InteractiveTile">
  <properties>
   <property name="animateoninteraction" type="bool" value="true"/>
   <property name="interactiontype" type="int" value="0"/>
  </properties>
  <image width="32" height="32" source="../../Assets/Textures/DoorTop_1.png"/>
  <objectgroup draworder="index" id="2">
   <object id="1" x="0" y="0" width="32" height="32"/>
  </objectgroup>
  <animation>
   <frame tileid="11" duration="500"/>
   <frame tileid="10" duration="500"/>
   <frame tileid="9" duration="500"/>
   <frame tileid="8" duration="0"/>
  </animation>
 </tile>
 <tile id="13" type="InteractiveTile">
  <properties>
   <property name="animateoninteraction" type="bool" value="true"/>
   <property name="interactiontype" type="int" value="0"/>
  </properties>
  <image width="32" height="32" source="../../Assets/Textures/DoorTop_2.png"/>
  <objectgroup draworder="index" id="2">
   <object id="1" x="0" y="0" width="32" height="32"/>
  </objectgroup>
  <animation>
   <frame tileid="9" duration="500"/>
   <frame tileid="10" duration="500"/>
   <frame tileid="11" duration="0"/>
  </animation>
 </tile>
 <tile id="14" type="StaticTile">
  <properties>
   <property name="drag" type="float" value="0.5"/>
   <property name="force_x" type="float" value="0"/>
   <property name="force_y" type="float" value="0"/>
   <property name="interactiontype" type="int" value="1"/>
   <property name="jumpimpulse_x" type="float" value="0"/>
   <property name="jumpimpulse_y" type="float" value="-12"/>
   <property name="maxdrag" type="float" value="0.25"/>
   <property name="maxspeed" type="float" value="5"/>
  </properties>
  <image width="32" height="32" source="../../Assets/Textures/Tile5.png"/>
  <objectgroup draworder="index" id="2">
   <object id="1" x="0" y="0" width="32" height="32"/>
  </objectgroup>
 </tile>
 <tile id="15" type="StaticTile">
  <properties>
   <property name="drag" type="float" value="0.5"/>
   <property name="force_x" type="float" value="0"/>
   <property name="force_y" type="float" value="0"/>
   <property name="interactiontype" type="int" value="1"/>
   <property name="jumpimpulse_x" type="float" value="0"/>
   <property name="jumpimpulse_y" type="float" value="-12"/>
   <property name="maxdrag" type="float" value="0.25"/>
   <property name="maxspeed" type="float" value="5"/>
  </properties>
  <image width="32" height="32" source="../../Assets/Textures/Tile1.png"/>
  <objectgroup draworder="index" id="2">
   <object id="1" x="0" y="0" width="32" height="32"/>
  </objectgroup>
 </tile>
 <tile id="16" type="StaticTile">
  <properties>
   <property name="drag" type="float" value="0.5"/>
   <property name="force_x" type="float" value="0"/>
   <property name="force_y" type="float" value="0"/>
   <property name="interactiontype" type="int" value="1"/>
   <property name="jumpimpulse_x" type="float" value="0"/>
   <property name="jumpimpulse_y" type="float" value="-12"/>
   <property name="maxdrag" type="float" value="0.25"/>
   <property name="maxspeed" type="float" value="5"/>
  </properties>
  <image width="32" height="32" source="../../Assets/Textures/Tile2.png"/>
  <objectgroup draworder="index" id="2">
   <object id="1" x="0" y="0" width="32" height="32"/>
  </objectgroup>
 </tile>
 <tile id="17" type="StaticTile">
  <properties>
   <property name="drag" type="float" value="0.5"/>
   <property name="force_x" type="float" value="0"/>
   <property name="force_y" type="float" value="0"/>
   <property name="interactiontype" type="int" value="1"/>
   <property name="jumpimpulse_x" type="float" value="0"/>
   <property name="jumpimpulse_y" type="float" value="-12"/>
   <property name="maxdrag" type="float" value="0.25"/>
   <property name="maxspeed" type="float" value="5"/>
  </properties>
  <image width="32" height="32" source="../../Assets/Textures/Tile3.png"/>
  <objectgroup draworder="index" id="2">
   <object id="1" x="0" y="0" width="32" height="32"/>
  </objectgroup>
 </tile>
 <tile id="18" type="StaticTile">
  <properties>
   <property name="drag" type="float" value="0.5"/>
   <property name="force_x" type="float" value="0"/>
   <property name="force_y" type="float" value="0"/>
   <property name="interactiontype" type="int" value="2"/>
   <property name="jumpimpulse_x" type="float" value="0"/>
   <property name="jumpimpulse_y" type="float" value="-12"/>
   <property name="maxdrag" type="float" value="0.25"/>
   <property name="maxspeed" type="float" value="5"/>
  </properties>
  <image width="32" height="32" source="../../Assets/Textures/Tile12.png"/>
  <objectgroup draworder="index" id="2">
   <object id="1" x="0" y="0" width="32" height="16"/>
  </objectgroup>
 </tile>
 <tile id="19" type="StaticTile">
  <properties>
   <property name="drag" type="float" value="0.5"/>
   <property name="force_x" type="float" value="0"/>
   <property name="force_y" type="float" value="0"/>
   <property name="interactiontype" type="int" value="2"/>
   <property name="jumpimpulse_x" type="float" value="0"/>
   <property name="jumpimpulse_y" type="float" value="-12"/>
   <property name="maxdrag" type="float" value="0.25"/>
   <property name="maxspeed" type="float" value="5"/>
  </properties>
  <image width="32" height="32" source="../../Assets/Textures/Tile13.png"/>
  <objectgroup draworder="index" id="2">
   <object id="1" x="0" y="0" width="32" height="16"/>
  </objectgroup>
 </tile>
 <tile id="20" type="StaticTile">
  <properties>
   <property name="drag" type="float" value="0.5"/>
   <property name="force_x" type="float" value="0"/>
   <property name="force_y" type="float" value="0"/>
   <property name="interactiontype" type="int" value="2"/>
   <property name="jumpimpulse_x" type="float" value="0"/>
   <property name="jumpimpulse_y" type="float" value="-12"/>
   <property name="maxdrag" type="float" value="0.25"/>
   <property name="maxspeed" type="float" value="5"/>
  </properties>
  <image width="32" height="32" source="../../Assets/Textures/Tile14.png"/>
  <objectgroup draworder="index" id="2">
   <object id="1" x="0" y="0" width="32" height="16"/>
  </objectgroup>
 </tile>
 <tile id="21" type="StaticTile">
  <properties>
   <property name="drag" type="float" value="0.5"/>
   <property name="force_x" type="float" value="0"/>
   <property name="force_y" type="float" value="0"/>
   <property name="interactiontype" type="int" value="2"/>
   <property name="jumpimpulse_x" type="float" value="0"/>
   <property name="jumpimpulse_y" type="float" value="-12"/>
   <property name="maxdrag" type="float" value="0.25"/>
   <property name="maxspeed" type="float" value="5"/>
  </properties>
  <image width="32" height="32" source="../../Assets/Textures/Tile15.png"/>
  <objectgroup draworder="index" id="2">
   <object id="1" x="0" y="0" width="32" height="16"/>
  </objectgroup>
 </tile>
 <tile id="22" type="StaticTile">
  <properties>
   <property name="drag" type="float" value="0.5"/>
   <property name="force_x" type="float" value="0"/>
   <property name="force_y" type="float" value="0"/>
   <property name="interactiontype" type="int" value="1"/>
   <property name="jumpimpulse_x" type="float" value="0"/>
   <property name="jumpimpulse_y" type="float" value="-12"/>
   <property name="maxdrag" type="float" value="0.25"/>
   <property name="maxspeed" type="float" value="5"/>
  </properties>
  <image width="32" height="32" source="../../Assets/Textures/Box.png"/>
  <objectgroup draworder="index" id="2">
   <object id="1" x="0" y="0" width="32" height="32"/>
  </objectgroup>
 </tile>
 <tile id="23" type="InteractiveTile">
  <properties>
   <property name="interactiontype" value="3"/>
  </properties>
  <image width="32" height="32" source="../../Assets/Textures/Acid1.png"/>
  <objectgroup draworder="index" id="2">
   <object id="1" x="0" y="16" width="32" height="16"/>
  </objectgroup>
 </tile>
 <tile id="24" type="InteractiveTile">
  <properties>
   <property name="interactiontype" value="3"/>
  </properties>
  <image width="32" height="32" source="../../Assets/Textures/Acid2.png"/>
  <objectgroup draworder="index" id="2">
   <object id="1" x="0" y="0" width="32" height="32"/>
  </objectgroup>
 </tile>
 <tile id="25" type="InteractiveTile">
  <properties>
   <property name="interactiontype" value="3"/>
  </properties>
  <image width="32" height="32" source="../../Assets/Textures/Spike_Up_1.png"/>
  <objectgroup draworder="index" id="2">
   <object id="2" x="8" y="24" width="16" height="8"/>
  </objectgroup>
 </tile>
 <tile id="26" type="InteractiveTile">
  <properties>
   <property name="interactiontype" value="3"/>
  </properties>
  <image width="32" height="32" source="../../Assets/Textures/Spike_Up_2.png"/>
 </tile>
 <tile id="27" type="InteractiveTile">
  <properties>
   <property name="interactiontype" value="3"/>
  </properties>
  <image width="32" height="32" source="../../Assets/Textures/Spike_Up_3.png"/>
 </tile>
 <tile id="28" type="InteractiveTile">
  <properties>
   <property name="interactiontype" type="int" value="3"/>
  </properties>
  <image width="32" height="32" source="../../Assets/Textures/Spike_Up_1.png"/>
  <objectgroup draworder="index" id="2">
   <object id="2" x="8" y="24" width="16" height="8"/>
  </objectgroup>
  <animation>
   <frame tileid="25" duration="500"/>
   <frame tileid="26" duration="500"/>
   <frame tileid="27" duration="500"/>
   <frame tileid="26" duration="500"/>
  </animation>
 </tile>
 <tile id="29" type="InteractiveTile">
  <properties>
   <property name="interactiontype" type="int" value="3"/>
  </properties>
  <image width="32" height="32" source="../../Assets/Textures/Spike_Up_2.png"/>
  <objectgroup draworder="index" id="2">
   <object id="2" x="8" y="24" width="16" height="8"/>
  </objectgroup>
  <animation>
   <frame tileid="26" duration="500"/>
   <frame tileid="27" duration="500"/>
   <frame tileid="26" duration="500"/>
   <frame tileid="25" duration="500"/>
  </animation>
 </tile>
 <tile id="30" type="InteractiveTile">
  <properties>
   <property name="interactiontype" value="3"/>
  </properties>
  <image width="32" height="32" source="../../Assets/Textures/Spike_Up_3.png"/>
  <objectgroup draworder="index" id="2">
   <object id="2" x="8" y="24" width="16" height="8"/>
  </objectgroup>
  <animation>
   <frame tileid="27" duration="500"/>
   <frame tileid="26" duration="500"/>
   <frame tileid="25" duration="500"/>
   <frame tileid="26" duration="500"/>
  </animation>
 </tile>
 <tile id="31" type="InteractiveTile">
  <properties>
   <property name="interactiontype" value="3"/>
  </properties>
  <image width="32" height="32" source="../../Assets/Textures/Spike_Up_2.png"/>
  <objectgroup draworder="index" id="2">
   <object id="2" x="8" y="24" width="16" height="8"/>
  </objectgroup>
  <animation>
   <frame tileid="26" duration="500"/>
   <frame tileid="25" duration="500"/>
   <frame tileid="26" duration="500"/>
   <frame tileid="27" duration="500"/>
  </animation>
 </tile>
 <tile id="32" type="InteractiveTile">
  <properties>
   <property name="interactiontype" value="3"/>
  </properties>
  <image width="32" height="32" source="../../Assets/Textures/Spike_Right_1.png"/>
  <objectgroup draworder="index" id="2">
   <object id="1" x="0" y="8" width="8" height="16"/>
  </objectgroup>
 </tile>
 <tile id="33" type="InteractiveTile">
  <properties>
   <property name="interactiontype" value="3"/>
  </properties>
  <image width="32" height="32" source="../../Assets/Textures/Spike_Right_2.png"/>
 </tile>
 <tile id="34" type="InteractiveTile">
  <properties>
   <property name="interactiontype" value="3"/>
  </properties>
  <image width="32" height="32" source="../../Assets/Textures/Spike_Right_3.png"/>
 </tile>
 <tile id="35" type="InteractiveTile">
  <properties>
   <property name="interactiontype" type="int" value="3"/>
  </properties>
  <image width="32" height="32" source="../../Assets/Textures/Spike_Right_1.png"/>
  <objectgroup draworder="index" id="2">
   <object id="1" x="0" y="8" width="8" height="16"/>
  </objectgroup>
  <animation>
   <frame tileid="32" duration="500"/>
   <frame tileid="33" duration="500"/>
   <frame tileid="34" duration="500"/>
   <frame tileid="33" duration="500"/>
  </animation>
 </tile>
 <tile id="36" type="InteractiveTile">
  <properties>
   <property name="interactiontype" type="int" value="3"/>
  </properties>
  <image width="32" height="32" source="../../Assets/Textures/Spike_Right_2.png"/>
  <objectgroup draworder="index" id="2">
   <object id="1" x="0" y="8" width="8" height="16"/>
  </objectgroup>
  <animation>
   <frame tileid="33" duration="500"/>
   <frame tileid="34" duration="500"/>
   <frame tileid="33" duration="500"/>
   <frame tileid="32" duration="500"/>
  </animation>
 </tile>
 <tile id="37" type="InteractiveTile">
  <properties>
   <property name="interactiontype" value="3"/>
  </properties>
  <image width="32" height="32" source="../../Assets/Textures/Spike_Right_3.png"/>
  <objectgroup draworder="index" id="2">
   <object id="1" x="0" y="8" width="8" height="16"/>
  </objectgroup>
  <animation>
   <frame tileid="34" duration="500"/>
   <frame tileid="33" duration="500"/>
   <frame tileid="32" duration="500"/>
   <frame tileid="33" duration="500"/>
  </animation>
 </tile>
 <tile id="38" type="InteractiveTile">
  <properties>
   <property name="interactiontype" value="3"/>
  </properties>
  <image width="32" height="32" source="../../Assets/Textures/Spike_Right_2.png"/>
  <objectgroup draworder="index" id="2">
   <object id="1" x="0" y="8" width="8" height="16"/>
  </objectgroup>
  <animation>
   <frame tileid="33" duration="500"/>
   <frame tileid="32" duration="500"/>
   <frame tileid="33" duration="500"/>
   <frame tileid="34" duration="500"/>
  </animation>
 </tile>
 <tile id="39" type="InteractiveTile">
  <properties>
   <property name="interactiontype" value="3"/>
  </properties>
  <image width="32" height="32" source="../../Assets/Textures/Spike_Down_1.png"/>
  <objectgroup draworder="index" id="2">
   <object id="1" x="8" y="0" width="16" height="8"/>
  </objectgroup>
 </tile>
 <tile id="40" type="InteractiveTile">
  <properties>
   <property name="interactiontype" value="3"/>
  </properties>
  <image width="32" height="32" source="../../Assets/Textures/Spike_Down_2.png"/>
 </tile>
 <tile id="41" type="InteractiveTile">
  <properties>
   <property name="interactiontype" value="3"/>
  </properties>
  <image width="32" height="32" source="../../Assets/Textures/Spike_Down_3.png"/>
 </tile>
 <tile id="42" type="InteractiveTile">
  <properties>
   <property name="interactiontype" type="int" value="3"/>
  </properties>
  <image width="32" height="32" source="../../Assets/Textures/Spike_Down_1.png"/>
  <objectgroup draworder="index" id="2">
   <object id="1" x="8" y="0" width="16" height="8"/>
  </objectgroup>
  <animation>
   <frame tileid="39" duration="500"/>
   <frame tileid="40" duration="500"/>
   <frame tileid="41" duration="500"/>
   <frame tileid="40" duration="500"/>
  </animation>
 </tile>
 <tile id="43" type="InteractiveTile">
  <properties>
   <property name="interactiontype" type="int" value="3"/>
  </properties>
  <image width="32" height="32" source="../../Assets/Textures/Spike_Down_2.png"/>
  <objectgroup draworder="index" id="2">
   <object id="1" x="8" y="0" width="16" height="8"/>
  </objectgroup>
  <animation>
   <frame tileid="40" duration="500"/>
   <frame tileid="41" duration="500"/>
   <frame tileid="40" duration="500"/>
   <frame tileid="39" duration="500"/>
  </animation>
 </tile>
 <tile id="44" type="InteractiveTile">
  <properties>
   <property name="interactiontype" value="3"/>
  </properties>
  <image width="32" height="32" source="../../Assets/Textures/Spike_Down_3.png"/>
  <objectgroup draworder="index" id="2">
   <object id="1" x="8" y="0" width="16" height="8"/>
  </objectgroup>
  <animation>
   <frame tileid="41" duration="500"/>
   <frame tileid="40" duration="500"/>
   <frame tileid="39" duration="500"/>
   <frame tileid="40" duration="500"/>
  </animation>
 </tile>
 <tile id="45" type="InteractiveTile">
  <properties>
   <property name="interactiontype" value="3"/>
  </properties>
  <image width="32" height="32" source="../../Assets/Textures/Spike_Down_2.png"/>
  <objectgroup draworder="index" id="2">
   <object id="1" x="8" y="0" width="16" height="8"/>
  </objectgroup>
  <animation>
   <frame tileid="40" duration="500"/>
   <frame tileid="39" duration="500"/>
   <frame tileid="40" duration="500"/>
   <frame tileid="41" duration="500"/>
  </animation>
 </tile>
 <tile id="46" type="InteractiveTile">
  <properties>
   <property name="interactiontype" value="3"/>
  </properties>
  <image width="32" height="32" source="../../Assets/Textures/Spike_Left_1.png"/>
  <objectgroup draworder="index" id="2">
   <object id="2" x="24" y="8" width="8" height="16"/>
  </objectgroup>
 </tile>
 <tile id="47" type="InteractiveTile">
  <properties>
   <property name="interactiontype" value="3"/>
  </properties>
  <image width="32" height="32" source="../../Assets/Textures/Spike_Left_2.png"/>
 </tile>
 <tile id="48" type="InteractiveTile">
  <properties>
   <property name="interactiontype" value="3"/>
  </properties>
  <image width="32" height="32" source="../../Assets/Textures/Spike_Left_3.png"/>
 </tile>
 <tile id="49" type="InteractiveTile">
  <properties>
   <property name="interactiontype" type="int" value="3"/>
  </properties>
  <image width="32" height="32" source="../../Assets/Textures/Spike_Left_1.png"/>
  <objectgroup draworder="index" id="2">
   <object id="1" x="24" y="8" width="8" height="16"/>
  </objectgroup>
  <animation>
   <frame tileid="46" duration="500"/>
   <frame tileid="47" duration="500"/>
   <frame tileid="48" duration="500"/>
   <frame tileid="47" duration="500"/>
  </animation>
 </tile>
 <tile id="50" type="InteractiveTile">
  <properties>
   <property name="interactiontype" type="int" value="3"/>
  </properties>
  <image width="32" height="32" source="../../Assets/Textures/Spike_Left_2.png"/>
  <objectgroup draworder="index" id="2">
   <object id="1" x="24" y="8" width="8" height="16"/>
  </objectgroup>
  <animation>
   <frame tileid="47" duration="500"/>
   <frame tileid="48" duration="500"/>
   <frame tileid="47" duration="500"/>
   <frame tileid="46" duration="500"/>
  </animation>
 </tile>
 <tile id="51" type="InteractiveTile">
  <properties>
   <property name="interactiontype" value="3"/>
  </properties>
  <image width="32" height="32" source="../../Assets/Textures/Spike_Left_3.png"/>
  <objectgroup draworder="index" id="2">
   <object id="1" x="24" y="8" width="8" height="16"/>
  </objectgroup>
  <animation>
   <frame tileid="48" duration="500"/>
   <frame tileid="47" duration="500"/>
   <frame tileid="46" duration="500"/>
   <frame tileid="47" duration="500"/>
  </animation>
 </tile>
 <tile id="52" type="InteractiveTile">
  <properties>
   <property name="interactiontype" value="3"/>
  </properties>
  <image width="32" height="32" source="../../Assets/Textures/Spike_Left_2.png"/>
  <objectgroup draworder="index" id="2">
   <object id="1" x="24" y="8" width="8" height="16"/>
  </objectgroup>
  <animation>
   <frame tileid="47" duration="500"/>
   <frame tileid="46" duration="500"/>
   <frame tileid="47" duration="500"/>
   <frame tileid="48" duration="500"/>
  </animation>
 </tile>
 <tile id="53" type="InteractiveTile">
  <properties>
   <property name="interactiontype" value="0"/>
  </properties>
  <image width="32" height="32" source="../../Assets/Textures/goldCoin1.png"/>
  <objectgroup draworder="index" id="2">
   <object id="1" x="8" y="8" width="16" height="16"/>
  </objectgroup>
 </tile>
 <tile id="54" type="InteractiveTile">
  <properties>
   <property name="interactiontype" value="0"/>
  </properties>
  <image width="32" height="32" source="../../Assets/Textures/goldCoin2.png"/>
  <objectgroup draworder="index" id="2">
   <object id="1" x="8" y="8" width="16" height="16"/>
  </objectgroup>
 </tile>
 <tile id="55" type="InteractiveTile">
  <properties>
   <property name="interactiontype" value="0"/>
  </properties>
  <image width="32" height="32" source="../../Assets/Textures/goldCoin3.png"/>
  <objectgroup draworder="index" id="2">
   <object id="1" x="8" y="8" width="16" height="16"/>
  </objectgroup>
 </tile>
 <tile id="56" type="InteractiveTile">
  <properties>
   <property name="interactiontype" value="0"/>
  </properties>
  <image width="32" height="32" source="../../Assets/Textures/goldCoin4.png"/>
  <objectgroup draworder="index" id="2">
   <object id="1" x="8" y="8" width="16" height="16"/>
  </objectgroup>
 </tile>
 <tile id="57" type="InteractiveTile">
  <properties>
   <property name="interactiontype" value="0"/>
  </properties>
  <image width="32" height="32" source="../../Assets/Textures/goldCoin5.png"/>
  <objectgroup draworder="index" id="2">
   <object id="1" x="8" y="8" width="16" height="16"/>
  </objectgroup>
 </tile>
 <tile id="58" type="InteractiveTile">
  <properties>
   <property name="interactiontype" value="0"/>
  </properties>
  <image width="32" height="32" source="../../Assets/Textures/goldCoin6.png"/>
  <objectgroup draworder="index" id="2">
   <object id="1" x="8" y="8" width="16" height="16"/>
  </objectgroup>
 </tile>
 <tile id="59" type="InteractiveTile">
  <properties>
   <property name="interactiontype" value="0"/>
  </properties>
  <image width="32" height="32" source="../../Assets/Textures/goldCoin7.png"/>
  <objectgroup draworder="index" id="2">
   <object id="1" x="8" y="8" width="16" height="16"/>
  </objectgroup>
 </tile>
 <tile id="60" type="InteractiveTile">
  <properties>
   <property name="interactiontype" value="0"/>
  </properties>
  <image width="32" height="32" source="../../Assets/Textures/goldCoin8.png"/>
  <objectgroup draworder="index" id="2">
   <object id="1" x="8" y="8" width="16" height="16"/>
  </objectgroup>
 </tile>
 <tile id="61" type="InteractiveTile">
  <properties>
   <property name="interactiontype" value="0"/>
  </properties>
  <image width="32" height="32" source="../../Assets/Textures/goldCoin9.png"/>
  <objectgroup draworder="index" id="2">
   <object id="1" x="8" y="8" width="16" height="16"/>
  </objectgroup>
 </tile>
 <tile id="62" type="InteractiveTile">
  <properties>
   <property name="interactiontype" value="4"/>
   <property name="vanishoninteraction" type="bool" value="true"/>
  </properties>
  <image width="32" height="32" source="../../Assets/Textures/goldCoin1.png"/>
  <animation>
   <frame tileid="53" duration="333"/>
   <frame tileid="54" duration="333"/>
   <frame tileid="55" duration="333"/>
   <frame tileid="56" duration="333"/>
   <frame tileid="57" duration="333"/>
   <frame tileid="58" duration="333"/>
   <frame tileid="59" duration="333"/>
   <frame tileid="60" duration="333"/>
   <frame tileid="61" duration="333"/>
  </animation>
 </tile>
 <tile id="63" type="BackgroundTile">
  <properties>
   <property name="drag" type="float" value="0.95"/>
   <property name="force_x" type="float" value="0"/>
   <property name="force_y" type="float" value="0.5"/>
   <property name="jumpforce_x" type="float" value="0"/>
   <property name="jumpforce_y" type="float" value="-0.75"/>
   <property name="jumpforcemax" type="float" value="-10"/>
   <property name="maxdrag" type="float" value="0.5"/>
   <property name="maxspeed" type="float" value="25"/>
  </properties>
  <image width="32" height="32" source="../../Assets/Textures/Empty.png"/>
 </tile>
</tileset>

@ECHO OFF

::
:: Set the build paremeters
::
SET OSDKADDR=$500
SET OSDKNAME=proto
SET OSDKFILE=texel_s tab3trigo  game_s kernel keybuf_s keyboard sprite_s dichobuf_s tablogtrigo_s raycast_s dda_s drawWalls_s column_s collision_s main 
SET OSDKCOMP=-O2
set OSDKLINK=
:: display buffer clip line8 profile ay_s viewport_s 
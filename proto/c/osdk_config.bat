@ECHO OFF

::
:: Set the build paremeters
::
SET OSDKADDR=$600
SET OSDKNAME=proto
SET OSDKFILE=texel_s dist_s vertcolbuf_s tab3trigo player_s game_s kernel keybuf_s keyboard sprite_s dichobuf_s tablogtrigo_s raycast_s dda_s drawWalls_s collision_s main 
SET OSDKFILE=%OSDKFILE%  profile
SET OSDKCOMP=-O2
set OSDKLINK=
:: display buffer clip line8 profile ay_s viewport_s column_s 
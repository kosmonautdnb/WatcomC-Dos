@echo off
PATH .;\;\LOCALE;\_DOS_\BIN;\_DOS_\OWN;C:\_WAT_C_\BINW
display con=(ega,,1)
SET DOSDIR=C:\_DOS_
SET INCLUDE=C:\_WAT_C_\H
SET WATCOM=C:\_WAT_C_
SET EDPATH=C:\_WAT_C_\EDDAT
CTMOUSE /R11
cd c:\_PAINT_
SETLANG DE
rem GOTO %CONFIG%
rem :1
rem mode con codepage prepare=((858) \locale\ega.cpx) > NUL
rem mode con codepage select=858 > NUL
rem keyb gr,,\locale\keyboard.sys
rem :2
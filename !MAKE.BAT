@echo off
@echo Starting..
@echo system dos4g > _BUILD\LINK.LNK
@echo build errors > LOGS.LOG
@echo Deleting exe..
del MAIN.EXE
@echo Generating exe..
call _BUILD\CO.BAT ZLIB\ADLER32.C               ADLER32.OBJ
call _BUILD\CO.BAT ZLIB\COMPRESS.C              COMPRESS.OBJ
call _BUILD\CO.BAT ZLIB\CRC32.C                 CRC32.OBJ
call _BUILD\CO.BAT ZLIB\DEFLATE.C               DEFLATE.OBJ
call _BUILD\CO.BAT ZLIB\GZIO.C                  GZIO.OBJ
call _BUILD\CO.BAT ZLIB\INFFAST.C               INFFAST.OBJ
call _BUILD\CO.BAT ZLIB\INFLATE.C               INFLATE.OBJ
call _BUILD\CO.BAT ZLIB\INFTREES.C              INFTREES.OBJ
call _BUILD\CO.BAT ZLIB\TREES.C                 TREES.OBJ
call _BUILD\CO.BAT ZLIB\UNCOMPR.C               UNCOMPR.OBJ
call _BUILD\CO.BAT ZLIB\ZUTIL.C                 ZUTIL.OBJ
call _BUILD\CO.BAT PNG\PNG.C                    PNG.OBJ
call _BUILD\CO.BAT PNG\PNGERROR.C               PNGERROR.OBJ
call _BUILD\CO.BAT PNG\PNGGET.C                 PNGGET.OBJ
call _BUILD\CO.BAT PNG\PNGMEM.C                 PNGMEM.OBJ
call _BUILD\CO.BAT PNG\PNGPREAD.C               PNGPREAD.OBJ
call _BUILD\CO.BAT PNG\PNGREAD.C                PNGREAD.OBJ
call _BUILD\CO.BAT PNG\PNGRIO.C                 PNGPRIO.OBJ
call _BUILD\CO.BAT PNG\PNGRTRAN.C               PNGRTRAN.OBJ
call _BUILD\CO.BAT PNG\PNGRUTIL.C               PNGRUTIL.OBJ
call _BUILD\CO.BAT PNG\PNGSET.C                 PNGSET.OBJ
call _BUILD\CO.BAT PNG\PNGTRANS.C               PNGTRANS.OBJ
call _BUILD\CO.BAT PNG\PNGWIO.C                 PNGWIO.OBJ
call _BUILD\CO.BAT PNG\PNGWRITE.C               PNGWRITE.OBJ
call _BUILD\CO.BAT PNG\PNGWTRAN.C               PNGWTRAN.OBJ
call _BUILD\CO.BAT PNG\PNGWUTIL.C               PNGWUTIL.OBJ
call _BUILD\CC.BAT MAIN.CPP                     MAIN.OBJ
call _BUILD\CC.BAT CHARSET.CPP                  CHARSET.OBJ
call _BUILD\CC.BAT BLIT.CPP                     BLIT.OBJ
call _BUILD\CC.BAT VGA.CPP                      VGA.OBJ
call _BUILD\CC.BAT PNGLOAD.CPP                  PNGLOAD.OBJ
call _BUILD\CC.BAT DOS.CPP                      DOS.OBJ
call _BUILD\CC.BAT STRING.CPP                   STRING.OBJ
call _BUILD\CC.BAT VBASE.CPP                    VBASE.OBJ
call _BUILD\CC.BAT VSTRLST.CPP                  VSTRLST.OBJ
call _BUILD\CC.BAT VPREVIEW.CPP                 VPREVIEW.OBJ
call _BUILD\CC.BAT IFILES.CPP                   IFILES.OBJ
call _BUILD\CC.BAT VTEXT.CPP                    VTEXT.OBJ
call _BUILD\CC.BAT VCODE.CPP                    VCODE.OBJ
call _BUILD\CC.BAT INPUT.CPP                    INPUT.OBJ
call _BUILD\CC.BAT UTIL.CPP                     UTIL.OBJ
call _BUILD\CC.BAT POINT.CPP                    POINT.OBJ
call _BUILD\CC.BAT CLIPBRD.CPP                  CLIPBRD.OBJ
call _BUILD\CC.BAT VHEX.CPP                     VHEX.OBJ
call _BUILD\CC.BAT VTREE.CPP                    VTREE.OBJ
call _BUILD\CC.BAT SYNTAX.CPP                   SYNTAX.OBJ
call _BUILD\CC.BAT VALERT.CPP                   VALERT.OBJ
call _BUILD\CC.BAT VBUTTON.CPP                  VBUTTON.OBJ
call _BUILD\CC.BAT VTXTLINE.CPP                 VTXTLINE.OBJ
call _BUILD\CC.BAT VTXTALRT.CPP                 VTXTALRT.OBJ
call _BUILD\CC.BAT VESA.CPP                      VESA.OBJ
call _BUILD\CC.BAT MEMORY.CPP                      MEMORY.OBJ
call _BUILD\AL.BAT _BUILD\LINK.LNK              MAIN.EXE
me LOGS.LOG
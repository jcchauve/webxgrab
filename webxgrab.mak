# ---------------------------------------------------------------------------
!if !$d(BCB)
BCB = $(MAKEDIR)\..
!endif

# ---------------------------------------------------------------------------
# IDE SECTION
# ---------------------------------------------------------------------------
# The following section of the project makefile is managed by the BCB IDE.
# It is recommended to use the IDE to change any of the values in this
# section.
# ---------------------------------------------------------------------------

VERSION = BCB.06.00
# ---------------------------------------------------------------------------
PROJECT = webxgrab.exe
OBJFILES = webxgrab.obj nopop1.obj histo.obj urlcon.obj struti.obj registr.obj \
    FavoriteEngine.obj Viewer.obj
RESFILES = webxgrab.res
MAINSOURCE = webxgrab.cpp
RESDEPEN = $(RESFILES) nopop1.dfm histo.dfm Viewer.dfm
LIBFILES = wininet.lib
IDLFILES = 
IDLGENFILES = 
LIBRARIES = thmanager.lib visualclx.lib bcb2kaxserver.lib indy.lib dbxcds.lib \
    dclocx.lib soaprtl.lib inetdbxpress.lib inetdbbde.lib bcbsmp.lib \
    dsnapcon.lib dsnapcrba.lib visualdbclx.lib teeqr.lib dss.lib tee.lib \
    teedb.lib teeui.lib qrpt.lib bdecds.lib vcldbx.lib bdertl.lib \
    dbexpress.lib dsnap.lib cds.lib GR32_CB5.lib nmfast.lib bcbie.lib \
    ibxpress.lib adortl.lib vcldb.lib dbrtl.lib vclx.lib vcl.lib rtl.lib
PACKAGES = rtl.bpi vcl.bpi vclx.bpi bcbsmp.bpi dbrtl.bpi vcldb.bpi adortl.bpi \
    ibsmp.bpi bdertl.bpi vcldbx.bpi qrpt.bpi teeui.bpi teedb.bpi tee.bpi \
    dss.bpi teeqr.bpi ibxpress.bpi dsnap.bpi vclie.bpi inetdb.bpi inet.bpi \
    nmfast.bpi webdsnap.bpi bcbie.bpi dclocx.bpi bcb97axserver.bpi DCLUSR.bpi \
    FlatStyle_Cb4.bpi
SPARELIBS = rtl.lib vcl.lib vclx.lib dbrtl.lib vcldb.lib adortl.lib ibxpress.lib \
    bcbie.lib nmfast.lib GR32_CB5.lib cds.lib dsnap.lib dbexpress.lib \
    bdertl.lib vcldbx.lib bdecds.lib qrpt.lib teeui.lib teedb.lib tee.lib \
    dss.lib teeqr.lib visualdbclx.lib dsnapcrba.lib dsnapcon.lib bcbsmp.lib \
    inetdbbde.lib inetdbxpress.lib soaprtl.lib dclocx.lib dbxcds.lib indy.lib \
    bcb2kaxserver.lib visualclx.lib thmanager.lib
DEFFILE = 
OTHERFILES = 
# ---------------------------------------------------------------------------
DEBUGLIBPATH = $(BCB)\lib\debug
RELEASELIBPATH = $(BCB)\lib\release
USERDEFINES = _DEBUG
SYSDEFINES = NO_STRICT
INCLUDEPATH = "..\..\thmanager\theme manager";$(BCB)\Projects;d:\bcb5eval\CBuilder5\Projects\;$(BCB)\include;$(BCB)\include\vcl;graphics32
LIBPATH = "..\..\thmanager\theme manager";$(BCB)\Projects;d:\bcb5eval\CBuilder5\Projects\;$(BCB)\Projects\Lib;$(BCB)\lib\obj;$(BCB)\lib
WARNINGS= -w-par
PATHCPP = .;
PATHASM = .;
PATHPAS = .;
PATHRC = .;
PATHOBJ = .;$(LIBPATH)
# ---------------------------------------------------------------------------
CFLAG1 = -Od -H=c:\bcb6\lib\vcl60.csm -Hc -Vx -Ve -X- -r- -a8 -b- -k -y -v -vi- -c \
    -tW -tWM
IDLCFLAGS = -src_suffix cpp -D_DEBUG -I"..\..\thmanager\theme manager" \
    -I$(BCB)\Projects -Id:\bcb5eval\CBuilder5\Projects\. -I$(BCB)\include \
    -I$(BCB)\include\vcl -Igraphics32 -boa
PFLAGS = -$YD -$W -$O- -$A8 -v -JPHNE -M
RFLAGS = 
AFLAGS = /mx /w2 /zi
LFLAGS = -D"" -aa -Tpe -x -Gn -v
# ---------------------------------------------------------------------------
ALLOBJ = c0w32.obj sysinit.obj $(OBJFILES)
ALLRES = $(RESFILES)
ALLLIB = $(LIBFILES) $(LIBRARIES) import32.lib cp32mt.lib
# ---------------------------------------------------------------------------
!ifdef IDEOPTIONS

[Version Info]
IncludeVerInfo=0
AutoIncBuild=0
MajorVer=1
MinorVer=0
Release=0
Build=0
Debug=0
PreRelease=0
Special=0
Private=0
DLL=0

[Version Info Keys]
CompanyName=
FileDescription=
FileVersion=1.0.0.0
InternalName=
LegalCopyright=
LegalTrademarks=
OriginalFilename=
ProductName=
ProductVersion=1.0.0.0
Comments=

[Debugging]
DebugSourceDirs=$(BCB)\source\vcl

!endif





# ---------------------------------------------------------------------------
# MAKE SECTION
# ---------------------------------------------------------------------------
# This section of the project file is not used by the BCB IDE.  It is for
# the benefit of building from the command-line using the MAKE utility.
# ---------------------------------------------------------------------------

.autodepend
# ---------------------------------------------------------------------------
!if "$(USERDEFINES)" != ""
AUSERDEFINES = -d$(USERDEFINES:;= -d)
!else
AUSERDEFINES =
!endif

!if !$d(BCC32)
BCC32 = bcc32
!endif

!if !$d(CPP32)
CPP32 = cpp32
!endif

!if !$d(DCC32)
DCC32 = dcc32
!endif

!if !$d(TASM32)
TASM32 = tasm32
!endif

!if !$d(LINKER)
LINKER = ilink32
!endif

!if !$d(BRCC32)
BRCC32 = brcc32
!endif


# ---------------------------------------------------------------------------
!if $d(PATHCPP)
.PATH.CPP = $(PATHCPP)
.PATH.C   = $(PATHCPP)
!endif

!if $d(PATHPAS)
.PATH.PAS = $(PATHPAS)
!endif

!if $d(PATHASM)
.PATH.ASM = $(PATHASM)
!endif

!if $d(PATHRC)
.PATH.RC  = $(PATHRC)
!endif

!if $d(PATHOBJ)
.PATH.OBJ  = $(PATHOBJ)
!endif
# ---------------------------------------------------------------------------
$(PROJECT): $(OTHERFILES) $(IDLGENFILES) $(OBJFILES) $(RESDEPEN) $(DEFFILE)
    $(BCB)\BIN\$(LINKER) @&&!
    $(LFLAGS) -L$(LIBPATH) +
    $(ALLOBJ), +
    $(PROJECT),, +
    $(ALLLIB), +
    $(DEFFILE), +
    $(ALLRES)
!
# ---------------------------------------------------------------------------
.pas.hpp:
    $(BCB)\BIN\$(DCC32) $(PFLAGS) -U$(INCLUDEPATH) -D$(USERDEFINES);$(SYSDEFINES) -O$(INCLUDEPATH) --BCB {$< }

.pas.obj:
    $(BCB)\BIN\$(DCC32) $(PFLAGS) -U$(INCLUDEPATH) -D$(USERDEFINES);$(SYSDEFINES) -O$(INCLUDEPATH) --BCB {$< }

.cpp.obj:
    $(BCB)\BIN\$(BCC32) $(CFLAG1) $(WARNINGS) -I$(INCLUDEPATH) -D$(USERDEFINES);$(SYSDEFINES) -n$(@D) {$< }

.c.obj:
    $(BCB)\BIN\$(BCC32) $(CFLAG1) $(WARNINGS) -I$(INCLUDEPATH) -D$(USERDEFINES);$(SYSDEFINES) -n$(@D) {$< }

.c.i:
    $(BCB)\BIN\$(CPP32) $(CFLAG1) $(WARNINGS) -I$(INCLUDEPATH) -D$(USERDEFINES);$(SYSDEFINES) -n. {$< }

.cpp.i:
    $(BCB)\BIN\$(CPP32) $(CFLAG1) $(WARNINGS) -I$(INCLUDEPATH) -D$(USERDEFINES);$(SYSDEFINES) -n. {$< }

.asm.obj:
    $(BCB)\BIN\$(TASM32) $(AFLAGS) -i$(INCLUDEPATH:;= -i) $(AUSERDEFINES) -d$(SYSDEFINES:;= -d) $<, $@

.rc.res:
    $(BCB)\BIN\$(BRCC32) $(RFLAGS) -I$(INCLUDEPATH) -D$(USERDEFINES);$(SYSDEFINES) -fo$@ $<



# ---------------------------------------------------------------------------





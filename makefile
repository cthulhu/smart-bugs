###################################################################################################
#
# Makefile for $(project) prj 
# By Stan (Stanislav Pogrebnyak) stas@mymail.bz
# Makefile for Visual C++ (cl.exe)
# for direct work you'll need some things
# Firstly correct PATH,INCLUDE and LIB vars
# secondly correct BACKUPDIR var
# for backuping the project versions
# and some tools: doxygen, gIncver etc.
#
###################################################################################################

# INCLUDING VERTION FILE
!INCLUDE VERSION
!IF $(BUILD) != 0 || $(REBUILD) != 0
VERSION=$(VER).$(SUBVER).$(BUILD).$(REBUILD)
!ELSE
VERSION=$(VER).$(SUBVER)$(LETTER)
!ENDIF

####################################################################################################
# PROJECT SETTING
####################################################################################################
#Project name
PROJECT = bugS
#Sources for compiler
SRC = .\bug.cpp       \
      .\trace.cpp 	  \
      .\field.cpp     \
      .\bugsuper.cpp  \
      .\cockroach.cpp \
      .\utils.cpp	  \
      .\exept.cpp 	  \
      .\main.cpp
#Object files for linker
OBJ = $(OUTDIR)\bug.obj       \
      $(OUTDIR)\trace.obj     \
      $(OUTDIR)\main.obj      \
      $(OUTDIR)\field.obj     \
      $(OUTDIR)\cockroach.obj \
      $(OUTDIR)\utils.obj	  \
      $(OUTDIR)\exept.obj	  \
      $(OUTDIR)\bugsuper.obj

FILE_TO_DEL = *.ilk *.pch *.pdb *.obj *.idb

#DEV TOOLS SERVICES
CC = @cl.exe
LINK = @link.exe

#BACKUP SERVICES
BACKUP = $(BACKUPDIR)
BACKUP_SRC = $(BACKUP)\src\$(PROJECT)\$(VERSION)
BACKUP_SRC_NEWEST = $(BACKUP)\src\$(PROJECT)\newest
BACKUP_EXE = $(BACKUP)\exe\$(PROJECT)\$(VERSION)
BACKUP_EXE_NEWEST = $(BACKUP)\exe\$(PROJECT)\newest

ARC = @7z
ARC_OPTIONS = a -mx -tzip -x!*.ncb -x!*.aps -x!*.clw
ARC_FILENAME = $(PROJECT).zip
ARC_FILES = *.* VERSION makefile
#OS SERVICES
TYPE = @type
ECHO = @echo
MKDIR = @md
DEL_TREE = @rd
COPY = @xcopy
DELETE = @del
DELETE_OPTIONS = /Q /S
SCRCLR = @CLS
noparams: help

all: cleanAll astyle CleanOrign debug backup doc clean

iv:
    gIncver -v1 -g$(PROJECT)Ver.h VERSION

isv:
    gIncver -v2 -g$(PROJECT)Ver.h VERSION

backup: release 
	$(ECHO) -------------------------------------------------------------------------------------
	$(ECHO) Backuping Files for $(PROJECT) current version is $(VERSION)
	$(ECHO) -------------------------------------------------------------------------------------
	$(ECHO) -------------------------------------------------------------------------------------
	$(ECHO) Compressing Files
	$(ECHO) -------------------------------------------------------------------------------------
    $(ARC) $(ARC_OPTIONS) $(ARC_FILENAME) $(ARC_FILES) > nul
   	$(ECHO) -------------------------------------------------------------------------------------
	$(ECHO) Saving files in $(BACKUPDIR)
	$(ECHO) -------------------------------------------------------------------------------------
    @if exist $(BACKUP_SRC) $(DELETE)  $(BACKUP_SRC) $(DELETE_OPTIONS) > nul
    @if exist $(BACKUP_EXE) $(DELETE)  $(BACKUP_EXE) $(DELETE_OPTIONS) > nul
    @if exist $(BACKUP_SRC) $(DEL_TREE) $(DELETE_OPTIONS) $(BACKUP_SRC) > nul
    @if exist $(BACKUP_EXE) $(DEL_TREE) $(DELETE_OPTIONS) $(BACKUP_EXE) > nul
    $(MKDIR) $(BACKUP_EXE)
    $(MKDIR) $(BACKUP_SRC)
    @if exist $(BACKUP_SRC_NEWEST) $(DELETE) $(DELETE_OPTIONS) $(BACKUP_SRC_NEWEST) > nul
    @if exist $(BACKUP_EXE_NEWEST) $(DELETE) $(DELETE_OPTIONS) $(BACKUP_EXE_NEWEST) > nul
    @if exist $(BACKUP_SRC_NEWEST) $(DEL_TREE) $(DELETE_OPTIONS) $(BACKUP_SRC_NEWEST) > nul
    @if exist $(BACKUP_EXE_NEWEST) $(DEL_TREE) $(DELETE_OPTIONS) $(BACKUP_EXE_NEWEST) > nul
    $(MKDIR) $(BACKUP_EXE_NEWEST)
    $(MKDIR) $(BACKUP_SRC_NEWEST)
    $(COPY)  $(ARC_FILENAME) $(BACKUP_SRC) > nul
    $(COPY)  $(ARC_FILENAME) $(BACKUP_SRC_NEWEST) > nul
    $(COPY)  Release\$(PROJECT).exe $(BACKUP_EXE_NEWEST) > nul
    $(COPY)  Release\$(PROJECT).exe $(BACKUP_EXE) > nul
    $(DELETE) $(ARC_FILENAME) > nul
   	$(ECHO) -------------------------------------------------------------------------------------
	$(ECHO) Backup successfully complite
	$(ECHO) -------------------------------------------------------------------------------------
debug_options:
INTDIR = Debug
OUTDIR = Debug
CC_OPTIONS = /nologo /MLd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\$(PROJECT).pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

LINKER_OPTIONS = kernel32.lib advapi32.lib          \
                 /nologo          /subsystem:console\
                 /incremental:yes                   \
                 /nodefaultlib:LIBCMT               \
                 /pdb:"$(OUTDIR)\$(PROJECT).pdb"    \
                 /debug /machine:I386               \
                 /out:"$(OUTDIR)\$(PROJECT).exe"    \
                 /pdbtype:sept 


LINKER_OBJECT = $(OBJ)

debug: debug_options 
	$(ECHO) -------------------------------------------------------------------------------------
	$(ECHO) Building Debug of $(PROJECT) version $(VERSION)
	$(ECHO) -------------------------------------------------------------------------------------
  	@if exist $(OUTDIR) $(DELETE)   $(OUTDIR) $(DELETE_OPTIONS) > nul
  	@if exist $(OUTDIR) $(DEL_TREE) $(OUTDIR) $(DELETE_OPTIONS) > nul
  	$(MKDIR) $(OUTDIR) > nul
  	$(ECHO) -------------------------------------------------------------------------------------
	$(ECHO) Compiling
	$(ECHO) -------------------------------------------------------------------------------------
  	$(CC) $(SRC) $(CC_OPTIONS)
  	$(ECHO) -------------------------------------------------------------------------------------
	$(ECHO) Linking
	$(ECHO) -------------------------------------------------------------------------------------
  	$(LINK) $(LINKER_OBJECT) $(LINKER_OPTIONS)
  	$(ECHO) -------------------------------------------------------------------------------------
	$(ECHO) Build success
	$(ECHO) -------------------------------------------------------------------------------------
release_options:
INTDIR = Release
OUTDIR = Release
CC_OPTIONS = /nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\$(PROJECT).pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

LINKER_OPTIONS = kernel32.lib   advapi32.lib          \
                 /nologo        /subsystem:console    \
                 /incremental:no /nodefaultlib:LIBCMT \
                 /pdb:"$(OUTDIR)\$(PROJECT).pdb"      \
                 /machine:I386 /out:"$(OUTDIR)\$(PROJECT).exe" 


LINKER_OBJECT = $(OBJ)
release: release_options 
	$(ECHO) -------------------------------------------------------------------------------------
	$(ECHO) Building Release of $(PROJECT) version $(VERSION)
	$(ECHO) -------------------------------------------------------------------------------------
	@if exist $(OUTDIR) $(DELETE)   $(OUTDIR) $(DELETE_OPTIONS)
	@if exist $(OUTDIR) $(DEL_TREE) $(OUTDIR) $(DELETE_OPTIONS)
	$(MKDIR) $(OUTDIR)
  	$(ECHO) -------------------------------------------------------------------------------------
	$(ECHO) Compiling
	$(ECHO) -------------------------------------------------------------------------------------
	$(CC) $(SRC) $(CC_OPTIONS)
  	$(ECHO) -------------------------------------------------------------------------------------
	$(ECHO) Linking
	$(ECHO) -------------------------------------------------------------------------------------
	$(LINK) $(LINKER_OBJECT) $(LINKER_OPTIONS)
  	$(ECHO) -------------------------------------------------------------------------------------
	$(ECHO) Build success
	$(ECHO) -------------------------------------------------------------------------------------


clean:
  $(DELETE) Debug\$(FILE_TO_DEL)   $(DELETE_OPTIONS)
  $(DELETE) Release\$(FILE_TO_DEL) $(DELETE_OPTIONS)

cleanAll: CleanDebug CleanRelease
CleanDebug:
  @if exist Debug\ $(DELETE)   Debug\ $(DELETE_OPTIONS) > nul
  @if exist Debug\ $(DEL_TREE) Debug\ $(DELETE_OPTIONS) > nul
CleanRelease:
  @if exist Release\ $(DELETE)   Release\ $(DELETE_OPTIONS) > nul
  @if exist Release\ $(DEL_TREE) Release\ $(DELETE_OPTIONS) > nul
help:
  $(ECHO) ------------------------------------------------------------------------------------ 
  $(ECHO) + This make file is for bilding $(PROJECT)  
  $(ECHO) + Use the make file in such way:
  $(ECHO) + maketool makefile target
  $(ECHO) + The target could be the next:
  $(ECHO) + iv --------------------- will increment the version. Current is $(VER)
  $(ECHO) + isv -------------------- will increment the subversion. Current is $(SUBVER)
  $(ECHO) + all -------------------- will bild debug realese and backup your project ($(BACKUP))
  $(ECHO) + debug ------------------ will bild debug vertion only 
  $(ECHO) + backup ----------------- will backup your project in to $(BACKUP)\$(PROJECT) 
  $(ECHO) + release ---------------- will bild release vertion only
  $(ECHO) -------------------------------------------------------------------------------------

.cpp{$(INTDIR)}.obj::
   $(C‘) @<<
   $(C‘_OPTIONS) $< 
<<

.obj{$(INTDIR)}.exe::
   $(LINK) @<<
   $(LINKER_OPTIONS) $< 
<<

doc:
	$(ECHO) -------------------------------------------------------------------------------------
	$(ECHO) Building documentation of $(PROJECT) version $(VERSION)
	$(ECHO) -------------------------------------------------------------------------------------
    @copy doxygen.cfg doxygen.config > nul
    @echo.  >> doxygen.config
    @echo PROJECT_NUMBER=$(VERSION) >> doxygen.config
    @doxygen doxygen.config
    @del doxygen.config
    @-hhc html\index.hhp > nul
	@if not exist chm\ $(MKDIR) chm    
	$(COPY) docs\*.ch? chm\*.ch? /y > nul
astyle:
	$(ECHO) -------------------------------------------------------------------------------------
	$(ECHO) Stylising all sources
	$(ECHO) -------------------------------------------------------------------------------------
	@astyle --style=ansi --indent-switches --indent-namespaces *.h *.cpp
CleanOrign:
	@if exist *.orig $(DELETE)   *.orig $(DELETE_OPTIONS)
#end of makefile
!if !$d(BCB)
BCB = $(MAKEDIR)\..
!endif

PROJECT = log4cpp.dll
OBJFILES = \
	SyslogAppender.obj AppenderSkeleton.obj BasicLayout.obj Category.obj \
	CategoryStream.obj \
    FileAppender.obj Filter.obj FixedContextCategory.obj \
    HierarchyMaintainer.obj IdsaAppender.obj LayoutAppender.obj \
    Log4cppCleanup.obj LoggingEvent.obj NDC.obj OstreamAppender.obj \
    OstringStream.obj Priority.obj SimpleLayout.obj StringQueueAppender.obj \
    Appender.obj
# ---------------------------------------------------------------------------
PATHCPP = .;..\..\src
USERDEFINES = _DEBUG;LOG4CPP_HAS_DLL;LOG4CPP_BUILD_DLL
SYSDEFINES = NO_STRICT;_NO_VCL;_RTLDLL
INCLUDEPATH = ..\..\src;$(BCB)\include;..\..\include
LIBPATH = ..\..\src;$(BCB)\lib\obj;$(BCB)\lib
WARNINGS= -w-par
# ---------------------------------------------------------------------------
CFLAG1 = -WD -Od -Vx -Ve -X- -r- -a8 -b- -k -y -v -vi- -tWD -tWM -c
LFLAGS = -I. -D"" -aa -Tpd -x -Gn -Gi -v
# ---------------------------------------------------------------------------
ALLOBJ = c0d32.obj $(OBJFILES)
ALLRES = $(RESFILES)
ALLLIB = $(LIBFILES) $(LIBRARIES) import32.lib cw32mti.lib
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

!if !$d(LINKER)
LINKER = ilink32
!endif

# ---------------------------------------------------------------------------
!if $d(PATHCPP)
.PATH.CPP = $(PATHCPP)
.PATH.C   = $(PATHCPP)
!endif

# ---------------------------------------------------------------------------
$(PROJECT): $(OBJFILES)
    $(BCB)\BIN\$(LINKER) @&&!
    $(LFLAGS) -L$(LIBPATH) +
    $(ALLOBJ), +
    $(PROJECT),, +
    $(ALLLIB), +
    , +
    $(ALLRES)
!

.cpp.obj:
    $(BCB)\BIN\$(BCC32) $(CFLAG1) $(WARNINGS) -I$(INCLUDEPATH) -D$(USERDEFINES);$(SYSDEFINES) -n$(@D) {$< }

.c.obj:
    $(BCB)\BIN\$(BCC32) $(CFLAG1) $(WARNINGS) -I$(INCLUDEPATH) -D$(USERDEFINES);$(SYSDEFINES) -n$(@D) {$< }



!ifndef ROOT
ROOT = $(MAKEDIR)\..
!endif

PROJECTS = log4cpp.dll testmain.exe testCategory.exe testNDC.exe \
  testFixedContextCategory.exe

default: $(PROJECTS)



log4cpp.dll:
  cd log4cpp
  $(ROOT)\bin\make -$(MAKEFLAGS) -f$*.mak
  cd ..

testmain.exe:
  cd testmain
  $(ROOT)\bin\make -$(MAKEFLAGS) -f$*.mak
  cd ..

testCategory.exe:
  cd testCategory
  $(ROOT)\bin\make -$(MAKEFLAGS) -f$*.mak
  cd ..

testNDC.exe:
  cd testNDC
  $(ROOT)\bin\make -$(MAKEFLAGS) -f$*.mak
  cd ..

testFixedContextCategory.exe:
  cd testFixedContextCategory
  $(ROOT)\bin\make -$(MAKEFLAGS) -f$*.mak
  cd ..



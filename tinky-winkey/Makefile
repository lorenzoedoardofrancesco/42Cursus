CC       = cl
WFLAGS   = /Wall /WX
CPPFLAGS = /I$(INCDIR) /std:c++latest /EHsc /external:W3
CFLAGS   = $(CPPFLAGS) $(WFLAGS)
LFLAGS   = psapi.lib advapi32.lib user32.lib kernel32.lib gdi32.lib Wtsapi32.lib winmm.lib ws2_32.lib Shell32.lib ole32.lib oleaut32.lib

SRCDIR   = src
INCDIR   = include
OBJDIR   = obj
OUTDIR   = out

HEADERS  = $(INCDIR)\bonus.hpp $(INCDIR)\config.hpp $(INCDIR)\helpers.hpp
OBJ      = $(OBJDIR)\bonus.obj $(OBJDIR)\config.obj $(OBJDIR)\helpers.obj $(OBJDIR)\svc.obj $(OBJDIR)\winkey.obj 

CONFIG_OBJ  = $(OBJDIR)\config.obj
HELPERS_OBJ = $(OBJDIR)\helpers.obj $(CONFIG_OBJ)
BONUS_OBJ   = $(OBJDIR)\bonus.obj   $(HELPERS_OBJ)
SVC_OBJ     = $(OBJDIR)\svc.obj     $(BONUS_OBJ)
WINKEY_OBJ  = $(OBJDIR)\winkey.obj  $(BONUS_OBJ)

SVC        = $(OUTDIR)\svc.exe
WINKEY     = $(OUTDIR)\winkey.exe
TARGETS    = $(SVC) $(WINKEY)

.PHONY: all dirs clean rebuild

all: dirs $(TARGETS)

dirs:
	@if not exist $(OUTDIR) mkdir $(OUTDIR)
	@if not exist $(OBJDIR) mkdir $(OBJDIR)

{$(SRCDIR)}.cpp{$(OBJDIR)}.obj:
	@echo Compiling $<
	@$(CC) $(CFLAGS) /c $< /Fo$@

$(OBJ): $(HEADERS)

$(SVC): $(SVC_OBJ)
	@echo Linking $@
	@$(CC) $** $(LFLAGS) /Fe$@

$(WINKEY): $(WINKEY_OBJ)
	@echo Linking $@
	@$(CC) $** $(LFLAGS) /Fe$@

clean:
	@if exist $(OUTDIR) rmdir /s /q $(OUTDIR)
	@if exist $(OBJDIR) rmdir /s /q $(OBJDIR)

rebuild: clean all

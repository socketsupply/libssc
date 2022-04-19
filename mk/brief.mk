BRIEF_FORMAT ?= "  %s   \t%s\n"
BRIEF_ECHO ?= printf $(BRIEF_FORMAT) "$(1)" "$(2)" | tr '\n' ' ' && echo
BRIEFC += AR CC CP LN MKDIR RM STRIP

-include ./deps/brief.mk/brief.mk
-include ../deps/brief.mk/brief.mk

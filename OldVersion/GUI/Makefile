CTARGET=qrc_resources.cpp moc_*.cpp ui_* *.o *~ *.core *.pro.user.*
RM=@rm -f

default:
	@mv Makefile oldMakefile
	@qmake GUI.pro
	@make
	@rm Makefile
	@mv oldMakefile Makefile
	$(RM) $(CTARGET)
    
removeAll:
	$(RM) $(CTARGET)

clean:
	@echo "Cleaning build targets..."
	$(RM) $(CTARGET)

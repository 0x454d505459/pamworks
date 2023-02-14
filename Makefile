compile:
	gcc -fPIC -c pam_numworks.c
	gcc -shared -o pam_numworks.so pam_numworks.o -lpam -lusb-1.0
	@echo "Compiled!"

install:
	cp pam_numworks.so /lib/security/
	@echo "Installed"
	
uninstall:
	rm /lib/security/pam_numworks.so
	@echo "Uninstalled"

clean:
	rm pam_numworks.so pam_numworks.o
	@echo -e "Cleaned !"
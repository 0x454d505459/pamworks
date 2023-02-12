gcc -fPIC -c pam_numworks.c
gcc -shared -o pam_numworks.so pam_numworks.o -lpam -lusb-1.0
sudo cp pam_numworks.so /lib/security/
rm pam_numworks.so pam_numworks.o
echo "Built and installed !, Ready to be tested"
# Pamworks
PAM module to authenticate using your numworks calculator (doesn't provide pam.d rules)

## Build and Install

### Dependencies
- gcc

### Steps
1) Compile using `make`
2) Install using `sudo make install`

## Editin pam.d rules
<span style="font-size:2em">⚠️</span> **Make sure to read pam and pam.d manual pages first!**

Add that rule to any pam-aware app rules-set located in /etc/pam.d/APP_NAME: `auth		sufficient	pam_numworks.so <SERIAL NUMBER>`

Edit it according to your needs. I personally use my [Upsilon](https://github.com/upsilonnumworks/upsilon) calculator to authenticate in sudo.

Make sure you replace `<SERIAL NUMBER>` with your numwork's serial number


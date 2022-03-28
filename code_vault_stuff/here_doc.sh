#https://youtu.be/LbADc98lY0I?t=196

#include <stdio.h>

#example of heredoc 
# : '
# cat << HereDocDelemiter 
# hello word HereDocDelemiter >> HereDocTest
# '
cat -e << LINES | wc -l >>heredoc.txt
alias cc='gcc -Wall -Werror -pthread -O'

# Compile and run in one shot
alias ccr='gcc -Wall -Werror -pthread -O -o temp_prog && ./temp_prog'

# Quick cleanup
alias cclean='rm -f *.o temp_prog a.out core'

# Full clean (including common executable names)
alias cclear='rm -f *.o temp_prog a.out core pzip zip main test'

# Compile with debug info for gdb
alias ccd='gcc -Wall -Werror -pthread -g'
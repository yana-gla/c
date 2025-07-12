#!/bin/bash
# gcc compilation aliases: c89, c99, debug mode, release mode
alias gd='gcc -ansi -pedantic-errors -Wall -Wextra -g'
alias gc='gcc -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3'
alias gdo='gcc -ansi -pedantic-errors -Wall -Wextra -g -c'
alias gco='gcc -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -c'

alias gd9='gcc -std=c99 -pedantic-errors -Wall -Wextra -g'
alias gdo9='gcc -std=c99 -pedantic-errors -Wall -Wextra -g -c'
alias gc9='gcc -std=c99 -pedantic-errors -Wall -Wextra -DNDEBUG -O3'
alias gco9='gcc -std=c99 -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -c'

# Valgrind alias
alias vlg='valgrind --leak-check=yes --track-origins=yes'

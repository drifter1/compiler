#ifndef ANSI_COLORS_H
#define ANSI_COLORS_H

/*
 * Reference:
 * https://gist.github.com/RabaDabaDoba/145049536f815903c79944599c6f952a
 *
 * Changes performed:
 * The escape character "\e" was replaced with an escape ("\") on its Hex value
 * in ASCII (1B), since "\e" is a non-standard sequence.
 */

// Regular text
#define BLK "\x1B[0;30m"
#define RED "\x1B[0;31m"
#define GRN "\x1B[0;32m"
#define YEL "\x1B[0;33m"
#define BLU "\x1B[0;34m"
#define MAG "\x1B[0;35m"
#define CYN "\x1B[0;36m"
#define WHT "\x1B[0;37m"

// Regular bold text
#define BBLK "\x1B[1;30m"
#define BRED "\x1B[1;31m"
#define BGRN "\x1B[1;32m"
#define BYEL "\x1B[1;33m"
#define BBLU "\x1B[1;34m"
#define BMAG "\x1B[1;35m"
#define BCYN "\x1B[1;36m"
#define BWHT "\x1B[1;37m"

// Regular underline text
#define UBLK "\x1B[4;30m"
#define URED "\x1B[4;31m"
#define UGRN "\x1B[4;32m"
#define UYEL "\x1B[4;33m"
#define UBLU "\x1B[4;34m"
#define UMAG "\x1B[4;35m"
#define UCYN "\x1B[4;36m"
#define UWHT "\x1B[4;37m"

// Regular background
#define BLKB "\x1B[40m"
#define REDB "\x1B[41m"
#define GRNB "\x1B[42m"
#define YELB "\x1B[43m"
#define BLUB "\x1B[44m"
#define MAGB "\x1B[45m"
#define CYNB "\x1B[46m"
#define WHTB "\x1B[47m"

// High intensty background
#define BLKHB "\x1B[0;100m"
#define REDHB "\x1B[0;101m"
#define GRNHB "\x1B[0;102m"
#define YELHB "\x1B[0;103m"
#define BLUHB "\x1B[0;104m"
#define MAGHB "\x1B[0;105m"
#define CYNHB "\x1B[0;106m"
#define WHTHB "\x1B[0;107m"

// High intensty text
#define HBLK "\x1B[0;90m"
#define HRED "\x1B[0;91m"
#define HGRN "\x1B[0;92m"
#define HYEL "\x1B[0;93m"
#define HBLU "\x1B[0;94m"
#define HMAG "\x1B[0;95m"
#define HCYN "\x1B[0;96m"
#define HWHT "\x1B[0;97m"

// Bold high intensity text
#define BHBLK "\x1B[1;90m"
#define BHRED "\x1B[1;91m"
#define BHGRN "\x1B[1;92m"
#define BHYEL "\x1B[1;93m"
#define BHBLU "\x1B[1;94m"
#define BHMAG "\x1B[1;95m"
#define BHCYN "\x1B[1;96m"
#define BHWHT "\x1B[1;97m"

// Reset
#define CRESET "\x1B[0m"

#endif /* ANSI_COLORS_H */
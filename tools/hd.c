/* Enhanced hexdump -- 2012 Zephyr <zephyr@dirtbags.net>
 * 
 * This file is in the public domain.  I make no promises
 * about the functionality of this program.
 */

#include <stdio.h>
#include <stdint.h>
#include <string.h>

const char* charset[] = {
  "·", "☺", "☻", "♥", "♦", "♣", "♠", "•", "◘", "○", "◙", "♂", "♀", "♪", "♫", "☼",
  "►", "◄", "↕", "‼", "¶", "§", "▬", "↨", "↑", "↓", "→", "←", "∟", "↔", "▲", "▼",
  " ", "!", "\"", "#", "$", "%", "&", "'", "(", ")", "*", "+", ",", "-", ".", "/",
  "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", ":", ";", "<", "=", ">", "?", 
  "@", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O",
  "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "[", "\\", "]", "^", "_", 
  "`", "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", 
  "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "{", "|", "}", "~", "⌂", 
  "Ç", "ü", "é", "â", "ä", "à", "å", "ç", "ê", "ë", "è", "ï", "î", "ì", "Ä", "Å", 
  "É", "æ", "Æ", "ô", "ö", "ò", "û", "ù", "ÿ", "Ö", "Ü", "¢", "£", "¥", "€", "ƒ", 
  "á", "í", "ó", "ú", "ñ", "Ñ", "ª", "º", "½", "⅓", "¼", "⅕", "⅙", "⅛", "«", "»", 
  "░", "▒", "▓", "│", "┤", "╡", "╢", "╖", "╕", "╣", "║", "╗", "╝", "╜", "╛", "┐", 
  "└", "┴", "┬", "├", "─", "┼", "╞", "╟", "╚", "╔", "╩", "╦", "╠", "═", "╬", "╧", 
  "╨", "╤", "╥", "╙", "╘", "╒", "╓", "╫", "╪", "┘", "┌", "█", "▄", "▌", "▐", "▀", 
  "α", "ß", "Γ", "π", "Σ", "σ", "µ", "τ", "Φ", "Θ", "Ω", "δ", "∞", "φ", "ε", "∩", 
  "⁰", "¹", "²", "³", "⁴", "⁵", "⁶", "⁷", "⁸", "⁹", "ⁱ", "ⁿ", "⁽", "⁼", "⁾", "¤"
};

int
dump(FILE *f)
{
  uint64_t p        = 0;
  uint8_t  buf[32];
  int      offset   = 0;
  int      skipping = 0;

  while (!feof(f)) {
    uint8_t *bytes = buf + offset;
    size_t   len;
    int      i;

    offset = 16 - offset;

    len = fread(bytes, 1, 16, f);
    if (0 == len) break;

    if (p && (0 == memcmp(buf, buf + 16, 16))) {
      if (! skipping) {
        printf("*\n");
        skipping = 1;
      }
      p += 16;
      continue;
    } else {
      skipping = 0;
    }

    printf("%08lx  ", (long unsigned int)p);
    for (i = 0; i < 16; i += 1) {
      if (i < len) {
        printf("%02x ", bytes[i]);
      } else {
        printf("   ");
      }
      if (7 == i) {
        printf(" ");
      }
    }
    printf(" ┆");
    for (i = 0; i < len; i += 1) {
      printf("%s", charset[bytes[i]]);
    }
    if (-1 == printf("┆\n")) {
      perror("printf");
      return 1;
    }
    p += len;
  }
  printf("%08lx\n", (long unsigned int)p);

  return 0;
}

int
main(int argc, char *argv[])
{
  if (1 == argc) {
    dump(stdin);
  } else {
    FILE *f = fopen(argv[1], "rb");

    if (! f) {
      perror("open");
      return 1;
    }

    dump(f);
  }

  return 0;
}

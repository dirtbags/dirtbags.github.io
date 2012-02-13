/*
 * Last Modified: Thu 09 Feb 2012 02:10:31 PM CST
 *
 *   _   _Hex Dumper _      ____                           _   _
 *  | \ | | _____  _| |_   / ___| ___ _ __   ___ _ __ __ _| |_(_) ___  _ __
 *  |  \| |/ _ \ \/ / __| | |  _ / _ \ '_ \ / _ \ '__/ _` | __| |/ _ \| '_ \
 *  | |\  |  __/>  <| |_  | |_| |  __/ | | |  __/ | | (_| | |_| | (_) | | | |
 *  |_| \_|\___/_/\_\\__|  \____|\___|_| |_|\___|_|  \__,_|\__|_|\___/|_| |_|
 *
 *   Zephyr <zephyr@dirtbags.net>
 *   pi-rho <pi-rho@tyr.cx>
 *
 * This file is in the public domain.  I make no promises about the
 * functionality of this program.
 *
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <getopt.h>

#define VERSION "0.1337"

const char     *charset[] = {
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

void
usage(char *prog, bool error)
{
    fprintf(error ? stderr : stdout,
            "Usage: %s [-hvox] [-w width] [filename]\n", prog);
    fprintf(error ? stderr : stdout,
            "\t-x\tdo not print hexadecimal bytes\n");
    fprintf(error ? stderr : stdout, "\t-o\tdo not print offsets\n");
    fprintf(error ? stderr : stdout,
            "\t-w\tlength of data to show on each line\n");
    fprintf(error ? stderr : stdout,
            "\tif a filename is not specified, stdin will be used\n");
}

void
version(bool error)
{
    fprintf(error ? stderr : stdout, "Next Generation Hex Dump v.%s\n\n",
            VERSION);
}

void
dump(FILE * f, uint8_t width, bool hex, bool offsets)
{
    uint64_t        p = 0;
    uint64_t        op = 0;
    uint8_t         buf[2 * width];
    int             skipping = 0;
    bool            nl = true;

    if (width == 0) {           /* handle special case where user
                                 * specifies width of 0 */
        width = 16;
        nl = false;
        hex = false;
        offsets = false;
    }

    while (!feof(f)) {
        uint8_t         bytes[width];
        size_t          len;
        int             i;

        len = fread(bytes, 1, width, f);
        if (0 == len)
            break;
        op = p;
        p += len;

        if (hex) {
            if (p && (0 == memcmp(buf, buf + width, width))) {
                if (!skipping) {
                    printf("*\n");
                    skipping = 1;
                }
                continue;
            } else {
                skipping = 0;
            }
        }

        if (offsets)
            printf("%08lx  ", (long unsigned int) op);

        if (hex) {
            for (i = 0; i < width; i += 1) {
                if (i < len) {
                    printf("%02x ", bytes[i]);
                } else {
                    printf("   ");
                }
                if ((i + 1) % 8 == 0) {
                    printf(" ");
                }
            }
            printf("┆");
        }

        for (i = 0; i < len; i += 1) {
            printf("%s", charset[bytes[i]]);
        }

        if (hex) {
            printf("┆");
        }
        if (nl) {
            printf("\n");
        }
    }

    if (offsets)
        printf("%08lx\n", (long unsigned int) p);

    printf("\n");
}

int
main(int argc, char *argv[])
{
    uint8_t         width = 16;
    bool            hex = true;
    bool            offsets = true;
    int             opt;

    while ((opt = getopt(argc, argv, "hvxow:")) != -1) {
        switch (opt) {
        case 'w':              /* width */
            width = atoi(optarg);
            break;
        case 'x':              /* hex off */
            hex = false;
            break;
        case 'o':              /* offset off */
            offsets = false;
            break;
        case 'h':              /* help */
            usage(argv[0], false);
            return 0;
            break;
        case 'v':              /* version */
            version(false);
            return 0;
            break;
        default:               /* '?' */
            version(true);
            usage(argv[0], true);
            return 1;
        }
    }

    if (optind < argc) {
        FILE           *f = fopen(argv[optind], "rb");
        if (!f) {
            perror("open");
            return 1;
        }
        dump(f, width, hex, offsets);
    } else {
        dump(stdin, width, hex, offsets);
    }

    return 0;
}

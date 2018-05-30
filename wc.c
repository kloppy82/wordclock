#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define FNAME_WC24H_DE  "wc24h-tables-de.txt"
#define FNAME_WC24H_PL  "wc24h-tables-pl.txt"
#define FNAME_WC12H_CH1 "wc12h-tables-ch1.txt"
#define FNAME_WC12H_CH2 "wc12h-tables-ch2.txt"
#define FNAME_WC12H_DE  "wc12h-tables-de.txt"
#define FNAME_WC12H_EN1 "wc12h-tables-en1.txt"
#define FNAME_WC12H_EN2 "wc12h-tables-en2.txt"
#define FNAME_WC12H_FR  "wc12h-tables-fr.txt"
#define FNAME_WC12H_SE  "wc12h-tables-se.txt"
#define FNAME_WC12H_IT  "wc12h-tables-it.txt"

#include "tables-gen.h"

static uint_fast8_t         wc_rows;
static uint_fast8_t         wc_columns;
static uint_fast8_t         wp_count;
static WORD_ILLUMINATION *  illumination;
static uint_fast8_t         tbl_it_is[2];

static uint_fast8_t         display_modes_count;
static DISPLAY_MODES *      tbl_modes;

static uint_fast8_t         hour_modes_count;
static uint_fast8_t         hour_count;
static uint_fast8_t         max_hour_words;
static uint8_t ***          tbl_hours;

static uint_fast8_t         minute_modes_count;
static uint_fast8_t         minute_count;
static uint_fast8_t         max_minute_words;
static MINUTEDISPLAY **     tbl_minutes;

/*-------------------------------------------------------------------------------------------------------------------------------------------
 * hex to integer
 *-------------------------------------------------------------------------------------------------------------------------------------------
 */
uint16_t
htoi (char * buf, uint8_t max_digits)
{
    uint8_t     i;
    uint8_t     x;
    uint16_t    sum = 0;

    for (i = 0; i < max_digits && *buf; i++)
    {
	x = buf[i];

	if (x >= '0' && x <= '9')
	{
	    x -= '0';
	}
	else if (x >= 'A' && x <= 'F')
	{
	    x -= 'A' - 10;
	}
	else if (x >= 'a' && x <= 'f')
	{
	    x -= 'a' - 10;
	}
	else
	{
	    x = 0;
	}
	sum <<= 4;
	sum += x;
    }

    return (sum);
}

int
readhex (FILE * fp)
{
    char  buf[2];
    int   ch;

    do
    {
	ch = fgetc (fp);
    } while (ch == '\r' || ch == '\n' || ch == ' ' || ch == '\t');

    if (ch == EOF)
    {
	return (EOF);
    }

    buf[0] = ch;
    ch = fgetc (fp);

    if (ch == EOF)
    {
	return (EOF);
    }
    
    buf[1] = ch;
    return htoi (buf, 2);
}

void
readfile (char * fname)
{
    FILE *  fp;
    int     i;
    int     j;
    int     k;
    int     ch;

    fp = fopen (fname, "rb");

    if (! fp)
    {
	perror (fname);
	exit (1);
    }

    wc_rows         = readhex (fp);
    wc_columns      = readhex (fp);
    wp_count        = readhex (fp);

    illumination = calloc (wp_count, sizeof (WORD_ILLUMINATION));

    for (i = 0; i < wp_count; i++)
    {
	illumination[i].row = readhex (fp);
	illumination[i].col = readhex (fp);
	illumination[i].len = readhex (fp);
    }

    tbl_it_is[0] = readhex (fp);
    tbl_it_is[1] = readhex (fp);

    display_modes_count = readhex (fp);

    tbl_modes = calloc (display_modes_count, sizeof (DISPLAY_MODES));

    for (i = 0; i < display_modes_count; i++)
    {
	tbl_modes[i].hour_idx   = readhex (fp);
	tbl_modes[i].minute_idx = readhex (fp);

	j = 0;

	while ((ch = readhex (fp)) != '\0' && ch != EOF)
	{
	    if (j < DISPLAY_MODE_TEXT_LEN)
	    {
		tbl_modes[i].description[j++] = ch;
	    }
	} 

	tbl_modes[i].description[j] = '\0';
    }

    hour_modes_count    = readhex (fp);
    hour_count          = readhex (fp);
    max_hour_words      = readhex (fp);

    tbl_hours = calloc (hour_modes_count, sizeof (uint8_t **));

    for (i = 0; i < hour_modes_count; i++)
    {
	tbl_hours[i] = calloc (hour_count, sizeof (uint8_t *));

	for (j = 0; j < hour_count; j++)
	{
	    tbl_hours[i][j] = calloc (max_hour_words, sizeof (uint8_t));

	    for (k = 0; k < max_hour_words; k++)
	    {
		ch = readhex (fp);
		tbl_hours[i][j][k] = ch;

		if (ch == 0)
		{
		    break;
		}
	    }
	}
    }

    minute_modes_count  = readhex (fp);
    minute_count        = readhex (fp);
    max_minute_words    = readhex (fp);

    tbl_minutes = calloc (minute_modes_count, sizeof (MINUTEDISPLAY *));

    for (i = 0; i < minute_modes_count; i++)
    {
	tbl_minutes[i] = calloc (minute_count, sizeof (MINUTEDISPLAY));

	for (j = 0; j < minute_count; j++)
	{
	    tbl_minutes[i][j].flags = readhex (fp);

	    for (k = 0; k < max_minute_words; k++)
	    {
		ch = readhex (fp);
		tbl_minutes[i][j].word_idx[k] = ch;

		if (ch == 0)
		{
		    break;
		}
	    }
	}
    }

    fclose (fp);
}

#define OFF         0
#define ON          1

static const char * display_wc24h_de =
{
    "ES#IST#VIERTELEINS"
    "DREINERSECHSIEBEN#"
    "ELFÜNFNEUNVIERACHT"
    "NULLZWEI#ZWÖLFZEHN"
    "UND#ZWANZIGVIERZIG"
    "DREISSIGFÜNFZIGUHR"
    "MINUTEN#VORUNDNACH"
    "EINDREIVIERTELHALB"
    "SIEBENEUNULLZWEINE"
    "FÜNFSECHSNACHTVIER"
    "DREINSUND#ELF#ZEHN"
    "ZWANZIGGRADREISSIG"
    "VIERZIGZWÖLFÜNFZIG"
    "MINUTENUHR#FRÜHVOR"
    "ABENDSMITTERNACHTS"
    "MORGENSWARMMITTAGS"
};

static const char * display_wc24h_pl =
{
    "JEST*TRZECIASZOSTA"
    "DZIEWIATADZIESIATA"
    "SIODMACZWARTAOSMA*"
    "PIATADRUGAPIERWSZA"
    "DWUNASTAJEDENASTA*"
    "*PIECDZIESIAT*****"
    "****DWADZIESCIA***"
    "ZEROCZTERDZIESCI**"
    "*TRZYDZIESCI**ZERO"
    "DZIESIECTRZYNASCIE"
    "JEDENASCIEDZIEWIEC"
    "*****SZESNASCIE***"
    "***DZIEWIETNASCIE*"
    "CZTERNASCIE*SZESC*"
    "******PIETNASCIE**"
    "OSIEMNASCIE*CZTERY"
    "PIECDWANASCIE*****"
    "SIEDEMNASCIE*AM*PM"
};

static const char * display_wc12h_ch1 =
{
    "ESKISCHAFÜF"
    "VIERTUBFZÄÄ"
    "ZWÄNZGSIVOR"
    "ABOHAUBIEPM"
    "EISZWÖISDRÜ"
    "VIERIFÜFIQT"
    "SÄCHSISIBNI"
    "ACHTINÜNIEL"
    "ZÄNIERBEUFI"
    "ZWÖUFIAMUHR"
};

static const char * display_wc12h_ch2 =
{
    "ESKESCHAZÄÄ"
    "FÖIFCVIERTU"
    "ZWÄNZGSIVOR"
    "ABOHAUBIEGE"
    "EISZWÖISDRÜ"
    "VIERITFÖIFI"
    "SÄCHSISEBNI"
    "ACHTIENÜNIL"
    "ZÄNIERBELFI"
    "ZWÖLFINAUHR"
};

static const char * display_wc12h_de =
{
    "ESKISTLFÜNF"
    "ZEHNZWANZIG"
    "DREIVIERTEL"
    "TGNACHVORJM"
    "HALBQZWÖLFP"
    "ZWEINSIEBEN"
    "KDREIRHFÜNF"
    "ELFNEUNVIER"
    "WACHTZEHNRS"
    "BSECHSFMUHR"
};

static const char * display_wc12h_en1 =
{
    "ITLISASAMPM"
    "ACQUARTERDC"
    "TWENTYFIVEX"
    "HALFSTENFTO"
    "PASTERUNINE"
    "ONESIXTHREE"
    "FOURFIVETWO"
    "EIGHTELEVEN"
    "SEVENTWELVE"
    "TENSEOCLOCK"
};

static const char * display_wc12h_en2 =
{
    "ITKISGHALFE"
    "TENYQUARTER"
    "DTWENTYFIVE"
    "TOPASTEFOUR"
    "FIVETWONINE"
    "THREETWELVE"
    "BELEVENONES"
    "SEVENWEIGHT"
    "ITENSIXTIES"
    "TINEOICLOCK"
};

static const char * display_wc12h_fr =
{
    "ILNESTODEUX"
    "QUATRETROIS"
    "NEUFUNESEPT"
    "HUITSIXCINQ"
    "MIDIXMINUIT"
    "ONZERHEURES"
    "MOINSOLEDIX"
    "ETRQUARTPMD"
    "VINGT-CINQU"
    "ETSDEMIEPAM"
};

static const char * display_wc12h_se =
{
    "KLOCKANTÄRK"
    "FEMYISTIONI"
    "KVARTQIENZO"
    "TJUGOLIVIPM"
    "ÖVERKAMHALV"
    "ETTUSVLXTVA"
    "TREMYKYFYRA"
    "FEMSFLORSEX"
    "SJUÄTTAINIO"
    "TIOELVATOLV"
};

static const char * display_wc12h_it =
{
    "SONOXLEBDUE"
    "ETRESEIOTTO"
    "LACINQUEUNA"
    "WALCKYSETTE"
    "DIECIUNDICI"
    "QUATTRONOVE"
    "DOCICISMENO"
    "EPUNCQUARTO"
    "TRENTADIECI"
    "VENTICINQUE"
};


static const char *     display;
static char *           wcname;

static unsigned char ** front;
static unsigned char ** fronton;

static void
show_letter (uint8_t y, uint8_t x, uint8_t onoff)
{
    front[y][x] = display[wc_columns * y + x];
    fronton[y][x] = onoff;
}

static void
show_table (void)
{
    uint8_t y;
    uint8_t x;

    for (y = 0; y < wc_rows; y++)
    {
	for (x = 0; x < wc_columns; x++)
	{
	    show_letter (y, x, OFF);
	}
    }
}

static void
show_word (uint8_t i)
{
    uint8_t y = illumination[i].row;
    uint8_t x = illumination[i].col;
    uint8_t l = illumination[i].len;

    while (l--)
    {
	show_letter (y, x, 1);
	x++;
    }
}

static void
show_clock (uint8_t mode, uint8_t hour, uint8_t minute)
{
    static uint8_t *        words;
    const MINUTEDISPLAY *   tbl_minute;
    uint8_t                 hour_mode;
    uint8_t                 minute_mode;
    uint_fast8_t            it_is_mode;
    uint8_t *               word_idx_p;
    int                     is_midnight = 0;
    uint8_t                 idx;

    if (! words)
    {
	words = calloc (wp_count, sizeof (uint8_t));
    }

    hour_mode = tbl_modes[mode].hour_idx;
    minute_mode = tbl_modes[mode].minute_idx;

    printf ("%s %02d:%02d&nbsp;&nbsp;<pre>", wcname, hour, minute);
    memset (words, 0, wp_count);
    show_table ();

    // get the minute words from minute table
    if (minute_count == 12)
    {
	tbl_minute  = &tbl_minutes[minute_mode][minute / 5];
    }
    else
    {
	tbl_minute = &tbl_minutes[minute_mode][minute];
    }

    it_is_mode = tbl_minute->flags & MDF_IT_IS_1;

    if (it_is_mode)
    {
	words[tbl_it_is[0]] = 1;
	words[tbl_it_is[1]] = 1;
    }

    for (idx = 0; idx < max_minute_words && tbl_minute->word_idx[idx] != 0; idx++)
    {
	words[tbl_minute->word_idx[idx]] = 1;
    }

    if (hour >= hour_count)                                     // WC12h: we have only 12 hours
    {
	hour -= hour_count;
    }
    else if (hour == 0)
    {
	is_midnight = 1;
    }

    if (tbl_minute->flags & MDF_HOUR_OFFSET_1)
    {
	hour += 1;                                              // correct hour offset
    }
    else if (tbl_minute->flags & MDF_HOUR_OFFSET_2)             // only used in jester mode
    {
	hour += 2;                                              // correct hour offset
    }

    if (hour >= hour_count)
    {
	if (hour == hour_count)
	{
	    is_midnight = 1;
	}
	hour -= hour_count;
    }

    word_idx_p = tbl_hours[hour_mode][hour];                    // get the hour words from hour table

    for (idx = 0; idx < MAX_HOUR_WORDS && word_idx_p[idx] != 0; idx++)
    {
	if (word_idx_p[idx] == WP_IF_MINUTE_IS_0)               // if minute is null take word index + 1, otherwise word index + 2
	{                                                       // this handles "EIN UHR" instead of "EINS UHR" at 01:00 & 13:00
	    if (minute == 0)
	    {
		words[word_idx_p[idx + 1]] = 1;
	    }
	    else
	    {
		words[word_idx_p[idx + 2]] = 1;
	    }
	    idx += 2;
	}
	else if (word_idx_p[idx] == WP_IF_HOUR_IS_0)            // if hour is null take word index + 1, otherwise word index + 2
	{                                                       // this handles "MINUIT" instead of "MIDI" at 00:00 in french moede
	    if (is_midnight)
	    {
		words[word_idx_p[idx + 1]] = 1;
	    }
	    else
	    {
		words[word_idx_p[idx + 2]] = 1;
	    }
	    idx += 2;
	}
	else
	{
	    words[word_idx_p[idx]] = 1;
	}
    }

    for (idx = 0; idx < wp_count; idx++)
    {
	if (words[idx])
	{
	    show_word (idx);
	}
    }

    puts ("</pre><P>");
}

static void
show_mode (int mode)
{
    printf ("<small>Mode %d: %s</small>", mode, tbl_modes[mode].description);
}

char *
to_html (int ch)
{
    static char str[8];

    switch (ch)
    {
	case 0xc4: strcpy (str, "&Auml"); break;
	case 0xd6: strcpy (str, "&Ouml"); break;
	case 0xdc: strcpy (str, "&Uuml"); break;
	default : str[0] = ch; str[1] = '\0'; break;
    }
    return str;
}

int
main (int argc, char ** argv)
{
    char *  fname;
    uint8_t y;
    uint8_t x;
    uint8_t hour        = 0;
    uint8_t minute      = 0;
    uint8_t mode        = 0;
    uint8_t i;
    uint8_t step;

    if (argc != 5)
    {
	return 1;
    }

    wcname = argv[1];

    if (! strcmp (wcname, "wc12h-ch1"))
    {
	fname = FNAME_WC12H_CH1;
	display = display_wc12h_ch1;
    }
    else if (! strcmp (wcname, "wc12h-ch2"))
    {
	fname = FNAME_WC12H_CH2;
	display = display_wc12h_ch2;
    }
    else if (! strcmp (wcname, "wc12h-de"))
    {
	fname = FNAME_WC12H_DE;
	display = display_wc12h_de;
    }
    else if (! strcmp (wcname, "wc12h-en1"))
    {
	fname = FNAME_WC12H_EN1;
	display = display_wc12h_en1;
    }
    else if (! strcmp (wcname, "wc12h-en2"))
    {
	fname = FNAME_WC12H_EN2;
	display = display_wc12h_en2;
    }
    else if (! strcmp (wcname, "wc12h-fr"))
    {
	fname = FNAME_WC12H_FR;
	display = display_wc12h_fr;
    }
    else if (! strcmp (wcname, "wc12h-se"))
    {
	fname = FNAME_WC12H_SE;
	display = display_wc12h_se;
    }
    else if (! strcmp (wcname, "wc12h-it"))
    {
    fname = FNAME_WC12H_IT;
    display = display_wc12h_it;
    }
    else if (! strcmp (wcname, "wc24h-pl"))
    {
	fname = FNAME_WC24H_PL;
	display = display_wc24h_pl;
	wcname = "wc24h-pl";
    }
    else // if (! strcmp (wcname, "wc24h-de"))
    {
	fname = FNAME_WC24H_DE;
	display = display_wc24h_de;
	wcname = "wc24h-de";
    }

    readfile (fname);

    mode = atoi (argv[2]);

    if (mode >= display_modes_count)
    {
	mode = 0;
    }

    hour = atoi (argv[3]);

    hour %= 24;

    minute = atoi (argv[4]);

    if (minute_count == 12)
    {
	minute = 5 * (minute / 5);
    }

    minute %= 60;

    front = calloc (wc_rows, sizeof (unsigned char *));

    for (i = 0; i < wc_rows; i++)
    {
	front[i] = calloc (wc_columns, sizeof (unsigned char));
    }

    fronton = calloc (wc_rows, sizeof (unsigned char *));

    for (i = 0; i < wc_rows; i++)
    {
	fronton[i] = calloc (wc_columns, sizeof (unsigned char));
    }

    puts ("<html>");

    puts (" <link rel=\"stylesheet\" href=\"styles.css\">\n");
    puts ("     <head>\n");
    puts ("         <title>WC24h</title>\n");
    puts ("     </head>\n");
    puts ("     <body>\n");

    puts ("<table border=0 cellspacing=0>");
    puts ("<tr valign=top><td width=120px>");

    if (minute_count == 12)
    {
	step = 5;
    }
    else
    {
	step = 1;
    }

    if (! strcmp (wcname, "wc24h-de"))
    {
	puts ("<a href=/?w=wc24h-de><font color=red>wc24h-de</font></a><BR>");
    }
    else
    {
	puts ("<a href=/?w=wc24h-de>wc24h-de</a><BR>");
    }

    if (! strcmp (wcname, "wc24h-pl"))
    {
	puts ("<a href=/?w=wc24h-pl><font color=red>wc24h-pl</font></a><BR>");
    }
    else
    {
	puts ("<a href=/?w=wc24h-pl>wc24h-pl</a><BR>");
    }

    if (! strcmp (wcname, "wc12h-de"))
    {
	puts ("<a href=/?w=wc12h-de><font color=red>wc12h-de</font></a><BR>");
    }
    else
    {
	puts ("<a href=/?w=wc12h-de>wc12h-de</a><BR>");
    }

    if (! strcmp (wcname, "wc12h-ch1"))
    {
	puts ("<a href=/?w=wc12h-ch1><font color=red>wc12h-ch1</font></a><BR>");
    }
    else
    {
	puts ("<a href=/?w=wc12h-ch1>wc12h-ch1</a><BR>");
    }

    if (! strcmp (wcname, "wc12h-ch2"))
    {
	puts ("<a href=/?w=wc12h-ch2><font color=red>wc12h-ch2</font></a><BR>");
    }
    else
    {
	puts ("<a href=/?w=wc12h-ch2>wc12h-ch2</a><BR>");
    }

    if (! strcmp (wcname, "wc12h-en1"))
    {
	puts ("<a href=/?w=wc12h-en1><font color=red>wc12h-en1</font></a><BR>");
    }
    else
    {
	puts ("<a href=/?w=wc12h-en1>wc12h-en1</a><BR>");
    }

    if (! strcmp (wcname, "wc12h-en2"))
    {
	puts ("<a href=/?w=wc12h-en2><font color=red>wc12h-en2</font></a><BR>");
    }
    else
    {
	puts ("<a href=/?w=wc12h-en2>wc12h-en2</a><BR>");
    }

    if (! strcmp (wcname, "wc12h-fr"))
    {
	puts ("<a href=/?w=wc12h-fr><font color=red>wc12h-fr</font></a><BR>");
    }
    else
    {
	puts ("<a href=/?w=wc12h-fr>wc12h-fr</a><BR>");
    }

    if (! strcmp (wcname, "wc12h-se"))
    {
	puts ("<a href=/?w=wc12h-se><font color=red>wc12h-se</font></a><BR>");
    }
    else
    {
	puts ("<a href=/?w=wc12h-se>wc12h-se</a><BR>");
    }


    puts ("</td><td valign=top width=230px>");

    for (i = 0; i < display_modes_count; i++)
    {
	if (i == mode)
	{
	    printf ("<a href=/?w=%s&x=%d&h=%d&m=%d><font color=red>%s</font></a><BR>", wcname, i, hour, minute, tbl_modes[i].description);
	}
	else
	{
	    printf ("<a href=/?w=%s&x=%d&h=%d&m=%d>%s</a><BR>", wcname, i, hour, minute, tbl_modes[i].description);
	}
    }
    puts ("<BR>");
    printf ("<a href=/?w=%s&x=%d&h=%d&m=%d>Stunde -</a>&nbsp;&nbsp;&nbsp;", wcname, mode, hour > 0 ? hour - 1 : 23, minute);
    printf ("<a href=/?w=%s&x=%d&h=%d&m=%d>Stunde +</a>&nbsp;&nbsp;&nbsp;", wcname, mode, hour < 23 ? hour + 1 : 0, minute);
    puts ("<BR>");
    printf ("<a href=/?w=%s&x=%d&h=%d&m=%d>Minute -</a>&nbsp;&nbsp;&nbsp;", wcname, mode, hour, minute >= step ? minute - step : 60 - step);
    printf ("<a href=/?w=%s&x=%d&h=%d&m=%d>Minute +</a>&nbsp;&nbsp;&nbsp;", wcname, mode, hour, minute <= 60 - step ? minute + step : 0);

    puts ("</td><td>");
    show_table ();
    show_clock (mode, hour, minute);
    show_mode (mode);

    puts ("<table border=0 cellspacing=0>");

    for (y = 0; y < wc_rows; y++)
    {
	puts ("<tr>");

	for (x = 0; x < wc_columns; x++)
	{
	    printf ("<td style=\"padding-left:3px;padding-right:3px;\" align=center bgcolor=black><font color=%s>%s</font></td>\n",
		    fronton[y][x]? "red" : "grey", to_html (front[y][x]));
	}

	puts ("</tr>");
    }

    puts ("</table>");

    puts ("</td></tr>");
    puts ("</table>");

    puts ("</body>");
    puts ("</html>");

    return 0;
}

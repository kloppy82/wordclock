/*-------------------------------------------------------------------------------------------------------------------------------------------
 * tables12h-it.c - tables for italian WordClock12h
 *
 * Copyright (c) 2018 Frank Meyer - frank(at)fli4l.de
 *
 * Layout:
 *
 *   SONOXLEBDUE
 *   ETRESEIOTTO
 *   LACINQUEUNA
 *   WALCKYSETTE
 *   DIECIUNDICI
 *   QUATTRONOVE
 *   DODICISMENO
 *   EPUNCQUARTO
 *   TRENTADIECI
 *   VENTICINQUE
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *-------------------------------------------------------------------------------------------------------------------------------------------
 */

#if WCLOCK24H == 0
#include "tables12h-it.h"
#include "tables-gen.h"
#include "tables-ext.h"

const DISPLAY_MODES tbl_modes[DISPLAY_MODES_COUNT] =
{
    { 0, 0, "ITALIANO" },
};

const uint8_t tbl_it_is[2] = { WP_SONO_IT_UNUSED, WP_LE_IT_UNUSED};

const uint8_t tbl_hours[HOUR_MODES_COUNT][HOUR_COUNT][MAX_HOUR_WORDS] =
{
    // SWISS1
    {                       // tbl_hours[1][] = hh:mm (not hh:00)
        {WP_SONO_IT,    WP_LE_IT,   WP_DODICI_IT},     // 00:mm
        {WP_E1_IT,      WP_LA_IT,   WP_UNA_IT},        // 01:mm
        {WP_SONO_IT,    WP_LE_IT,   WP_DUE_IT},        // 02:mm
        {WP_SONO_IT,    WP_LE_IT,   WP_TRE_IT},        // 03:mm
        {WP_SONO_IT,    WP_LE_IT,   WP_QUATTRO_IT},    // 04:mm
        {WP_SONO_IT,    WP_LE_IT,   WP_CINQUE1_IT},    // 05:mm
        {WP_SONO_IT,    WP_LE_IT,   WP_SEI_IT},        // 06:mm
        {WP_SONO_IT,    WP_LE_IT,   WP_SETTE_IT},      // 07:mm
        {WP_SONO_IT,    WP_LE_IT,   WP_OTTO_IT},       // 08:mm
        {WP_SONO_IT,    WP_LE_IT,   WP_NOVE_IT},       // 09:mm
        {WP_SONO_IT,    WP_LE_IT,   WP_DIECI1_IT},     // 10:mm
        {WP_SONO_IT,    WP_LE_IT,   WP_UNDICI_IT}      // 11:mm
    },
};

const MINUTEDISPLAY tbl_minutes[MINUTE_MODES_COUNT][MINUTE_COUNT] =
{
    {                                                               // tbl_minutes[4][] = ITALIENISCH
        {MDF_IT_IS_1 | MDF_HOUR_OFFSET_0, {0                                           }},         // 00
        {MDF_IT_IS_1 | MDF_HOUR_OFFSET_0, {WP_E2_IT,    WP_CINQUE2_IT                  }},         // 05
        {MDF_IT_IS_1 | MDF_HOUR_OFFSET_0, {WP_E2_IT,    WP_DIECI2_IT                   }},         // 10
        {MDF_IT_IS_1 | MDF_HOUR_OFFSET_0, {WP_E2_IT,    WP_UN_IT,       WP_QUARTO_IT   }},         // 15
        {MDF_IT_IS_1 | MDF_HOUR_OFFSET_0, {WP_E2_IT,    WP_VENTI_IT                    }},         // 20
        {MDF_IT_IS_1 | MDF_HOUR_OFFSET_1, {WP_E2_IT,    WP_VENTI_IT,    WP_CINQUE2_IT  }},         // 25
        {MDF_IT_IS_1 | MDF_HOUR_OFFSET_1, {WP_E2_IT,    WP_TRENTA_IT                   }},         // 30
        {MDF_IT_IS_1 | MDF_HOUR_OFFSET_1, {WP_E2_IT,    WP_TRENTA_IT,   WP_CINQUE2_IT, }},         // 35
        {MDF_IT_IS_1 | MDF_HOUR_OFFSET_1, {WP_MENO_IT,  WP_VENTI_IT                    }},         // 40
        {MDF_IT_IS_1 | MDF_HOUR_OFFSET_1, {WP_MENO_IT,  WP_UN_IT,       WP_QUARTO_IT   }},         // 45
        {MDF_IT_IS_1 | MDF_HOUR_OFFSET_1, {WP_MENO_IT,  WP_DIECI2_IT                   }},         // 50
        {MDF_IT_IS_1 | MDF_HOUR_OFFSET_1, {WP_MENO_IT,  WP_CINQUE2_IT                  }},         // 55
    },
};

const WORD_ILLUMINATION illumination[WP_COUNT] =
{
    {0,0,0},  //  0 = WP_END_OF_WORDS = ""

    {0,0,4},  // 27 = WP_SONO_IT,   = "ES"
    {0,5,2},  // 28 = WP_LE_IT,   = "ISCH"
    {2,2,6},  // 29 = WP_CINQUE1_IT,   = "FÜF"
    {7,5,6},  // 30 = WP_QUARTO_IT,   = "VIERTU"
    {4,0,5},  // 31 = WP_DIECI1_IT,   = "ZÄÄ"
    {9,0,5},  // 32 = WP_VENTI_IT,   = "ZWÄNZG"
    {6,7,4},  // 33 = WP_MENO_IT,    = "VOR"
    {1,0,1},  // 34 = WP_E1_IT,  = "AB"
    {3,3,5},  // 35 = WP_MEZZO_IT,   = "HAUBI"
    {2,8,3},  // 36 = WP_UNA_IT,   = "EIS"
    {0,8,3},  // 37 = WP_DUE_IT,   = "ZWÖI"
    {1,1,3},  // 38 = WP_TRE_IT,   = "DRÜ"
    {5,0,7},  // 39 = WP_QUATTRO_IT,   = "VIERI"
    {9,5,6},  // 40 = WP_CINQUE2_IT,   = "FÜFI"
    {1,4,3},  // 41 = WP_SEI_IT,   = "SÄCHSI"
    {3,6,5},  // 42 = WP_SETTE_IT,   = "SIBNI"
    {1,7,4},  // 43 = WP_OTTO_IT,   = "ACHTI"
    {5,7,4},  // 44 = WP_NOVE_IT,   = "NÜNI"
    {8,6,5},  // 45 = WP_DIECI2_IT,   = "ZÄNI"
    {4,5,6},  // 46 = WP_UNDICI_IT,   = "EUFI"
    {6,0,6},  // 47 = WP_DODICI_IT,   = "ZWÖUFI"
    {7,2,2},  // 48 = WP_UN_IT,   = "UHR"
    {8,0,6},  // 49 = WP_TRENTA_IT
    {2,0,2},  // 49 = WP_LA_IT,
    {7,0,1},  // 49 = WP_E2_IT,
};
    
    
#if 0 // ITALIAN
const char * display[WC_ROWS] =
{
    "SONOXLEBDUE",
    "ETRESEIOTTO",
    "LACINQUEUNA",
    "WALCKYSETTE",
    "DIECIUNDICI",
    "QUATTRONOVE",
    "DODICISMENO",
    "EPUNCQUARTO",
    "TRENTADIECI",
    "VENTICINQUE"
};
#endif // 0

#endif

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
 *   DOCICISMENO
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

const uint8_t tbl_it_is[2] = { WP_SONO_IT, WP_LE_IT };

const uint8_t tbl_hours[HOUR_MODES_COUNT][HOUR_COUNT][MAX_HOUR_WORDS] =
{
    // SWISS1
    {                       // tbl_hours[1][] = hh:mm (not hh:00)
        {WP_DODICI_IT},     // 00:mm
        {WP_UNA_IT},        // 01:mm
        {WP_DUE_IT},        // 02:mm
        {WP_TRE_IT},        // 03:mm
        {WP_QUATTRO_IT},    // 04:mm
        {WP_CINQUE1_IT},    // 05:mm
        {WP_SEI_IT},        // 06:mm
        {WP_SETTE_IT},      // 07:mm
        {WP_OTTO_IT},       // 08:mm
        {WP_NOVE_IT},       // 09:mm
        {WP_DIECI1_IT},     // 10:mm
        {WP_UNDICI_IT}      // 11:mm
    },
};

const MINUTEDISPLAY tbl_minutes[MINUTE_MODES_COUNT][MINUTE_COUNT] =
{
    {                                                               // tbl_minutes[4][] = SCHWEIZERDEUTSCH1
        {MDF_IT_IS_1 | MDF_HOUR_OFFSET_0, {0                                        }},         // 00
        {MDF_IT_IS_1 | MDF_HOUR_OFFSET_0, {WP_CINQUE2_IT,   WP_E_IT                  }},         // 05
        {MDF_IT_IS_1 | MDF_HOUR_OFFSET_0, {WP_DIECI2_IT,    WP_E_IT                  }},         // 10
        {MDF_IT_IS_1 | MDF_HOUR_OFFSET_0, {WP_QUARTO_IT,    WP_E_IT                  }},         // 15
        {MDF_IT_IS_1 | MDF_HOUR_OFFSET_0, {WP_VENTI_IT,     WP_E_IT                  }},         // 20
        {MDF_IT_IS_1 | MDF_HOUR_OFFSET_1, {WP_VENTI_IT,     WP_CINQUE2_IT    }},         // 25
        {MDF_IT_IS_1 | MDF_HOUR_OFFSET_1, {WP_MEZZO_IT                              }},         // 30
        {MDF_IT_IS_1 | MDF_HOUR_OFFSET_1, {WP_TRENTA_IT,    WP_CINQUE2_IT,   }},         // 35
        {MDF_IT_IS_1 | MDF_HOUR_OFFSET_1, {WP_VENTI_IT,     WP_MENO_IT                 }},         // 40
        {MDF_IT_IS_1 | MDF_HOUR_OFFSET_1, {WP_QUARTO_IT,    WP_MENO_IT                 }},         // 45
        {MDF_IT_IS_1 | MDF_HOUR_OFFSET_1, {WP_DIECI2_IT,    WP_MENO_IT                 }},         // 50
        {MDF_IT_IS_1 | MDF_HOUR_OFFSET_1, {WP_CINQUE2_IT,   WP_MENO_IT                 }},         // 55
    },
};

const WORD_ILLUMINATION illumination[WP_COUNT] =
{
    {0,0,0},                                                        //  0 = WP_END_OF_WORDS = ""

    {0,0,4},                                                        // 27 = WP_ES_IT        = "ES"
    {0,3,4},                                                        // 28 = WP_ISCH_IT      = "ISCH"
    {0,8,3},                                                        // 29 = WP_FUEF_IT      = "FÜF"
    {1,0,6},                                                        // 30 = WP_VIERTU_IT    = "VIERTU"
    {1,8,3},                                                        // 31 = WP_ZAEAE_IT     = "ZÄÄ"
    {2,0,6},                                                        // 32 = WP_ZWAENZG_IT   = "ZWÄNZG"
    {2,8,3},                                                        // 33 = WP_MENO_IT       = "VOR"
    {3,0,2},                                                        // 34 = WP_E_IT        = "AB"
    {3,3,5},                                                        // 35 = WP_HAUBI_IT     = "HAUBI"
    {4,0,3},                                                        // 36 = WP_EIS_IT       = "EIS"
    {4,3,4},                                                        // 37 = WP_ZWOEI_IT     = "ZWÖI"
    {4,8,3},                                                        // 38 = WP_DRUE_IT      = "DRÜ"
    {5,0,5},                                                        // 39 = WP_VIERI_IT     = "VIERI"
    {5,5,4},                                                        // 40 = WP_FUEFI_IT     = "FÜFI"
    {6,0,6},                                                        // 41 = WP_SAECHSI_IT   = "SÄCHSI"
    {6,6,5},                                                        // 42 = WP_SIBNI_IT     = "SIBNI"
    {7,0,5},                                                        // 43 = WP_ACHTI_IT     = "ACHTI"
    {7,5,4},                                                        // 44 = WP_NUENI_IT     = "NÜNI"
    {8,0,4},                                                        // 45 = WP_ZAENI_IT     = "ZÄNI"
    {8,7,4},                                                        // 46 = WP_EUFI_IT      = "EUFI"
    {9,0,6},                                                        // 47 = WP_ZWOEFI_IT    = "ZWÖUFI"
    {9,8,3},                                                        // 48 = WP_UHR_IT       = "UHR"

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
    "DOCICISMENO",
    "EPUNCQUARTO",
    "TRENTADIECI",
    "VENTICINQUE"
};
#endif // 0

#endif

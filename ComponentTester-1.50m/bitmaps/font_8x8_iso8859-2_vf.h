/* ************************************************************************
 *
 *   monospaced 8x8 font based on ISO 8859-2
 *   vertically aligned, vertical bit order flipped
 *
 *   (c) 2015-2023 by Markus Reschke
 *   Central European characters added by Bohu
 *   Inverted digits 1-3 by Feliciano, inverted x by indman
 *
 * ************************************************************************ */


/* ************************************************************************
 *   font data
 * ************************************************************************ */

#ifdef FONT_8X8_ISO8859_2_VF


/* source management */
#define FONT_SET                   /* font set included */

/* font size */
#define FONT_SIZE_X          8     /* width:  8 dots */
#define FONT_SIZE_Y          8     /* height: 8 dots */

/* font data format */
#define FONT_BYTES_N         8     /* 8 bytes per character */
#define FONT_BYTES_X         8     /* 8 bytes in x direction */
#define FONT_BYTES_Y         1     /* 1 byte in y direction */


/*
 *  character bitmaps
 *  - to reduce size we place some symbols and special characters at
 *    positions 0-15, and we move the standard chars up in the list by
 *    16 positions (using ASCII's 0-31 for control chars)
 *  - format:
 *    - 8 bytes per character
 *    - first byte: first vertical line (left to right)
 *    - bit #0: top / bit #7: bottom (vertically flipped)
 */

const uint8_t FontData[] PROGMEM = {
  /* symbols and special characters */
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,   /* 0x00 n/a */
  0x08,0x7F,0x3E,0x1C,0x08,0x7F,0x7F,0x08,   /* 0x01 symbol: diode A-C */
  0x08,0x7F,0x7F,0x08,0x1C,0x3E,0x7F,0x08,   /* 0x02 symbol: diode C-A */
  0x08,0x7F,0x7F,0x00,0x00,0x7F,0x7F,0x08,   /* 0x03 symbol: capacitor */
  0x4C,0x5E,0x72,0x02,0x72,0x5E,0x4C,0x00,   /* 0x04 omega */
  0xC0,0x7E,0x3E,0x20,0x1E,0x3E,0x20,0x00,   /* 0x05 µ (micro) */
  0x08,0x7F,0x41,0x41,0x41,0x41,0x41,0x41,   /* 0x06 symbol: resistor left side */
  0x41,0x41,0x41,0x41,0x41,0x41,0x7F,0x08,   /* 0x07 symbol: resistor right side */

  0x7D,0x7E,0x13,0x11,0x13,0x7E,0x7D,0x00,   /* 0x08 Ä (A umlaut) */
  0x1D,0x3E,0x63,0x41,0x63,0x3E,0x1D,0x00,   /* 0x09 Ö (O umlaut) */
  0x3F,0x7F,0x41,0x40,0x41,0x7F,0x3F,0x00,   /* 0x0a Ü (U umlaut) */
  0xFF,0xFF,0x49,0x49,0x49,0x7F,0x36,0x00,   /* 0x0b ß (sharp s) */
  0x31,0x7A,0x4A,0x4A,0x7E,0x3D,0x40,0x00,   /* 0x0c ä (a umlaut) */
  0x18,0x3D,0x66,0x42,0x66,0x3D,0x18,0x00,   /* 0x0d ö (o umlaut) */
  0x3E,0x7E,0x41,0x40,0x21,0x7E,0x7E,0x00,   /* 0x0e ü (u umlaut) */
  0x00,0x00,0x02,0x05,0x02,0x00,0x00,0x00,   /* 0x0f ° (degree) */

  /* standard characters */
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,   /* 0x10 space */
  0x00,0x06,0x6F,0x6F,0x06,0x00,0x00,0x00,   /* 0x11 ! */
  0x00,0x0B,0x07,0x00,0x00,0x0B,0x07,0x00,   /* 0x12 " */
  0x36,0x7F,0x7F,0x36,0x7F,0x7F,0x36,0x00,   /* 0x13 # */
  0x04,0x2E,0x2A,0x6B,0x2A,0x3A,0x10,0x00,   /* 0x14 $ */
  0x63,0x73,0x38,0x1C,0x0E,0x67,0x63,0x00,   /* 0x15 % */
  0x36,0x7F,0x49,0x79,0x3B,0x6A,0x48,0x00,   /* 0x16 & */
  0x00,0x00,0x07,0x0B,0x00,0x00,0x00,0x00,   /* 0x17 Ž */
  0x00,0x00,0x1C,0x3E,0x63,0x41,0x00,0x00,   /* 0x18 ( */
  0x00,0x00,0x41,0x63,0x3E,0x1C,0x00,0x00,   /* 0x19 ) */
  0x00,0x15,0x0A,0x1F,0x1F,0x0A,0x15,0x00,   /* 0x1a * */
  0x00,0x18,0x18,0x7E,0x7E,0x18,0x18,0x00,   /* 0x1b + */
  0x00,0x00,0xB0,0x70,0x00,0x00,0x00,0x00,   /* 0x1c , */
  0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x00,   /* 0x1d - */
  0x00,0x00,0x60,0x60,0x00,0x00,0x00,0x00,   /* 0x1e . */
  0x60,0x70,0x38,0x1C,0x0E,0x07,0x03,0x00,   /* 0x1f / */
  0x1C,0x3E,0x63,0x41,0x63,0x3E,0x1C,0x00,   /* 0x20 0 */
  0x00,0x42,0x7F,0x7F,0x40,0x00,0x00,0x00,   /* 0x21 1 */
  0x62,0x73,0x51,0x59,0x49,0x4F,0x46,0x00,   /* 0x22 2 */
  0x22,0x63,0x41,0x49,0x49,0x77,0x36,0x00,   /* 0x23 3 */
  0x18,0x1C,0x16,0x13,0x7F,0x7F,0x10,0x00,   /* 0x24 4 */
  0x27,0x67,0x45,0x45,0x45,0x7D,0x38,0x00,   /* 0x25 5 */
  0x3C,0x7E,0x4B,0x49,0x49,0x79,0x30,0x00,   /* 0x26 6 */
  0x03,0x03,0x71,0x79,0x0D,0x07,0x03,0x00,   /* 0x27 7 */
  0x36,0x7F,0x49,0x49,0x49,0x7F,0x36,0x00,   /* 0x28 8 */
  0x06,0x4F,0x49,0x49,0x69,0x3F,0x1E,0x00,   /* 0x29 9 */
  0x00,0x00,0x00,0x66,0x66,0x00,0x00,0x00,   /* 0x2a : */
  0x00,0x00,0x00,0xA6,0x66,0x00,0x00,0x00,   /* 0x2b ; */
  0x00,0x08,0x1C,0x36,0x63,0x00,0x00,0x00,   /* 0x2c < */
  0x36,0x36,0x36,0x36,0x36,0x36,0x36,0x00,   /* 0x2d = */
  0x00,0x41,0x63,0x36,0x1C,0x08,0x00,0x00,   /* 0x2e > */
  0x02,0x03,0x69,0x6D,0x07,0x06,0x00,0x00,   /* 0x2f ? */
  0x3E,0x63,0x5D,0x55,0x5D,0x6B,0x2E,0x00,   /* 0x30 @ */
  0x7C,0x7E,0x13,0x11,0x13,0x7E,0x7C,0x00,   /* 0x31 A */
  0x7F,0x7F,0x49,0x49,0x49,0x7F,0x36,0x00,   /* 0x32 B */
  0x1C,0x3E,0x63,0x41,0x41,0x63,0x22,0x00,   /* 0x33 C */
  0x7F,0x7F,0x41,0x41,0x63,0x3E,0x1C,0x00,   /* 0x34 D */
  0x7F,0x7F,0x49,0x49,0x49,0x49,0x41,0x00,   /* 0x35 E */
  0x7F,0x7F,0x09,0x09,0x09,0x09,0x01,0x00,   /* 0x36 F */
  0x1C,0x3E,0x63,0x41,0x49,0x79,0x79,0x00,   /* 0x37 G */
  0x7F,0x7F,0x08,0x08,0x08,0x7F,0x7F,0x00,   /* 0x38 H */
  0x00,0x00,0x41,0x7F,0x7F,0x41,0x00,0x00,   /* 0x39 I */
  0x30,0x70,0x40,0x40,0x40,0x7F,0x3F,0x00,   /* 0x3a J */
  0x7F,0x7F,0x18,0x3C,0x36,0x63,0x41,0x00,   /* 0x3b K */
  0x7F,0x7F,0x40,0x40,0x40,0x40,0x40,0x00,   /* 0x3c L */
  0x7F,0x7F,0x0E,0x1C,0x0E,0x7F,0x7F,0x00,   /* 0x3d M */
  0x7F,0x7F,0x0E,0x1C,0x38,0x7F,0x7F,0x00,   /* 0x3e N */
  0x1C,0x3E,0x63,0x41,0x63,0x3E,0x1C,0x00,   /* 0x3f O */
  0x7F,0x7F,0x11,0x11,0x11,0x1F,0x0E,0x00,   /* 0x40 P */
  0x3E,0x7F,0x41,0x51,0x71,0x3F,0x5E,0x00,   /* 0x41 Q */
  0x7F,0x7F,0x09,0x19,0x39,0x6F,0x46,0x00,   /* 0x42 R */
  0x26,0x6F,0x49,0x49,0x49,0x7B,0x32,0x00,   /* 0x43 S */
  0x00,0x01,0x01,0x7F,0x7F,0x01,0x01,0x00,   /* 0x44 T */
  0x3F,0x7F,0x40,0x40,0x40,0x7F,0x3F,0x00,   /* 0x45 U */
  0x0F,0x1F,0x38,0x70,0x38,0x1F,0x0F,0x00,   /* 0x46 V */
  0x3F,0x7F,0x40,0x38,0x40,0x7F,0x3F,0x00,   /* 0x47 W */
  0x63,0x77,0x3E,0x1C,0x3E,0x77,0x63,0x00,   /* 0x48 X */
  0x00,0x07,0x0F,0x78,0x78,0x0F,0x07,0x00,   /* 0x49 Y */
  0x61,0x71,0x79,0x5D,0x4F,0x47,0x43,0x00,   /* 0x4a Z */
  0x00,0x7F,0x7F,0x41,0x41,0x00,0x00,0x00,   /* 0x4b [ */
  0x03,0x07,0x0E,0x1C,0x38,0x70,0x60,0x00,   /* 0x4c \ */
  0x00,0x41,0x41,0x7F,0x7F,0x00,0x00,0x00,   /* 0x4d ] */
  0x08,0x0C,0x06,0x03,0x06,0x0C,0x08,0x00,   /* 0x4e ^ */
  0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x00,   /* 0x4f _ */
  0x00,0x00,0x07,0x0B,0x00,0x00,0x00,0x00,   /* 0x50 ` */
  0x30,0x7A,0x4A,0x4A,0x7E,0x3C,0x40,0x00,   /* 0x51 a */
  0x7F,0x7F,0x44,0x42,0x62,0x7E,0x3C,0x00,   /* 0x52 b */
  0x18,0x3C,0x66,0x42,0x42,0x66,0x24,0x00,   /* 0x53 c */
  0x3C,0x7E,0x42,0x42,0x44,0x7F,0x7F,0x00,   /* 0x54 d */
  0x3C,0x7E,0x4A,0x4A,0x4A,0x6E,0x2C,0x00,   /* 0x55 e */
  0x00,0x08,0x7E,0x7F,0x09,0x0A,0x00,0x00,   /* 0x56 f */
  0x1C,0x3E,0xA2,0xA2,0x92,0xFE,0x7C,0x00,   /* 0x57 g */
  0x7F,0x7F,0x04,0x02,0x02,0x7E,0x7C,0x00,   /* 0x58 h */
  0x00,0x00,0x48,0x7B,0x7B,0x40,0x00,0x00,   /* 0x59 i */
  0x00,0x40,0xC0,0x88,0xFB,0x7B,0x00,0x00,   /* 0x5a j */
  0x00,0x7F,0x7F,0x08,0x34,0x66,0x42,0x00,   /* 0x5b k */
  0x00,0x00,0x01,0x7F,0x7F,0x00,0x00,0x00,   /* 0x5c l */
  0x7E,0x7E,0x02,0x7E,0x04,0x7E,0x7C,0x00,   /* 0x5d m */
  0x7E,0x7E,0x04,0x02,0x06,0x7C,0x78,0x00,   /* 0x5e n */
  0x18,0x3C,0x66,0x42,0x66,0x3C,0x18,0x00,   /* 0x5f o */
  0xFE,0xFE,0x22,0x42,0x42,0x7E,0x3C,0x00,   /* 0x60 p */
  0x00,0x3C,0x7E,0x42,0x42,0x22,0xFE,0xFE,   /* 0x61 q */
  0x7E,0x7E,0x04,0x02,0x02,0x0E,0x0C,0x00,   /* 0x62 r */
  0x24,0x6E,0x4A,0x4A,0x4A,0x7A,0x30,0x00,   /* 0x63 s */
  0x04,0x04,0x3F,0x7F,0x44,0x64,0x20,0x00,   /* 0x64 t */
  0x3E,0x7E,0x40,0x40,0x20,0x7E,0x7E,0x00,   /* 0x65 u */
  0x0E,0x1E,0x30,0x60,0x30,0x1E,0x0E,0x00,   /* 0x66 v */
  0x3E,0x7E,0x40,0x30,0x40,0x7E,0x3E,0x00,   /* 0x67 w */
  0x62,0x76,0x1C,0x08,0x1C,0x76,0x62,0x00,   /* 0x68 x */
  0x1E,0x3E,0xA0,0xA0,0x90,0xFE,0x7E,0x00,   /* 0x69 y */
  0x42,0x62,0x72,0x5A,0x4E,0x46,0x00,0x00,   /* 0x6a z */
  0x08,0x3E,0x77,0x41,0x41,0x00,0x00,0x00,   /* 0x6b { */
  0x00,0x00,0x00,0x7F,0x7F,0x00,0x00,0x00,   /* 0x6c | */
  0x00,0x00,0x41,0x41,0x77,0x3E,0x08,0x00,   /* 0x6d } */
  0x1C,0x1C,0x1C,0x7F,0x3E,0x1C,0x08,0x00,   /* 0x6e ~ */
  
  /* Czech characters */
  0x70,0x78,0x2C,0x26,0x2D,0x78,0x70,0x00,   /* 0x6f Á (A with acute) */
  0x20,0x74,0x54,0x56,0x7D,0x38,0x40,0x00,   /* 0x70 á (a with acute) */
  0x7C,0x7C,0x54,0x56,0x55,0x54,0x44,0x00,   /* 0x71 É (E with acute) */
  0x38,0x7C,0x54,0x56,0x55,0x5C,0x08,0x00,   /* 0x72 é (e with acute) */
  0x00,0x00,0x44,0x7C,0x7E,0x45,0x00,0x00,   /* 0x73 Í (I with acute) */
  0x00,0x00,0x40,0x7C,0x7E,0x41,0x00,0x00,   /* 0x74 í (i with acute) */
  0x10,0x38,0x6C,0x46,0x6D,0x38,0x10,0x00,   /* 0x75 Ó (O with acute) */
  0x10,0x28,0x44,0x46,0x45,0x28,0x10,0x00,   /* 0x76 ó (o with acute) */
  0x3C,0x7C,0x40,0x42,0x41,0x7C,0x3C,0x00,   /* 0x77 Ú (U with acute) */
  0x3C,0x78,0x40,0x42,0x21,0x78,0x7C,0x00,   /* 0x78 ú (u with acute) */
  0x00,0x04,0x5C,0x70,0x72,0x5D,0x04,0x00,   /* 0x79 Ý (Y with acute) */
  0x1C,0x38,0xA0,0xA2,0x91,0xF8,0x7C,0x00,   /* 0x7a ý (y with acute) */
  0x38,0x7C,0x45,0x46,0x45,0x6C,0x28,0x00,   /* 0x7b Č (C with caron) */
  0x10,0x38,0x6D,0x46,0x45,0x6C,0x28,0x00,   /* 0x7c č (c with caron) */
  0x7C,0x7C,0x45,0x46,0x6D,0x38,0x10,0x00,   /* 0x7d Ď (D with caron) */
  0x38,0x6C,0x44,0x44,0x2F,0x78,0x73,0x00,   /* 0x7e d´ (d with caron) */
  0x7C,0x7C,0x55,0x56,0x55,0x54,0x44,0x00,   /* 0x7f Ě (E with caron) */
  0x38,0x7C,0x55,0x56,0x55,0x5C,0x08,0x00,   /* 0x80 ě (e with caron) */
  0x7C,0x7C,0x09,0x1A,0x31,0x7C,0x7C,0x00,   /* 0x81 Ň (N with caron) */
  0x7C,0x7D,0x0A,0x05,0x0C,0x78,0x70,0x00,   /* 0x82 ň (n with caron) */
  0x7C,0x7C,0x15,0x36,0x35,0x5C,0x48,0x00,   /* 0x83 Ř (R with caron) */
  0x7C,0x7D,0x0A,0x05,0x04,0x1C,0x18,0x00,   /* 0x84 ř (r with caron) */
  0x68,0x4C,0x55,0x56,0x55,0x64,0x2C,0x00,   /* 0x85 Š (S with caron) */
  0x08,0x5C,0x55,0x56,0x55,0x74,0x20,0x00,   /* 0x86 š (s with caron) */
  0x00,0x04,0x05,0x7E,0x7D,0x04,0x04,0x00,   /* 0x87 Ť (T with caron) */
  0x04,0x04,0x3E,0x7E,0x44,0x64,0x23,0x00,   /* 0x88 t' (t with caron) */
  0x3C,0x78,0x42,0x45,0x22,0x78,0x7C,0x00,   /* 0x89 ů (u with ring above) */
  0x64,0x64,0x75,0x56,0x5D,0x4C,0x4C,0x00,   /* 0x8a Ž (Z with caron) */
  0x44,0x64,0x55,0x56,0x4D,0x44,0x00,0x00,   /* 0x8b ž (z with caron) */

  /* additional Polish characters */
  0x7C,0x7E,0x13,0x11,0x13,0x5E,0xB0,0x00,   /* 0x8c Ą (A with ogonek) */  
  0x30,0x7A,0x4A,0x4A,0x3E,0x7C,0xA0,0x00,   /* 0x8d ą (a with ogonek) */
  0x18,0x3E,0x66,0x43,0x43,0x66,0x24,0x00,   /* 0x8e Ć (C with caron) */
  0x18,0x3C,0x64,0x46,0x45,0x68,0x28,0x00,   /* 0x8f ć (c with caron) */
  0x3F,0x3F,0x25,0x25,0x25,0x65,0xA1,0x00,   /* 0x90 Ę (E with ogonek) */
  0x18,0x3C,0x4E,0x4A,0x2A,0x6E,0xA0,0x00,   /* 0x91 ę (e with ogonek) */
  0x08,0x7F,0x7F,0x44,0x40,0x40,0x00,0x00,   /* 0x92 Ł (L with stroke) */
  0x00,0x00,0x09,0x7F,0x7F,0x04,0x00,0x00,   /* 0x93 ł (l with stroke) */
  0x7F,0x7F,0x08,0x1A,0x31,0x7C,0x7F,0x00,   /* 0x94 Ń (N with acute) */
  0x0E,0x7E,0x04,0x06,0x05,0x7C,0x78,0x00,   /* 0x95 ń (n with acute) */
  0x24,0x6E,0x4A,0x53,0x53,0x76,0x24,0x00,   /* 0x96 Ś (S with acute) */
  0x08,0x5C,0x54,0x56,0x55,0x74,0x20,0x00,   /* 0x97 ś (s with acute) */
  0x64,0x64,0x74,0x56,0x5D,0x4C,0x4C,0x00,   /* 0x98 Ź (Z with acute) */
  0x44,0x64,0x54,0x56,0x4D,0x44,0x00,0x00,   /* 0x99 ź (z with acute) */
  0x62,0x72,0x7A,0x5F,0x4F,0x46,0x42,0x00,   /* 0x9a Ż (Z with dot above) */
  0x44,0x64,0x55,0x55,0x4C,0x44,0x00,0x00,   /* 0x9b ż (z with dot above) */

  /* additional Romanian characters */
  0x70,0x7A,0x29,0x25,0x29,0x7A,0x70,0x00,   /* 0x9c Â (A with circumflex) */  
  0x20,0x72,0x51,0x55,0x79,0x32,0x40,0x00,   /* 0x9d â (a with circumflex) */
  0x70,0x78,0x29,0x26,0x29,0x78,0x70,0x00,   /* 0x9e Ă (A with breve) */  
  0x20,0x75,0x56,0x55,0x78,0x30,0x40,0x00,   /* 0x9f ă (a with breve) */
  0x00,0x00,0x42,0x7D,0x7D,0x42,0x00,0x00,   /* 0xa0 Î (I with circumflex) */
  0x00,0x00,0x8A,0x79,0x79,0x42,0x00,0x00,   /* 0xa1 î (i with circumflex) */
  0x06,0xAF,0xA9,0x69,0x29,0x3B,0x12,0x00,   /* 0xa2 Ş (S with cedilla) */
  0x04,0xAE,0xAA,0x6A,0x2A,0x3A,0x10,0x00,   /* 0xa3 ş (s with cedilla) */
  0x00,0x01,0x81,0xBF,0x5F,0x01,0x01,0x00,   /* 0xa4 Ţ (T with cedilla) */
  0x04,0x04,0xBF,0xBF,0x44,0x64,0x20,0x00,   /* 0xa5 ţ (t with cedilla) */ 

  /* additional Hungarian characters */
  0x18,0x3B,0x64,0x42,0x64,0x3B,0x18,0x00,   /* 0xa6 Ő (O with double acute) */
  0x10,0x3B,0x6C,0x44,0x6C,0x3A,0x10,0x00,   /* 0xa7 ő (o with double acute) */
  0x3C,0x7C,0x43,0x40,0x43,0x7C,0x3C,0x00,   /* 0xa8 Ű (U with double acute) */
  0x3C,0x78,0x43,0x40,0x23,0x78,0x7C,0x00,   /* 0xa9 ű (u with double acute) */

  /* additional Serbo-Croatian characters */
  0x08,0x7F,0x7F,0x49,0x63,0x3E,0x1C,0x00,   /* 0xaa Đ (D with stroke) */
  0x3C,0x7E,0x42,0x42,0x54,0x7F,0x7F,0x00,   /* 0xab đ (d with stroke) */

  /* additional Albanian characters */
  0x1C,0xBE,0xA3,0x61,0x21,0x33,0x12,0x00,   /* 0xac Ç (C with cedilla) */
  0x18,0xBC,0xA6,0x62,0x22,0x26,0x14,0x00    /* 0xad ç (c with cedilla) */
  #ifdef FONT_EXTRA
  ,

  /* extra characters */
  0xFF,0xBD,0x80,0x80,0xBF,0xFF,0xFF,0xFF,   /* 0xae 1 (reversed color) */
  0x9D,0x8C,0xAE,0xA6,0xB6,0xB0,0xB9,0xFF,   /* 0xaf 2 (reversed color) */
  0xDD,0x9C,0xBE,0xB6,0xB6,0x88,0xC9,0xFF,   /* 0xb0 3 (reversed color) */
  0xFF,0xBD,0x99,0xE7,0xE7,0x99,0xBD,0xFF,   /* 0xb1 x (reversed color) */
  0x7E,0x42,0x42,0x42,0x42,0x42,0x42,0x42,   /* 0xb2 symbol: battery left side, low */
  0x7E,0x42,0x5A,0x5A,0x5A,0x5A,0x5A,0x42,   /* 0xb3 symbol: battery left side, high */
  0x42,0x42,0x42,0x42,0x42,0x42,0x7E,0x18,   /* 0xb4 symbol: battery right side, low */
  0x5A,0x5A,0x5A,0x5A,0x5A,0x42,0x7E,0x18    /* 0xb5 symbol: battery right side, high */
  #endif
};


/*
 *  font lookup table for ISO 8859-2
 *  - 8 bit ISO 8859-2 to custom font
 *  - ff: no bitmap available
 */

const uint8_t FontTable[] PROGMEM = {
  0xff,        /* 0x00 -> n/a */
  0x01,        /* 0x01 -> symbol: diode A-C */
  0x02,        /* 0x02 -> symbol: diode C-A */
  0x03,        /* 0x03 -> symbol: capacitor */
  0x04,        /* 0x04 -> omega */
  0x05,        /* 0x05 -> µ micro */
  0x06,        /* 0x06 -> symbol: resistor left side */
  0x07,        /* 0x07 -> symbol: resistor right side */
  #ifdef FONT_EXTRA
  0xae,        /* 0x08 -> 1 (reversed color) */
  0xaf,        /* 0x09 -> 2 (reversed color) */
  0xb0,        /* 0x0a -> 3 (reversed color) */
  0xb1,        /* 0x0b -> x (reversed color) */
  0xb2,        /* 0x0c -> symbol: battery left side, low */
  0xb3,        /* 0x0d -> symbol: battery left side, high */
  0xb4,        /* 0x0e -> symbol: battery right side, low */
  0xb5,        /* 0x0f -> symbol: battery right side, high */
  #else
  0xff,        /* 0x08 -> n/a */
  0xff,        /* 0x09 -> n/a */
  0xff,        /* 0x0a -> n/a */
  0xff,        /* 0x0b -> n/a */
  0xff,        /* 0x0c -> n/a */
  0xff,        /* 0x0d -> n/a */
  0xff,        /* 0x0e -> n/a */
  0xff,        /* 0x0f -> n/a */
  #endif

  0xff,        /* 0x10 -> n/a */
  0xff,        /* 0x11 -> n/a */
  0xff,        /* 0x12 -> n/a */
  0xff,        /* 0x13 -> n/a */
  0xff,        /* 0x14 -> n/a */
  0xff,        /* 0x15 -> n/a */
  0xff,        /* 0x16 -> n/a */
  0xff,        /* 0x17 -> n/a */
  0xff,        /* 0x18 -> n/a */
  0xff,        /* 0x19 -> n/a */
  0xff,        /* 0x1a -> n/a */
  0xff,        /* 0x1b -> n/a */
  0xff,        /* 0x1c -> n/a */
  0xff,        /* 0x1d -> n/a */
  0xff,        /* 0x1e -> n/a */
  0xff,        /* 0x1f -> n/a */

  0x10,        /* 0x20 -> space */
  0x11,        /* 0x21 -> ! */
  0x12,        /* 0x22 -> " */
  0x13,        /* 0x23 -> # */
  0x14,        /* 0x24 -> $ */
  0x15,        /* 0x25 -> % */
  0x16,        /* 0x26 -> & */
  0x17,        /* 0x27 -> ´ */
  0x18,        /* 0x28 -> ( */
  0x19,        /* 0x29 -> ) */
  0x1a,        /* 0x2a -> * */
  0x1b,        /* 0x2b -> + */
  0x1c,        /* 0x2c -> , */
  0x1d,        /* 0x2d -> - */
  0x1e,        /* 0x2e -> . */
  0x1f,        /* 0x2f -> / */

  0x20,        /* 0x30 -> 0 */
  0x21,        /* 0x31 -> 1 */
  0x22,        /* 0x32 -> 2 */
  0x23,        /* 0x33 -> 3 */
  0x24,        /* 0x34 -> 4 */
  0x25,        /* 0x35 -> 5 */
  0x26,        /* 0x36 -> 6 */
  0x27,        /* 0x37 -> 7 */
  0x28,        /* 0x38 -> 8 */
  0x29,        /* 0x39 -> 9 */
  0x2a,        /* 0x3a -> : */
  0x2b,        /* 0x3b -> ; */
  0x2c,        /* 0x3c -> < */
  0x2d,        /* 0x3d -> = */
  0x2e,        /* 0x3e -> > */
  0x2f,        /* 0x3f -> ? */

  0x30,        /* 0x40 -> @ */
  0x31,        /* 0x41 -> A */
  0x32,        /* 0x42 -> B */
  0x33,        /* 0x43 -> C */
  0x34,        /* 0x44 -> D */
  0x35,        /* 0x45 -> E */
  0x36,        /* 0x46 -> F */
  0x37,        /* 0x47 -> G */
  0x38,        /* 0x48 -> H */
  0x39,        /* 0x49 -> I */
  0x3a,        /* 0x4a -> J */
  0x3b,        /* 0x4b -> K */
  0x3c,        /* 0x4c -> L */
  0x3d,        /* 0x4d -> M */
  0x3e,        /* 0x4e -> N */
  0x3f,        /* 0x4f -> O */

  0x40,        /* 0x50 -> P */
  0x41,        /* 0x51 -> Q */
  0x42,        /* 0x52 -> R */
  0x43,        /* 0x53 -> S */
  0x44,        /* 0x54 -> T */
  0x45,        /* 0x55 -> U */
  0x46,        /* 0x56 -> V */
  0x47,        /* 0x57 -> W */
  0x48,        /* 0x58 -> X */
  0x49,        /* 0x59 -> Y */
  0x4a,        /* 0x5a -> Z */
  0x4b,        /* 0x5b -> [ */
  0x4c,        /* 0x5c -> \ */
  0x4d,        /* 0x5d -> ] */
  0x4e,        /* 0x5e -> ^ */
  0x4f,        /* 0x5f -> _ */

  0x50,        /* 0x60 -> ` */
  0x51,        /* 0x61 -> a */
  0x52,        /* 0x62 -> b */
  0x53,        /* 0x63 -> c */
  0x54,        /* 0x64 -> d */
  0x55,        /* 0x65 -> e */
  0x56,        /* 0x66 -> f */
  0x57,        /* 0x67 -> g */
  0x58,        /* 0x68 -> h */
  0x59,        /* 0x69 -> i */
  0x5a,        /* 0x6a -> j */
  0x5b,        /* 0x6b -> k */
  0x5c,        /* 0x6c -> l */
  0x5d,        /* 0x6d -> m */
  0x5e,        /* 0x6e -> n */
  0x5f,        /* 0x6f -> o */

  0x60,        /* 0x70 -> p */
  0x61,        /* 0x71 -> q */
  0x62,        /* 0x72 -> r */
  0x63,        /* 0x73 -> s */
  0x64,        /* 0x74 -> t */
  0x65,        /* 0x75 -> u */
  0x66,        /* 0x76 -> v */
  0x67,        /* 0x77 -> w */
  0x68,        /* 0x78 -> x */
  0x69,        /* 0x79 -> y */
  0x6a,        /* 0x7a -> z */
  0x6b,        /* 0x7b -> { */
  0x6c,        /* 0x7c -> | */
  0x6d,        /* 0x7d -> } */
  0x6e,        /* 0x7e -> ~ */
  0xff,        /* 0x7f -> n/a */

  0xff,        /* 0x80 -> n/a */
  0xff,        /* 0x81 -> n/a */
  0xff,        /* 0x82 -> n/a */
  0xff,        /* 0x83 -> n/a */
  0xff,        /* 0x84 -> n/a */
  0xff,        /* 0x85 -> n/a */
  0xff,        /* 0x86 -> n/a */
  0xff,        /* 0x87 -> n/a */
  0xff,        /* 0x88 -> n/a */
  0xff,        /* 0x89 -> n/a */
  0xff,        /* 0x8a -> n/a */
  0xff,        /* 0x8b -> n/a */
  0xff,        /* 0x8c -> n/a */
  0xff,        /* 0x8d -> n/a */
  0xff,        /* 0x8e -> n/a */
  0xff,        /* 0x8f -> n/a */

  0xff,        /* 0x90 -> n/a */
  0xff,        /* 0x91 -> n/a */
  0xff,        /* 0x92 -> n/a */
  0xff,        /* 0x93 -> n/a */
  0xff,        /* 0x94 -> n/a */
  0xff,        /* 0x95 -> n/a */
  0xff,        /* 0x96 -> n/a */
  0xff,        /* 0x97 -> n/a */
  0xff,        /* 0x98 -> n/a */
  0xff,        /* 0x99 -> n/a */
  0xff,        /* 0x9a -> n/a */
  0xff,        /* 0x9b -> n/a */
  0xff,        /* 0x9c -> n/a */
  0xff,        /* 0x9d -> n/a */
  0xff,        /* 0x9e -> n/a */
  0xff,        /* 0x9f -> n/a */

  0xff,        /* 0xa0 -> n/a */
  0x8c,        /* 0xa1 -> Ą (A with ogonek) */
  0xff,        /* 0xa2 -> n/a */
  0x92,        /* 0xa3 -> Ł (L with stroke) */
  0xff,        /* 0xa4 -> n/a */
  0xff,        /* 0xa5 -> n/a */
  0x96,        /* 0xa6 -> Ś (S with acute) */
  0xff,        /* 0xa7 -> n/a */
  0xff,        /* 0xa8 -> n/a */
  0x85,        /* 0xa9 -> Š (S with caron) */
  0xa2,        /* 0xaa -> Ş (S with cedilla) */
  0x87,        /* 0xab -> Ť (T with caron) */
  0x98,        /* 0xac -> Ź (Z with acute) */
  0xff,        /* 0xad -> n/a */
  0x8a,        /* 0xae -> Ž (Z with caron) */
  0x9a,        /* 0xaf -> Ż (Z with dot above) */

  0x0f,        /* 0xb0 -> ° (degree sign) */
  0x8d,        /* 0xb1 -> ą (a with ogonek) */  
  0xff,        /* 0xb2 -> n/a */
  0x93,        /* 0xb3 -> ł (l with stroke) */
  0xff,        /* 0xb4 -> n/a */
  0x05,        /* 0xb5 -> µ (micro) */
  0x97,        /* 0xb6 -> ś (s with acute) */
  0xff,        /* 0xb7 -> n/a */
  0xff,        /* 0xb8 -> n/a */
  0x86,        /* 0xb9 -> š (s with caron) */
  0xa3,        /* 0xba -> ş (s with cedilla) */
  0x88,        /* 0xbb -> t' (t with caron) */
  0x99,        /* 0xbc -> ź (z with acute) */
  0xff,        /* 0xbd -> n/a */
  0x8b,        /* 0xbe -> ž (z with caron) */
  0x9b,        /* 0xbf -> ż (z with dot above) */
  
  0xff,        /* 0xc0 -> n/a */
  0x6f,        /* 0xc1 -> Á (A with acute) */
  0x9c,        /* 0xc2 -> Â (A with circumflex) */  
  0x9e,        /* 0xc3 -> Ă (A with breve) */ 
  0x08,        /* 0xc4 -> Ä (A umlaut) */
  0xff,        /* 0xc5 -> n/a */
  0x8e,        /* 0xc6 -> Ć (C with caron) */
  0xac,        /* 0xc7 -> Ç (C with cedilla) */
  0x7b,        /* 0xc8 -> Č (C with caron) */
  0x71,        /* 0xc9 -> É (E with acute) */
  0x90,        /* 0xca -> Ę (E with ogonek) */
  0xff,        /* 0xcb -> n/a */
  0x7f,        /* 0xcc -> Ě (E with caron) */
  0x73,        /* 0xcd -> Í (I with acute) */
  0xa0,        /* 0xce -> Î (I with circumflex) */
  0x7d,        /* 0xcf -> Ď (D with caron) */

  0xaa,        /* 0xd0 -> Đ (D with stroke) */
  0x94,        /* 0xd1 -> Ń (N with acute) */
  0x81,        /* 0xd2 -> Ň (N with caron) */
  0x75,        /* 0xd3 -> Ó (O with acute) */
  0xff,        /* 0xd4 -> n/a */
  0xa6,        /* 0xd5 -> Ő (O with double acute) */
  0x09,        /* 0xd6 -> Ö (O umlaut) */
  0xff,        /* 0xd7 -> n/a */
  0x83,        /* 0xd8 -> Ř (R with caron) */
  0xff,        /* 0xd9 -> n/a */
  0x77,        /* 0xda -> Ú (U with acute) */
  0xa8,        /* 0xdb -> Ű (U with double acute) */
  0x0a,        /* 0xdc -> Ü (U umlaut) */
  0x79,        /* 0xdd -> Ý (Y with acute) */
  0xa4,        /* 0xde -> Ţ (T with cedilla) */
  0x0b,        /* 0xdf -> ß (sharp s) */
  
  0xff,        /* 0xe0 -> n/a */
  0x70,        /* 0xe1 -> á (a with acute) */
  0x9d,        /* 0xe2 -> â (a with circumflex) */
  0x9f,        /* 0xe3 -> ă (a with breve) */
  0x0c,        /* 0xe4 -> ä (a umlaut) */
  0xff,        /* 0xe5 -> n/a */
  0x8f,        /* 0xe6 -> ć (c with caron) */
  0xad,        /* 0xe7 -> ç (c with cedilla) */
  0x7c,        /* 0xe8 -> č (c with caron) */
  0x72,        /* 0xe9 -> é (e with acute) */
  0x91,        /* 0xea -> ę (e with ogonek) */
  0xff,        /* 0xeb -> n/a */
  0x80,        /* 0xec -> ě (e with caron) */
  0x74,        /* 0xed -> í (i with acute) */
  0xa1,        /* 0xee -> î (i with circumflex) */
  0x7e,        /* 0xef -> d´ (d with caron) */

  0xab,        /* 0xf0 -> đ (d with stroke) */
  0x95,        /* 0xf1 -> ń (n with acute) */
  0x82,        /* 0xf2 -> ň (n with caron) */
  0x76,        /* 0xf3 -> ó (o with acute)*/
  0xff,        /* 0xf4 -> n/a */
  0xa7,        /* 0xf5 -> ő (o with double acute) */
  0x0d,        /* 0xf6 -> ö (o umlaut) */
  0xff,        /* 0xf7 -> n/a */
  0x84,        /* 0xf8 -> ř (r with caron) */
  0x89,        /* 0xf9 -> ů (u with ring above) */
  0x78,        /* 0xfa -> ú (u with acute)*/
  0xa9,        /* 0xfb -> ű (u with double acute) */
  0x0e,        /* 0xfc -> ü (u umlaut) */
  0x7a,        /* 0xfd -> ý (y with acute)*/
  0xa5,        /* 0xfe -> ţ (t with cedilla) */ 
  0xff         /* 0xff -> n/a */
};

#endif

/* ************************************************************************
 *   EOF
 * ************************************************************************ */

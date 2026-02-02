/* ************************************************************************
 *
 *   ATmega 328 specific global configuration, setup and settings
 *
 *   (c) 2012-2023 by Markus Reschke
 *   based on code from Markus Frejek and Karl-Heinz Kübbeler
 *
 * ************************************************************************ */


/* source management */
#define CONFIG_328_H



/* ************************************************************************
 *   display module
 * ************************************************************************ */


/*
 *  display module / controller
 *
 *  Please uncomment the package matching your LCD/OLED module and adjust
 *  settings. And comment out the default package (ST7565R, bit-bang SPI)
 *  if not used.
 *
 *  To uncomment, remove the enclosing "#if 0" and "#endif" or put
 *  a "//" in front of both. To comment out, remove the "//" in front
 *  of the "#if 0" and "#endif".
 *
 *  Individual settings can be enabled by removing the leading "//", or
 *  disabled by placing a "//" in front of the setting.
 */


/*
 *  HD44780 plus PCF8574 based backpack
 *  - I2C interface using bit-bang I2C
 *  - if you change LCD_DB4/5/6/7 comment out LCD_DB_STD!
 *  - PCF8574T is 0x27, PCF8574AT is 0x3f
 */

#define LCD_HD44780                     /* display controller HD44780 */
#define LCD_TEXT                        /* character display */
#define LCD_PCF8574                     /* PCF8574 backpack */
#define LCD_I2C_ADDR     0x27           /* PCF8574's I2C address */
/* control and data lines */
#define LCD_DB_STD                      /* use standard pins 4-7 for DB4-7 */
#define LCD_DB4          PCF8574_P4     /* port pin used for DB4 */
#define LCD_DB5          PCF8574_P5     /* port pin used for DB5 */
#define LCD_DB6          PCF8574_P6     /* port pin used for DB6 */
#define LCD_DB7          PCF8574_P7     /* port pin used for DB7 */
#define LCD_RS           PCF8574_P0     /* port pin used for RS */
#define LCD_RW           PCF8574_P1     /* port pin used for RW */
#define LCD_EN1          PCF8574_P2     /* port pin used for E */
#define LCD_LED          PCF8574_P3     /* port pin used for backlight */
/* display settings */
#define LCD_CHAR_X       16             /* characters per line */
#define LCD_CHAR_Y       2              /* number of lines */
//#define LCD_BACKLIGHT_LOW               /* backlight is low active */
/* HD44780 has an internal 5x7 font */
#define FONT_HD44780_INT                /* International font (English) */
//#define FONT_HD44780_WIN1251             /* Cyrillic font (European) */
/* I2C bus */
#define I2C_BITBANG                     /* bit-bang I2C */
#define I2C_STANDARD_MODE               /* 100kHz bus speed */
#define I2C_PORT         PORTC          /* I2C port data register */
#define I2C_DDR          DDRC           /* I2C port data direction register */
#define I2C_PIN          PINC           /* I2C port input pins register */
#define I2C_SDA          PC4            /* port pin used for SDA */
#define I2C_SCL          PC5            /* port pin used for SCL */



/* ************************************************************************
 *   port and pin assignments
 * ************************************************************************ */


/*
 *  test pins / probes:
 *  - Must be an ADC port!
 *  - It's recommended to use the lower 3 pins for the probes.
 *  - Don't share this port with POWER_CTRL or TEST_BUTTON!
 */

#define ADC_PORT         PORTC     /* port data register */
#define ADC_DDR          DDRC      /* port data direction register */
#define ADC_PIN          PINC      /* port input pins register */
#define TP1              PC0       /* test pin / probe #1 */
#define TP2              PC1       /* test pin / probe #2 */
#define TP3              PC2       /* test pin / probe #3 */

#define TP_ZENER         PC3       /* test pin for for Zener check (10:1 voltage divider) */
#define TP_REF           PC6       /* test pin for 2.5V reference and relay */
#define TP_BAT           PC7       /* test pin for battery (4:1 voltage divider) */
#define TP_LOGIC         PC3       /* test pin for Logic Probe (4:1 voltage divider) */


/*
 *  probe resistors
 *  - For PWM/squarewave output via probe #2 R_RL_2 has to be PB2/OC1B.
 *  - Don't share this port with POWER_CTRL or TEST_BUTTON!
 */

#define R_PORT           PORTB     /* port data register */
#define R_DDR            DDRB      /* port data direction register */
#define R_RL_1           PB0       /* Rl (680R) for test pin #1 */
#define R_RH_1           PB1       /* Rh (470k) for test pin #1 */
#define R_RL_2           PB2       /* Rl (680R) for test pin #2 */
#define R_RH_2           PB3       /* Rh (470k) for test pin #2 */
#define R_RL_3           PB4       /* Rl (680R) for test pin #3 */
#define R_RH_3           PB5       /* Rh (470k) for test pin #3 */


/*
 *  dedicated signal output via OC1B
 *  - don't change this!
 */

#define SIGNAL_PORT      PORTB     /* port data register */
#define SIGNAL_DDR       DDRB      /* port data direction register */
#define SIGNAL_OUT       PB2       /* MCU's OC1B pin */


/*
 *  power control
 *  - can't be same port as ADC_PORT or R_PORT
 */

#define POWER_PORT       PORTD     /* port data register */
#define POWER_DDR        DDRD      /* port data direction register */
#define POWER_CTRL       PD6       /* control pin (1: on / 0: off) */


/*
 *  test push button 
 *  - can't be same port as ADC_PORT or R_PORT
 */

#define BUTTON_PORT      PORTD     /* port data register */
#define BUTTON_DDR       DDRD      /* port data direction register */
#define BUTTON_PIN       PIND      /* port input pins register */
#define TEST_BUTTON      PD7       /* test/start push button (low active) */


/*
 *  rotary encoder
 */

#define ENCODER_PORT     PORTD     /* port data register */
#define ENCODER_DDR      DDRD      /* port data direction register */
#define ENCODER_PIN      PIND      /* port input pins register */
#define ENCODER_A        PD3       /* rotary encoder A signal */
#define ENCODER_B        PD2       /* rotary encoder B signal */


/*
 *  increase/decrease push buttons
 */

#define KEY_PORT         PORTD     /* port data register */
#define KEY_DDR          DDRD      /* port data direction register */
#define KEY_PIN          PIND      /* port input pins register */
#define KEY_INC          PD2       /* increase push button (low active) */
#define KEY_DEC          PD3       /* decrease push button (low active) */


/*
 *  frequency counter
 *  - input must be pin PD4/T0
 */

#define COUNTER_PORT     PORTD     /* port data register */
#define COUNTER_DDR      DDRD      /* port data direction register */
#define COUNTER_IN       PD4       /* signal input T0 */


/*
 *  ring tester
 *  - counter input must be pin PD4/T0 (uses COUNTER_IN)
 */

#define RINGTESTER_PORT  PORTD     /* port data register */
#define RINGTESTER_DDR   DDRD      /* port data direction register */
#define RINGTESTER_OUT   PD5       /* pulse output */



/*
 *  IR detector/decoder
 *  - fixed module connected to dedicated I/O pin
 */

#define IR_PORT          PORTD     /* port data register */
#define IR_DDR           DDRD      /* port data direction register */
#define IR_PIN           PIND      /* port input pins register */
#define IR_DATA          PD5       /* data signal */


/*
 *  SPI
 *  - hardware SPI uses
 *    SCK PB5, MOSI PB3, MISO PB4 and /SS PB2
 *  - could be already set in display section
 *  - unused signals can be ignored
 *  - /SS is set to output mode for hardware SPI but not used
 */

/* SPI not set yet (for bit-bang or hardware SPI) */
#ifndef SPI_PORT
  #define SPI_PORT       PORTB     /* port data register */
  #define SPI_DDR        DDRB      /* port data direction register */
  #define SPI_PIN        PINB      /* port input pins register */
  #define SPI_SCK        PB5       /* pin for SCK */
  #define SPI_MOSI       PB3       /* pin for MOSI */
  #define SPI_MISO       PB4       /* pin for MISO */
  #define SPI_SS         PB2       /* pin for /SS */
#endif

/* SPI_PIN/SPI_MISO not set yet (for bit-bang SPI with read support) */
//#define SPI_PIN          PINB      /* port input pins register */
//#define SPI_MISO         PB4       /* pin for MISO */


/*
 *  I2C
 *  - hardware I2C (TWI) uses
 *    SDA PC4 and SCL PC5
 *  - could be already set in display section
 */

/* I2C not set yet (for bit-bang I2C) */
#ifndef I2C_PORT
  #define I2C_PORT       PORTC     /* port data register */
  #define I2C_DDR        DDRC      /* port data direction register */
  #define I2C_PIN        PINC      /* port input pins register */
  #define I2C_SDA        PC4       /* pin for SDA */
  #define I2C_SCL        PC5       /* pin for SCL */
#endif


/*
 *  TTL serial interface
 *  - hardware USART uses
 *    USART0: Rx PD0 and Tx PD1
 */

/* for hardware RS232 */
#define SERIAL_USART     0         /* use USART0 */
/* for bit-bang RS232 */
#define SERIAL_PORT      PORTD     /* port data register */
#define SERIAL_DDR       DDRD      /* port data direction register */
#define SERIAL_PIN       PIND      /* port input pins register */
#define SERIAL_TX        PD1       /* pin for Tx (transmit) */
#define SERIAL_RX        PD0       /* pin for Rx (receive) */
#define SERIAL_PCINT     16        /* PCINT# for Rx pin */


/*
 *  OneWire
 *  - dedicated I/O pin
 */

#define ONEWIRE_PORT     PORTD     /* port data register */
#define ONEWIRE_DDR      DDRD      /* port data direction register */
#define ONEWIRE_PIN      PIND      /* port input pins register */
#define ONEWIRE_DQ       PD5       /* DQ (data line) */


/*
 *  buzzer
 */

#define BUZZER_PORT      PORTD     /* port data register */
#define BUZZER_DDR       DDRD      /* port data direction register */
#define BUZZER_CTRL      PD5       /* control pin (low: off / high: on) */


/*
 *  MAX6675
 */

#define MAX6675_PORT     PORTD     /* port data register */
#define MAX6675_DDR      DDRD      /* port data direction register */
#define MAX6675_CS       PD5       /* port pin used for /CS */


/*
 *  MAX31855
 */

#define MAX31855_PORT    PORTD     /* port data register */
#define MAX31855_DDR     DDRD      /* port data direction register */
#define MAX31855_CS      PD5       /* port pin used for /CS */


/*
 *  boost converter for Zener check (dedicated I/O pin)
 */

#define BOOST_PORT       PORTD     /* port data register */
#define BOOST_DDR        DDRD      /* port data direction register */
#define BOOST_CTRL       PD5       /* control pin */


/*
 *  flashlight / general purpose switched output
 */

#define FLASHLIGHT_PORT  PORTD     /* port data register */
#define FLASHLIGHT_DDR   DDRD      /* port data direction register */
#define FLASHLIGHT_CTRL  PD5       /* control pin */



/* ************************************************************************
 *   internal stuff
 * ************************************************************************ */


/* ADC reference selection: AVcc */
#define ADC_REF_VCC           (1 << REFS0)

/* ADC reference selection: internal 1.1V bandgap */
#define ADC_REF_BANDGAP       ((1 << REFS1) | (1 << REFS0))

/* ADC reference selection: filter mask for register bits */
#define ADC_REF_MASK          ((1 << REFS1) | (1 << REFS0))

/* ADC MUX channel: internal 1.1V bandgap reference */
#define ADC_CHAN_BANDGAP      0x0e      /* 1110 */

/* ADC MUX channel: filter mask for register bits */
#define ADC_CHAN_MASK         0b00001111     /* MUX0-3 */



/* ************************************************************************
 *   MCU specific setup to support different AVRs
 * ************************************************************************ */


/*
 *  ATmega 328/328P
 */

#if defined (__AVR_ATmega328__)

  /* estimated internal resistance of port to GND (in 0.1 Ohms) */
  #define R_MCU_LOW           200

  /* estimated internal resistance of port to VCC (in 0.1 Ohms) */
  #define R_MCU_HIGH          220

  /* voltage offset of MCU's analog comparator (in mV): -50 up to 50 */
  #define COMPARATOR_OFFSET   0

  /* this MCU has 32kB Flash, 1kB EEPROM and 2kB RAM (enable extra features) */
  #define RES_FLASH           32
  #define RES_EEPROM          1
  #define RES_RAM             2


/*
 *  missing or unsupported MCU
 */

#else
  #error <<< No or wrong MCU type selected! >>>
#endif



/* ************************************************************************
 *   EOF
 * ************************************************************************ */

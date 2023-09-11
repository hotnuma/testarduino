
double capa_LC(double L, double freq, double k)
{
    return (1 / (pow((2 * M_PI * freq), 2) * L)) * 1e12 * k;
}

// Mode 1 : LM711 LC
double lc711_L = 100e-6;
double lc711_cal = 1000;
double lc711_k = 1; //(10000.0/8957.0);

        case 1:
            printfreq();
            
            if (digitalRead(CalPin) == LOW)
            {
                lc711_cal = capa_LC(lc711_L, gpsFreq.freq, lc711_k);
                printval(linestr, "Cal...", 3);
                lcd.setCursor(0, 1);
                lcd.print(linestr);
            }
            else
            {
                double result = capa_LC(lc711_L, gpsFreq.freq, lc711_k) - lc711_cal;
                dtostrf(result, 1, 2, tempstr);
                printval(linestr, tempstr, 3);
                strcpy(linestr + (LSIZE-3), " pF");
                lcd.setCursor(0, 1);
                lcd.print(linestr);
            }
        break;
        

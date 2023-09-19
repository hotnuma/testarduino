double hcapa_RC(double R, double tics, double k)
{
    return (1 / (k * R * (4e6 / tics))) * 1e6;
}

        case 2:
            printfreq();
            
            if (digitalRead(CalPin) == LOW)
            {
                rc711_cal = hcapa_RC(rc711_R, gpsFreq.freq, rc711_k);
                printval(linestr, "Cal...", 3);
                lcd.setCursor(0, 1);
                lcd.print(linestr);
            }
            else
            {
                double result = hcapa_RC(rc711_R, gpsFreq.freq, rc711_k) /*- rc711_cal*/;
                dtostrf(result, 1, 2, tempstr);
                printval(linestr, tempstr, 3);
                strcpy(linestr + (LSIZE-3), " uF");
                lcd.setCursor(0, 1);
                lcd.print(linestr);
            }
        break;


    case 2:
        printfreq();
        
        if (digitalRead(CalPin) == LOW)
        {
            cal_555 = capa_555(R1_555, R2_555, gpsFreq.freq);
            printval(linestr, "Cal...", 3);
            lcd.setCursor(0, 1);
            lcd.print(linestr);
        }
        else
        {
            double result = capa_555(R1_555, R2_555, gpsFreq.freq) - cal_555;
            dtostrf(result, 1, 2, tempstr);
            printval(linestr, tempstr, 3);
            strcpy(linestr + (LSIZE-3), " pF");
            lcd.setCursor(0, 1);
            lcd.print(linestr);
        }
    break;
    

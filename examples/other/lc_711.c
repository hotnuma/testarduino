
double LC_cal(double C2, double F2, double F1)
{
    double FF2 = pow(F2, 2);
    
    double result = C2 * (FF2 / (pow(F1, 2) - FF2));
    
    printf("C1 = %f\n", result * 1e12);
    
    return result;
}

double LC_capa(double F, double F1, double C1, double k)
{
    //return (1 / (pow(F1, 2) * part));
    
    return C1 * ((pow(F1, 2) / pow(F, 2)) - 1.0) * k;
}

// Mode 2 : LM711 LC
double C2 = 1000e-12;
double F1 = 523773;
double C1 = 1020e-12;
double k = 0.95;

        case 2:
            printfreq();
            
            if (digitalRead(CalPin) == LOW)
            {
                C1 = LC_cal(C2, gpsFreq.freq, F1);
                printval(linestr, "Cal...", 3);
                lcd.setCursor(0, 1);
                lcd.print(linestr);
            }
            else
            {
                double result = LC_capa(gpsFreq.freq, F1, C1, k);
                dtostrf(result * 1e12, 1, 2, tempstr);
                printval(linestr, tempstr, 3);
                strcpy(linestr + (LSIZE-3), " pF");
                lcd.setCursor(0, 1);
                lcd.print(linestr);
            }
        break;
        



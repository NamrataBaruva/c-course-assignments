#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    char *unit[2];
    if (argc < 3)
    {
        fprintf(stderr, "%s: error: Not enough arguments.\nUsage: temp_convert INPUT_SCALE OUTPUT_SCALE [TEMPERATURE]...\n", argv[0]);
        abort();
        return EXIT_FAILURE;
    }

    if (argc >= 3)
    {

        for (int count = 1; (count <= 2); count++)
        {
            if (((argv[count][1]) == 'C') || (0 == strcmp(argv[count], "c")) || (0 == strcmp(argv[count], "C")) || (0 == strcmp(argv[count], "celsius")) || (0 == strcmp(argv[count], "Celsius")))
            {
                // (argv[count][1]) == 'C') takes care of ° C   ((argv[count][1]) == 'C')
                // fputs("Celsius", stdout);
                unit[count] = "C";
            }
            else if (((argv[count][1]) == 'F') || (0 == strcmp(argv[count], "f")) || (0 == strcmp(argv[count], "F")) || (0 == strcmp(argv[count], "fahrenheit")) || (0 == strcmp(argv[count], "Fahrenheit")))
            {
                // (argv[count][1]) == 'F') takes care of ° F  alt+ 0176
                // fputs("Fahrenheit", stdout);
                unit[count] = "F";
            }
            else if ((0 == strcmp(argv[count], "k")) || (0 == strcmp(argv[count], "K")) || (0 == strcmp(argv[count], "kelvin")) || (0 == strcmp(argv[count], "Kelvin")))
            {
                // fputs("Kelvin", stdout);
                unit[count] = "K";
            }
            else
            {
                printf("error: Unrecognized temperature scale %s", argv[count]); // unrecognised temperature scale
                return EXIT_FAILURE;
            }
        } // for loop end

        if (argc == 3) // recognised scale but without temp values
        {
            // fputs("Not enough inputs for calculation", stderr);
            return EXIT_SUCCESS;
        }

        // get conversion type eg c->f
        int ConvetType;
        if (unit[1] == "C")
        {
            if (unit[2] == "F") // c ->F
            {
                ConvetType = 1;
            }
            else if (unit[2] == "K") // c->K
            {
                ConvetType = 2;
            }
            else
            {
                ConvetType = 0;
            }
        }
        else if (unit[1] == "F")
        {
            if (unit[2] == "C") // F ->C
            {
                ConvetType = 3;
            }
            else if (unit[2] == "K") // F-> K
            {
                ConvetType = 4;
            }
            else
            {
                ConvetType = 0;
            }
        }
        else if (unit[1] == "K")
        {
            if (unit[2] == "C") // K ->C
            {
                ConvetType = 5;
            }
            else if (unit[2] == "F") // K->F
            {
                ConvetType = 6;
            }
            else
            {
                ConvetType = 0;
            }
        }
        else
        {
            fputs("error: Unknown Error1 ", stderr);
            return EXIT_FAILURE;
        }

        float OpTemp;

        for (int ip = 3; (ip < argc); ip++)
        {
            float IpTemp = atof(argv[ip]);

            switch (ConvetType)
            {
            case 0:
                OpTemp = IpTemp;
                break;
            case 1: // CF
                OpTemp = (IpTemp * 9 / 5) + 32;
                break;
            case 2: // CK
                OpTemp = IpTemp + 273.15;
                break;
            case 3: // FC
                OpTemp = (IpTemp - 32) * 5 / 9;
                break;
            case 4: // FK
                OpTemp = 5 / 9 * (IpTemp - 32) + 273.15;
                break;
            case 5: // KC
                OpTemp = IpTemp - 273.15;
                break;
            case 6: // KF
                OpTemp = 9 / 5 * (IpTemp - 273) + 32;
                break;

            default:
                fputs("error: Unknown Error2 ", stderr);
                return EXIT_FAILURE;
                break;
            }
            printf("%.2f\n", OpTemp);
        }
    }
    return EXIT_SUCCESS;
}
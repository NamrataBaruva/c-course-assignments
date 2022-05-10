#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int ReadIp(char Input[])
{
   char unit1;
    if (((Input[1]) == 'C') || (0 == strcmp(Input, "c")) || (0 == strcmp(Input, "C")) || (0 == strcmp(Input, "celsius")) || (0 == strcmp(Input, "Celsius")))
         {
            // (Input[1]) == 'C') takes care of ° C   ((Input[1]) == 'C')            
            unit1 = 'C';
         }
         else if (((Input[1]) == 'F') || (0 == strcmp(Input, "f")) || (0 == strcmp(Input, "F")) || (0 == strcmp(Input, "fahrenheit")) || (0 == strcmp(Input, "Fahrenheit")))
         {
            // (Input[1]) == 'F') takes care of ° F  alt+ 0176            
            unit1 = 'F';
         }
         else if ((0 == strcmp(Input, "k")) || (0 == strcmp(Input, "K")) || (0 == strcmp(Input, "kelvin")) || (0 == strcmp(Input, "Kelvin")))
         {            
            unit1 = 'K';
         }
         else
         {
            printf("error: Unrecognized temperature scale %s", Input); // unrecognised temperature scale
            return EXIT_FAILURE;
         }        
         return unit1;
}
int GetConvertType(char u1, char u2)
{
   int ConvertType =0;
   if (u1 == 'C')
   {
      if (u2 == 'F') // c ->F
      {
         ConvertType = 1;
      }
      else if (u2 == 'K') // c->K
      {
         ConvertType = 2;
      }
      else
      {
         ConvertType = 0;
      }
   }
   else if (u1 == 'F')
   {
      if (u2 == 'C') // F ->C
      {
         ConvertType = 3;
      }
      else if (u2 == 'K') // F-> K
      {
         ConvertType = 4;
      }
      else
      {
         ConvertType = 0;
      }
   }
   else if (u1 == 'K')
   {
      if (u2 == 'C') // K ->C
      {
         ConvertType = 5;
      }
      else if (u2 == 'F') // K->F
      {
         ConvertType = 6;
      }
      else
      {
         ConvertType = 0;
      }
   }
   else
   {     
      fputs("error: Unknown Error1 ", stderr);
      return EXIT_FAILURE;
   } 
   return ConvertType;
}

int TempCalcs(int ConvertType, int IpTemp)
{
   float OpTemp = 0;
   switch (ConvertType)
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
   return OpTemp;
}



int main(int argc, char *argv[])
{ 
   char *unit[3];
     
   if (argc < 3)
   {
      fprintf(stderr, "%s: error: Not enough arguments.\nUsage: temp_convert INPUT_SCALE OUTPUT_SCALE [TEMPERATURE]...\n", argv[0]);
      return EXIT_FAILURE;
   }

   if (argc >= 3)
   {
      char u1= ReadIp(argv[1]);
      char u2= ReadIp(argv[2]);     

      if (argc == 3) // recognised scale but without temp values
      {
         return EXIT_SUCCESS;
      }

      int ConvertType = GetConvertType(u1,u2);
      printf("%d", ConvertType);

      for (int ip = 3; (ip < argc); ip++)
      {
         float IpTemp = atof(argv[ip]);
         float OpTemp = TempCalcs(ConvertType, IpTemp);
         printf("%.2f\n", OpTemp);
      }
   }
   return EXIT_SUCCESS;
}
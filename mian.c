#include <stdio.h>
#include <conio.h>

int main()
{
    int opt, ser, elm;
    printf("------Basic Statistical Operations-----------------\n");

    printf("Which Type of Series?\n1.) Individual\n2.) Discrete\n");
    scanf("%d", &ser);

    printf("How many elements?\n");
    scanf("%d", &elm);

    float ind_ser[elm];
    float disc_ser[elm][2];

    // In fist switch we are accepting the data from user and storing it in a array
    switch (ser)
    {
    case 1:
        printf("Enter the Elements of the Series: (x)\n");
        for (int i = 0; i < elm; i++)
        {
            scanf("%f", &ind_ser[i]);
        }
        break;

    case 2:
        printf("First Enter The Element and Then Its Frequency:(x-f) \n");
        for (int i = 0; i < elm; i++)
        {
            scanf("%f", &disc_ser[i][0]); // for X
            scanf("%d", &disc_ser[i][1]);  // for F
        }
        break;

    default:
        printf("Invalid Option For Type Series :(\n");
        break;
    }

    if (ser == 1 || ser == 2)
    {
        printf("What you wanna do?\n1.) Mean\n2.) Median\n3.) Mode\n");
        scanf("%d", &opt);

        // In this switch we are performing statistical operations on the data
        switch (opt)
        {
        case 1:
            break;

        case 2:
            break;

        case 3:
            break;

        default:
            printf("Invalid Option for Type Operation :( \n");
            break;
        }
    }

    getch();
    return 0;
}
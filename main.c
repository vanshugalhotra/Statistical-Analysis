#include <stdio.h>
#include <conio.h>

float ind_mean(float series[], int size) // sigma X / n
{
    float sum = 0, mean;
    for (int i = 0; i < size; i++)
    {
        sum += series[i];
    }
    mean = sum / size;
    return mean;
}

float disc_mean(float series[][2], int size) // sigma Fx/ sigma F
{
    float sum = 0, mean, sigmaf = 0;
    for (int i = 0; i < size; i++)
    {
        sum += series[i][0] * series[i][1];
        sigmaf += series[i][1];
    }
    mean = sum / sigmaf;
    return mean;
}

float ind_median(float series[], int size)
{
    float temp, median;
    int med_index;

    // logic to convert the series into ascending order
    for (int i = 0; i < size; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            if (series[i] > series[j])
            {
                temp = series[i];
                series[i] = series[j];
                series[j] = temp;
            }
        }
    }

    if (size % 2 != 0) // if elements are odd // n+1/2 th element
    {
        med_index = (size + 1) / 2;
        median = series[med_index - 1];
    }

    else // if elements are even n/2th n/2 +1
    {
        med_index = size / 2;
        median = (series[med_index - 1] + series[med_index]) / 2;
    }
    return median;
}

float disc_median(float series[][2], int size)
{
    float temp, median, temp_freq, cf_class;
    int cf[size], cf_ind;
    float sigmaf = 0;

    // logic to convert the series into ascending order
    for (int i = 0; i < size; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            if (series[i][0] > series[j][0])
            {
                temp = series[i][0];
                temp_freq = series[i][1];

                series[i][0] = series[j][0];
                series[i][1] = series[j][1];

                series[j][0] = temp;
                series[j][1] = temp_freq;
            }
        }
    }
    for (int i = 0; i < size; i++)
    {
        sigmaf += series[i][1];
        cf[i] = sigmaf;
    }

    cf_class = (sigmaf + 1)/2;
    
    for (int i = 0; i < size; i++)
    {
        if(cf_class <= cf[i])
        {
            cf_ind = i;
            printf("%d ", cf_ind);
            break;
        }
    }
    median = series[cf_ind][0];
    return median;
    
}

int main()
{
    int opt, ser, elm;
    float mean, median, mode;
    printf("------Basic Statistical Operations-----------------\n");

    printf("Which Type of Series?\n1.) Individual\n2.) Discrete\n");
    scanf("%d", &ser);

    printf("How many elements?\n");
    scanf("%d", &elm);

    float ind_ser[elm];
    float disc_ser[elm][2];

    // In first switch we are accepting the data from user and storing it in a array
    switch (ser)
    {
    case 1:
        printf("Enter the Elements of the Series: (x)\n");
        for (int i = 0; i < elm; i++)
        {
            printf("Enter the value of X: (%d) element\n", i + 1);
            scanf("%f", &ind_ser[i]);
        }
        break;

    case 2:
        printf("First Enter The Element and Then Its Frequency:(x-f) \n");
        for (int i = 0; i < elm; i++)
        {
            printf("Enter the value of X: (%d) element\n", i + 1);
            scanf("%f", &disc_ser[i][0]); // for X
            printf("Enter the value of F: (%d) element\n", i + 1);
            scanf("%f", &disc_ser[i][1]); // for F
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
            if (ser == 1)
            {
                mean = ind_mean(ind_ser, elm);
                printf("The mean is %f\n", mean);
            }

            else if (ser == 2)
            {
                mean = disc_mean(disc_ser, elm);
                printf("The mean is %f\n", mean);
            }

            break;

        case 2:
            if (ser == 1)
            {
                median = ind_median(ind_ser, elm);
                printf("The median is %f\n", median);
            }

            else if (ser == 2)
            {
                median = disc_median(disc_ser, elm);
                printf("The median is %f\n", median);
            }
            break;

        case 3:
            if (ser == 1)
            {
            }

            else if (ser == 2)
            {
            }
            break;

        default:
            printf("Invalid Option for Type Operation :( \n");
            break;
        }
    }

    getch();
    return 0;
}
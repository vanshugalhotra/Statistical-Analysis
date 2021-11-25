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

    cf_class = (sigmaf + 1) / 2;

    for (int i = 0; i < size; i++)
    {
        if (cf_class <= cf[i])
        {
            cf_ind = i;
            printf("%d ", cf_ind);
            break;
        }
    }
    median = series[cf_ind][0];
    return median;
}

float ind_mode(float series[], int size) // calculating mode for individual series
{
    float mode, series_freq[size][2];
    float freq = 1, max_freq, check_double, mean, median;
    int mode_index;
    for (int i = 0; i < size; i++) // looping to convert the individual series to discrete one to get highest frequency
    {
        for (int j = i + 1; j < size; j++)
        {
            if (series[i] == series[j])
            {
                freq++;
            }
        }
        series_freq[i][0] = series[i];
        series_freq[i][1] = freq;
        freq = 1;
    }
    max_freq = series_freq[0][1];
    for (int i = 0; i < size; i++)
    {
        if (series_freq[i][1] > max_freq)
            max_freq = series_freq[i][1];
    }

    check_double = 0;
    for (int i = 0; i < size; i++)
    {
        if (series_freq[i][1] == max_freq)
        {
            mode_index = i;
            check_double++;
        }
    }
    if (check_double <= 1) // if there is only one highest frequency
    {
        mode = series_freq[mode_index][0];
    }

    else
    { // mode = 3 median - 2 mean
        mean = ind_mean(series, size);
        median = ind_median(series, size);
        mode = (3 * median) - (2 * mean);
    }
    return mode;
}

float disc_mode(float series[][2], int size) // to find mode for discrete series
{
    float max_freq, check_double, mode, sigmaf;
    int mode_index, g1_ind[size], gi2, gi3, gi4, gi5, gi6;
    float g1[size], g2[size], g3[size], g4[size], g5[size], g6[size];
    float maxg1, maxg2, maxg3, maxg4, maxg5, maxg6;

    max_freq = series[0][1];
    for (int i = 0; i < size; i++)
    {
        if (series[i][1] > max_freq)
            max_freq = series[i][1];
    }

    check_double = 0;
    for (int i = 0; i < size; i++)
    {
        if (series[i][1] == max_freq)
        {
            mode_index = i;
            check_double++;
        }
    }
    if (check_double <= 1) // if there is only one highest frequency its simple
    {
        mode = series[mode_index][0];
    }

    else
    { // grouping method:  to break the tie between 2 or more values of same frequency
        // filling the groups
        int j = 0, x = 0;
        sigmaf = 0;
        for (int i = 0; i < size; i++, j += 2, x += 3)
        {
            g1[i] = series[i][1];                                           // only frequencies
            g2[i] = series[j][1] + series[j + 1][1];                        // only 1+2
            g3[i] = series[j + 1][1] + series[j + 2][1];                    // only 2+3
            g4[i] = series[x][1] + series[x + 1][1] + series[x + 2][1];     // only 1+2+3
            g5[i] = series[x + 1][1] + series[x + 2][1] + series[x + 3][1]; // only 2+3+4
            g6[i] = series[x + 2][1] + series[x + 3][1] + series[x + 4][1]; // only 3+4+5
            sigmaf += series[i][1];
        }
        maxg1 = g1[0];
        maxg2 = g2[0];
        maxg3 = g3[0];
        maxg4 = g4[0];
        maxg5 = g5[0];
        maxg6 = g6[0];

        // --------------------------------Looping in each group to find the maximum value----------------------------
        for (int i = 0; i < size; i++)
        {
            if (g1[i] > maxg1)
            {
                maxg1 = g1[i];
            }
        }
        int v2 = 0;
        while (g2[v2] < sigmaf && g2[v2] > 0)
        {
            if (g2[v2] > maxg2)
            {
                maxg2 = g2[v2];
            }
            v2++;
        }
        int v3 = 0;
        while (g3[v3] < sigmaf && g2[v3] > 0)
        {
            if (g3[v3] > maxg3)
            {
                maxg3 = g3[v3];
            }
            v3++;
        }
        int v4 = 0;
        while (g4[v4] < sigmaf && g4[v4] > 0)
        {
            if (g4[v4] > maxg4)
            {
                maxg4 = g4[v4];
            }
            v4++;
        }
        int v5 = 0;
        while (g5[v5] < sigmaf && g5[v5] > 0)
        {
            if (g5[v5] > maxg5)
            {
                maxg5 = g5[v5];
            }
            v5++;
        }
        int v6 = 0;
        while (g6[v6] < sigmaf && g6[v6] > 0)
        {
            if (g6[v6] > maxg6)
            {
                maxg6 = g6[v6];
            }
            v6++;
        }
        // ------------------------------------looping in each group to find the index at which the maximum value exists
        int ind = 0;
        for (int i = 0; i < size; i++)
        {
            if (series[i][1] == maxg1)
            {
                g1_ind[ind] = i;
                ind++;
            }
        }

        int vi2 = 0;
        while (g2[vi2] < sigmaf && g2[vi2] > 0)
        {
            if (g2[vi2] == maxg2)
            {
                gi2 = vi2;
            }
            vi2++;
        }
        int vi3 = 0;
        while (g3[vi3] < sigmaf && g3[vi3] > 0)
        {
            if (g3[vi3] == maxg3)
            {
                gi3 = vi3;
            }
            vi3++;
        }
        int vi4 = 0;
        while (g4[vi4] < sigmaf && g4[vi4] > 0)
        {
            if (g4[vi4] == maxg4)
            {
                gi4 = vi4;
            }
            vi4++;
        }
        int vi5 = 0;
        while (g5[vi5] < sigmaf && g5[vi5] > 0)
        {
            if (g5[vi5] == maxg5)
            {
                gi5 = vi5;
            }
            vi5++;
        }
        int vi6 = 0;
        while (g6[vi6] < sigmaf && g6[vi6] > 0)
        {
            if (g6[vi6] == maxg6)
            {
                gi6 = vi6;
            }
            vi6++;
        }

        // -----------------------Adjusting the frequencies according to the groups to break the tie--------
        int vb = 0;
        while (g1_ind[vb] < sigmaf && g1_ind[vb] > 0)
        {
            series[g1_ind[vb]][1] += 1;
            vb++;
        }
        // for g2
        series[((gi2 + 1) * 2) - 1 - 1][1] += 1;
        series[((gi2 + 1) * 2) - 1][1] += 1;

        // for g3
        series[((gi3 + 1) * 2) - 1][1] += 1;
        series[((gi3 + 1) * 2) + 1 - 1][1] += 1;

        // for g4
        series[((gi4 + 1) * 3) - 1][1] += 1;
        series[((gi4 + 1) * 3) - 1 - 1][1] += 1;
        series[((gi4 + 1) * 3) - 2 - 1][1] += 1;

        // for g5
        series[((gi5 + 1) * 3) + 1 - 1][1] += 1;
        series[((gi5 + 1) * 3) - 1][1] += 1;
        series[((gi5 + 1) * 3) - 1 - 1][1] += 1;

        // for g6
        series[((gi6 + 1) * 3) + 2 - 1][1] += 1;
        series[((gi6 + 1) * 3) + 1 - 1][1] += 1;
        series[((gi6 + 1) * 3) - 1][1] += 1;

        max_freq = series[0][1];
        for (int i = 0; i < size; i++)
        {
            if (series[i][1] > max_freq)
                max_freq = series[i][1];
        }

        for (int i = 0; i < size; i++)
        {
            if (series[i][1] == max_freq)
            {
                mode_index = i;
            }
        }

        mode = series[mode_index][0];
    }
    return mode;
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
                mode = ind_mode(ind_ser, elm);
                printf("The Mode is %f\n", mode);
            }

            else if (ser == 2)
            {
                mode = disc_mode(disc_ser, elm);
                printf("The Mode is %f\n", mode);
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
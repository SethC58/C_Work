// Include Standard I/O Library for basic output and input (so we can invoke ("call") printf(), scanf(), etc. in our program)
#include <stdio.h>

// This lets us use handy math symbols like PI and E
#define _USE_MATH_DEFINES
// Include math so we can call useful math symbols and functions
#include <math.h>
#ifndef M_PI
#define M_PI acos(-1.0)
#endif

// This is a function called CylinderVolume(float, float). The only differences between this and the main() entry point we have been using are:
// 1. it expects to have a float as its return data type, which is the first thing declared when defining a function; main() expects to return an integer, which is why it is "int main()" and not "float main()"
// 2. it requires input arguments from the user, which is another option for main()... but not currently (will be discussed later!)
// 3. the line before the final bracket does in fact return a float value (as long as all of the other, previous float values are valid), whereas in "int main()" we have been returning an integer 0 ("return 0")
float CylinderVolume(float width, float height)
{
    float radius = width / 2;

    // This is new. I am using M_PI and pow() from math.h, which allow me to use pi and raise a value to the power of two, respectively
    float area = M_PI * pow(radius, 2);
    return area * height;
}
// You will see all sorts of placement for functions in in-class examples and online: before main(), half after half before main(), from a different file... but for this lab, functions in the same file and above main() are fine

float PoolVolume(float W, float D, float LD, float DS, float LS, float WI, float T)
{
    // Calculate pool volume based on above parameters
    //------------------------------------------------

    // Interval 1 area is a rectangle
    float i1 = D * LD;

    // Interval 2 area is a Rectangle +- Triangle
    float i2 = (1/2)*((DS*D)*T);

    // Interval 3 area is a rectangle
    float i3 = DS * LS;

    // Interval 4 area is a triangle
    float i4 = WI * DS / 2;

    // Multiply Width and intervals to get total volume from area (since width is constant)
    return W * (i1 + i2 + i3 + i4);
}

// We can use this for both hot tub and pool cost calc
float WaterCost(float volume)
{
    // Get gallons, then get quarts... though this is done in two steps here, it can be done in a single step by initializing "float quarts = 4 * 7.481 * volume"
    float gallons = 7.481 * volume;
    float quarts = 4 * gallons;

    // return quarts times cost
    return quarts * 0.07;
}

// Remember #1
int main()
// Remember #2
{
    float WHT, DHT;
    float min_width = 6.0;
    float max_width = 12.0;
    float min_depth = 3.0;
    float max_depth = 5.0;
    do
    {
        printf("What is the width of your hot tub between 6 and 12 ft: ");
        scanf("%f", &WHT);

        if (WHT < min_width || WHT > max_width)
        {
            printf("The input is not in the range [%.1f, %.1f]. Please enter a value within this range.\n", min_width, max_width);
        }
    } while (WHT < min_width || WHT > max_width);
    do
    {
        printf("What is the Depth of your hot tub between 3 and 5 ft: ");
        scanf("%f", &DHT);

        if (DHT < min_depth || DHT > max_depth)
        {
            printf("The input is not in the range [%.1f, %.1f]. Please enter a value within this range.\n", min_depth, max_depth);
        }
    } while (DHT < min_depth || DHT > max_depth);
    float htempty = 0.667;

    // Variables for hot tub volume and cost
    float htv, htcost;
    
    // Invoking (calling) the CylinderVolume functions to calculate the hot tub volume minus the empty space
    htv = CylinderVolume(WHT, DHT-htempty);
    htcost = WaterCost(htv);
     
    float D, W, DS, L;
    float LD, LS, WI, T;
    do
    {
        {
            printf("Enter the depth of the pool for the deep end (8 - 17 feet): ");
            scanf("%f", &D);
            if (D >= 8 && D <= 17)
                break;
            else
                printf("Invalid depth. Please enter a value between 8 and 17 feet.\n");
        } 
    } while (D >= 8 && D <= 17);
    
    do
    {
        {
        printf("Enter the width of the pool (15 - 30 feet): ");
        scanf("%f", &W);
        if (W >= 15 && W <= 30)
            break;
        else
            printf("Invalid width. Please enter a value between 15 and 30 feet.\n");
        }
    } while (W >= 15 && W <= 30);

    do
    {
        printf("Enter the depth of the pool in the shallow end (0 - 4 feet): ");
        scanf("%f", &DS);
        if (DS >= 0 && DS <= 4)
            break;
        else
            printf("Invalid depth. Please enter a value between 0 and 4 feet.\n");
    } while (DS >= 0 && DS <= 4);

    do
    {
        printf("Enter the length of the pool (40 - 70 feet): ");
        scanf("%f", &L);
        if (L >= 40 && L <= 70)
            break;
        else
            printf("Invalid length. Please enter a value between 40 and 70 feet.\n");
    } while (L >= 40 && L <= 70);
    float WIa = 5, WIz = L/3;
    do
    {
        printf("Enter the length of walk in for the pool in feet  (5 - %.1f): ", WIz);
        scanf("%f", &WI);
        if (WI >= 5 && WI <= WIz)
            break;
        else
            printf("Invalid length. Please enter a value of 5 feet minimum to %.1f.\n", WIz);
    } while (WI >= 5 && WI <= WIz);
    float LSa = 10, LSz = L/2;
    do
    {
        printf("Enter the length of the shallow end of the pool (10 - %.1f): ", LSz);
        scanf("%f", &LS);
        if (LS >= 10 && LS <= LSz)
            break;
        else
            printf("Invalid length. Please enter a value of 10 feet minimum to %.1f.\n",LSz);
    } while (LS >= 10 && LS <= LSz);
    float LDa = 12, LDz = L/2;
    do
    {
        printf("Enter the length of the deep end of the pool (12 - %.1f): ",LDz);
        scanf("%f", &LD);
        if (LD >= 12 && LD <= LDz)
            break;
        else
            printf("Invalid length. Please enter a value of 12 feer to %.1f .\n", LDz);
    } while (LD >= 12 && LD <= LDz);

    printf("what is the length of transition between the deep and shallow end of the pool: ");
    scanf("%f", &T);
    // pool empty is six inches...
    float pempty = 1/2;

    // Store range values rounded to integers... Why? So we can use them for "for loops" later; for loops only take integer values for iteration, so we use implicit conversion... at the cost of precision (but we only need one output for this lab, anyway, no?)
    

    // Declare variables for length calculations... we need to figure out the lengths based on all of the rules, so we can store the values with these variables
    
    float pv, pcost;

    // If user input is good, then move onto the loops...
    if((L >= 40 && L <= 70) && (D >= 8 && D <= 17) && (W >= 13 && W <= 30) && (DS >= 0 && DS <= 4))
    {
        // For loops let us check every value within a range, so we don't have to make the user guess
        for(int i = WIa; i <= WIz; i++)
        {
            for(int j = LSa; j <= LSz; j++)
            {
                for(int k = LDa; k <= LDz; k++)
                {
                    // The above three loops will take us through each value within each of the three ranges for us to check for validity... in this case, "is T > 0?". Yes, we will get a lot of configurations

                    // Take the difference of the total length and those of the calculated intervals in order to calculate T, the transition length
                    T = L - (i + j + k);

                    // If T is greater than 0, print the lengths of resulting, acceptable configuration
                    if (T > 0)
                    {
                        printf("%d %d %d %d\n", i, j, k, T);

                        // Something like below will calculate the volume, then the pool cost of the pool volume minus empty
                        pv = PoolVolume(W, D-pempty, LD, DS-pempty, LS, WI, T);
                        pcost = WaterCost(pv);
                    }
                }
            }
        }
    }

    // We can put hot tub volume and cost here because the parameters do not change
    printf("Hot Tub Volume: %.2f gallons; Hot Tub Cost: $%.2f\n", htv, htcost);
    printf("Pool Volume: %.2f gallons; Pool Cost: $%.2f\n", pv, pcost);

    // Remember #3
    return 0;
// Remember #4
}
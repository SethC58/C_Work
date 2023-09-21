#include <stdio.h>
#include <math.h>

#define _USE_MATH_DEFINES

#ifndef M_PI
#define M_PI acos(-1.0)
#endif

// Function to calculate the volume of a cylinder
float CylinderVolume(float width, float height)
{
    float radius = width / 2;
    float area = M_PI * pow(radius, 2);
    return area * height;
}

// Function to calculate the volume of a pool
float PoolVolume(float W, float D, float LD, float DS, float LS, float WI, float T)
{
    float i1 = D * LD;
    float i2 = (1.0 / 2) * ((DS * D) * T);
    float i3 = DS * LS;
    float i4 = WI * DS / 2;
    return W * (i1 + i2 + i3 + i4);
}

// Function to calculate water cost
float WaterCost(float volume)
{
    float gallons = 7.481 * volume;
    float quarts = 4 * gallons;
    return quarts * 0.07;
}

// Function to get a valid dimension input from the user within a specified range
float GetValidDimension(const char *dimension_name, float min_value, float max_value)
{
    float dimension;
    do
    {
        printf("Enter the %s (%.1f - %.1f): ", dimension_name, min_value, max_value);
        scanf("%f", &dimension);

        if (dimension < min_value || dimension > max_value)
        {
            printf("Invalid input. Please enter a value between %.1f and %.1f.\n", min_value, max_value);
        }
    } while (dimension < min_value || dimension > max_value);
    return dimension;
}

// Function to calculate hot tub volume and cost
void CalculateHotTub()
{
    float WHT, DHT;
    float min_width = 6.0;
    float max_width = 12.0;
    float min_depth = 3.0;
    float max_depth = 5.0;

    WHT = GetValidDimension("width of your hot tub", min_width, max_width);
    DHT = GetValidDimension("depth of your hot tub", min_depth, max_depth);

    float htempty = 0.667;
    float htv, htcost;
    htv = CylinderVolume(WHT, DHT - htempty);
    htcost = WaterCost(htv);

    printf("Hot Tub Volume: %.2f gallons; Hot Tub Cost: $%.2f\n", htv, htcost);
}

// Function to calculate pool volume and cost
void CalculatePool()
{
    float D, W, DS, L;
    float LD, LS, WI, T;
    float min_depth_pool = 8.0;
    float max_depth_pool = 17.0;
    float min_width_pool = 15.0;
    float max_width_pool = 30.0;
    float min_depth_shallow = 0.0;
    float max_depth_shallow = 4.0;
    float min_length_pool = 40.0;
    float max_length_pool = 70.0;
    float min_length_walkin = 5.0;
    float max_length_walkin = max_length_pool / 3.0;
    float min_length_shallow = 10.0;
    float max_length_shallow = max_length_pool / 2.0;
    float min_length_deep = 12.0;
    float max_length_deep = max_length_pool / 2.0;

    D = GetValidDimension("depth of the pool for the deep end", min_depth_pool, max_depth_pool);
    W = GetValidDimension("width of the pool", min_width_pool, max_width_pool);
    DS = GetValidDimension("depth of the pool in the shallow end", min_depth_shallow, max_depth_shallow);
    L = GetValidDimension("length of the pool", min_length_pool, max_length_pool);
    WI = GetValidDimension("length of walk-in for the pool", min_length_walkin, max_length_walkin);
    LS = GetValidDimension("length of the shallow end of the pool", min_length_shallow, max_length_shallow);
    LD = GetValidDimension("length of the deep end of the pool", min_length_deep, max_length_deep);

    printf("Enter the length of transition between the deep and shallow end of the pool: ");
    scanf("%f", &T);
    float pempty = 0.5;
    float pv, pcost;

    if ((L >= min_length_pool && L <= max_length_pool) && (D >= min_depth_pool && D <= max_depth_pool) &&
        (W >= min_width_pool && W <= max_width_pool) && (DS >= min_depth_shallow && DS <= max_depth_shallow))
    {
        for (int i = min_length_walkin; i <= max_length_walkin; i++)
        {
            for (int j = min_length_shallow; j <= max_length_shallow; j++)
            {
                for (int k = min_length_deep; k <= max_length_deep; k++)
                {
                    T = L - (i + j + k);
                    if (T > 0)
                    {
                        printf("%d %d %d %d\n", i, j, k, T);
                        pv = PoolVolume(W, D - pempty, LD, DS - pempty, LS, WI, T);
                        pcost = WaterCost(pv);
                    }
                }
            }
        }
        printf("Pool Volume: %.2f gallons; Pool Cost: $%.2f\n", pv, pcost);
    }
    else
    {
        printf("Invalid pool dimensions.\n");
    }
}

// Function to calculate factorial
int factorial(int n)
{
    if (n == 0)
    {
        return 1;
    }
    else
    {
        return n * factorial(n - 1);
    }
}

// Function prototype for Towers of Hanoi
void runHanoi(int n, char fromPeg, char toPeg, char tempPeg);

// Function to calculate Towers of Hanoi
void CalculateTowersOfHanoi()
{
    int n;

    // Input from the user
    printf("Enter the number of disks for the Tower of Hanoi: ");
    scanf("%d", &n);

    // Call the Tower of Hanoi function
    runHanoi(n, 'A', 'C', 'B');
}

// Function to solve Tower of Hanoi for n disks
void runHanoi(int n, char fromPeg, char toPeg, char tempPeg)
{
    // Base case: If there's only one disk, move it from the source to the target peg
    if (n == 1)
    {
        printf("Move disk 1 from peg %c to peg %c\n", fromPeg, toPeg);
        return;
    }

    // Step 1: Move (n-1) disks from the source peg to the auxiliary peg using the target peg as auxiliary
    runHanoi(n - 1, fromPeg, tempPeg, toPeg);

    // Step 2: Move the nth disk from the source peg to the target peg
    printf("Move disk %d from peg %c to peg %c\n", n, fromPeg, toPeg);

    // Step 3: Move (n-1) disks from the auxiliary peg to the target peg using the source peg as auxiliary
    runHanoi(n - 1, tempPeg, toPeg, fromPeg);
}

// Function to calculate Fibonacci Numbers
void CalculateFibonacciNumbers()
{
    int n;
    printf("Enter the number of terms for Fibonacci sequence: ");
    scanf("%d", &n);

    int first = 0, second = 1;
    printf("Fibonacci Sequence: %d %d ", first, second);

    for (int i = 3; i <= n; i++)
    {
        int next = first + second;
        printf("%d ", next);
        first = second;
        second = next;
    }
    printf("\n");
}

// Function to calculate Sum of N
void CalculateSumOfN()
{
    int n, sum = 0;
    printf("Enter a positive integer: ");
    scanf("%d", &n);

    for (int i = 1; i <= n; i++)
    {
        sum += i;
    }

    printf("Sum of first %d natural numbers is %d\n", n, sum);
}

// Menu Option for Hot tub, Pool, Factorial, Towers of Hanoi, Fibonacci Numbers, and Sum of N
int main()
{
    int choice;

    printf("Choose an option:\n");
    printf("A. Calculate the volume and water cost of a hot tub\n");
    printf("B. Calculate the volume and water cost of a pool\n");
    printf("C. Calculate factorial\n");
    printf("D. Calculate the Towers of Hanoi\n");
    printf("E. Calculate the Fibonacci Numbers\n");
    printf("F. Calculate the Sum of N\n");
    printf("Enter your choice (A, B, C, D, E, or F): ");
    scanf(" %c", &choice);

    switch (choice)
    {
    case 'A':
    case 'a':
        CalculateHotTub();
        break;
    case 'B':
    case 'b':
        CalculatePool();
        break;
    case 'C':
    case 'c':
        int n;
        // User Input
        printf("Enter an integer: ");
        scanf("%d", &n);
        // Calculate the factorial and print the result
        int result = factorial(n);
        printf("Factorial of %d is: %d\n", n, result);
        break;
    case 'D':
    case 'd':
        CalculateTowersOfHanoi();
        break;
    case 'E':
    case 'e':
        CalculateFibonacciNumbers();
        break;
    case 'F':
    case 'f':
        CalculateSumOfN();
        break;
    default:
        printf("Invalid choice. Please choose A, B, C, D, E, or F.\n");
        break;
    }

    return 0;
}

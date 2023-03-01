#include <iostream>
#include <cmath>

using namespace std;

/**
 * https://www.youtube.com/watch?v=p8u_k2LIZyo
 *
 * @benpapp8860 1 year ago
The video goes kind of light on the Newton iteration part so I wanted to clarify some things:
f(y) = 1/(y^2) - x
y is our estimated inverse square root, and we’re trying to get a better estimate. To do that we want to get f(y) close to zero, which happens when y is correct and x equals the number that we’re taking the inverse-square-root of, ie the input named ‘number’. The x from the above formula isn’t being updated, we know it exactly already.

The derivative of f(y) is -2/(y^3). This is because the x is constant, 1/y^2 is the same as y^-2, so multiply by -2 and subtract 1 from the exponent.
I was confused about why it looked like we were solving for a new value of x but we aren’t we’re getting a new value of y so the line is really ynew = y - f(y)/f’(y), which after we enter the function and its derivative is
ynew = y - (1/(y^2) -x)/(-2/(y^3))
= y + y/2 - x*(y^3)/2
= y * (3/2 - y * y * x/2)
…and then it matches the code

 * @dkyle11 2 years ago
 * FYI for anyone learning C/C++: the "i = *(long*)x" approach is not standards compliant.
 * It obviously worked for Quake III, but for a modern compiler under high optimization, this could produce bugs.
 * The reason is complicated (search "strict aliasing" if you want to know more), but the correct alternative would be "memcpy(&i, &x, 4)".
 * It's also a good idea to use "uint32_t" instead of "long" to ensure "i" has 4 bytes. Modern systems often have "long"s that are 8 bytes.
*/

float fast_inverse_sqrt(float number)
{
    uint32_t i;
    float x2, y;
    const float threehalfs = 1.5F;

    x2 = number * 0.5F;
    y = number;

    memcpy(&i, &y, 4);         // evil floating point bit hack
    i = 0x5f3759df - (i >> 1); // WTF
    memcpy(&y, &i, 4);
    cout << "y: " << y << endl;
    y = y * (threehalfs - (x2 * y * y)); // Newton's Iteration to find better estimate
    cout << "y post 1 Newton's Iteration: " << y << endl;

    y = y * (threehalfs - (x2 * y * y)); // Newton's Iteration to find better estimate
    cout << "y post 2 Newton's Iteration: " << y << endl;

    return y;
}

int main()
{
    cout << fast_inverse_sqrt(4.0F) << endl;
    cout << (1.0F / sqrt(4.0F)) << endl;

    return 0;
}
#include <iostream>
#include <climits>
using namespace std;

int main()
{
    int n;

    cout << "Enter number of matrices: ";
    cin >> n;

    int p[n + 1];

    cout << "Enter dimensions of matrices:\n";
    cout << "For example, for A1(10x20), A2(20x30), enter: 10 20 30\n";

    for (int i = 0; i <= n; i++)
        cin >> p[i];

    int m[n + 1][n + 1];

    // Cost of multiplying one matrix is 0
    for (int i = 1; i <= n; i++)
        m[i][i] = 0;

    // Chain length
    for (int L = 2; L <= n; L++)
    {
        for (int i = 1; i <= n - L + 1; i++)
        {
            int j = i + L - 1;
            m[i][j] = INT_MAX;

            // Try every possible split
            for (int k = i; k < j; k++)
            {
                int cost = m[i][k]
                         + m[k + 1][j]
                         + p[i - 1] * p[k] * p[j];

                if (cost < m[i][j])
                    m[i][j] = cost;
            }
        }
    }

    cout << "\nMinimum number of scalar multiplications = "
         << m[1][n] << endl;

    return 0;
}

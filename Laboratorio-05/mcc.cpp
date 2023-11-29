
#include <bits/stdc++.h>
using namespace std;

class Array
{
public:
    template <class T>
    static void input(vector<T> &A, int n)
    {
        for (int i = 0; i < n; i++)
        {
            scanf("%d ", &A[i]);
        }
    }

    template <class T>
    static void print(vector<T> &A)
    {
        for (int i = 0; i < A.size(); i++)
        {
            cout << A[i] << " ";
        }
        cout << endl;
    }
};

// Utilizamos un array tridimensional para almacenar los resultados
int dp[101][1001][101];

class Solution
{
public:
    bool makeChanges(int N, int K, int target, const std::vector<int> &coins)
    {
        // Utilizamos un vector bidimensional para almacenar los resultados
        // Usamos un tamaño de (target + 1) ya que queremos incluir 0 hasta target
        std::vector<std::vector<bool>> dp(K + 1, std::vector<bool>(target + 1, false));

        // Inicializamos dp[0][0] como verdadero ya que con 0 monedas y 0 de objetivo siempre es posible
        dp[0][0] = true;

        // Iteramos cada moneda
        for (int i = 1; i <= N; ++i)
        {
            // Iteramos el número de monedas que podemos usar
            for (int k = 1; k <= K; ++k)
            {
                // Iteramos el objetivo
                for (int j = coins[i - 1]; j <= target; ++j)
                {
                    // Actualizamos dp[k][j] si podemos hacer el cambio con la moneda actual
                    dp[k][j] = dp[k][j] || dp[k - 1][j - coins[i - 1]];
                }
            }
        }

        return dp[K][target];
    }
};

int main()
{
    int t;
    scanf("%d ", &t);
    while (t--)
    {

        int N;
        scanf("%d", &N);

        int K;
        scanf("%d", &K);

        int target;
        scanf("%d", &target);

        vector<int> coins(N);
        Array::input(coins, N);
        Solution obj;
        bool res = obj.makeChanges(N, K, target, coins);

        cout << res << endl;
    }
    return 0;
}
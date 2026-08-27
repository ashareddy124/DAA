def knapsack(weights, values, capacity):
    n = len(weights)

    # dp[i][w] = maximum value using first i items
    # with a knapsack capacity of w
    dp = [[0] * (capacity + 1) for _ in range(n + 1)]

    for i in range(1, n + 1):
        for w in range(capacity + 1):

            # Current item can fit
            if weights[i - 1] <= w:
                include = values[i - 1] + dp[i - 1][w - weights[i - 1]]
                exclude = dp[i - 1][w]

                dp[i][w] = max(include, exclude)
            else:
                # Current item cannot fit
                dp[i][w] = dp[i - 1][w]

    return dp[n][capacity]


# Example
weights = [1, 3, 4, 5]
values = [1, 4, 5, 7]
capacity = 7

print("Maximum value:", knapsack(weights, values, capacity))

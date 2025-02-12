#include <algorithm>
#include <bits/stdc++.h>
#include <iostream>
#include <vector>
using namespace std;

int maxProfit(vector<int> &prices) {
  int maxP, l, r = 0;
  r = 1;
  while (r < prices.size() - 1) {
    if (prices[r] > prices[l]) {
      maxP = prices[r] - prices[l];
      r++;
    } else {
      l = r;
      r++;
    }
  }
  return maxP;
  // int s = 0;
  // int buy_price_index = 0;
  // vector<int> sorted_prices(prices);
  // sort(sorted_prices.begin(), sorted_prices.end());
  // int buy_price = sorted_prices[0];
  // for (int i = 0; i < prices.size(); i++) {
  //   if (prices[i] == buy_price) {
  //     buy_price_index = i;
  //     break;
  //   }
  // }
  // if (buy_price_index == prices.size() - 1) {
  //   return 0;
  // }
  // int max_profit = 0;
  // for (int i = 0; i < prices.size() - 1; i++) {
  //   for (int j = i + 1; j < prices.size() - 1; j++) {
  //     int profit = prices[j] - prices[i];
  //     if (profit > max_profit) {
  //       max_profit = profit;
  //     }
  //   }
  // }
  // return max_profit;
}

int main() {
  vector<int> prices = {5, 1, 5, 6, 7, 1, 10};
  int result = maxProfit(prices);
  cout << result << endl;
  return 0;
}

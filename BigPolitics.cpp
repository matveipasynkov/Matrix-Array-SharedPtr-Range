// #include <iostream>
// #include <queue>
//
// int main() {
//   std::priority_queue<int64_t, std::vector<int64_t>, std::greater<>> provinces;
//   size_t n = 0;
//   std::cin >> n;
//   for (size_t i = 0; i < n; ++i) {
//     int64_t number_of_citizens = 0;
//     std::cin >> number_of_citizens;
//     provinces.push(number_of_citizens);
//   }
//   int64_t result = 0;
//   while (provinces.size() != 1) {
//     int64_t first_province = provinces.top();
//     provinces.pop();
//
//     int64_t second_province = provinces.top();
//     provinces.pop();
//
//     result += first_province + second_province;
//     provinces.push(result);
//   }
//   std::cout << result << "\n";
//   return 0;
// }

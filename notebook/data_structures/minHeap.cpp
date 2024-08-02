template <typename T>
using min_heap = priority_queue<T, vector<T>, greater<T>>;

// ejemplo:
// min_heap<pair<int, int>> q;
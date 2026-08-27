int main() {
	ios :: sync_with_stdio(0);
	cin.tie(0);

	int t = 50; // Assign the number of tests that you want
	cout << t << "\n";
	
	mt19937 rng(time(0));

	uniform_int_distribution<long long> dist_x(1000, 1e7); // Chose the range [a,b] that you will generate the numbers
	uniform_int_distribution<int> dist_sum(2, 23); // n+m must be at least 2
	uniform_int_distribution<int> dist_n;

	for (int i = 0; i < t; i++) {
		// Generate x in [1000, 1e7]
		long long x = dist_x(rng);

		// Generate a total sum of n + m <= 40
		int total = dist_sum(rng);

		// Now generate n in [1, total-1], m = total - n
		dist_n = uniform_int_distribution<int>(1, total - 1);
		int n = dist_n(rng);
		int m = total - n;

		// Output test case
		cout << x << " " << n << " " << m << "\n";
	}
}

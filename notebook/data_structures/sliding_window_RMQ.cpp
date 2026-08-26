struct SlidingWindow_RMQ{
	int n; vi A;
	deque<int> q;  // stores indices, A[q.front()] is the min
	int l = 0, r = 0;  	// [l, r).
	
	SlidingWindow_RMQ(const vi &_A) : A(_A) { n = SIZE(A); }
	
	int get_minimum(){
		assert(!q.empty());
		return A[q.front()];
	}
	
	void advance_right(){
		assert(r < n);
		while(!q.empty() && A[r] <= A[q.back()]) { q.pop_back(); }
		q.push_back(r);
		r++;
	}
	
	void advance_left(){
		assert(l < r);
		if(l == q.front()) { q.pop_front(); }
		l++;
	}
};
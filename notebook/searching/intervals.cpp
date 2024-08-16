// We suppose that the intervals are correct: p.first <= p.second
// The intervals describe this: [p.first, p.second]

// This function checks if the intervals p1 and p2 are disjoint
bool areDisjoint(pair<ll, ll> &p1, pair<ll, ll> &p2) {
    ll startingTimeP1 = p1.first;
    ll endingTimeP1 = p1.second;
    ll startingTimeP2 = p2.first;
    ll endingTimeP2 = p2.second;

    // This option checks supposing that p1 starts before than p2
    bool option1 = endingTimeP1 < startingTimeP2;
    // This option checks supposing that p2 starts before than p1
    bool option2 = endingTimeP2 < startingTimeP1;

    return option1 || option2;
}

// This function checks if p1 is included in p2
bool isIncluded(pair<ll, ll> &p1, pair<ll, ll> &p2){
    ll startingTimeP1 = p1.first;
    ll endingTimeP1 = p1.second;
    ll startingTimeP2 = p2.first;
    ll endingTimeP2 = p2.second;

    bool res = startingTimeP2 <= startingTimeP1 && endingTimeP1 <= endingTimeP2;
    return res;
}

bool belongsToTheInterval(pair<ll, ll> &p1, ll x){
    ll startingTimeP1 = p1.first;
    ll endingTimeP1 = p1.second;

    return startingTimeP1 <= x && x <= endingTimeP1;
}

// This function helps me to sort the intervals to have first those which finish earlier. In case of a tie, I choose first the interval which starts earlier.
bool customCompare(pair<ll, ll> &p1, pair<ll, ll> &p2){
    ll endingTimeP1 = p1.second;
    ll endingTimeP2 = p2.second;

    if (endingTimeP1 < endingTimeP2){
        return true;
    } else if (endingTimeP1 > endingTimeP2){
        return false;
    }

    ll startingTimeP1 = p1.first;
    ll startingTimeP2 = p2.first;

    return startingTimeP1 < startingTimeP2;
}

// This function helps me to sort the intervals to have first those which start earlier. In case of a tie, I choose first the interval which ends later.
bool customCompare2(pair<ll,ll> &p1, pair<ll,ll> &p2){
    ll startingTimeP1 = p1.first;
    ll startingTimeP2 = p2.first;

    if (startingTimeP1 < startingTimeP2){
        return true;
    } else if (startingTimeP1 > startingTimeP2){
        return false;
    }

    ll endingTimeP1 = p1.second;
    ll endingTimeP2 = p2.second;

    return endingTimeP1 > endingTimeP2;
}

ll maximumNumberOfDisjointIntervals(vector<pair<ll, ll>> &intervals){
    int n = intervals.size();
    if (n == 0) return 0;
    sort(all(intervals), customCompare);

    pair<ll, ll> lastInterval = intervals[0];
    int res = 1;

    forsn(i,1,n){
        pair<ll, ll> currentInterval = intervals[i];

        if (areDisjoint(currentInterval,lastInterval)){
            lastInterval = currentInterval;
            res++;
        }
    }

    return res;
}


pair<ll, ll> redundantInterval(vector<pair<ll, ll>> &intervals){
    int n = intervals.size();
    pair<ll, ll> res = {UNDEFINED, UNDEFINED};

    sort(all(intervals), customCompare2);

    forn(i, n-1){
        pair<ll, ll> currentInterval = intervals[i];
        pair<ll, ll> nextInterval = intervals[i+1];

        if (isIncluded(nextInterval, currentInterval)){
            res = nextInterval;
            break;
        } else if (i+2 <= n-1){
            pair<ll, ll> laterInterval = intervals[i+2];

            if (belongsToTheInterval(currentInterval, nextInterval.first)){
                pair<ll,ll> newInterval = {currentInterval.second + 1, nextInterval.second};

                if (isIncluded(newInterval, laterInterval)){
                    res = nextInterval;
                    break;
                }
            }

        }
    }

    return res;
}
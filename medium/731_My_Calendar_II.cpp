/******************************************************************************
 * Implement a MyCalendarTwo class to store your events. A new event can be added
 * if adding the event will not cause a triple booking.
 *
 * Your class will have one method, book(int start, int end). Formally, this
 * represents a booking on the half open interval [start, end), the range of real
 * numbers x such that start <= x < end.
 *
 * A triple booking happens when three events have some non-empty intersection
 * (ie., there is some time that is common to all 3 events.)
 *
 * For each call to the method MyCalendar.book, return true if the event can be
 * added to the calendar successfully without causing a triple booking. Otherwise,
 * return false and do not add the event to the calendar.
 *
 * Your class will be called like this: MyCalendar cal = new MyCalendar();
 * MyCalendar.book(start, end)
 * Example 1:
 * MyCalendar();
 * MyCalendar.book(10, 20); // returns true
 * MyCalendar.book(50, 60); // returns true
 * MyCalendar.book(10, 40); // returns true
 * MyCalendar.book(5, 15); // returns false
 * MyCalendar.book(5, 10); // returns true
 * MyCalendar.book(25, 55); // returns true
 * Explanation: 
 * The first two events can be booked.  The third event can be double booked.
 * The fourth event (5, 15) can't be booked, because it would result in a triple booking.
 * The fifth event (5, 10) can be booked, as it does not use time 10 which is already double booked.
 * The sixth event (25, 55) can be booked, as the time in [25, 40) will be double booked with the third event;
 * the time [40, 50) will be single booked, and the time [50, 55) will be double booked with the second event.
 * Note:
 *
 * The number of calls to MyCalendar.book per test case will be at most 1000.
 * In calls to MyCalendar.book(start, end), start and end are integers in the range [0, 10^9].
******************************************************************************/

#include <map>
#include <iostream>
#include <algorithm>

using namespace std;

class MyCalendarTwo {
public:
    MyCalendarTwo() {
        
    }
    
    bool book(int start, int end) {
        // check overlap
        // cout << "try to insert (" << start << ", " << end << ")" << endl;
        if (!overlaps.empty()) {
            auto it = overlaps.lower_bound(end);
            if (it != overlaps.begin()) {
                auto p = prev(it);
                if (p->second > start) {
                    // cout << "\tfailed to book this" << endl;
                    return false;
                }
            }
        }
        // update overlap if existing
        auto e_it = bookings.lower_bound(end);
        if (e_it != bookings.begin()) {
            for (auto it = bookings.begin(); it != e_it; ++it) {
                int o_s = max(it->first, start);
                int o_e = min(it->second, end);
                if (o_s < o_e) {
                    overlaps[o_s] = o_e;
                }
            }
        }
        auto it = bookings.insert(make_pair(start, end));
        if (!it.second && it.first->second < end) {
            it.first->second = end;
        }
        /*cout << "\tbookings: ";
        for (auto& kv : bookings) {
            cout << "(" << kv.first << ", " << kv.second << ") ";
        }
        cout << endl;
        cout << "\toverlaps: ";
        for (auto& kv : overlaps) {
            cout << "(" << kv.first << ", " << kv.second << ") ";
        }
        cout << endl;
        */
        return true;
    }
    
private:
    map<int, int> bookings;
    map<int, int> overlaps;
};

/**
 * Your MyCalendarTwo object will be instantiated and called as such:
 * MyCalendarTwo obj = new MyCalendarTwo();
 * bool param_1 = obj.book(start,end);
 */

int main() {
  MyCalendarTwo cal;
  cout << (cal.book(24, 40) ? "yes" : "no") << endl;
  cout << (cal.book(43, 50) ? "yes" : "no") << endl;
  cout << (cal.book(27, 43) ? "yes" : "no") << endl;
  cout << (cal.book(5, 21) ? "yes" : "no") << endl;
  cout << (cal.book(30, 40) ? "yes" : "no") << endl;
  return 0;
}



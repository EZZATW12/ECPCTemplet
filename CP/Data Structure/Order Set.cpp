#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define ordered_set tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>
// find_by_order() returns an iterator to the k-th smallest element (counting from zero)
// order_of_key() returns the number of items in a set that are strictly smaller than our item
#define ordered_multiset tree<int, null_type, less_equal<int>, rb_tree_tag, tree_order_statistics_node_update>
#define ordered_multiset1 tree<int, null_type, greater_equal<int>, rb_tree_tag, tree_order_statistics_node_update>

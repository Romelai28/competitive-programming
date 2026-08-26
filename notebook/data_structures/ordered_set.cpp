#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp> 
using namespace __gnu_pbds; 

template<typename T>
using ordered_set = tree<T, null_type,less<T>, rb_tree_tag,tree_order_statistics_node_update>;

template <typename T>
using ordered_multiset = tree<
    pair<T, int>,
    null_type,
    less<pair<T, int>>, // NOT less_equal
    rb_tree_tag,
    tree_order_statistics_node_update
>;

ordered_set v;
ordered_multiset<int> ms;
v.insert(0);
*v.find_by_order(k); // Elemento en la posicion k-th
*v.find_by_rank(m); // Te dice el index del elemento m en v (suponiend que v ya esta ahi)
v.order_of_key(val);  // Numero de elementos que son < val (o indice de val en caso de que val pertenezca)


ordered_multiset<T> s;
s.insert({t, id}); // T es el tipo del primer elemento del pair. El segundo es un indice unico para definir una relacion de orden estricto (se rompe sin esto)

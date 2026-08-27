// Leer/escribir archivos externos
freopen("prueba.in", "r", stdin);
freopen("prueba.out", "w", stdout);

// Input/Output
cout << fixed << setprecision(1); // Imprimir con 1 decimal
cout << setprecision(numeric_limits<ld>::digits10 + 1); // Muestra con full precision para ld

// cin.ignore(numeric_limits<streamsize>::max(), '\n'); Si leimos previamente algo, poner esto antes del getline
string s;
getline(cin, s); // Leer un string con espacios

istringstream iss(s);
string word; vector<string> words;
while (iss >> word) words.pb(word); // Leer todas las palabras de un string separado por espacio

// String 
string stri = to_string(myInt);
char c; isupper(c); isdigit(c); toupper(c);

// Otros
int myint1 = stoi(myString); // Funciona con int y float.
sort(all(A), greater()); // Para ordenar un vector, llamar a una funcion bool
*max_element(all(A)); *min_element(all(A)); 
mt19937 rng(time(0));
shuffle(all(A), rng); // Mezclar un vector, rng es mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
do {...} while (next_permutation(all(A))); // Generar todas las permutaciones de un vector (A debe estar ordenado!)
__int128 x; // Tipo de datos para calculaciones muy grandes

const double DINF=numeric_limits<double>::infinity();  // double inf

int __builtin_popcount (unsigned int x) // Return the numbers the numbers of 1-bit in x
int __builtin_ctz (unsigned int x) // Returns the number of trailing 0-bits in x. x=0 is undefined.
int __builtin_clz (unsigned int x) // Returns the number of leading 0-bits in x. x=0 is undefined.
int __builtin_popcountll (unsigned long long x) // x of type long long just add 'll' at the end of the function.

set_intersection(all(set1), all(set2), inserter(res, res.begin()));
set_union(all(set1), all(set2), inserter(res, res.begin()));


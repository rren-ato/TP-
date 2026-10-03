La memoria dinamica se plantea con datos que no presentan un linkeo directo de su posicion en el stack a donde apunta en el heap.
La dirección va cambiando

Un puntero vale 4 bits ya sea si es int *arr o double *arr.

Por ejemplo...
//! Aplicando el '&' acceso a la dirección de memoria y con '*' accedo al valor del dato en esa dirección de memoria2
int *p = &a
(*p)++;

cout << a << endl //! apuntara al valor de a

cout << &p >> endl;    //! apuntara a la dirección de memoria de la variable
cout << p << endl;     //! su valor será la direccion de la ultima variable que apunto
cout << *p << endl;    //! apuntara al valor de la variable, de la direccion a la que apunta

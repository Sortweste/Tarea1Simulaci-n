#include <fstream>

//Esta funci�n recibe:
//- Un flujo de archivo de texto para extraer la informaci�n
//- La cantidad de l�neas a omitir (puede ser 1 o 2)
//- La cantidad de filas de informaci�n a extraer
//- El arreglo de objetos a llenar con la informaci�n extraida
//La funci�n extrae del archivo de texto los datos de inter�s en la malla
//de acuerdo a los par�metros enviados.
void obtenerDatos(istream &file,int nlines,int n,int mode,item* item_list){
    //Se prepara una variable string para leer las l�neas a omitir
    string line;
    //Siempre se omite al menos una l�nea
    file >> line;
    //Si es necesario omitir una l�nea adicional, se efect�a
    if(nlines==DOUBLELINE) file >> line;

    //Se itera una cantidad de veces igual a la cantidad de datos a extraer
    //que ser� igual a la cantidad de objetos a instanciar
    for(int i=0;i<n;i++){
        //Se verifica la cantidad y tipos de datos a extraer por fila
        switch(mode){
        //Se extrae un entero y un real por fila
        case INT_FLOAT:
            int e; float r;
            file >> e >> r;
            //Se instancian el entero y el real del objeto actual
            item_list[i].setIntFloat(e,r);
            break;
        //Se extraen tres enteros
        case INT_INT_INT:
            int e1,e2,e3;
            file >> e1 >> e2 >> e3;
            //Se instancia los tres enteros en el objeto actual
            item_list[i].setIntIntInt(e1,e2,e3);
            break;
        }
    }
}

//Esta funci�n recibe:
//- El objeto mesh con toda la informaci�n de la malla
//La funci�n solicita el nombre del archivo que contiene la informaci�n de la malla
//y procede a extraer todos los datos para colocarlos adecuadamente dentro del objeto mesh
void leerMallayCondiciones(mesh &m){
    //Se prepara un arreglo para el nombre del archivo
    char filename[10];
    //Se prepara un flujo para el archivo
    ifstream file;
    //Se preparan variables para extraer los par�metros del problema y las cantidades de
    //datos en la malla (nodos, elementos, condiciones de Dirichlet, condiciones de Neumann)
    //Ya no necesitamos tener una longitud porque esta ya no es la misma para todos los elementos
    float k,Q;
    int nnodes,neltos,ndirich,nneu;

    //Se obliga al usuario a ingresar correctamente el nombre del archivo
    do{
        cout << "Ingrese el nombre del archivo que contiene los datos de la malla: ";
        cin >> filename;
        //Se intenta abrir el archivo
        file.open(filename);
    }while(!file); //Si no fue posible abrir el archivo, se intenta de nuevo

    //Se leen y guardan los par�metros y cantidades

    //Quitar la l
    //file >> l >> k >> Q;
    //Ya no necesitamos leer la longitud porque esta ya no es la misma para todos los elementos
    file >> k >> Q;
    file >> nnodes >> neltos >> ndirich >> nneu;

    //Se instancian los par�metros y cantidades en el objeto mesh
    //Ya no necesitamos asignar la longitud a la mesh
    m.setParameters(k,Q);
    m.setSizes(nnodes,neltos,ndirich,nneu);
    //En base a las cantidades, se preparan arreglos de objetos para guardar
    //el resto de la informaci�n
    m.createData();

    //Se extraen, siguiendo el formato del archivo, la informaci�n de:
    //- Los nodos de la malla
    //- Los elementos de la malla
    //- Las condiciones de Dirichlet impuestas
    //- Las condiciones de Neumann impuestas
    obtenerDatos(file,SINGLELINE,nnodes,INT_FLOAT,m.getNodes());
    obtenerDatos(file,DOUBLELINE,neltos,INT_INT_INT,m.getElements());
    obtenerDatos(file,DOUBLELINE,ndirich,INT_FLOAT,m.getDirichlet());
    obtenerDatos(file,DOUBLELINE,nneu,INT_FLOAT,m.getNeumann());

    //Se cierra el archivo antes de terminar
    file.close();
}



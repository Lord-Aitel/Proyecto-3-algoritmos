#include <iostream>
#include <string>
#include <random>
#include <set>
#include <algorithm>
#include <iterator>
#include <chrono>
#include <stack>
#include <utility>
#include <vector>
#include <numeric>

using namespace std;
using std::cout;
using std::endl;

// Generar números aleatorios únicos según rango
set<int> numerosAleatorios(int contador, int inicio, int fin)
{
    random_device rd;
    mt19937 gen(rd());
    set<int> aleatorio;

    while (aleatorio.size() < contador)
    {
        uniform_int_distribution<int> dis_range(inicio, fin);
        int num = dis_range(gen);
        aleatorio.insert(num);
    }
    return aleatorio;
}

// Convertir un set en un vector y desordenarlo
vector<int> vectorDesordenado(set<int>& numeros)
{
    vector<int> vectorNumeros(numeros.begin(), numeros.end());
    random_device rd;
    mt19937 gen(rd());
    shuffle(vectorNumeros.begin(), vectorNumeros.end(), gen);
    return vectorNumeros;
}

// Generar un conjunto de datos aleatorio sin repetición
vector<int> numerosAleatoriosSinRepeticion(int min, int max, int inicio, int fin)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis_count(min, max);
    int contador = dis_count(gen);

    set<int> random = numerosAleatorios(contador, 0, max);
    return vectorDesordenado(random);
}

// Generar datos aleatorios con repetición
vector<int> numerosAleatoriosConRepeticion(int min, int max, int inicio, int fin)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis_count(min, max);
    int contador = dis_count(gen);

    vector<int> randomDuplicados(contador);
    uniform_int_distribution<int> dis_positive(inicio, fin);

    generate(randomDuplicados.begin(), randomDuplicados.end(), [&gen, &dis_positive]() 
    {
        return dis_positive(gen);
    });

    return randomDuplicados;
}

// Generar un conjunto de datos ordenado (ascendente o descendente)
vector<int> datosOrdenados(int min, int max, int inicio, bool orden)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis_count(min, max);
    int contador = dis_count(gen);

    vector<int> ordenados(contador);
    iota(ordenados.begin(), ordenados.end(), inicio);

    if (!orden)
    {
        reverse(ordenados.begin(), ordenados.end());
    }

    return ordenados;
}

// Generar un conjunto de datos con variación por categoría
vector<vector<int>> datosPorCategoria(int categorias, int min, int max)
{
    random_device rd;
    mt19937 gen(rd());

    vector<vector<int>> datos(categorias);

    for (int i = 0; i < categorias; ++i)
    {
        uniform_int_distribution<int> dis_count(min, max);
        int contador = dis_count(gen);

        set<int> numeros;
        uniform_int_distribution<int> dis(0, 2000);

        // Generar un set de números únicos en el rango deseado
        while (numeros.size() < contador) 
        {
            int numero = dis(gen);
            numeros.insert(numero);
        }
        datos[i] = vectorDesordenado(numeros);
    }
    return datos;
}

// Generar datos de carrera
vector<int> datosCarrera(const vector<int>& datos, bool aleatorios, bool duplicados, bool orden)
{
    vector<int> carrera = datos;

    if (aleatorios)
    {
        shuffle(carrera.begin(), carrera.end(), mt19937(std::random_device()()));
    }

    if (!duplicados)
    {
        sort(carrera.begin(), carrera.end());
        carrera.erase(unique(carrera.begin(), carrera.end()), carrera.end());
    }

    if (!orden)
    {
        reverse(carrera.begin(), carrera.end());
    }

    return carrera;
}

// Bubble Sort
void bubbleSort(vector<int>& datos, bool orden)
{
    int tamano = datos.size();
    for (int i = 0; i < tamano - 1; ++i)
    {
        for (int j = 0; j < tamano - i - 1; ++j)
        {
            if (orden)
            {
                if (datos[j] > datos[j + 1])
                {
                    swap(datos[j], datos[j + 1]);
                }
            }
            else
            {
                if (datos[j] < datos[j + 1])
                {
                    swap(datos[j], datos[j + 1]);
                }
            }
        }
    }
}

// Heap Sort

void heapify(vector<int>& datos, int tamano, int indice, bool orden)
{
    int mayor = indice;
    int izquierda = 2 * indice + 1;
    int derecha = 2 * indice + 2;

    if (orden)
    {
        if (izquierda < tamano && datos[izquierda] > datos[mayor])
        {
            mayor = izquierda;
        }

        if (derecha < tamano && datos[derecha] > datos[mayor])
        {
            mayor = derecha;
        }
    }
    else
    {
        if (izquierda < tamano && datos[izquierda] < datos[mayor])
        {
            mayor = izquierda;
        }

        if (derecha < tamano && datos[derecha] < datos[mayor])
        {
            mayor = derecha;
        }
    }

    if (mayor != indice)
    {
        swap(datos[indice], datos[mayor]);
        heapify(datos, tamano, mayor, orden);
    }
}

void heapSort(vector<int>& datos, bool orden)
{
    int tamano = datos.size();
    for (int i = tamano / 2 - 1; i >= 0; --i)
    {
        heapify(datos, tamano, i, orden);
    }

    for (int i = tamano - 1; i >= 0; --i)
    {
        swap(datos[0], datos[i]);
        heapify(datos, i, 0, orden);
    }
}

// Quick Sort
void quickSort(vector<int>& datos, int inicio, int fin, bool orden)
{
    stack<pair<int, int>> pila;
    pila.push(make_pair(inicio, fin));

    while (!pila.empty())
    {
        int inicioActual = pila.top().first;
        int finActual = pila.top().second;
        pila.pop();

        if (inicioActual >= finActual)
            continue;

        int pivote = datos[finActual];
        int i = inicioActual - 1;

        for (int j = inicioActual; j <= finActual - 1; ++j)
        {
            if (orden)
            {
                if (datos[j] < pivote)
                {
                    ++i;
                    swap(datos[i], datos[j]);
                }
            }
            else
            {
                if (datos[j] > pivote)
                {
                    ++i;
                    swap(datos[i], datos[j]);
                }
            }
        }

        swap(datos[i + 1], datos[finActual]);
        int indicePivote = i + 1;

        pila.push(make_pair(inicioActual, indicePivote - 1));
        pila.push(make_pair(indicePivote + 1, finActual));
    }
}

// Merge Sort
void merge(vector<int>& datos, int inicio, int medio, int fin, bool orden)
{
    int tamanoIzquierda = medio - inicio + 1;
    int tamanoDerecha = fin - medio;

    vector<int> izquierda(datos.begin() + inicio, datos.begin() + medio + 1);
    vector<int> derecha(datos.begin() + medio + 1, datos.begin() + fin + 1);

    int indiceIzquierda = 0;
    int indiceDerecha = 0;
    int indiceMerge = inicio;

    while (indiceIzquierda < tamanoIzquierda && indiceDerecha < tamanoDerecha)
    {
        if (orden)
        {
            if (izquierda[indiceIzquierda] <= derecha[indiceDerecha])
            {
                datos[indiceMerge] = izquierda[indiceIzquierda];
                ++indiceIzquierda;
            }
            else
            {
                datos[indiceMerge] = derecha[indiceDerecha];
                ++indiceDerecha;
            }
        }
        else
        {
            if (izquierda[indiceIzquierda] >= derecha[indiceDerecha])
            {
                datos[indiceMerge] = izquierda[indiceIzquierda];
                ++indiceIzquierda;
            }
            else
            {
                datos[indiceMerge] = derecha[indiceDerecha];
                ++indiceDerecha;
            }
        }
        ++indiceMerge;
    }

    while (indiceIzquierda < tamanoIzquierda)
    {
        datos[indiceMerge] = izquierda[indiceIzquierda];
        ++indiceIzquierda;
        ++indiceMerge;
    }

    while (indiceDerecha < tamanoDerecha)
    {
        datos[indiceMerge] = derecha[indiceDerecha];
        ++indiceDerecha;
        ++indiceMerge;
    }
}


void mergeSort(vector<int>& datos, int inicio, int fin, bool orden)
{
    if (inicio < fin)
    {
        int medio = inicio + (fin - inicio) / 2;
        mergeSort(datos, inicio, medio, orden);
        mergeSort(datos, medio + 1, fin, orden);
        merge(datos, inicio, medio, fin, orden);
    }
}

// Selection Sort
void selectionSort(vector<int>& datos, bool orden)
{
    int tamano = datos.size();

    for (int i = 0; i < tamano - 1; ++i)
    {
        int indiceExtremo = i;
        for (int j = i + 1; j < tamano; ++j)
        {
            if (orden)
            {
                if (datos[j] < datos[indiceExtremo])
                {
                    indiceExtremo = j;
                }
            }
            else
            {
                if (datos[j] > datos[indiceExtremo])
                {
                    indiceExtremo = j;
                }
            }
        }
        swap(datos[i], datos[indiceExtremo]);
    }
}

// Insertion Sort
void insertionSort(vector<int>& datos, bool orden)
{
    int tamano = datos.size();
    for (int i = 1; i < tamano; ++i)
    {
        int valorActual = datos[i];
        int j = i - 1;
        if (orden)
        {
            while (j >= 0 && datos[j] > valorActual)
            {
                datos[j + 1] = datos[j];
                --j;
            }
        }
        else
        {
            while (j >= 0 && datos[j] < valorActual)
            {
                datos[j + 1] = datos[j];
                --j;
            }
        }
        datos[j + 1] = valorActual;
    }
}

// Shell Sort
void shellSort(vector<int>& datos, bool orden)
{
    int tamano = datos.size();
    for (int brecha = tamano / 2; brecha > 0; brecha /= 2)
    {
        for (int i = brecha; i < tamano; ++i)
        {
            int valorActual = datos[i];
            int j = i;
            if (orden)
            {
                while (j >= brecha && datos[j - brecha] > valorActual)
                {
                    datos[j] = datos[j - brecha];
                    j -= brecha;
                }
            }
            else
            {
                while (j >= brecha && datos[j - brecha] < valorActual)
                {
                    datos[j] = datos[j - brecha];
                    j -= brecha;
                }
            }
            datos[j] = valorActual;
        }
    }
}


struct ResultadoAlgoritmo 
{
    string nombre;
    double tiempo;
};

// Función para realizar la carrera
void carrera(int set, vector<int>& datos, bool orden) 
{
    vector<ResultadoAlgoritmo> resultados;
    switch (set)
    {
    case 1:
        cout << "Aleatorio sin repetición" << endl;
        break;
    case 2:
        cout << "Aleatorio con repetición" << endl;
        break;
    case 3:
        cout << "Ordenado" << endl;
        break;
    case 4:
        cout << "Inversamente Ordenado" << endl;
        break;
    default:
        break;
    }

    // Variables para guardar el algoritmo más rápido
    int algoritmoMasRapido = -1;
    double tiempoMasRapido = numeric_limits<double>::max();

    // BubbleSort
    vector<int> bubble = datos;
    auto inicio = std::chrono::high_resolution_clock::now();
    bubbleSort(bubble, orden);
    auto fin = std::chrono::high_resolution_clock::now();    
    std::chrono::duration<double> duracion = fin - inicio;
    ResultadoAlgoritmo bubbleResult;
            bubbleResult.nombre = "Bubble Sort";
            bubbleResult.tiempo = duracion.count();
            resultados.push_back(bubbleResult);

    if (duracion.count() < tiempoMasRapido)
    {algoritmoMasRapido = 1;tiempoMasRapido = duracion.count();}

    // HeapSort
    vector<int> heap = datos;
    inicio = std::chrono::high_resolution_clock::now();
    heapSort(heap, orden);
    fin = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duracion2 = fin - inicio;
    ResultadoAlgoritmo HeapResult;
            HeapResult.nombre = "Heap Sort";
            HeapResult.tiempo = duracion2.count();
            resultados.push_back(HeapResult);

    if (duracion2.count() < tiempoMasRapido)
    {algoritmoMasRapido = 2;tiempoMasRapido = duracion2.count();}

    // Quick Sort
    vector<int> quick = datos;
     inicio = std::chrono::high_resolution_clock::now();
    quickSort(quick, 0, quick.size() - 1, orden);
    fin = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duracion3 = fin - inicio;
    ResultadoAlgoritmo QuickResult;
            QuickResult.nombre = "Quick Sort";
            QuickResult.tiempo = duracion3.count();
            resultados.push_back(QuickResult);

    if (duracion3.count() < tiempoMasRapido)
    {algoritmoMasRapido = 3;tiempoMasRapido = duracion3.count();}

    // Merge Sort
    vector<int> merge = datos;
    inicio = std::chrono::high_resolution_clock::now();
    mergeSort(merge, 0, merge.size() - 1, orden);
    fin = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duracion4 = fin - inicio;
    ResultadoAlgoritmo MergeResult;
            MergeResult.nombre = "Merge Sort";
            MergeResult.tiempo = duracion4.count();
            resultados.push_back(MergeResult);

    // Actualizar el algoritmo más rápido
    if (duracion4.count() < tiempoMasRapido)
    {algoritmoMasRapido = 4;tiempoMasRapido = duracion4.count();}

    // Selection Sort
    vector<int> selection = datos;
    inicio = std::chrono::high_resolution_clock::now();
    selectionSort(selection, orden);
    fin = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duracion5 = fin - inicio;
    ResultadoAlgoritmo SelectionResult;
            SelectionResult.nombre = "Selection Sort";
            SelectionResult.tiempo = duracion5.count();
            resultados.push_back(SelectionResult);

    // Actualizar el algoritmo más rápido
    if (duracion5.count() < tiempoMasRapido)
    {algoritmoMasRapido = 5;tiempoMasRapido = duracion5.count();}

    // Insertion Sort
    vector<int> insertion = datos;
    inicio = std::chrono::high_resolution_clock::now();
    insertionSort(insertion, orden);
    fin = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duracion6 = fin - inicio;
    ResultadoAlgoritmo InsertionResult;
            InsertionResult.nombre = "Insertion Sort";
            InsertionResult.tiempo = duracion6.count();
            resultados.push_back(InsertionResult);

    // Actualizar el algoritmo más rápido
    if (duracion6.count() < tiempoMasRapido)
    {algoritmoMasRapido = 6;tiempoMasRapido = duracion6.count();}

    // Shell Sort
    vector<int> shell = datos;
    inicio = std::chrono::high_resolution_clock::now();
    shellSort(shell, orden);
    fin = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duracion7 = fin - inicio;
    ResultadoAlgoritmo ShellResult;
            ShellResult.nombre = "Shell Sort";
            ShellResult.tiempo = duracion7.count();
            resultados.push_back(ShellResult);

    // Actualizar el algoritmo más rápido
    if (duracion7.count() < tiempoMasRapido)
    {algoritmoMasRapido = 7;tiempoMasRapido = duracion7.count();}

    // Mostrar resultados enumerados de la carrera
    cout << "Resultados de la carrera:" << endl;
    for (size_t i = 0; i < resultados.size(); ++i) 
    {
        cout << i + 1 << ". " << resultados[i].nombre << ": " << resultados[i].tiempo << " segundos" << endl;
    }
    
    cout << "El ganador es: ";

    switch (algoritmoMasRapido)
    {
    case 1:
        cout << "Bubble Sort";
        break;
    case 2:
        cout << "Heap Sort";
        break;
    case 3:
        cout << "Quick Sort";
        break;
    case 4:
        cout << "Merge Sort";
        break;
    case 5:
        cout << "Selection Sort";
        break;
    case 6:
        cout << "Insertion Sort";
        break;
    case 7:
        cout << "Shell Sort";
        break;
    default:
        break;
    }

    cout << " con un tiempo de " << tiempoMasRapido << " segundos" << endl;

}

int main() 
{

    vector<int> colaSinRepeticion = numerosAleatoriosSinRepeticion(100000, 110000, 0, 1000000);
    vector<int> colaConRepeticion = numerosAleatoriosConRepeticion(100000, 110000, 0, 1000000);
    vector<int> colaOrdenada = datosOrdenados(90000, 100000, 1, true);
    vector<int> colaInversa = datosOrdenados(90000, 100000, 1, false);

    // Generar diferentes conjuntos para eventos
    vector<int> eventosSinRepeticion = numerosAleatoriosSinRepeticion(60000, 80000, 0, 1000000);
    vector<int> eventosConRepeticion = numerosAleatoriosConRepeticion(60000, 80000, 0, 1000000);
    vector<int> eventosOrdenados = datosOrdenados(50000, 70000, 1, true);
    vector<int> eventosInversa = datosOrdenados(50000, 70000, 1, false);

    // Generar los conjuntos de datos para la trazabilidad de objetos
    int categorias = 15;
    int objetosMinimos = 1000;
    int objetosMaximos = 1500;

    vector<vector<int>> datosCategoria = datosPorCategoria(categorias, 1000, 1500);

    // Generar los conjuntos de datos de carrera con las características requeridas
    bool aleatorios = true;
    bool duplicados = false;
    bool orden = true;

    vector<vector<int>> informacionCarrera;

    for (const auto& sets : datosCategoria)
    {
        vector<int> carreraAleatoriaSinRepeticion = datosCarrera(sets, aleatorios, duplicados, orden);
        vector<int> carreraAleatoriaConRepeticion = datosCarrera(sets, aleatorios, !duplicados, orden);
        vector<int> carreraOrdenada = datosCarrera(sets, false, aleatorios, orden);
        vector<int> carreraInversa = datosCarrera(sets, false, aleatorios, !orden);

        informacionCarrera.push_back(carreraAleatoriaSinRepeticion);
        informacionCarrera.push_back(carreraAleatoriaConRepeticion);
        informacionCarrera.push_back(carreraOrdenada);
        informacionCarrera.push_back(carreraInversa);
    }

    cout << "Datos en arreglo 1 " << colaSinRepeticion.size() << endl;
    cout << "Datos en arreglo 2 " << eventosSinRepeticion.size() << endl;

    int set = 1;

    int opcion = 0;

    do {
        std::cout << "Carrera de algoritmos" << std::endl;
        std::cout << "1. Colas de espera" << std::endl;
        std::cout << "2. Trazabilidad de objetos" << std::endl;
        std::cout << "3. Eventos de cada escenario" << std::endl;
        std::cout << "4. Salir" << std::endl;
        std::cout << "Seleccione una opcion: ";
        std::cin >> opcion;

        switch (opcion) {
            case 1:
                // Lógica para la carrera de colas de espera
                cout << "Carrera de Colas de espera" << std::endl;
                carrera(1, colaSinRepeticion, true);
                carrera(2, colaConRepeticion, true);
                carrera(3, colaOrdenada, true);
                carrera(4, colaInversa, true);
                break;
            case 2:
                // Lógica para la carrera de trazabilidad de objetos
                cout << "Carrera de Trazabilidad de objetos" << std::endl;
                for (auto& dato : informacionCarrera)
                {
                    bool orden = true;
                    carrera(set, dato, !orden);
                    set++;
                    if(set > 4)
                    {
                        break;
                    }
                }
                break;
            case 3:
                // Lógica para la carrera de eventos de cada escenario
                cout << "Carrera de Eventos de cada escenario" << std::endl;
                carrera(1, eventosSinRepeticion, true);
                carrera(2, eventosConRepeticion, true);
                carrera(3, eventosOrdenados, true);
                carrera(4, eventosInversa, true);
                break;
            case 4:
                std::cout << "Saliendo del programa..." << std::endl;
                break;
            default:
                std::cout << "Opción inválida. Por favor, seleccione una opción válida." << std::endl;
                break;
        }
    } while (opcion != 4);
    return 0;
}
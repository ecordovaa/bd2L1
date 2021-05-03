#include "lib.h"
//-- Estructura del ejercicio --
struct Alumno {
    char codigo [5];
    char nombre [11];
    char apellidos [20];
    char carrera [15];
};
const int P1_sizeAlumno = sizeof(Alumno);
inline bool operator == (Alumno a1, Alumno a2){
    int comp = strcmp(a1.codigo, a2.codigo) & strcmp(a1.nombre, a2.nombre) &
               strcmp(a1.apellidos, a2.apellidos) & strcmp(a1.carrera, a2.carrera);
    return comp == 0;
}

//-- Clase a desarrollar --
class P1_FixedRecord{
private:
    string filename {};
public:
    explicit P1_FixedRecord(string filename);
    vector<Alumno> load();
    void add(Alumno record);
    Alumno readRecord(int pos);
    static void test(const string& filename);
};

//-- Métodos --
inline P1_FixedRecord::P1_FixedRecord(string filename) {
    this->filename = filename.append(".txt");
}

inline vector<Alumno> P1_FixedRecord::load() {
    ifstream file(filename, ios::in);
    if(!file.is_open()) exit(1);
    vector<Alumno> dataSet {};
    Alumno alumno {};
    while(file.read((char*) &alumno, P1_sizeAlumno)) {
        dataSet.push_back(alumno);
        file.get();
    }
    file.close();
    return dataSet;
}

inline void P1_FixedRecord::add(Alumno record) {
    fstream file(filename, ios::app);
    if(!file.is_open()) exit(-2);
    file << '\n';
    file.write((char*) &record, P1_sizeAlumno);
    file << flush;
    file.close();
}

inline Alumno P1_FixedRecord::readRecord(int pos) {
    ifstream file(filename);
    if(!file.is_open()) exit(1);
    Alumno alumno {};
    file.seekg(pos * P1_sizeAlumno, ios::beg);
    if(pos > 0) {
        string fixPos {};
        getline(file, fixPos);
    }
    file.read((char *) &alumno, P1_sizeAlumno);
    file.close();
    return alumno;
}

//-- Tester --
inline void P1_FixedRecord::test(const string& filename) {
    printf("------ P1 ------\n");
    string testFilename = filename;
    ofstream testDeInicializacion (testFilename.append(".txt"), ios::app);
    if(!testDeInicializacion.is_open()) {
        printf("ERROR: No se puede abrir el archivo");
        exit(1);
    }
    printf("El archivo ha sido abierto con normalidad");
    auto test = P1_FixedRecord(filename);
    auto data = test.load();
    int errCount {};
    for (int i = 0; i < data.size(); i++) {
        printf("Alumno %d: Codigo(%s) Nombre(%s) Apellidos(%s), Carrera(%s)\n",
               i, data[i].codigo, data[i].nombre, data[i].apellidos, data[i].carrera);
        if (!(data[i] == test.readRecord(i))) {
            errCount++;
            printf("ERROR: Indice %d, hay un problema con readRecord o load\n", i);
        }
    }
    Alumno newAlumno = {"1037", "Alonso", "Gutierrez", "CS"};
    test.add(newAlumno);
    auto newData = test.load();
    if (!(newData[newData.size() - 1] == newAlumno)){
        errCount++;
        printf("ERROR: Hay un problema con el add\n");
    }
    printf("Test1 terminado con %d errores \n", errCount);
}
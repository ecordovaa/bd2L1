#include <iostream>
#include "lib.h"
struct Alumno3 {
    string nombre;
    string apellidos;
    string carrera;
    float mensualidad;
};
const int P3_sizeAlumno = sizeof(Alumno3);
inline bool operator == (const Alumno3& a1, const Alumno3& a2){
    int comp = a1.nombre == a2.nombre & a1.apellidos == a2.apellidos &
               a1.carrera == a2.carrera & (float) a1.mensualidad == (float) a2.mensualidad;
    return comp == 0;
}

class P3_VariableRecord{
private:
    string filename {};
public:
    explicit P3_VariableRecord(string filename);
    vector<Alumno3> load();
    void add(const Alumno3& record);
    Alumno3 readRecord(int pos);
    static void test(const string& filename);
};

inline P3_VariableRecord::P3_VariableRecord(string filename) {
    this->filename = filename.append(".txt");
}

inline vector<Alumno3> P3_VariableRecord::load() {
    ifstream file(filename, ios::out | ios::in);
    vector<Alumno3> dataSet {};
    while (!file.eof()) {
        Alumno3 alumno {};
        getline(file, alumno.nombre, '|');
        getline(file, alumno.apellidos, '|');
        getline(file, alumno.carrera, '|');
        string mensualidad {};
        getline(file, mensualidad, '\n');
        alumno.mensualidad = stof(mensualidad);
        dataSet.push_back(alumno);
    }
    file.close();
    return dataSet;
}

inline void P3_VariableRecord::add(const Alumno3& record) {
    fstream file(filename, ios::out);
    file.seekg(0, ios::end);
    file.write(record.nombre.data(), record.nombre.size());
    file << '|';
    file.write(record.apellidos.data(), record.apellidos.size());
    file << '|';
    file.write(record.carrera.data(), record.carrera.size());
    file << '|';
    string mensualidad = to_string(record.mensualidad);
    file.write(mensualidad.data(), mensualidad.size());
    file << '\n';
    file.close();
}

inline Alumno3 P3_VariableRecord::readRecord(int pos) {
    ifstream file(filename, ios::out | ios::in | ios::binary);
    while(--pos > 0){
        char* iter {};
        if(!file.eof()) file.getline(iter, '\n');
    }
    Alumno3 alumno {};
    getline(file, alumno.nombre, '|');
    getline(file, alumno.apellidos, '|');
    getline(file, alumno.carrera, '|');
    string mensualidad {};
    getline(file, mensualidad, '\n');
    alumno.mensualidad = stof(mensualidad);
    file.close();
    return alumno;
}

inline void P3_VariableRecord::test(const string &filename) {
    printf("------ P3 ------\n");
    string testFilename = filename;
    ofstream testDeInicializacion (testFilename.append(".txt"), ios::app);
    if(!testDeInicializacion.is_open()) {
        printf("ERROR: No se puede abrir el archivo.\n");
        exit(1);
    }
    printf("El archivo ha sido abierto con normalidad.\n");
    auto test = P3_VariableRecord(filename);
    auto data = test.load();
    int errCount {};
    for (int i = 0; i < data.size(); i++) {
        printf("Alumno %d: Nombre(%s) Apellidos(%s), Carrera(%s), Mensualidad(%f)\n",
               i, data[i].nombre.data(), data[i].apellidos.data(), data[i].carrera.data(),
               data[i].mensualidad);
        auto valorReal = test.readRecord(i);
        if (!(data[i] == valorReal)) {
            errCount++;
            printf("ERROR: Indice %d, hay un problema con readRecord o load\n", i);
        }
    }
    Alumno3 newAlumno = {"Alonso", "Gutierrez", "CS", 2000};
    test.add(newAlumno);
    auto newData = test.load();
    if (!(newData[newData.size() - 1] == newAlumno)){
        errCount++;
        printf("ERROR: Hay un problema con el add\n");
    }
    printf("Test1 terminado con %d errores \n", errCount);
}

//-- Métodos --



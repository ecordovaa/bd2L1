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
               a1.carrera == a2.carrera & a1.mensualidad == a2.mensualidad;
    return comp == 0;
}

class P3_FixedRecord{
private:
    string filename {};
public:
    explicit P3_FixedRecord(string filename);
    vector<Alumno3> load();
    void add(Alumno3 record);
    Alumno3 readRecord(int pos);
    static void test(const string& filename);
};

inline P3_FixedRecord::P3_FixedRecord(string filename) {
    this->filename = filename.append(".txt");
}

inline vector<Alumno3> P3_FixedRecord::load() {
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
    return dataSet;
}

inline void P3_FixedRecord::add(Alumno3 record) {
}

inline Alumno3 P3_FixedRecord::readRecord(int pos) {
    return Alumno3();
}

inline void P3_FixedRecord::test(const string &filename) {

}

//-- Métodos --



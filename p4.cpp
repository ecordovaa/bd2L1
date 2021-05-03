#include "lib.h"

struct Matricula {
    string codigo;
    int ciclo;
    float mensualidad;
    string observaciones;
};

struct metada
{
  int pos;
  int size;
}

inline bool operator == (const Alumno3& a1, const Alumno3& a2){
    int comp = a1.codigo == a2.codigo & a1.ciclo == a2.ciclo &
               a1.mensualidad == a2.mensualidad & a1.observaciones == a2.observaciones;
    return comp == 0;
}

ostream &operator<<(ostream &os, Matricula const &k) {
    return os <<k.codigo<<" "<<k.ciclo<<" "<<k.mensualidad<<" "<<k.observaciones<<endl;
}

class P4_FixedRecord{
private:
    string filename {};
public:
    explicit P4_FixedRecord(string filename);
    vector<Alumno> load();
    void add(Alumno3 record);
    Alumno3 readRecord(int pos);
    static void test(const string& filename);
};

inline P4_FixedRecord::P4_FixedRecord(string filename) {
    this->filename = filename.append(".txt");
}

inline vector<Alumno3> P4_FixedRecord::load() {
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

inline void P4_FixedRecord::add(Alumno3 record) {
}

inline Alumno3 P4_FixedRecord::readRecord(int pos) {
    return Alumno3();
}

inline void P4_FixedRecord::test(const string &filename) {

}

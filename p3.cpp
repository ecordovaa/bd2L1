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
    void add(const Alumno3& record);
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
    file.close();
    return dataSet;
}

inline void P3_FixedRecord::add(const Alumno3& record) {
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

inline Alumno3 P3_FixedRecord::readRecord(int pos) {
    ifstream file(filename, ios::out | ios::in | ios::binary);
    while(--pos >= 0){
        char* iter {};
        file.getline(iter, '\n');
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

inline void P3_FixedRecord::test(const string &filename) {
  printf("------ P3 ------\n");
  string testFilename = filename;
  ofstream testDeInicializacion (testFilename.append(".dat"), ios::app);
  if(!testDeInicializacion.is_open()) {
      printf("ERROR: No se puede abrir el archivo");
      exit(1);
  }
  printf("El archivo ha sido abierto con normalidad.\n");
  auto test = P3_FixedRecord(filename);
}

//-- Métodos --

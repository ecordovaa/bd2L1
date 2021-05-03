#include "lib.h"
struct Alumno2 {
    char codigo [5];
    char nombre [11];
    char apellidos [20];
    char carrera [15];
    int ciclo;
    float mensualidad;
    int nextDel;
};
const int P2_sizeAlumno = sizeof(Alumno2);
inline bool operator == (Alumno2 a1, Alumno2 a2){
    int comp = strcmp(a1.codigo, a2.codigo) & strcmp(a1.nombre, a2.nombre) &
               strcmp(a1.apellidos, a2.apellidos) & strcmp(a1.carrera, a2.carrera) &
               a1.ciclo == a2.ciclo & a1.mensualidad == a2.mensualidad;
    return comp == 0;
}

class P2_FixedRecord{
private:
    string filename {};
    int header = -1;
public:
    explicit P2_FixedRecord(string filename);
    vector<Alumno2> load();
    void add(Alumno2 record);
    Alumno2 readRecord(int pos);
    bool deleteRecord(int pos);
    static void test(const string& filename);
    void reset();
};

inline P2_FixedRecord::P2_FixedRecord(string filename): filename(filename.append(".dat")) {
    fstream file(filename, ios::binary | ios::out);
    if(!file.is_open()) exit(-2);
}

inline vector<Alumno2> P2_FixedRecord::load() {
    ifstream file(filename, ios::in | ios::binary);
    vector<Alumno2> dataSet {};
    Alumno2 alumno {};
    while(file.read((char*) &alumno, P2_sizeAlumno)) dataSet.push_back(alumno);
    file.close();
    return dataSet;
}

inline void P2_FixedRecord::add(Alumno2 record) {
    fstream file(filename, ios::out | ios::in | ios::binary);
    if(header == -1) {
        file.seekp(0, ios::end);
        file.write((char*) &record, P2_sizeAlumno);
    } else {
        int delIndex {};
        int offset = offsetof(Alumno2, nextDel);
        file.seekp(header * P2_sizeAlumno + offset);
        file.read((char *) &delIndex, sizeof(int));
        file.seekp(header * P2_sizeAlumno);
        file.write((char *) &record, P2_sizeAlumno);
        header = delIndex;
    }
    file.close();
}

inline Alumno2 P2_FixedRecord::readRecord(int pos) {
    pos--;
    fstream file(filename, ios::out | ios::in | ios::binary);
    Alumno2 alumno {};
    file.seekg(pos * P2_sizeAlumno, ios::beg);
    file.read((char *) &alumno, P2_sizeAlumno);
    if(file.eof()) exit(-2);
    file.close();
    return alumno;
}

inline bool P2_FixedRecord::deleteRecord(int pos) {
    pos--;
    fstream file(filename, ios::in | ios::out | ios::binary);
    int offset = offsetof(Alumno2, nextDel);
    int delIndex {};
    file.seekg(pos * P2_sizeAlumno + offset);
    file.read((char *) (&delIndex), sizeof(int));
    if(delIndex != 0) return false;
    file.seekg(pos * P2_sizeAlumno + offset);
    file.write((char*) &header, sizeof(int));
    file.close();
    header = pos + 1;
    return true;
}

inline void P2_FixedRecord::test(const string &filename) {
    printf("------ P2 ------\n");
    string testFilename = filename;
    ofstream testDeInicializacion (testFilename.append(".dat"), ios::app);
    if(!testDeInicializacion.is_open()) {
        printf("ERROR: No se puede abrir el archivo");
        exit(1);
    }
    printf("El archivo ha sido abierto con normalidad.\n");
    auto test = P2_FixedRecord(filename);
    test.reset();
    auto data = test.load();
    int errCount {};
    printf("Registros actuales: \n");
    for (int i = 0; i < data.size(); i++) {
        if(data[i].nextDel == 0) {
            printf("Alumno2 %d: Codigo(%s) Nombre(%s) Apellidos(%s), Carrera(%s), Ciclo(%d), Mensualidad(%f)\n",
                   i, data[i].codigo, data[i].nombre, data[i].apellidos, data[i].carrera,
                   data[i].ciclo, data[i].mensualidad);
            if (!(data[i] == test.readRecord(i))) {
                errCount++;
                printf("ERROR: Indice %d, hay un problema con readRecord o load\n", i);
            }
        }
    }
    for(int i = 0; i < 2; i++){
        printf("Eliminando record %d...\n", i+1);
        test.deleteRecord(i+1);
        //deberia eliminar el primer y segundo record
    }
    printf("Registros eliminados:\n");
    int eliminados = test.header - 1;
    fstream file(filename, ios::binary);
    for(const Alumno2& alumno: data){
        int delIndex {};
        if(alumno.nextDel != 0) {
            printf("- Alumno Eliminado: Codigo(%s) Nombre(%s) Apellidos(%s), Carrera(%s), Ciclo(%d), Mensualidad(%f)\n",
                   alumno.codigo, alumno.nombre, alumno.apellidos, alumno.carrera,
                   alumno.ciclo, alumno.mensualidad);
        }
    }
    Alumno2 newAlumno = {"1037", "Alonso", "Gutierrez", "CS", 2, 1800, 0};
    printf("Cambiando uno de los registros eliminados por un nuevo alumno...\n");
    test.add(newAlumno);
    auto alumno = test.readRecord(3);
    if(!(alumno == newAlumno)){
        errCount++;
        printf("ERROR: Hay un problema con el add");
    }
    printf("Act. Alumno2 1: Codigo(%s) Nombre(%s) Apellidos(%s), Carrera(%s), Ciclo(%d), Mensualidad(%f)\n",
           alumno.codigo, alumno.nombre, alumno.apellidos, alumno.carrera,
           alumno.ciclo, alumno.mensualidad);
    printf("Test terminado con %d errores", errCount);
}

inline void P2_FixedRecord::reset() {
    ofstream reset(filename);
    Alumno2 alumnos[7]{
            {"0001", "Howard",  "Paredes Zegarra", "Computacion", 7, 1500, 0},
            {"0002", "Penny",   "Vargas Cordero",  "Industrial", 3, 1200, 0},
            {"0003", "Sheldon", "Cooper Vega",     "Mecatronica", 4, 2200, 0},
            {"0004", "Pamela",  "Vargas Cordero",  "Industrial", 1, 2200, 0},
            {"0005", "Vanesa",  "Cooper Quizpe",   "Mecatronica", 1, 1750, 0},
            {"0006", "Jesus",   "Vega Cordero",    "Industrial", 9, 2000, 0},
            {"0007", "Heider",  "Sanchez Quizpe",  "Mecatronica", 5, 2200, 0}
    };
    for (const auto &alumno : alumnos) this->add(alumno);
}

#ifndef RealTimeStore_h
#define RealTimeStore_h

#include "HardwareSerial.h"
#include "FirebaseESP32.h"


class RealTimeStore
{

  private: // Variables y funciones de la clase de ámbito privado
    FirebaseData firebaseData;
    String myPathFB;

  public:            // Variables y funciones de la clase de ámbito público
    RealTimeStore(); // Constructor por defecto
    RealTimeStore(String pathFB);
    ~RealTimeStore(); // Destructor

    void connect(const String host, const String auth);
    bool existNode(); // Existe el nodo {1: SI; <1: NO}
    bool deleteNode();
    bool sendIntValue(const String tag, int value);
};

#endif
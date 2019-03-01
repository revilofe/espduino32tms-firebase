
#ifndef RealTimeStore_h
#define RealTimeStore_h

#include "HardwareSerial.h"
#include "FirebaseESP32.h"
#include <utility>
#include <map>

typedef void (*SetParamCallback)(long);

class RealTimeStore
{

  private: // Variables y funciones de la clase de ámbito privado
    FirebaseData firebaseData_out;
    FirebaseData firebaseData_in;
    String myPathFB_in;
    String myPathFB_out;
    //Si hay mas parametros
    //typedef std::pair<String, SetParamCallback> Callback;
    //std::map <String, SetParamCallback> m;


  public:            // Variables y funciones de la clase de ámbito público
    SetParamCallback aa=nullptr;
    RealTimeStore(); // Constructor por defecto
    RealTimeStore(String pathFB_out, String pathFB_in);
    ~RealTimeStore(); // Destructor

    void connect(const String host, const String auth);
    bool existNode(); // Existe el nodo {1: SI; <1: NO}
    bool deleteNode();
    bool sendIntValue(const String tag, int value);
    bool setCallback(const String tagParam, StreamEventCallback dataAvailablecallback,\
         StreamTimeoutCallback timeoutCallback);

};

#endif
#include "RealTimeStore.h"

// Constructor sobrecargado
RealTimeStore::RealTimeStore()
{
}

// Constructor sobrecargado
RealTimeStore::RealTimeStore(String pathFB_out, String pathFB_in)
{
    myPathFB_out = pathFB_out;
    myPathFB_in = pathFB_in;
}

// Destructor
RealTimeStore::~RealTimeStore()
{
    //delete ;
}

// Destructor
void RealTimeStore::connect(const String host, const String auth)
{
    Serial.println("Conectando a Firebase...");
    Firebase.begin(host, auth);
    Firebase.reconnectWiFi(true);
}

// Pregunta por si existe el nodo de salida (Donde se escriben los datos leidos)
bool RealTimeStore::existNode()
{
    bool exist;
    Serial.println("-----------------------------------");
    Serial.println("----------Path Exist Test----------");
    Serial.println("-----------------------------------");

    Serial.println();

    exist = Firebase.pathExist(firebaseData_out, myPathFB_out);
    if (exist)
        Serial.println(String("") + "Path " + myPathFB_out + " exists");
    else
        Serial.println(String("") + "Path " + myPathFB_out + " is not exist");
    Serial.println();

    return exist;
}

// Borra nodo de salida (Donde se escriben los datos leidos)
bool RealTimeStore::deleteNode()
{
    //Si fuera necesario borrar el nodo.
    bool deletedOK;

    Serial.println("-----------------------------------------");
    Serial.println("----------Delete Path Node Test----------");
    Serial.println("-----------------------------------------");

    Serial.println();

    deletedOK = Firebase.deleteNode(firebaseData_out, myPathFB_out);
    if (deletedOK)
        Serial.println(String("") + "Path " + myPathFB_out + " deleted!");
    else
        Serial.println(String("") + "Path " + myPathFB_out + " - Error, no deleted!");
    Serial.println();

    return deletedOK;
}

// Envia los datos leidos
bool RealTimeStore::sendIntValue(const String tag, int value)
{
    Serial.println("--------------------------------------------------");
    Serial.println("----------Begin Set (SendIntValue) Test-----------");
    Serial.println("--------------------------------------------------");
    Serial.println();

    bool sendOK = Firebase.setInt(firebaseData_out, String("") + myPathFB_out + "/" + tag, value);
    if (sendOK)
    {
        Serial.println("----------Set result-----------");
        Serial.println("PATH: " + firebaseData_out.dataPath());
        Serial.print("PUSH NAME: ");
        Serial.println("TYPE: " + firebaseData_out.dataType());
        Serial.print("VALUE: ");
        if (firebaseData_out.dataType() == "int")
            Serial.println(firebaseData_out.intData());
        else if (firebaseData_out.dataType() == "float")
            Serial.println(firebaseData_out.floatData());
        else if (firebaseData_out.dataType() == "string")
            Serial.println(firebaseData_out.stringData());
        else if (firebaseData_out.dataType() == "json")
            Serial.println(firebaseData_out.jsonData());
        Serial.println("--------------------------------");
        Serial.println();
    }
    else
    {
        Serial.println("----------Can't Set data--------");
        Serial.println("REASON: " + firebaseData_out.errorReason());
        Serial.println("--------------------------------");
        Serial.println();
    }
    return sendOK;
}

// Envia los datos leidos
bool RealTimeStore::setCallback(const String tagParam, StreamEventCallback dataAvailablecallback, StreamTimeoutCallback timeoutCallback)
{
    Serial.println("**************************************");
    Serial.println("----------Set CallBack Test-----------");
    Serial.println("**************************************");
    Serial.println();

    bool setCallbackOK = Firebase.beginStream(firebaseData_in, String("") + myPathFB_in + "/" + tagParam);
    if (!setCallbackOK)
    {
        Serial.println("------Can't begin stream 1 connection------");
        Serial.println("REASON: " + firebaseData_in.errorReason());
        Serial.println();
    }
    Firebase.setStreamCallback(firebaseData_in, dataAvailablecallback, timeoutCallback);
}

#include "RealTimeStore.h"

// Constructor sobrecargado
RealTimeStore::RealTimeStore()
{
    
}

// Constructor sobrecargado
RealTimeStore::RealTimeStore(String pathFB)
{
    myPathFB = pathFB;
}

// Destructor
RealTimeStore::~RealTimeStore()
{
    //delete rad;
}

// Destructor
void RealTimeStore::connect(const String host, const String auth)
{
    Serial.println("Conectando a Firebase...");
    Firebase.begin(host, auth);
    Firebase.reconnectWiFi(true);
}

// Establecer el radio del círculo
bool RealTimeStore::existNode()
{
    bool exist;
    Serial.println("-----------------------------------");
    Serial.println("----------Path Exist Test----------");
    Serial.println("-----------------------------------");

    Serial.println();

    exist = Firebase.pathExist(firebaseData, myPathFB);
    if (exist)
        Serial.println(String("") + "Path " + myPathFB + " exists");
    else
        Serial.println(String("") + "Path " + myPathFB + " is not exist");
    Serial.println();

    return exist;
}

// Establecer el diámetro del círculo
bool RealTimeStore::deleteNode()
{
    //Si fuera necesario borrar el nodo.
    bool deletedOK;

    Serial.println("-----------------------------------------");
    Serial.println("----------Delete Path Node Test----------");
    Serial.println("-----------------------------------------");

    Serial.println();

    deletedOK = Firebase.deleteNode(firebaseData, myPathFB);
    if (deletedOK)
        Serial.println(String("") + "Path " + myPathFB + " deleted!");
    else
        Serial.println(String("") + "Path " + myPathFB + " - Error, no deleted!");
    Serial.println();

    return deletedOK;
}

// Cálculo del área del círculo
bool RealTimeStore::sendIntValue(const String tag, int value)
{
    Serial.println("--------------------------------------------------");
    Serial.println("----------Begin Set (SendIntValue) Test-----------");
    Serial.println("--------------------------------------------------");
    Serial.println();

    bool sendOK = Firebase.setInt(firebaseData, String("") + myPathFB + "/" + tag, value);
    if (sendOK)
    {
        Serial.println("----------Set result-----------");
        Serial.println("PATH: " + firebaseData.dataPath());
        Serial.print("PUSH NAME: ");
        Serial.println("TYPE: " + firebaseData.dataType());
        Serial.print("VALUE: ");
        if (firebaseData.dataType() == "int")
            Serial.println(firebaseData.intData());
        else if (firebaseData.dataType() == "float")
            Serial.println(firebaseData.floatData());
        else if (firebaseData.dataType() == "string")
            Serial.println(firebaseData.stringData());
        else if (firebaseData.dataType() == "json")
            Serial.println(firebaseData.jsonData());
        Serial.println("--------------------------------");
        Serial.println();
    }
    else
    {
        Serial.println("----------Can't Set data--------");
        Serial.println("REASON: " + firebaseData.errorReason());
        Serial.println("--------------------------------");
        Serial.println();
    }
    return sendOK;
}

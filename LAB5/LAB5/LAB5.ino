//Katherine Caceros
//LABORATORIO 5
// 18307

#include <SPI.h>
#include <SD.h>


int num; //variable del archivo .txt
int fin; // variable para terminar programa
void printDirectory(void);

File myFile; // leer SD


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while(!Serial){
  ;     //Esperamos a que se conecte el puerto
}
  SPI.setModule(0);   //Configuracion para la inicializacion del SPI
  Serial.println();
  Serial.println("Inicializando la memoria SD...");
  Serial.println();
 
    if (!SD.begin(4)){ //repite 
      Serial.println("Inicializacion fallida...!"); //inicializacion fallida de la SD
    return;
}
  Serial.println("Inicializacion correcta "); //muestra el menu al ususario
  Serial.println(); //muestra el menu
  Serial.println("****** ARCHIVOS EN LA SD ******");
  Serial.println();
  myFile = SD.open("/");                      //Abre el archivo en sd
  printDirectory(myFile, 0);                 //Muestra el archivo dentro de la SD
  Serial.println("");
  Serial.println("***********************************************");
  Serial.println("        Escoja el archivo que desea ver        ");
  Serial.println("***********************************************");
}

void loop() {
  // put your main code here, to run repeatedly: 
  while (fin !=4){   //mientras el usuario no seleccione 4 sigue el programa
if (Serial.available()>0){
  num = Serial.read();
   }
  if (num == '1'){                   //primer archivo
    myFile = SD.open("Pacman.txt");    //debe de ir el nombre del archivo 
    if (myFile){
      Serial.println();
      Serial.println("*******************************************");
      Serial.println("                  Pacman                   ");
      Serial.println("*******************************************");
      
      while (myFile.available()){
        Serial.write(myFile.read());
      }
      myFile.close();
    }
    else{
      Serial.println("Error al abrir el .txt");
    }
      Serial.println();
      Serial.println("*********************************************************************");
      Serial.println("         Escoja nuevamente o seleccione 4 para terminar              ");
      Serial.println("*********************************************************************");
  }
  
if (num == '2'){
  myFile = SD.open("Fantasma.txt");//segundo archivo
  if(myFile){
      Serial.println();
      Serial.println("*******************************************");
      Serial.println("                Fantasma                   ");
      Serial.println("*******************************************");
      
      while (myFile.available()){
        Serial.write(myFile.read());
    }
    myFile.close();
  }
  else{
    Serial.println("Error al abrir el .txt");
  }
      Serial.println();
      Serial.println("*********************************************************************");
      Serial.println("         Escoja nuevamente o seleccione 4 para terminar              ");
      Serial.println("*********************************************************************");
}

if(num == '3'){
  myFile = SD.open("Cerezas.txt");//tercer archivo
  if(myFile){
      Serial.println();
      Serial.println("*******************************************");
      Serial.println("                  Cerezas                  ");
      Serial.println("*******************************************");
      
    while (myFile.available()){
      Serial.write(myFile.read());
    }
    myFile.close();
  } else{
    Serial.println("Error al abrir el .txt");
  }
      Serial.println("*********************************************************************");
      Serial.println("         Escoja nuevamente o seleccione 4 para terminar              ");
      Serial.println("*********************************************************************");   
  } 
else if (num =='4'){ //funcion para termina el programa
  Serial.println("");
  Serial.println(" Fin del Programa ");
  fin=4;
}
else{}      
}
}
/*La funcion del vector de interrupciones y las subrutinas
  para el directorio de la SD */
void printDirectory(File dir, int numTabs){//funcion para mostrar el directorio
  while(true){ //entra al directorio 
    File entry = dir.openNextFile();
    if(!entry){                       //no más archivos
      break;
    }
    for (uint8_t i=0; i<numTabs; i++){ //
      Serial.print('\t');
    }
    Serial.print(entry.name());
    if (entry.isDirectory()){
      Serial.println("/");
      printDirectory(entry, numTabs+1);
    }
    else{
      //mostrara el tamaño de los archivos 
      Serial.print("\t\t");
      Serial.println(entry.size(), DEC);
    }
    entry.close();
  }
}

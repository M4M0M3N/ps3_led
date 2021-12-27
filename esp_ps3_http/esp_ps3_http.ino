#include <ESP8266WiFi.h>
#include <FastLED.h>
#include <ESP8266HTTPClient.h>

#define LED_TYPE WS2812B  //tipo di led usati
#define COLOR_ORDER GRB   //ordine di colori [verde,rosso,blu]
/*Se si riscontrano colori sbagliati, provare ad accende uno dei tre colori {rosso, verde, blu}
 * e cambiare l'ordine*/
#define NUM_LEDS 6       //Per questo progetto ho usato 6 led, 2 per ogni lettera

//ATTENZIONE
#define DATA_PIN 2       //Collegati i led al pin digitale 4, nell'ide e il gpio 2
//ATTENZIONE

#define da 0
#define fino 5
//#define slow 500

//creato oggetto led
CRGB leds[NUM_LEDS];

/*Ho come scrtitta ps3, quindi le variabili si chiamano
  p_len/s_len/3_len
  led_p/led_s/led_3*/

int led_p[]={0,1};   //led assegnati alla lettera p
#define p_len 1

int led_s[]={2,3};   //led assegnati alla lettera s
#define s_len 3

int led_tre[]={4.5};   //led assegnati alla lettera 3
#define tre_len 5


//3 array per ogni lettera
//ogni array memorizza il colore [r,g,b]
int lettera_p[]={0,0,0};
int lettera_s[]={0,0,0};
int lettera_tre[]={0,0,0};

int modalita_led=1;   //0 man, 1 auto, 2 pulse
//cambiare 0/1/2 per cambiare la modalità con cui settarsi automaticamente
//sconsigliata la modalità man {0}


int colore = 0, R=0, G=0, B=0;

const char* ssid1 = "wifi ssid";
const char* password1 = "pass";

//se il wifi non viene trovato si prova a connettere ad un secondo wifi
const char* ssid2 = "wifi ssid 2";
const char* password2 = "pass 2";


WiFiServer server(80);

void setup() {

  //inizializzo i led
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);

  //nel codice non ho eliminato i serial.print per un futuro debug
  //Serial.begin(115200);
  
  //Serial.println();
  //Serial.print("Wifi connecting");

  //provo a connettermi al wifi
  WiFi.begin(ssid1,password1);

  //Serial.println();
  //Serial.print("Connecting");

  int led=da;
  int fine=0;
  
  //Se non sono connesso, faccio la sequenza di connessione.
  //Quando cambio il wifi, cambio colore dei led {vedere video}
  
  while( WiFi.status() != WL_CONNECTED ){
    
    for (int i=0; i<=255; i++){
      
      if (fine<3){
        //Serial.println("viola");
        leds[led] = CRGB(i,0,i);
      }
      else{
        //Serial.println("fine = 2");
        leds[led] = CRGB(i,i,0);
      }
        
      delay(0);
      FastLED.show();
      delay(0);
    }
    if ( (led==fino) and (fine==3) ){
      WiFi.disconnect();
      delay(1000);
      //Serial.print("\nCambio wifi");
      WiFi.begin(ssid2,password2);
    }

    
    if (led != fino)
      led++;
    else{
      led=da;
      fine++;

      int a=random(0, 255);
      int b=random(0, 255);
      int c=random(0, 255);
      
      for (int led=da; led<=fino; led++){
        leds[led] = CRGB(a,b,c);
        delay(0);
      }
      FastLED.show();
      delay(0);
    
    }
      
    //Serial.print(".");

  }
  
  //Serial.println();

  //Serial.println("Wifi Connected Success!");
  //Serial.print("NodeMCU IP Address : ");
  //Serial.println(WiFi.localIP() );

  server.begin();
  //Serial.println("NodeMCU Server started");
    
  // Print the IP address
  //Serial.print("Use this URL to connect: ");
  //Serial.print("http://");
  //Serial.print(WiFi.localIP());
  //Serial.println("/");  

  //Sequenza per notificare l'avvenuta connessione
  Connesso();
   
}

void loop() {
  /*
  Serial.print(R);
  Serial.print("   ");
  Serial.print(G);
  Serial.print("   ");
  Serial.println(B);//*/
  
  if ( modalita_led == 1 ){ //modalità auto
     delay(10);
     switch (colore) {
      case 0:
        if (R!=255){
          int col[] = {R,G,B};
          Aggiorna_led( col, col, col);
          R++;
          }
        else{
          R=255;
          colore++;
        }
        break;
      
      case 1:
        if (B!=0){
          int col[] = {R,G,B};
          Aggiorna_led( col, col, col);
          B--;
          }
        else{
          B=0;
          colore++;
        }
        break;
        
      case 2:
        if (G!=255){
          int col[] = {R,G,B};
          Aggiorna_led( col, col, col);
          G++;
          }
        else{
          G=255;
          colore++;
        }
        break;
      
      case 3:
        if (R!=0){
          int col[] = {R,G,B};
          Aggiorna_led( col, col, col);
          R--;
          }
        else{
          R=0;
          colore++;
        }
        break;
        
      case 4:
        if (B!=255){
          int col[] = {R,G,B};
          Aggiorna_led( col, col, col);
          B++;
          }
        else{
          B=255;
          colore++;
        }
        break;
      
      case 5:
        if (G!=0){
          int col[] = {R,G,B};
          Aggiorna_led( col, col, col);
          G--;
          }
        else{
          G=0;
          colore=0;
        }
        break;
      }
  }

  if ( modalita_led == 2 ){ //modalità pulse
    delay(10);
    //Serial.println(colore);
    switch (colore) {
      case 0:
        if (R!=255){
          int col[] = {R,G,B};
          Aggiorna_led( col, col, col);
          R++;
          }
        else{
          R=255;
          colore++;
        }
        break;
      
      case 1:
        if (R!=0){
          int col[] = {R,G,B};
          Aggiorna_led( col, col, col);
          R--;
          }
        else{
          R=0;
          colore++;
        }
        break;
        
      case 2:
        if (G!=255){
          int col[] = {R,G,B};
          Aggiorna_led( col, col, col);
          G++;
          }
        else{
          G=255;
          colore++;
        }
        break;
      
      case 3:
        if (G!=0){
          int col[] = {R,G,B};
          Aggiorna_led( col, col, col);
          G--;
          }
        else{
          G=0;
          colore++;
        }
        break;
        
      case 4:
        if (B!=255){
          int col[] = {R,G,B};
          Aggiorna_led( col, col, col);
          B++;
          }
        else{
          B=255;
          colore++;
        }
        break;
      
      case 5:
        if (B!=0){
          int col[] = {R,G,B};
          Aggiorna_led( col, col, col);
          B--;
          }
        else{
          B=0;
          colore++;
        }
        break;

      case 6:
        if (R!=255){
          int col[] = {R,G,B};
          Aggiorna_led( col, col, col);
          R++;
          B++;
          }
        else{
          R=255;
          B=255;
          colore++;
        }
        break;
      
      case 7:
        if (R!=0){
          int col[] = {R,G,B};
          Aggiorna_led( col, col, col);
          R--;
          B--;          
          }
        else{
          R=0;
          B=0;
          colore++;
        }
        break;

      case 8:
        if (R<=255){
          int col[] = {R,G,B};
          Aggiorna_led( col, col, col);
          R++;
          G++;
          }
        else{
          R=255;
          G=255;
          colore++;
        }
        break;
      
      case 9:
        if (R!=0){
          int col[] = {R,G,B};
          Aggiorna_led( col, col, col);
          R--;
          G--;          
          }
        else{
          R=0;
          G=0;
          colore++;
        }
        break;

      case 10:
        if (B!=255){
          int col[] = {R,G,B};
          Aggiorna_led( col, col, col);
          B++;
          G++;
          }
        else{
          B=255;
          G=255;
          colore++;
        }
        break;
      
      case 11:
        if (B!=0){
          int col[] = {R,G,B};
          Aggiorna_led( col, col, col);
          B--;
          G--;          
          }
        else{
          B=0;
          G=0;
          colore = 0;
        }
        break;
        
      }
  }

    //Se rilevo una connessione, mando la pagina html
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  client.println("HTTP/1.1 200 OK");
  // Wait until the client sends some data
  //Serial.println("Hello New client");
  while(!client.available()){
    delay(1);
  }
  
   // Read the first line of the request
  String request = client.readStringUntil('\r');
  //Serial.println(request);
  //Serial.println(client);
  if (request == "GET HTTP/1.1")
    client.flush();
   
   // Match the request
  String tmp = request.substring(5,12);
  
  /*if (request.substring(0,3) == "POST")
    tmp = request.substring(5,12);
   else
    tmp = request.substring(4,11);*/
  //Serial.println(request);
  //da rispondere all'host, come?

  //Quando viene premuto qualcosa sulla pagina, viene fatta una richiesta http al'esp
  //qui la elaboro
  if (tmp == "/reddd=")   {  //devo aggiornare il valore rosso
    char lettera=request[12];
    int val=request.substring(14, request.indexOf("HTTP")-1).toInt();
  
    switch (lettera) { //individuo quale lettera cambiare
      case 'p':
        //Serial.print("case p -->");
        lettera_p[0]=val;  
        //Serial.println(lettera_p[0]);    
        break;
      case 's':
        //Serial.print("case s -->");
        lettera_s[0]=val;
        //Serial.println(lettera_s[0]);
        break;
      case '3':
        //Serial.print("case 3 -->");
        lettera_tre[0]=val;
        //Serial.println(lettera_tre[0]);
        break;
      }
    //funzione per aggiornare il colore della lettera
    Aggiorna_led(lettera_p,lettera_s, lettera_tre);
    return;
  }

  if (tmp == "/green=")  {    //devo aggiornare il valore verde
    char lettera=request[12];
    int val=request.substring(14, request.indexOf("HTTP")-1).toInt();
  
    switch (lettera) {    //individuo quale lettera cambiare
      case 'p':
        //Serial.print("case p -->");
        lettera_p[1]=val;
        //Serial.println(lettera_p[1]);
        break;
      case 's':
        //Serial.print("case s -->");
        lettera_s[1]=val;
        //Serial.println(lettera_s[1]);
        break;
      case '3':
        //Serial.print("case 3 -->");
        lettera_tre[1]=val;
        //Serial.println(lettera_tre[1]);
        break;
      }
    Aggiorna_led(lettera_p,lettera_s, lettera_tre);
    return;
  }

  if (tmp == "/bluee=")  {      //devo aggiornare il valore verde
    char lettera=request[12];
    int val=request.substring(14, request.indexOf("HTTP")-1).toInt();
  
    switch (lettera) {   //individuo quale lettera cambiare
      case 'p':
        //Serial.print("case p -->");
        lettera_p[2]=val;
        //Serial.println(lettera_p[2]);
        break;
      case 's':
        //Serial.print("case s -->");
        lettera_s[2]=val;
        //Serial.println(lettera_s[2]);
        break;
      case '3':
        //Serial.print("case 3 -->");
        lettera_tre[2]=val;
        //Serial.println(lettera_tre[2]);
        break;
      }
    Aggiorna_led(lettera_p,lettera_s, lettera_tre);
    return;
  }
    
  if (tmp == "/autoo=")  {    //Cambio madalità in auto 
    int val=request[12];

    switch (val) {
      //man
      case '0':
        Aggiorna_led(lettera_p,lettera_s, lettera_tre);
        modalita_led=0; 
        break;

      //auto
      case '1':
        modalita_led=1;
        
        for (int led=da; led<=fino; led++){
          leds[led] = CRGB(0,0,0);
          delay(0);
        }
        FastLED.show();
        delay(0);
        
        colore=0;
        R=0;
        G=0;
        B=0;
        break;

      //pulse
      case '2':
        modalita_led=2;
        
        for (int led=da; led<=fino; led++){
          leds[led] = CRGB(0,0,0);
          delay(0);
        }
        FastLED.show();
        delay(0);
        
        colore=0;
        R=0;
        G=0;
        B=0;
        break;
      }
    return;
  }

 
    //questa e' la pagina html
    //modificare con parsimonia...
    
    client.println("Content-Type: text/html");
    client.println(""); //  do not forget this one
    client.println("<!DOCTYPE html>");
    client.println("<html><head>");
    
    client.println("<style>");
    client.println("body {background-color: black;color:white;}");
    
    client.println(".red_slider { -webkit-appearance: none; width: 90%; height: 30px; border-radius: 30px; background: #d3d3d3; outline: none; }");
    client.println(".red_slider::-webkit-slider-thumb { -webkit-appearance: none; appearance: none; width: 40px; height: 40px; border-radius: 50%; background: rgb(255,0,0); cursor: pointer; }");
    client.println(".green_slider { -webkit-appearance: none; width: 90%; height: 30px; border-radius: 30px; background: #d3d3d3; outline: none; }");
    client.println(".green_slider::-webkit-slider-thumb { -webkit-appearance: none; appearance: none; width: 40px; height: 40px; border-radius: 50%;  background: rgb(0,255,0); cursor: pointer;}"); 
    client.println(".blue_slider { -webkit-appearance: none; width: 90%; height: 30px; border-radius: 30px; background: #d3d3d3; outline: none; }");
    client.println(".blue_slider::-webkit-slider-thumb { -webkit-appearance: none; appearance: none; width: 40px; height: 40px; border-radius: 50%; background: rgb(0,0,255); cursor: pointer; }");
      
    client.println("</style></head><body><div  align = \"center\">");
    client.println("<h1 style=\"font-size:100px; font-family:Verdana Pro Semibold\">Selezionare una lettera</h1>");
    client.println("<div style=\"font-size:100px; font-family:Verdana Pro Semibold\">");
    
    client.println("<input id=radio_p type=\"radio\" name=\"lettera\" value=\"p\" onclick=\"press()\" style=\"height:40px; width:40px; vertical-align: 15px;\">P");
    client.println("<input id=radio_s type=\"radio\" name=\"lettera\" value=\"s\" onclick=\"press()\" style=\"height:40px; width:40px; vertical-align: 15px;\">S");
    client.println("<input id=radio_3 type=\"radio\" name=\"lettera\" value=\"3\" onclick=\"press()\" style=\"height:40px; width:40px; vertical-align: 15px;\">3<br>");
      
    client.println("<input id=auto type=\"radio\" name=\"lettera\" value=\"auto\" onclick=\"press()\" style=\"height:40px; width:40px; vertical-align: 15px;\" >Auto");
    client.println("<input id=pulse type=\"radio\" name=\"lettera\" value=\"pulse\" onclick=\"press()\" style=\"height:40px; width:40px; vertical-align: 15px;\" checked>Pulse<br></div>");
    
    client.println("<h1 id=\"lettera_stampata\" style=\"font-size:200px; font-family:Verdana Pro Semibold\"><span id=\"out\" ></span></h1>");
    
    client.println("<input type=\"range\" min=\"0\" max=\"255\" value=\"127\" class=\"red_slider\" id=\"red_slider\"><br><br><br><br>");
    client.println("<input type=\"range\" min=\"0\" max=\"255\" value=\"127\" class=\"green_slider\" id=\"green_slider\"><br><br><br><br>");
    client.println("<input type=\"range\" min=\"0\" max=\"255\" value=\"127\" class=\"blue_slider\" id=\"blue_slider\"><br><br><br><br>");
    
    client.println("<script>");
    
    client.print("var p=[");
      client.print(lettera_p[0]);
      client.print(",");
      client.print(lettera_p[1]);
      client.print(",");
      client.print(lettera_p[2]);
      client.println("];");
      
    client.print("var s=[");
      client.print(lettera_s[0]);
      client.print(",");
      client.print(lettera_s[1]);
      client.print(",");
      client.print(lettera_s[2]);
      client.println("];");
    
    client.print("var tre=[");
      client.print(lettera_tre[0]);
      client.print(",");
      client.print(lettera_tre[1]);
      client.print(",");
      client.print(lettera_tre[2]);
      client.println("];");

    client.println("var lettera_checked='';");
       
    client.println("var lettera_p = document.getElementById(\"radio_p\"); var lettera_s = document.getElementById(\"radio_s\"); var lettera_3 = document.getElementById(\"radio_3\");");
    client.println("var lettera_auto = document.getElementById(\"auto\"); var lettera_pulse = document.getElementById(\"pulse\"); var lettera_stampata = document.getElementById(\"lettera_stampata\");");
    client.println("var red_slider = document.getElementById(\"red_slider\"); var green_slider = document.getElementById(\"green_slider\"); var blue_slider = document.getElementById(\"blue_slider\");");
    client.println("var out = document.getElementById(\"out\");");
    client.println("press();");
      
    client.println("function press(){");
    
    client.println("if (lettera_p.checked == true){");
    client.println("color=\"rgb(\"+p[0]+\",\"+p[1]+\",\"+p[2]+\")\";");
    client.println("lettera_stampata.style.color = color;");
    client.println("red_slider.value=p[0];");
    client.println("green_slider.value=p[1];");
    client.println("blue_slider.value=p[2];");
    client.println("out.innerHTML = \"P\";");
    client.println("red_slider.style.visibility = \"visible\";");
    client.println("green_slider.style.visibility = \"visible\";");
    client.println("blue_slider.style.visibility = \"visible\"; ");
    client.println("var req = new XMLHttpRequest();");
    client.println("req.open('POST', '/autoo=0');");
    client.println("req.send();");
    client.println("lettera_checked='p'}");    

    client.println("else if (lettera_s.checked == true){");
    client.println("color=\"rgb(\"+s[0]+\",\"+s[1]+\",\"+s[2]+\")\";");
    client.println("lettera_stampata.style.color =  color;");
    client.println("red_slider.value=s[0];");
    client.println("green_slider.value=s[1];");
    client.println("blue_slider.value=s[2];");
    client.println("out.innerHTML = \"S\";");
    client.println("red_slider.style.visibility = \"visible\";");
    client.println("green_slider.style.visibility = \"visible\";");
    client.println("blue_slider.style.visibility = \"visible\";  ");
    client.println("var req = new XMLHttpRequest();");
    client.println("req.open('POST', '/autoo=0');");
    client.println("req.send();");
    client.println("lettera_checked='s'}");   

    client.println("else if (lettera_3.checked == true){");
    client.println("color=\"rgb(\"+tre[0]+\",\"+tre[1]+\",\"+tre[2]+\")\";");
    client.println("lettera_stampata.style.color =  color;");
    client.println("red_slider.value=tre[0];");
    client.println("green_slider.value=tre[1];");
    client.println("blue_slider.value=tre[2];");
    client.println("out.innerHTML = \"3\";");
    client.println("red_slider.style.visibility = \"visible\";");
    client.println("green_slider.style.visibility = \"visible\";");
    client.println("blue_slider.style.visibility = \"visible\"; ");
    client.println("var req = new XMLHttpRequest();");
    client.println("req.open('POST', '/autoo=0');");
    client.println("req.send();");
    client.println("lettera_checked='3'}");
    
    client.println("else if (lettera_auto.checked == true){");
    client.println("lettera_stampata.style.color = 'white';");
    client.println("out.innerHTML = \"Auto\";");
    client.println("var req = new XMLHttpRequest();");
    client.println("req.open('POST', '/autoo=1');");
    client.println("req.send();");
    client.println("red_slider.style.visibility = \"hidden\";");
    client.println("green_slider.style.visibility = \"hidden\";");
    client.println("blue_slider.style.visibility = \"hidden\";}");


    client.println("else if (lettera_pulse.checked == true){");
    client.println("lettera_stampata.style.color = 'white';");
    client.println("out.innerHTML = \"Pulse\";");
    client.println("var req = new XMLHttpRequest();");
    client.println("req.open('POST', '/autoo=2');");
    client.println("req.send();");
    client.println("red_slider.style.visibility = \"hidden\";");
    client.println("green_slider.style.visibility = \"hidden\";");
    client.println("blue_slider.style.visibility = \"hidden\";}}");    
            
    client.println("red_slider.oninput = function() {");
    client.println("tmp=this.value");
    client.println("var req = new XMLHttpRequest();");
    client.println("req.open('POST', '/reddd=' +lettera_checked+','+tmp, true);");
    client.println("req.send();");
    client.println("aggiorna_valore(tmp,0)}");
        
         
    client.println("green_slider.oninput = function() {");
    client.println("tmp=this.value");
    client.println("var req = new XMLHttpRequest();");
    client.println("req.open('POST', '/green=' +lettera_checked+','+tmp, true);");
    client.println("req.send();");
    client.println("aggiorna_valore(tmp,1) }");
         
    client.println("blue_slider.oninput = function() {");
    client.println("tmp=this.value");
    client.println("var req = new XMLHttpRequest();");
    client.println("req.open('POST', '/bluee=' +lettera_checked+','+tmp, true);");
    client.println("req.send();");
    
    client.println("aggiorna_valore(tmp,2) }");
        
    client.println("function aggiorna_valore(valore,colore){");
    client.println("if (lettera_p.checked == true){");
    client.println("p[colore]=tmp;");
    client.println("color=\"rgb(\"+p[0]+\",\"+p[1]+\",\"+p[2]+\")\";");
    client.println("lettera_stampata.style.color = color; }");
            
    client.println("else if (lettera_s.checked == true){");
    client.println("s[colore]=tmp;");
    client.println("color=\"rgb(\"+s[0]+\",\"+s[1]+\",\"+s[2]+\")\";");
    client.println("lettera_stampata.style.color =  color; }");
            
    client.println("else if (lettera_3.checked == true){");
    client.println("tre[colore]=tmp;");
    client.println("color=\"rgb(\"+tre[0]+\",\"+tre[1]+\",\"+tre[2]+\")\";");
    client.println("lettera_stampata.style.color =  color;}}");
    
    
    client.println("</script></div></body></html>");
  
  delay(0);
  //Serial.println("Client disonnected");
  //Serial.println("");
  
}


//Funzione per modificare il colore dei led
void Aggiorna_led(int p[],int s[],int tre[]){
  for (int i=led_p[0]; i<=p_len; i++){
    leds[i] = CRGB(p[0],p[1],p[2]);
    delay(0);
  }

  for (int i=led_s[0]; i<=s_len; i++){
    leds[i] = CRGB(s[0],s[1],s[2]);
    delay(0);
  }

  for (int i=led_tre[0]; i<=tre_len; i++){
    leds[i] = CRGB(tre[0],tre[1],tre[2]);
    delay(0);
  }
  delay(10);
  FastLED.show();
  delay(0);
  
}

//Sequenza per norificare l'avvenuta accensione
void Connesso(){
  
  for (int led=da; led<=fino; led++){
    leds[led] = CRGB(0,0,0);
    delay(0);
  }

  FastLED.show();
  delay(0);

  for (int led=da; led<=fino; led++){
    for (int i=1; i<=255; i+=2){
      leds[led] = CRGB(0,i,i);
      delay(0);
      FastLED.show();
      delay(0);
    }
  }

  lettera_p[0]={0};
  lettera_p[1]={255};
  lettera_p[2]={255};
  
  lettera_s[0]={0};
  lettera_s[1]={255};
  lettera_s[2]={255};
  
  lettera_tre[0]={0};
  lettera_tre[1]={255};
  lettera_tre[2]={255};  

}

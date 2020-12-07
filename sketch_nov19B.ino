#include <SPI.h>
#include <RFID.h>


#define SS_PIN D2
#define RST_PIN D1

RFID rfid(SS_PIN,RST_PIN);

String cardType; // รับ string
char cardTypeChar; //รับ char  
String myStrings[60];
String serNum[5]; 
String Temp[4]; // เก็บค่าไพ่ที่ลง 4 รอบ {A,B,C,D}
char TempF;

//Card C = Club , A = Diamond , S = Spade , H = Heart 
//*14 = 1(A)
String C14[5] = {"134","91","252","9","40"}; 
String A14[5] = {"22","67","234","9","182"};
String H14[5] = {"6","80","46","10","114"};
String S14[5] = {"246","91","31","10","184"};
String C02[5] = {"118","125","238","9","236"};
String A02[5] = {"182","205","15","10","126"};
String H02[5] = {"86","223","42","10","169"};
String S02[5] = {"22","119","252","9","148"};
String C03[5] = {"118","7","245","9","141"};
String A03[5] = {"214","80","233","9","102"};
String H03[5] = {"86","151","238","9","38"};
String S03[5] = {"230","153","237","9","155"};
String C04[5] = {"102","36","244","9","191"};
String A04[5] = {"198","232","242","9","213"};
String H04[5] = {"6","59","245","9","193"};
String S04[5] = {"54","1","231","9","217"};
String C05[5] = {"54","230","244","9","45"};
String A05[5] = {"134","11","230","9","98"};
String H05[5] = {"182","238","244","9","165"};
String S05[5] = {"6","147","237","9","113"};
String C06[5] = {"22","111","9","10","122"};
String A06[5] = {"70","110","239","9","206"};
String H06[5] = {"118","160","231","9","56"};
String S06[5] = {"86","43","13","10","122"};
String C07[5] = {"86","71","244","9","236"};
String A07[5] = {"246","29","42","10","203"};
String H07[5] = {"198","198","244","9","253"};
String S07[5] = {"198","39","244","9","28"};
String C08[5] = {"102","195","231","9","75"};
String A08[5] = {"38","155","242","9","70"};
String H08[5] = {"246","4","11","10","243"};
String S08[5] = {"150","212","25","10","81"};
String C09[5] = {"22","232","242","9","5"};
String A09[5] = {"230","125","30","10","143"};
String H09[5] = {"118","108","233","9","250"};
String S09[5] = {"230","74","33","10","135"};
String C10[5] = {"214","176","238","9","129"};
String A10[5] = {"198","156","235","9","184"}; 
String H10[5] = {"54","194","13","10","243"};
String S10[5] = {"182","40","43","10","191"};
String C11[5] = {"214","17","234","9","36"};
String A11[5] = {"38","59","240","9","228"};
String H11[5] = {"182","82","18","10","252"};
String S11[5] = {"230","94","24","10","170"};
String C12[5] = {"246","32","245","9","42"};
String A12[5] = {"6","160","241","9","94"};
String H12[5] = {"102","203","241","9","85"};
String S12[5] = {"38","248","231","9","48"};
String C13[5] = {"214","223","238","9","238"};
String A13[5] = {"118","91","236","9","200"};
String H13[5] = {"198","217","235","9","253"}; 
String S13[5] = {"118","229","242","9","104"}; 


String A[13];
String B[13];
String C[13];
String D[13]; 

String Aa[52];
String Bb[52];
String Cc[52];
String Dd[52];

String tempA[12];
String tempB[12];
String tempC[12];
String tempD[12];
String tempZ[12];
String TempChk[52]; //Temp

int Count = -1;
int Count1 = 0;
int stateRFID = false;
int j = 0;
int k = 0;
int reB = 0;

String readSerial;
String biddingSerial; //เก็บค่าทรัมป์ C,A,H,S
int Test1 = 1;
int Test2 = 1;

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.init();
}

void loop() {
  if (Serial.available() > 0) {
    if(Count == 52){
    biddingSerial = Serial.readString(); //ทรัมป์
    Serial.print("Contract is " + biddingSerial);
    Count++;
    }else{
      readSerial = Serial.readString();
      Serial.print("Serial read : ");
      Serial.println(readSerial); 
      Test1 = readSerial.toInt();
    }   
  }
  if(Test1 == 1){
    stateRFID = true;
    if (rfid.isCard()&& stateRFID){
    if (rfid.readCardSerial() ){
      for(int i = 0 ; i <= 4 ; i++){
        serNum[i] = rfid.serNum[i];
      }
      //delay(300);
      if(Count<=51){
          Serial.print("Cardnumber : ");
          printArray(serNum,4);
          changeValue();
          myStrings[Count] = cardType;
          Serial.println("Count : " + String(Count));
          Serial.println("Card Type : " + cardType);
          Serial.print("CardInList : ");
          printArray(myStrings,51);
        //  int sizeArray = sizeof(myStrings)/sizeof(myStrings[0]);
        //  Serial.println(sizeArray);
          Serial.println("");
          delay(300);
      } 
        if(Test2 == 2){ //Round 1 Turn 1
          changeValue();
          Temp[0] = cardType;
          //removing item in A[i] = cardType
          for(int y = 0; y<=12 ;y++){
            if(A[y] == cardType){
              A[y] = ""; //removing
            }
          }
          Serial.println(Temp[0]);
          delay(500);
        } 
        if(Test2 == 3){ //Round 1 Turn 2
          changeValue();
          //กรณีผู้เล่นคนที่ 2(B} มีไพ่เหมือนกับผู้เล่นคนแรกมากกว่า 1ใบ
          if(j>=1){ //มีมากกว่า 1 ใบ //กรณีไม่มีในมือให้ลงทรัมป์ else { } ยังไม่ไดเขียน
            //เช็คว่าถ้าที่รับมาไม่เท่ากับหน้าของคนแรกที่ลง เตือนผู้เล่นว่าในมือมีที่เล่นได้อยู่นะ
            if(cardTypeChar != Temp[0].charAt(0)){             
                Serial.print("---You must to play cards that you can play !--- ");
                j = 0; //ทำการเครียอาเรย์ tempB[j] ให้วนหาใหม่
                Test2 = 2; //ทำการรีรอบใหม่ให้ไปเข้ารอบ 2 
                Test1 = 3; //เปิดฟังก์ชั่นเล่นรอบ 2 ใหม่
            }else{    
              Temp[1] = cardType; 
              for(int y = 0; y<=12 ;y++){
                if(B[y] == cardType){
                  B[y] = ""; //removing
                }
              }
              j = 0; //รีเซ็ตค่า j ใหม่เพื่อใช้งานในรอบคนที่ 3
            }
          }
          Serial.println(Temp[1]); //Temp[4] = {A,B,C,D}
          printArray(Temp,4); 
          delay(500);
      }
       if(Test2 == 4){ //Round 1 Turn 3
          changeValue();
          //กรณีผู้เล่นคนที่ 3(C} มีไพ่เหมือนกับผู้เล่นคนแรกมากกว่า 1ใบ
          if(j>=1){ //มีมากกว่า 1 ใบ
            //เช็คว่าถ้าที่รับมาไม่เท่ากับหน้าของคนแรกที่ลง เตือนผู้เล่นว่าในมือมีที่เล่นได้อยู่นะ
            if(cardTypeChar != Temp[0].charAt(0)){             
                Serial.print("---You must to play cards that you can play !--- : ");
                j = 0;
                Test2 = 3; //ทำการรีรอบใหม่ให้ไปเข้ารอบ 2 
                Test1 = 3; //เปิดฟังก์ชั่นเล่นรอบ 2 ใหม่
            }else{
              Temp[2] = cardType; 
              for(int y = 0; y<=12 ;y++){
                if(C[y] == cardType){
                  C[y] = ""; //removing
                }
              }
              j = 0; //รีเซ็ตค่า j ใหม่เพื่อใช้งานในรอบคนที่ 3
            }
          }
          
          Serial.println(Temp[2]); //Temp[4] = {A,B,C,D}
          printArray(Temp,4); 
          delay(500);          
      }  
      if(Test2 == 5){ //Round 1 Turn 4
              changeValue();
          //กรณีผู้เล่นคนที่ 4(D} มีไพ่เหมือนกับผู้เล่นคนแรกมากกว่า 1ใบ
          if(j>=1){ //มีมากกว่า 1 ใบ
            //เช็คว่าถ้าที่รับมาไม่เท่ากับหน้าของคนแรกที่ลง เตือนผู้เล่นว่าในมือมีที่เล่นได้อยู่นะ
            if(cardTypeChar != Temp[0].charAt(0)){             
                Serial.print("---You must to play cards that you can play !--- : ");  
                j = 0;
                Test2 = 4; //ทำการรีรอบใหม่ให้ไปเข้ารอบ 4 
                Test1 = 3; //เปิดฟังก์ชั่นเล่นรอบ 2 ใหม่
            }else{
              Temp[3] = cardType; 
               for(int y = 0; y<=12 ;y++){
                if(D[y] == cardType){
                  D[y] = ""; //removing
                }
              }
              j = 0; //รีเซ็ตค่า j ใหม่เพื่อใช้งานในรอบคนที่ 3
            }
          }
          Serial.println(Temp[3]); //Temp[4] = {A,B,C,D}
          printArray(Temp,4); 
          delay(500);
          //ฟังก์ชั่นสรุปผลในรอบแรก
          for(int i = 0; i < 4 ; i++){
            //เช็คว่ามีทรัมป์กี่ตัว 
            if(Temp
            /*
            if(Temp[i].charAt(0)==Temp[0].charAt(0)){
              TempChk[k] = Temp[i];
               k++;
               Serial.println("K = "+k);
               delay(500);
               //ถ้ามีแค่ตัวเดียวตัวนั้นคือ max ละก็คนนั้นชนะรอบ
              if(k = 1){
               //0 Max = Temp[i];
                Serial.println("K = 1 in loop");
                delay(1000);
              }
            }*/
            
          }
      }   
    }
  }
  }
  if(Test1 == 2){ //rfid off
    stateRFID = false;
    }
    
     if(Count == 51){
      //เก็บค่าไพ่ทั้ง 52 ใบเข้าสู่อาเรย์ของทั้ง 4 คน
        for(int Home = 0 ; Home <=12 ; Home++){
          A[Home] = myStrings[Count1]; 
          B[Home] = myStrings[Count1+1];
          C[Home] = myStrings[Count1+2];
          D[Home] = myStrings[Count1+3];
          Count1 = Count1 + 4;
        }    
        printArray(A,12);
        printArray(B,12);
        printArray(C,12);
        printArray(D,12);
        Serial.println(".......................................................");
        Serial.println("Binding state ......");
        Count++; //52
      }
      
      if(Test1 == 3){
          Serial.println(".......................................................");
          if(Test2 == 1){
            Serial.println("Turn " + String(Test2) + " you start placing the card");
          }else{
             Serial.println("Turn " + String(Test2) + " placing the card.");
          }
          Serial.print("Cards in your hand : ");
          if(Test2 == 1){
            printArray(A,12);
          }
          if(Test2 == 2){
            printArray(B,12);
          }
          if(Test2 == 3){
            printArray(C,12);
          }
          if(Test2 == 4){
            printArray(D,12);
          }
         Serial.print("Cards you can play : ");
         if(Test2 == 1){
            printArray(A,12);
          }
          if(Test2 == 2){
            //เช็คจากคนแรกที่ลง
            for(int i=0;i<=12;i++){
              //กรณีที่ในมือมีไพ่หน้าเดียวกับคนแรกที่ลง
              if(B[i].charAt(0) == Temp[0].charAt(0)){ //Temp[0] = A ที่เลือกลง
                   tempB[j] = B[i]; //tempB ที่เก็บข้อมูลชั่วคราว
                   j++; //บอกว่ามีกี่ใบที่ลงได้
              }
            }
            printArray(tempB,12);
          }
          if(Test2 == 3){
           //เช็คจากคนแรกที่ลง
            for(int i=0;i<=12;i++){
              //กรณีที่ในมือมีไพ่หน้าเดียวกับคนแรกที่ลง
              if(C[i].charAt(0) == Temp[0].charAt(0)){
                if(reB == 1){ 
                  tempC[j] ="";
                }else{
                   tempC[j] = C[i]; //tempB ที่เก็บข้อมูลชั่วคราว
                }
                j++; //บอกว่ามีกี่ใบที่ลงได้
              }
            }
            printArray(tempC,12);
          }
          if(Test2 == 4){
            //เช็คจากคนแรกที่ลง
            for(int i=0;i<=12;i++){
              //กรณีที่ในมือมีไพ่หน้าเดียวกับคนแรกที่ลง
              if(D[i].charAt(0) == Temp[0].charAt(0)){
                if(reB == 1){
                  tempD[j] ="";
                }else{
                   tempD[j] = D[i]; //tempB ที่เก็บข้อมูลชั่วคราว
                }
                j++; //บอกว่ามีกี่ใบที่ลงได้
              }
            }
            printArray(tempD,12);
          }
          Serial.print("Placing the cards : ");
          Test1 = 1;     
          Test2++;   
      } 
      if(Test1 == 4){
        
      }
     
}


void bidding(){
  //ฟังก์ชันประมูล
  //รับค่ามาจากหน้าเว็บ --> MongoDB --> Arduino นำมาเก็บค่าไว้ในตัวแปร
  
}
void printArray(String Arr[],int size){
 /* String DoubleQ = "\"";
      Serial.println("["+DoubleQ+Arr[0]+DoubleQ+","+DoubleQ+Arr[1]+DoubleQ+","+DoubleQ+Arr[2]+DoubleQ+","+DoubleQ+Arr[3]+DoubleQ+","+DoubleQ+Arr[4]+DoubleQ+"];"); */
        for(int i=0;i<=size;i++){
      Serial.print(Arr[i]); 
      Serial.print(",");
    }
    Serial.println();
}
void clearArray(String Arr[],int size){
  for(int i = 0 ; i<=size ; i++){
     Arr[i] = tempZ[i];
  }
}
void changeValue(){
if(serNum[0] == C14[0] && serNum[1] == C14[1] && serNum[2] == C14[2] && serNum[3] == C14[3]){ cardType = "C14";  cardTypeChar = cardType.charAt(0); Count++; }
if(serNum[0] == A14[0] && serNum[1] == A14[1] && serNum[2] == A14[2] && serNum[3] == A14[3]){ cardType = "A14";  cardTypeChar = cardType.charAt(0); Count++; }
if(serNum[0] == H14[0] && serNum[1] == H14[1] && serNum[2] == H14[2] && serNum[3] == H14[3]){ cardType = "H14";  cardTypeChar = cardType.charAt(0); Count++; }
if(serNum[0] == S14[0] && serNum[1] == S14[1] && serNum[2] == S14[2] && serNum[3] == S14[3]){ cardType = "S14";  cardTypeChar = cardType.charAt(0); Count++; }
if(serNum[0] == C02[0] && serNum[1] == C02[1] && serNum[2] == C02[2] && serNum[3] == C02[3]){ cardType = "C02";  cardTypeChar = cardType.charAt(0); Count++; }
if(serNum[0] == A02[0] && serNum[1] == A02[1] && serNum[2] == A02[2] && serNum[3] == A02[3]){ cardType = "A02";  cardTypeChar = cardType.charAt(0); Count++; }
if(serNum[0] == H02[0] && serNum[1] == H02[1] && serNum[2] == H02[2] && serNum[3] == H02[3]){ cardType = "H02";  cardTypeChar = cardType.charAt(0); Count++; }
if(serNum[0] == S02[0] && serNum[1] == S02[1] && serNum[2] == S02[2] && serNum[3] == S02[3]){ cardType = "S02";  cardTypeChar = cardType.charAt(0); Count++; }
if(serNum[0] == C03[0] && serNum[1] == C03[1] && serNum[2] == C03[2] && serNum[3] == C03[3]){ cardType = "C03";  cardTypeChar = cardType.charAt(0); Count++; }
if(serNum[0] == A03[0] && serNum[1] == A03[1] && serNum[2] == A03[2] && serNum[3] == A03[3]){ cardType = "A03";  cardTypeChar = cardType.charAt(0); Count++; }
if(serNum[0] == H03[0] && serNum[1] == H03[1] && serNum[2] == H03[2] && serNum[3] == H03[3]){ cardType = "H03";  cardTypeChar = cardType.charAt(0); Count++; }
if(serNum[0] == S03[0] && serNum[1] == S03[1] && serNum[2] == S03[2] && serNum[3] == S03[3]){ cardType = "S03";  cardTypeChar = cardType.charAt(0); Count++; }
if(serNum[0] == C04[0] && serNum[1] == C04[1] && serNum[2] == C04[2] && serNum[3] == C04[3]){ cardType = "C04";  cardTypeChar = cardType.charAt(0); Count++; }
if(serNum[0] == A04[0] && serNum[1] == A04[1] && serNum[2] == A04[2] && serNum[3] == A04[3]){ cardType = "A04";  cardTypeChar = cardType.charAt(0); Count++; }
if(serNum[0] == H04[0] && serNum[1] == H04[1] && serNum[2] == H04[2] && serNum[3] == H04[3]){ cardType = "H04";  cardTypeChar = cardType.charAt(0); Count++; }
if(serNum[0] == S04[0] && serNum[1] == S04[1] && serNum[2] == S04[2] && serNum[3] == S04[3]){ cardType = "S04";  cardTypeChar = cardType.charAt(0); Count++; }
if(serNum[0] == C05[0] && serNum[1] == C05[1] && serNum[2] == C05[2] && serNum[3] == C05[3]){ cardType = "C05";  cardTypeChar = cardType.charAt(0); Count++; }
if(serNum[0] == A05[0] && serNum[1] == A05[1] && serNum[2] == A05[2] && serNum[3] == A05[3]){ cardType = "A05";  cardTypeChar = cardType.charAt(0); Count++; }
if(serNum[0] == H05[0] && serNum[1] == H05[1] && serNum[2] == H05[2] && serNum[3] == H05[3]){ cardType = "H05";  cardTypeChar = cardType.charAt(0); Count++; }
if(serNum[0] == S05[0] && serNum[1] == S05[1] && serNum[2] == S05[2] && serNum[3] == S05[3]){ cardType = "S05";  cardTypeChar = cardType.charAt(0); Count++; }
if(serNum[0] == C06[0] && serNum[1] == C06[1] && serNum[2] == C06[2] && serNum[3] == C06[3]){ cardType = "C06";  cardTypeChar = cardType.charAt(0); Count++; }
if(serNum[0] == A06[0] && serNum[1] == A06[1] && serNum[2] == A06[2] && serNum[3] == A06[3]){ cardType = "A06";  cardTypeChar = cardType.charAt(0); Count++; }
if(serNum[0] == H06[0] && serNum[1] == H06[1] && serNum[2] == H06[2] && serNum[3] == H06[3]){ cardType = "H06";  cardTypeChar = cardType.charAt(0); Count++; }
if(serNum[0] == S06[0] && serNum[1] == S06[1] && serNum[2] == S06[2] && serNum[3] == S06[3]){ cardType = "S06";  cardTypeChar = cardType.charAt(0); Count++; }
if(serNum[0] == C07[0] && serNum[1] == C07[1] && serNum[2] == C07[2] && serNum[3] == C07[3]){ cardType = "C07";  cardTypeChar = cardType.charAt(0); Count++; }
if(serNum[0] == A07[0] && serNum[1] == A07[1] && serNum[2] == A07[2] && serNum[3] == A07[3]){ cardType = "A07";  cardTypeChar = cardType.charAt(0); Count++; }
if(serNum[0] == H07[0] && serNum[1] == H07[1] && serNum[2] == H07[2] && serNum[3] == H07[3]){ cardType = "H07";  cardTypeChar = cardType.charAt(0); Count++; }
if(serNum[0] == S07[0] && serNum[1] == S07[1] && serNum[2] == S07[2] && serNum[3] == S07[3]){ cardType = "S07";  cardTypeChar = cardType.charAt(0); Count++; }
if(serNum[0] == C08[0] && serNum[1] == C08[1] && serNum[2] == C08[2] && serNum[3] == C08[3]){ cardType = "C08";  cardTypeChar = cardType.charAt(0); Count++; }
if(serNum[0] == A08[0] && serNum[1] == A08[1] && serNum[2] == A08[2] && serNum[3] == A08[3]){ cardType = "A08";  cardTypeChar = cardType.charAt(0); Count++; }
if(serNum[0] == H08[0] && serNum[1] == H08[1] && serNum[2] == H08[2] && serNum[3] == H08[3]){ cardType = "H08";  cardTypeChar = cardType.charAt(0); Count++; }
if(serNum[0] == S08[0] && serNum[1] == S08[1] && serNum[2] == S08[2] && serNum[3] == S08[3]){ cardType = "S08";  cardTypeChar = cardType.charAt(0); Count++; }
if(serNum[0] == C09[0] && serNum[1] == C09[1] && serNum[2] == C09[2] && serNum[3] == C09[3]){ cardType = "C09";  cardTypeChar = cardType.charAt(0); Count++; }
if(serNum[0] == A09[0] && serNum[1] == A09[1] && serNum[2] == A09[2] && serNum[3] == A09[3]){ cardType = "A09";  cardTypeChar = cardType.charAt(0); Count++; }
if(serNum[0] == H09[0] && serNum[1] == H09[1] && serNum[2] == H09[2] && serNum[3] == H09[3]){ cardType = "H09";  cardTypeChar = cardType.charAt(0); Count++; }
if(serNum[0] == S09[0] && serNum[1] == S09[1] && serNum[2] == S09[2] && serNum[3] == S09[3]){ cardType = "S09";  cardTypeChar = cardType.charAt(0); Count++; }
if(serNum[0] == C10[0] && serNum[1] == C10[1] && serNum[2] == C10[2] && serNum[3] == C10[3]){ cardType = "C10";  cardTypeChar = cardType.charAt(0); Count++; }
if(serNum[0] == A10[0] && serNum[1] == A10[1] && serNum[2] == A10[2] && serNum[3] == A10[3]){ cardType = "A10";  cardTypeChar = cardType.charAt(0); Count++; }
if(serNum[0] == H10[0] && serNum[1] == H10[1] && serNum[2] == H10[2] && serNum[3] == H10[3]){ cardType = "H10";  cardTypeChar = cardType.charAt(0); Count++; }
if(serNum[0] == S10[0] && serNum[1] == S10[1] && serNum[2] == S10[2] && serNum[3] == S10[3]){ cardType = "S10";  cardTypeChar = cardType.charAt(0); Count++; }
if(serNum[0] == C11[0] && serNum[1] == C11[1] && serNum[2] == C11[2] && serNum[3] == C11[3]){ cardType = "C11";  cardTypeChar = cardType.charAt(0); Count++; }
if(serNum[0] == A11[0] && serNum[1] == A11[1] && serNum[2] == A11[2] && serNum[3] == A11[3]){ cardType = "A11";  cardTypeChar = cardType.charAt(0); Count++; }
if(serNum[0] == H11[0] && serNum[1] == H11[1] && serNum[2] == H11[2] && serNum[3] == H11[3]){ cardType = "H11";  cardTypeChar = cardType.charAt(0); Count++; }
if(serNum[0] == S11[0] && serNum[1] == S11[1] && serNum[2] == S11[2] && serNum[3] == S11[3]){ cardType = "S11";  cardTypeChar = cardType.charAt(0); Count++; }
if(serNum[0] == C12[0] && serNum[1] == C12[1] && serNum[2] == C12[2] && serNum[3] == C12[3]){ cardType = "C12";  cardTypeChar = cardType.charAt(0); Count++; }
if(serNum[0] == A12[0] && serNum[1] == A12[1] && serNum[2] == A12[2] && serNum[3] == A12[3]){ cardType = "A12";  cardTypeChar = cardType.charAt(0); Count++; }
if(serNum[0] == H12[0] && serNum[1] == H12[1] && serNum[2] == H12[2] && serNum[3] == H12[3]){ cardType = "H12";  cardTypeChar = cardType.charAt(0); Count++; }
if(serNum[0] == S12[0] && serNum[1] == S12[1] && serNum[2] == S12[2] && serNum[3] == S12[3]){ cardType = "S12";  cardTypeChar = cardType.charAt(0); Count++; }
if(serNum[0] == C13[0] && serNum[1] == C13[1] && serNum[2] == C13[2] && serNum[3] == C13[3]){ cardType = "C13";  cardTypeChar = cardType.charAt(0); Count++; }
if(serNum[0] == A13[0] && serNum[1] == A13[1] && serNum[2] == A13[2] && serNum[3] == A13[3]){ cardType = "A13";  cardTypeChar = cardType.charAt(0); Count++; }
if(serNum[0] == H13[0] && serNum[1] == H13[1] && serNum[2] == H13[2] && serNum[3] == H13[3]){ cardType = "H13";  cardTypeChar = cardType.charAt(0); Count++; }
if(serNum[0] == S13[0] && serNum[1] == S13[1] && serNum[2] == S13[2] && serNum[3] == S13[3]){ cardType = "S13";  cardTypeChar = cardType.charAt(0); Count++; }
}

/*
void changeValue1(){
  switch(Count1) {
    case 0 :   cardType = "C14";  break;
    case 1 :   cardType = "A14";  break;
    case 2 :   cardType = "H14";  break;
    case 3 :   cardType = "S14";  break;
    case 4 :   cardType = "C02";  break;
    case 5 :   cardType = "A02";  break;
    case 6 :   cardType = "H02";  break;
    case 7 :   cardType = "S02";  break;
    case 8 :   cardType = "C03";  break;
    case 9 :   cardType = "A03";  break;
    case 10 :  cardType = "H03";  break;
    case 11 :  cardType = "S03";  break;
    case 12 :  cardType = "C04";  break;
    case 13 :  cardType = "A04";  break;
    case 14 :  cardType = "H04";  break;
    case 15 :  cardType = "S04";  break;
    case 16 :  cardType = "C05";  break;
    case 17 :  cardType = "A05";  break;
    case 18 :  cardType = "H05";  break;
    case 19 :  cardType = "S05";  break;
    case 20 :  cardType = "C06";  break;
    case 21 :  cardType = "A06";  break;
    case 22 :  cardType = "H06";  break;
    case 23 :  cardType = "S06";  break;
    case 24 :  cardType = "C07";  break;
    case 25 :  cardType = "A07";  break;
    case 26 :  cardType = "H07";  break;
    case 27 :  cardType = "S07";  break;
    case 28 :  cardType = "C08";  break;
    case 29 :  cardType = "A08";  break;
    case 30 :  cardType = "H08";  break;
    case 31 :  cardType = "S08";  break;
    case 32 :  cardType = "C09";  break;
    case 33 :  cardType = "A09";  break;
    case 34 :  cardType = "H09";  break;
    case 35 :  cardType = "S09";  break;
    case 36 :  cardType = "C10";  break;
    case 37 :  cardType = "A10";  break;
    case 38 :  cardType = "H10";  break;
    case 39 :  cardType = "S10";  break;
    case 40 :  cardType = "C11";  break;
    case 41 :  cardType = "A11";  break;
    case 42 :  cardType = "H11";  break;
    case 43 :  cardType = "S11";  break;
    case 44 :  cardType = "C12";  break;
    case 45 :  cardType = "A12";  break;
    case 46 :  cardType = "H12";  break;
    case 47 :  cardType = "S12";  break;
    case 48 :  cardType = "C13";  break;
    case 49 :  cardType = "A13";  break;
    case 50 :  cardType = "H13";  break;
    case 51 :  cardType = "S13";  break;
  }
}
*/
  

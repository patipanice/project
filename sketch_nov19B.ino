#include <SPI.h>
#include <RFID.h>


#define SS_PIN D2
#define RST_PIN D1

RFID rfid(SS_PIN,RST_PIN);

String cardType; // รับ string
char cardTypeChar; //รับ char  
String myStrings[52]; //เก็บไพ่ 52 ใบ
String serNum[5];  // เก็บค่า rfid tag
String Temp[4]; // เก็บค่าไพ่ที่ลง 4 รอบ {A,B,C,D}
String newTemp[10];
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

/*
String A[13] = {"H02"," C09", "S05"," A06"," S09"," A07"," S04"," C08"," S14"," C11" ,"H14"," H13","H12"};
String B[13] ={"C05", "C06", "S02", "A12", "C03" ,"A13", "S03", "A14", "A11", "S08", "H11","H10"," H09 "};
String C[13] ={"C10", "C12", "A09", "S10", "S07", "A03", "C07", "A05 ","S13 ","C02,"," H08", "H07 ","H06 "};
String D[13] ={"S12" ,"S06", "A04","S11" ,"A08" ,"A02" ,"C14","A10"," C04" ,"C13"," H05 ","H04"," H03" };*/

String A[13];
String B[13];
String C[13];
String D[13];
String Keep_A[52];
String Keep_B[52];
String Keep_C[52];
String Keep_D[52];
String tempA[13];
String tempB[12];
String tempC[13];
String tempD[13];
String tempZ[13];
String TempChk[52]; //Temp

int Count =-1;
int Count1 = 0;
int stateRFID = false;
int j = 0;
int k = 0;
int m = 0;
int Kc = 1;
int reB = 0;
int Max;
int n = 0;
String readSerial;
String biddingSerial; //เก็บค่าทรัมป์ C,A,H,S
char biddingChar = 'C';
int Test1 = 1;
int Test2 = 1;
String Win = "A"; //ตั้งค่าเริ่มต้นให้เริ่มที่คนแรก
boolean addChar = true;
void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.init();
}

void loop() {
  if (Serial.available() > 0) {
    if(Count == 52){
      Serial.print("Contract is : ");
      biddingSerial = Serial.readString(); //ทรัมป์ String
      biddingChar = biddingSerial.charAt(0); //เก็บทรัมป์ char 
      Serial.println(biddingChar);
      Count++;
    }else{
      readSerial = Serial.readString();
      Serial.print("Serial read : ");
      Serial.println(readSerial); 
      Test1 = readSerial.toInt();//Serial Integer
    }   
  }
  if(Test1 == 1){
    stateRFID = true;
    if (rfid.isCard() && stateRFID){
      if (rfid.readCardSerial() ){
        for(int i = 0 ; i <= 4 ; i++){
          serNum[i] = rfid.serNum[i];
        }
      if(Count<=51){
        //Serial.print("Cardnumber : ");
       // printArray(serNum,4);
        changeValue();
        myStrings[Count] = cardType;
        Serial.println("Count : " + String(Count));
        Serial.println("Card Type : " + cardType);
        Serial.print("CardInList : ");
        printArray(myStrings,51);
        Serial.println("");
        delay(300);
      } 
      if(Test2 == 2){ //Round 1 Turn 1
        changeValue();
        Temp[0] = cardType;
        //removing
        deleteElement(A,13,Temp[0]);        
        Serial.print(Temp[0]);
        Serial.println(" | Remove "+ cardType+" from the deck");
        Serial.println("END A");
        Serial.print("In [A] Decks : ");
        printArray(A,13);
        Test1 = 0;    
      } 
        if(Test2 == 3){ //Round 1 Turn 2
          changeValue();
          //กรณีผู้เล่นคนที่ 2(B} มีไพ่เหมือนกับผู้เล่นคนแรกมากกว่า 1ใบ     
          if(j>=1){ //มีมากกว่า 1 ใบ
            //เช็คว่าถ้าที่รับมาไม่เท่ากับหน้าของคนแรกที่ลง เตือนผู้เล่นว่าในมือมีที่เล่นได้อยู่นะ
            if(cardTypeChar != tempB[0].charAt(0)){             
                Serial.println(" !You must to play cards that you can play !, Please try again.");
                j = 0; //ทำการเครียอาเรย์ tempB[j] ให้วนหาใหม่
                Test2 = 2; //ทำการรีรอบใหม่ให้ไปเข้ารอบ 2 
                Test1 = 3; //เปิดฟังก์ชั่นเล่นรอบ 2 ใหม่
            }else{    
                Temp[1] = cardType; 
                deleteElement(B, 13,Temp[1]); 
                Serial.print(Temp[1]);
                Serial.println(" | Remove "+ cardType+" from the deck");
                Serial.println("END B");
                Serial.print("In [B] Decks : ");
                printArray(B,13);  
                Test1 = 0;            
              j = 0; //รีเซ็ตค่า j ใหม่เพื่อใช้งานในรอบคนที่ 3   
            }
          }else if(j==0){ //กรณีที่ j=0 ไม่มีไพ่เหมือนคนแรกให้ลงอะไรก็ได้
              Temp[1] = cardType; 
              deleteElement(B, 13,Temp[1]); 
              Serial.print(Temp[1]);
              Serial.println(" | Remove "+ cardType+" from the deck");
              Serial.println("END B");
              Serial.print("In [B] Decks : ");
              printArray(B,13);
              Test1 = 0;       
          }    
        }
       if(Test2 == 4){ //Round 1 Turn 3
          changeValue();
          if(j>=1){ //มีมากกว่า 1 ใบ
            //เช็คว่าถ้าที่รับมาไม่เท่ากับหน้าของคนแรกที่ลง เตือนผู้เล่นว่าในมือมีที่เล่นได้อยู่นะ
            if(cardTypeChar != tempC[0].charAt(0)){             
                Serial.print("---You must to play cards that you can play !--- ");
                j = 0; //ทำการเครียอาเรย์ tempB[j] ให้วนหาใหม่
                Test2 = 3; //ทำการรีรอบใหม่ให้ไปเข้ารอบ 3 
                Test1 = 3; //เปิดฟังก์ชั่นเล่นรอบ 2 ใหม่
            }else{    
              Temp[2] = cardType; 
              deleteElement(C, 13,Temp[2]); 
              Serial.print(Temp[2]);
              Serial.println(" | Remove "+ cardType+" from the deck");
              Serial.println("END C");
              Serial.print("In [C] Decks : ");
              printArray(C,13); 
              j = 0; //รีเซ็ตค่า j ใหม่เพื่อใช้งานในรอบคนที่ 3  
              Test1 = 0; 
            }
            }else if(j==0){ //กรณีที่ j=0 ไม่มีไพ่เหมือนคนแรกให้ลงอะไรก็ได้
              Temp[2] = cardType; 
              deleteElement(C, 13,Temp[2]); 
              Serial.print(Temp[2]);
              Serial.println(" | Remove "+ cardType+" from the deck");
              Serial.println("END C");
              Serial.print("In [C] Decks : ");
              printArray(C,13);
              Test1 = 0;              
          }        
      }  
      if(Test2 == 5){ //Round 1 Turn 4 D
          changeValue();
          if(j>=1){ //มีมากกว่า 1 ใบ
            //เช็คว่าถ้าที่รับมาไม่เท่ากับหน้าของคนแรกที่ลง เตือนผู้เล่นว่าในมือมีที่เล่นได้อยู่นะ
            if(cardTypeChar != tempD[0].charAt(0)){             
                Serial.print("---You must to play cards that you can play !--- ");
                j = 0; //ทำการเครียอาเรย์ tempB[j] ให้วนหาใหม่
                Test2 = 4; //ทำการรีรอบใหม่ให้ไปเข้ารอบ 4
                Test1 = 3; //เปิดฟังก์ชั่นเล่นรอบ 2 ใหม่
            }else{    
              Temp[3] = cardType; 
              deleteElement(D, 13,Temp[3]); 
              Serial.print(Temp[3]);
              Serial.println(" | Remove "+ cardType+" from the deck");
              Serial.println("END D");
              Serial.print("In [D] Decks : ");
              printArray(D,13);
              Test2 = 1;
              Test1 = 0;  
              j = 0; //รีเซ็ตค่า j ใหม่เพื่อใช้งานในรอบคนที่ 3   
            }
          }else if(j==0){ //กรณีที่ j=0 ไม่มีไพ่เหมือนคนแรกให้ลงอะไรก็ได้
              Temp[3] = cardType; 
              deleteElement(D, 13,Temp[3]); 
              Serial.print(Temp[3]);
              Serial.println(" | Remove "+ cardType+" from the deck");
              Serial.println("END C");
              Serial.print("In [D] Decks : ");
              printArray(D,13);
              Test2 = 1;
              Test1 = 0;    
          }           
      }   
    }
  }
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
        Serial.print("A : ");   
        printArray(A,12); 
        Serial.print("B : ");   
        printArray(B,12);
        Serial.print("C : ");   
        printArray(C,12); 
        Serial.print("D : ");   
        printArray(D,12);
        Serial.println(".......................................................");
        Serial.println("");
        Serial.println("-------------------- Binding state --------------------");
        
        Count++; //52
      }
      
      if(Test1 == 4){
        //สรุปผล
        if(addChar){
          Temp[0]  = Temp[0]+"A";
          Temp[1]  = Temp[1]+"B";
          Temp[2]  = Temp[2]+"C";
          Temp[3]  = Temp[3]+"D"; 
          Serial.print("ADDING COMPLETED | ");
          Serial.println(Temp[0]+","+Temp[1]+","+Temp[2]+","+Temp[3]);
          addChar = false;
          }    
          //กรณีทุกตัวหน้าเดียวกันหมด
          if(Temp[0].charAt(0)==Temp[1].charAt(0) && Temp[0].charAt(0)==Temp[2].charAt(0) && Temp[0].charAt(0)==Temp[3].charAt(0)){
            int Max0 = max(Temp[0].substring(1,3).toInt(),Temp[1].substring(1,3).toInt());
            int Max1 = max(Temp[2].substring(1,3).toInt(),Temp[3].substring(1,3).toInt());  
            if(Max0 > Max1){
              Max = Max0;
            }else{
              Max = Max1;
            }          
            for(int i=0 ;i<=3 ;i++){
              if(Temp[i].substring(1,3).toInt() == Max){
                // Serial.println(Temp[i]); //H05C
                 if(Temp[i].charAt(3) == 'A'){
                  for(int j=0; j<=3 ; j++){
                    Keep_A[j] = Temp[i]; //เอาทุกตัวไปใส่ 
                  }
                  Win = "A";
                  Test2  = 1;  
                   break;
                 }
                 else if(Temp[i].charAt(3) == 'B'){
                  for(int j=0; j<=3 ; j++){
                    Keep_B[j] = Temp[i]; //เอาทุกตัวไปใส่   
                    
                  }       
                   Win = "B";
                   Test2  = 2;  
                   break;
                 }
                 else if(Temp[i].charAt(3) == 'C'){
                  for(int j=0; j<=3 ; j++){
                    Keep_C[j] = Temp[i]; //เอาทุกตัวไปใส่   
                  }
                   Win = "C";
                   Test2  = 3;  
                  break;
                 }
                 else if(Temp[i].charAt(3) == 'D'){
                  for(int j=0; j<=3 ; j++){
                    Keep_D[j] = Temp[i]; //เอาทุกตัวไปใส่   
                  }
                   Win = 'D';
                   Test2  = 4;  
                   break;
                 }                
              }
            }
            while(Kc == 1){
              Serial.println("THIS TURN ["+Win+"] IS WINNER"); 
              Kc++;
            }     
          }else { //ไม่หน้าเดียวกันหมด
            for(int i=0;i<=3;i++){
              if(Temp[i].charAt(0) == biddingChar){
                newTemp[m] = Temp[i];
                m++;  
              }
            }
            if(m==1){ //H05C newTemp[0]; //มีทรัมป์ตัวเดียว
              for(int i=0; i<=3 ; i++){
                if(Temp[i].charAt(3) == 'A'){
                  for(int j=0; j<=3 ; j++){
                    Keep_A[j] = Temp[i]; //เอาทุกตัวไปใส่   
                  }
                  Win = 'A';
                  Test2  = 1;  
                 }
                 else if(Temp[i].charAt(3) == 'B'){
                  for(int j=0; j<=3 ; j++){
                    Keep_B[j] = Temp[i]; //เอาทุกตัวไปใส่   
                  }
                  Win = 'B';
                  Test2  = 2;  
                 }
                 else if(Temp[i].charAt(3) == 'C'){
                  for(int j=0; j<=3 ; j++){
                    Keep_C[j] = Temp[i]; //เอาทุกตัวไปใส่   
                  }
                  Win = 'C';
                  Test2  = 3;  
                 }
                 else if(Temp[i].charAt(3) == 'D'){
                  for(int j=0; j<=3 ; j++){
                    Keep_D[j] = Temp[i]; //เอาทุกตัวไปใส่   
                  }
                  Win = 'D';
                  Test2  = 4;  
                 }
                }
              while(Kc == 1){
                Serial.println("THIS TURN ["+Win+"] IS WINNER"); 
              Kc++;
              }     
            }
            else if(m==2){ // ทรัมป์ 2 ตัว H09A H14B
              Max = max(Temp[0].substring(1,3).toInt(),Temp[1].substring(1,3).toInt()); 
              for(int i=0 ;i<=3 ;i++){
                if(Temp[i].substring(1,3).toInt() == Max){
                  //Serial.println(Temp[i]); //H05C
                  if(Temp[i].charAt(3) == 'A'){
                    for(int j=0; j<=3 ; j++){
                      Keep_A[j] = Temp[i]; //เอาทุกตัวไปใส่   
                    }
                   Win = "A";
                   Test2  = 1;  
                 }
                 else if(Temp[i].charAt(3) == 'B'){
                  for(int j=0; j<=3 ; j++){
                    Keep_B[j] = Temp[i]; //เอาทุกตัวไปใส่   
                  }
                   Win = "B";
                   Test2  = 2;  
                 }
                 else if(Temp[i].charAt(3) == 'C'){
                  for(int j=0; j<=3 ; j++){
                    Keep_C[j] = Temp[i]; //เอาทุกตัวไปใส่   
                  }
                   Win = "C";
                   Test2  = 3;  
                 }
                 else if(Temp[i].charAt(3) == 'D'){
                  for(int j=0; j<=3 ; j++){
                    Keep_D[j] = Temp[i]; //เอาทุกตัวไปใส่   
                  }
                  Win = "D";
                  Test2  = 4;  
                 }                
              }
            }
            while(Kc == 1){
              Serial.println("THIS TURN ["+Win+"] IS WINNER"); 
              Kc++;
            }
            }
            else if(m==3){  // 3 ตัว H09A H14B H08C
              int Max0 = max(Temp[0].substring(1,3).toInt(),Temp[1].substring(1,3).toInt()); 
              if(Max0 > Temp[2].substring(1,3).toInt()){
                Max = Max0;
              }else{
                Max = Temp[2].substring(1,3).toInt();
              }
              for(int i=0 ;i<=3 ;i++){
                if(Temp[i].substring(1,3).toInt() == Max){
                 // Serial.println(Temp[i]); //H05C
                  if(Temp[i].charAt(3) == 'A'){
                    for(int j=0; j<=3 ; j++){
                      Keep_A[j] = Temp[i]; //เอาทุกตัวไปใส่   
                    }
                   Win = "A";
                   Test2  = 1;  
                 }
                 else if(Temp[i].charAt(3) == 'B'){
                  for(int j=0; j<=3 ; j++){
                    Keep_B[j] = Temp[i]; //เอาทุกตัวไปใส่   
                  }
                   Win = "B";
                   Test2  = 2;  
                 }
                 else if(Temp[i].charAt(3) == 'C'){
                  for(int j=0; j<=3 ; j++){
                    Keep_C[j] = Temp[i]; //เอาทุกตัวไปใส่   
                  }
                     Win = "C";
                     Test2  = 3;  
                 }
                 else if(Temp[i].charAt(3) == 'D'){
                  for(int j=0; j<=3 ; j++){
                    Keep_D[j] = Temp[i]; //เอาทุกตัวไปใส่   
                  }
                   Win = "D";
                   Test2  = 4;  
                 }                
              }
            }
             while(Kc == 1){
                Serial.println("THIS TURN ["+Win+"] IS WINNER"); 
              Kc++;
            } 
            }
            
          }
      }
      
      if(Test1 == 3){ 
          Serial.println(".......................................................");
          if(Test2 == 1){
             Serial.println("");
            Serial.println("....................PLAYING STATE.....................");
            Serial.println("Turn " + String(Test2) + " you start placing the card");
          }else{
             Serial.println("Turn " + String(Test2) + " placing the card."); //2-4
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
          //เช็คจากคนแรกที่ลง
          for(int i=0;i<=12;i++){ 
              if (Win == "A"){
                 tempA[i] = A[i]; 
              }
              else if(A[i].charAt(0) == Temp[0].charAt(0) && Win != "A"){ //Temp[0] = A ที่เลือกลง //กรณีที่ในมือมีไพ่หน้าเดียวกับคนแรกที่ลง
                   tempA[j] = A[i]; //tempB ที่เก็บข้อมูลชั่วคราว
                   j++; //บอกว่ามีกี่ใบที่ลงได้
              } 
              else if( i == 12 && j == 0){
                //กรณีไม่มีไพ่ที่สามารถลงได้ตามทรัมป์จาก Temp[0] สามารถลงอะไรก็ได้ // กรณีนี้ j=0;
                tempA[i] = A[i]; 
              }
            }
            printArray(tempA,12);
         }
         if(Test2 == 2){
         //เช็คจากคนแรกที่ลง
          for(int i=0;i<=12;i++){ 
              if (Win == "B"){
                 tempB[i] = B[i]; 
              }
              else if(B[i].charAt(0) == Temp[0].charAt(0) && Win != "B"){ //Temp[0] = A ที่เลือกลง //กรณีที่ในมือมีไพ่หน้าเดียวกับคนแรกที่ลง
                   tempB[j] = B[i]; //tempB ที่เก็บข้อมูลชั่วคราว
                   j++; //บอกว่ามีกี่ใบที่ลงได้
              } 
              else if( i == 12 && j == 0){
                //กรณีไม่มีไพ่ที่สามารถลงได้ตามทรัมป์จาก Temp[0] สามารถลงอะไรก็ได้ // กรณีนี้ j=0;
                tempB[i] = B[i]; 
              }
            }
            printArray(tempB,12);
          }
          
          if(Test2 == 3){
           //เช็คจากคนแรกที่ลง
            for(int i=0;i<=12;i++){
               if (Win == "C"){
                 tempC[i] = C[i]; 
              }
              //กรณีที่ในมือมีไพ่หน้าเดียวกับคนแรกที่ลง
              else if(C[i].charAt(0) == Temp[0].charAt(0) && Win != "C"){
                tempC[j] = C[i]; //tempC ที่เก็บข้อมูลชั่วคราว
                 j++; //บอกว่ามีกี่ใบที่ลงได้
            }else if( i == 12 && j == 0){
                //กรณีไม่มีไพ่ที่สามารถลงได้ตามทรัมป์จาก Temp[0] สามารถลงอะไรก็ได้ // กรณีนี้ j=0;
                tempC[i] = C[i]; 
              }
          }
          printArray(tempC,12);
          }
          
          if(Test2 == 4){
            //เช็คจากคนแรกที่ลง
            for(int i=0;i<=12;i++){ 
               if (Win == "D"){
                 tempD[i] = D[i]; 
              }
              //กรณีที่ในมือมีไพ่หน้าเดียวกับคนแรกที่ลง
              if(D[i].charAt(0) == Temp[0].charAt(0) && Win != "D"){
                tempD[j] = D[i]; //tempD ที่เก็บข้อมูลชั่วคราว
                j++; //บอกว่ามีกี่ใบที่ลงได้
              }else if( i == 12 && j == 0){
                //กรณีไม่มีไพ่ที่สามารถลงได้ตามทรัมป์จาก Temp[0] สามารถลงอะไรก็ได้ // กรณีนี้ j=0;
                tempD[i] = D[i]; 
              }
            }
            printArray(tempD,12);
          }
          Serial.print("Placing the card : ");
          Test1 = 1;     
          Test2++;   
      } 
}


void bidding(){
  //ฟังก์ชันประมูล
  //รับค่ามาจากหน้าเว็บ --> MongoDB --> Arduino นำมาเก็บค่าไว้ในตัวแปร
  
}
void deleteElement(String arr[], int n, String x) 
{ 
   // Search x in array 
   int i; 
   for (i=0; i<n; i++){ 
      if (arr[i] == x) {
         break; }
   }
   // If x found in array 
   if (i < n) 
   { 
     // reduce size of array and move all 
     // elements on space ahead 
    // n = n - 1; 
     for (int j=i; j<n; j++) {
        arr[j] = arr[j+1]; }
   } 
} 
void printArray(String Arr[],int size){
  for(int i=0;i<=size;i++){
    Serial.print(Arr[i]); 
    Serial.print(" ");
  }
    Serial.println();
}
void reSet(){

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
  

#include <SPI.h>
#include <RFID.h>
RFID rfid(10,9); // SS veya SDA pini,RST pini

void setup() {
  SPI.begin(); // SPI haberleşme başlatıldı.
  rfid.init(); // kart okumaya hazır.
  pinMode(2,OUTPUT); // yeşil led bağlantısı.
  pinMode(3,OUTPUT); // kırmızı led bağlantısı.
}
// yetki verdiğimiz kart numarasını aşağıdaki alana girin.
byte kartim[5]={0x29, 0x61, 0x16, 0xBA, 0xE4};
void loop() {
  bool gecerliKart=true; // başlangıçta geçerliKart bilgisi "true" olarak kabul ediliyor.
  if(rfid.isCard()) // yeni kart okunduysa
  {
    if(rfid.readCardSerial())
    {
      Serial.print("Kart ID: ");
      Serial.print(rfid.serNum[0],HEX);
      Serial.print(rfid.serNum[1],HEX);
      Serial.print(rfid.serNum[2],HEX);
      Serial.print(rfid.serNum[3],HEX);
      Serial.println(rfid.serNum[4],HEX);
    }
    for(int i=0;i<5;i++){
      if(rfid.serNum[i] != kartim[i]) // sisteme kayıtlı kart ile okunan kart karşılaştırılıyor.
      {
        gecerliKart=false; //kart farklı ise geçerliKart değişkeni "false" yapılıyor.
      }
    }
    if(gecerliKart==true) // eğer geçerli kart ise
    {
      digitalWrite(2,HIGH); // yeşil ledi yak
      dely(2000);
      digitalWrite(2,LOW); // yeşil ledi söndür
    }
    else // eğer geçerliKart değil ise
    {
      digitalWrite(3,HIGH); // kırmızı ledi yak
      delay(2000);
      digitalWrite(3,LOW); // kırmızı ledi söndür
    }
    rfid.halt();
  }
}

int detik = 23;
int menit = 59;
int jam = 0;

int tanggal=17;
int bulan =7;
int tahun = 19;

void setup() {
  Serial.begin(9600);

}

void loop() {
  //Mengubah angka menjadi huruf 3 digit

  int m ;

  detik++;
  if (detik>59){
    menit++;
    detik=0;
    if(menit>59){
      jam++;
      menit=0;
      if (jam>23){
        jam=0;
      }
    }
  }
  char buffS[30];
  m = sprintf(buffS , "Time:%02d/%02d/20%02d %02d:%02d:%02d" ,tanggal,bulan,tahun, jam, menit, detik);
  Serial.println(buffS);
  delay(1000);

}

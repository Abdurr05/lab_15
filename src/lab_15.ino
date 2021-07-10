SYSTEM_MODE(MANUAL);
SYSTEM_THREAD(ENABLED);

os_thread_t thread1;
os_thread_t thread2;
os_thread_t thread3;

int b = 0;

// print a random number in serial port every second
void myThread1(void *args) {
  while (1) {
    int a = rand();
    WITH_LOCK(Serial) {
      Serial.println(a);
    }
    delay(1000);
  }
}

// increment a number and print it in serial port every half a second
void myThread2(void *args) {
  while (1) {
    b = b+1;
    WITH_LOCK(Serial) {
      Serial.println(b);
    }
    delay(500);
  }
}

// flash an led four times every second
void myThread3(void *args) {
  while (1) {
    digitalWrite(D7,HIGH);
    delay(125);
    digitalWrite(D7,LOW);
    delay(125);
  }
}
// setup() runs once, when the device is first turned on.
void setup() {
  pinMode(D7,OUTPUT);
  Serial.begin(9600);
  while(!Serial.isConnected());
  // Put initialization like pinMode and begin functions here.
  os_thread_create(&thread1, "anyName", OS_THREAD_PRIORITY_DEFAULT, myThread1, NULL, 1024);
  os_thread_create(&thread2, "anyName", OS_THREAD_PRIORITY_DEFAULT, myThread2, NULL, 1024);
  os_thread_create(&thread3, "anyName", OS_THREAD_PRIORITY_DEFAULT, myThread3, NULL, 1024);
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  // The core of your code will likely live here.

}
#define DAC_PIN_FIR 25 // define pin ?? as the DAC analog output
#define ADC_PIN 34 // define pin ?? as the ADC analog input
#define DAC_PIN_IIR 26
float x[21] = {0}; // input values
float y_FIR; // output values
float z[21] = {0}; // output valuesv  
float coef_FIR[]= {0.00178205 ,0.00602911 ,0.01906286 ,0.04458056 ,0.08060471 ,0.11910949
                    ,0.14882606 ,0.16001032 ,0.14882606 ,0.11910949 ,0.08060471 ,0.04458056
                    ,0.01906286 ,0.00602911 ,0.00178205};
float x_IIR [] = {0.08612656, 0.25837967, 0.25837967, 0.08612656};
float z_IIR [] = {0,-0.51993154, 0.24279083, -0.03384683};
float temp_now;
float temp_then;
int fs = 1500;//hz

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(DAC_PIN_FIR, OUTPUT);
  pinMode(DAC_PIN_IIR, OUTPUT);
}

void loop() {
  temp_now = micros();
  if(((temp_now - temp_then)/1000000) >= (1/fs))
  {
    x[0] = (float) analogRead(ADC_PIN) * 3.3 / 4096.0;
    for(int i=0;i<16;i++)
    {
      y_FIR += coef_FIR[i]*x[i];
    }
    for(int i=0;i<4;i++)
    {
      z[0] += x_IIR[i]*x[i] - z_IIR[i]*z[i];
    }

    Serial.print(x[0]);
    Serial.print(" ");
    Serial.print(y_FIR);
    Serial.print(" ");
    Serial.println(z[0]);

    int dacVoltage_FIR = (int)(y_FIR*4096.0/3.3);
    int dacVoltage_IIR = (int)(z[0]*4096.0/3.3);
    analogWrite(DAC_PIN_FIR,dacVoltage_FIR);
    analogWrite(DAC_PIN_IIR,dacVoltage_IIR);

    // update x and y data vectors
    for(int i = 0; i < 9; i++){
      //entradas
      x[i+1] = x[i]; 
      //saidas
      z[i+1] = z[i]; 
    }
    z[0] = 0;
    y_FIR=0;
    temp_then = micros();
  }
}



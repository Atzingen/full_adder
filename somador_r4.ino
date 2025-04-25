#include "Arduino_LED_Matrix.h"

ArduinoLEDMatrix matrix;
bool bin_a[4], bin_b[4], resposta[5];
const int gpioPins[5] = {2, 3, 4, 5, 6};
uint8_t frame[8][12] = {0};

void setup() {
  Serial.begin(9600);
  matrix.begin();
  for (int i = 0; i < 5; i++) {
    pinMode(gpioPins[i], OUTPUT);
    digitalWrite(gpioPins[i], LOW);
  }
}

void displayLine(int line, bool data[], int size) {
  for (int i = 0; i < size; i++) {
    frame[line][i] = data[size - 1 - i];
  }
  matrix.renderBitmap(frame, 8, 12);
}

void loop() {
  if (Serial.available()) {
    String entrada = Serial.readStringUntil('\n');

    if (entrada.length() == 10 && entrada.charAt(0) == 'A' && entrada.charAt(5) == 'B') {
      bool valido = true;

      for (int i = 0; i < 4; i++) {
        if ((entrada.charAt(i+1) != '0' && entrada.charAt(i+1) != '1') || 
            (entrada.charAt(i+6) != '0' && entrada.charAt(i+6) != '1')) {
          valido = false;
          break;
        }
        bin_a[3 - i] = (entrada.charAt(i+1) == '1');
        bin_b[3 - i] = (entrada.charAt(i+6) == '1');
      }

      if (valido) {
        bool carry = 0;
        for (int i = 0; i < 4; i++) {
          bool xor1 = bin_a[i] ^ bin_b[i];
          bool xor2 = xor1 ^ carry;
          bool and1 = bin_a[i] & bin_b[i];
          bool and2 = xor1 & carry;
          carry = and1 | and2;
          resposta[i] = xor2;
        }
        resposta[4] = carry;

        for (int i = 0; i < 5; i++) {
          digitalWrite(gpioPins[i], resposta[4 - i]);
        }

        matrix.clear();
        displayLine(0, bin_a, 4);  // Linha A
        displayLine(1, bin_b, 4);  // Linha B
        displayLine(2, resposta, 5);  // Linha Resultado

        Serial.print("Resultado: ");
        for (int i = 4; i >= 0; i--) {
          Serial.print(resposta[i]);
        }
        Serial.println();

      } else {
        Serial.println("Entrada invalida!");
      }
    } else {
      Serial.println("Formato invalido! Use: AxxxxByyyy");
    }
  }
}

// Implementação do somador binário usando Arduino

bool bin_a[4], bin_b[4], resposta[5];
const int gpioPins[5] = {2, 3, 4, 5, 6}; // GPIOs onde o resultado será exibido (carry + 4 bits)

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 5; i++) {
    pinMode(gpioPins[i], OUTPUT);
    digitalWrite(gpioPins[i], LOW);
  }
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
        // Cálculo do somador completo
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

        // Escreve nos GPIOs (carry no gpioPins[0])
        for (int i = 0; i < 5; i++) {
          digitalWrite(gpioPins[i], resposta[4 - i]);
        }

        // Retorno no Serial Monitor
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

# Somador Binário de 4 Bits com Somador Completo

Este projeto implementa um somador binário de 4 bits em Python, utilizando a lógica de um **somador completo** (full adder). É uma simulação de como o hardware realiza a adição de números binários.

---

## 💡 Visão Geral

O **somador completo** é um circuito lógico que soma dois bits e um bit de "carry-in", produzindo um bit de **soma** e um bit de **carry-out**. Esta implementação simula esse comportamento digital.

---

## 📥 Entradas

- Dois números binários de 4 bits fornecidos como `strings`:
  - Exemplo: `numero_a = "1010"`, `numero_b = "0111"`
- O programa valida se os números são binários válidos (`0` ou `1`).

---

## ⚙️ Lógica do Somador Completo

A lógica do somador completo é implementada para cada posição de bit (do menos significativo ao mais significativo):

```
Para cada bit i:
  xor1 = bin_a[i] XOR bin_b[i]
  xor2 = xor1 XOR carry
  and1 = bin_a[i] AND bin_b[i]
  and2 = xor1 AND carry
  or   = and1 OR and2

  carry = or
  resposta[i] = xor2
```

- `xor1`: soma intermediária entre os bits
- `xor2`: soma final com o carry anterior
- `and1`, `and2`, `or`: cálculo do novo carry
- `carry`: armazenado para uso no próximo bit
- `resposta[4]`: armazena o carry final (bit mais significativo)

---

## 🔌 Equivalente em Portas Lógicas

A implementação simula diretamente o comportamento físico de um somador completo:

| Função Lógica | Operação |
|---------------|-----------|
| XOR           | Soma parcial (^) |
| AND           | Geração de carry (&) |
| OR            | Combinação de carry (/) |

---

## 🧾 Saída

- O resultado é impresso como um número binário de 5 bits (carry final + 4 bits da soma), do **bit mais significativo** ao **menos significativo**.

---

## 🧪 Exemplo

```text
Entrada:
  numero_a = "1010"
  numero_b = "0111"

Saída:
  Soma Binária: 10001
```

---

## 💻 Código Python

```python
def validar_binario(numero):
    return len(numero) == 4 and all(c in '01' for c in numero)

def entrada_valida(mensagem):
    while True:
        entrada = input(mensagem)
        if validar_binario(entrada):
            return entrada
        print("Entrada inválida. Digite um número binário de 4 bits.")

numero_a = entrada_valida("Digite o primeiro número binário (4 bits): ")
numero_b = entrada_valida("Digite o segundo número binário (4 bits): ")

# Converte os números binários em listas de booleanos invertidas (LSB -> MSB)
bin_a = [int(bit) for bit in reversed(numero_a)]
bin_b = [int(bit) for bit in reversed(numero_b)]

resposta = [0] * 5
carry = 0

for i in range(4):
    xor1 = bin_a[i] ^ bin_b[i]
    xor2 = xor1 ^ carry
    and1 = bin_a[i] & bin_b[i]
    and2 = xor1 & carry
    carry = and1 | and2
    resposta[i] = xor2

resposta[4] = carry

# Imprime o resultado do bit mais significativo para o menos significativo
print("Soma Binária:", ''.join(str(bit) for bit in reversed(resposta)))
```

---

## 📚 Referências

- [YouTube: Full Adder Logic](https://www.youtube.com/watch?v=wvJc9CZcvBc)
- [Wikipedia: Adder (electronics)](https://en-m-wikipedia-org.translate.goog/wiki/Adder_(electronics)?_x_tr_sl=en&_x_tr_tl=pt&_x_tr_hl=pt&_x_tr_pto=tc)

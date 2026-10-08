# 🚧 Barreira Automática para Garagem com Arduino

Projeto desenvolvido para simular uma **barreira automática de garagem** utilizando Arduino, sensor ultrassônico, servomotor, LED e buzzer.

A ideia é simples: quando um veículo (ou qualquer objeto) se aproxima da barreira, o sensor percebe a presença, o Arduino manda o servo abrir a cancela e o sistema emite um sinal sonoro. Depois que o objeto se afasta, a barreira espera alguns segundos e fecha automaticamente.

O projeto foi pensado como uma forma prática de trabalhar com **sensores, atuadores e lógica de programação no Arduino**, simulando uma situação que poderia ser encontrada em um estacionamento ou entrada de garagem.

## 🎯 Objetivo

O objetivo principal é automatizar a abertura e o fechamento de uma pequena barreira.

O funcionamento acontece da seguinte forma:

1. O sensor ultrassônico verifica constantemente a distância até o objeto.
2. Quando algo é detectado a **15 cm ou menos**, a barreira é aberta.
3. O LED acende para indicar que a barreira está aberta.
4. O buzzer emite um sinal sonoro.
5. Quando o objeto deixa a área de detecção, o sistema aguarda aproximadamente **1,5 segundo**.
6. Depois desse tempo, a barreira fecha e o LED é desligado.

## 🧰 Componentes utilizados

- Arduino Uno
- Sensor ultrassônico HC-SR04
- Servomotor
- LED
- Buzzer
- Protoboard
- Cabos jumper
- Resistor para o LED

## 🔌 Ligações

As ligações utilizadas pelo código são:

| Componente | Pino do Arduino |
|---|---:|
| TRIG do HC-SR04 | 7 |
| ECHO do HC-SR04 | 6 |
| Servomotor | 9 |
| LED | 10 |
| Buzzer | A5 |

> **Observação:** o código foi desenvolvido considerando exatamente esses pinos. Caso o circuito seja montado com os componentes em outros pinos, será necessário alterar as constantes no início do código.

## ⚙️ Como funciona

O coração do projeto é o **sensor ultrassônico HC-SR04**.

O Arduino envia um pequeno pulso pelo pino `TRIG`. O sensor então emite uma onda ultrassônica e espera o retorno desse sinal pelo pino `ECHO`.

A partir do tempo que o sinal leva para voltar, o Arduino calcula aproximadamente a distância do objeto.

No código, essa distância é comparada com o limite de **15 cm**:

```cpp
if (distance <= 15) {
    abreCancela();
    buzzerOn();
}
```

Quando essa condição é verdadeira, significa que existe um objeto próximo da barreira. Então o servo é colocado em **90 graus**, representando a posição aberta.

Ao mesmo tempo, o LED é ligado e o buzzer é acionado.

Quando não há mais nenhum objeto dentro da distância definida, o sistema entra na parte responsável pelo fechamento:

```cpp
else {
    buzzerOff();

    if (barreiraAberta) {
        delay(1500);
        fechaCancela();
    }
}
```

Nesse momento, o Arduino espera aproximadamente **1,5 segundo** antes de fechar a barreira.

## 🚦 Estados da barreira

O projeto utiliza a variável:

```cpp
bool barreiraAberta = false;
```

Ela serve para o Arduino saber se a barreira está atualmente aberta ou fechada.

### Barreira fechada

- Servo em `0°`
- LED desligado
- `barreiraAberta = false`

### Barreira aberta

- Servo em `90°`
- LED ligado
- `barreiraAberta = true`
- Buzzer emitindo sinal sonoro durante a detecção

## 🔊 Buzzer

O buzzer é utilizado como uma indicação sonora para complementar o LED.

A função responsável pelo acionamento é:

```cpp
void buzzerOn() {
  tone(pinBuzzer, 1294);
  delay(1000);
  noTone(pinBuzzer);
  delay(1000);
}
```

A frequência utilizada é de **1294 Hz**, aproximadamente correspondente à nota Ré (D4).

O buzzer permanece ligado por cerca de 1 segundo e depois fica desligado por aproximadamente 1 segundo antes de poder ser acionado novamente.

## 🧠 Organização do código

O código foi separado em pequenas funções para deixar a lógica mais fácil de entender e modificar.

### `abreCancela()`

Abre a barreira, acende o LED e registra que ela está aberta.

### `fechaCancela()`

Fecha a barreira, apaga o LED e registra que ela está fechada.

### `buzzerOn()`

Liga o buzzer e produz o sinal sonoro utilizado pelo projeto.

### `buzzerOff()`

Interrompe qualquer som que esteja sendo produzido pelo buzzer.

### `setup()`

É executado uma vez quando o Arduino é ligado. Aqui são configurados os pinos, o servo é conectado e a barreira começa fechada.

### `loop()`

É a parte principal do programa. Ela fica repetindo continuamente:

- mede a distância;
- verifica se existe um objeto próximo;
- abre a barreira quando necessário;
- controla o buzzer;
- aguarda o afastamento;
- fecha a barreira.

## ▶️ Como executar

1. Abra o projeto na **Arduino IDE**.
2. Certifique-se de ter a biblioteca `Servo` disponível.
3. Monte o circuito seguindo os pinos indicados neste README.
4. Conecte o Arduino ao computador.
5. Selecione a placa e a porta COM correta na Arduino IDE.
6. Compile o código.
7. Faça o upload para o Arduino.
8. Aproxime um objeto do sensor e observe a barreira funcionando.

O projeto também pode ser adaptado para simuladores como o **Tinkercad**, permitindo testar a lógica antes de montar o circuito fisicamente.

## 📁 Estrutura do projeto

Uma estrutura simples para organizar os arquivos pode ser:

```text
barreira-automatica/
├── README.md
└── barreira-automatica.ino
```

## 💡 Possíveis melhorias

Apesar de cumprir a proposta, o projeto ainda pode ser evoluído.

Algumas ideias seriam:

- utilizar um sensor adicional para aumentar a segurança;
- impedir que a barreira feche enquanto ainda houver um veículo passando;
- adicionar um botão para abertura manual;
- utilizar RFID para identificar veículos autorizados;
- adicionar um display para mostrar mensagens;
- utilizar um controle remoto para abrir a barreira;
- melhorar o controle do tempo para evitar `delay()` e deixar o sistema mais responsivo.

Também é importante lembrar que o HC-SR04 **não sabe se o objeto detectado é realmente um carro**. Para ele, qualquer objeto dentro dos 15 cm pode provocar a abertura da barreira.

## 📚 Contexto do projeto

Este projeto foi desenvolvido como uma atividade prática de **Introdução ao Hardware**, utilizando Arduino para demonstrar na prática a integração entre um sensor e diferentes atuadores.

A proposta é transformar uma situação cotidiana — a entrada de um veículo em uma garagem — em um pequeno sistema automatizado, permitindo visualizar de forma simples como o Arduino pode receber informações do ambiente, tomar uma decisão e controlar componentes externos.

## 👥 Integrantes

- Gabriel Lunelli
- Eduardo Jean Padilha
- Vandoir Gerhard
- Vinicius Gabriel Flores da Cunha

## 📝 Observação

Este README descreve o funcionamento do código e do circuito utilizado no projeto. Os valores de distância, posição do servo, tempo de espera e frequência do buzzer podem ser modificados diretamente no código para adaptar o comportamento da barreira a diferentes situações.

---

**Projeto acadêmico — Arduino | Barreira Automática para Garagem**

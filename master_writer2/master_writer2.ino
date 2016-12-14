//Uses an arduino leonardo to type random strings into a chat app while turning solenoids 
//on and off to make a life sized alien look like he's typing on a laptop
//2016-2017 part of Alien Afterlife show at Yours Mine and Ours
//jeremy couillard

#include <avr/pgmspace.h>
#include <Keyboard.h>

const byte solenoid1 = 8;
const byte solenoid2 = 9;
const byte OnOffSwitch = 2;

unsigned int typeTime; //how much time between keystrokes
unsigned int delayBetweenTyping; //how much time between sentences

//alien dialogue
const char string_0[] PROGMEM = "At work today we watched a power point on efficiency.";   // Strings to store
const char string_1[] PROGMEM = "I had a dream last night that I was France.";
const char string_2[] PROGMEM = "Excel spreadsheets for kids.";
const char string_3[] PROGMEM = "Do you know how many different shirts have been made since Jefferson was president?";
const char string_4[] PROGMEM = "I hate cleaning cat litter.";
const char string_5[] PROGMEM = "Fifteen holidays about misogyny.";
const char string_6[] PROGMEM = "Lets get high and go to spa castle.";
const char string_7[] PROGMEM = "What does dango mean?";
const char string_8[] PROGMEM = "The ancient tribe of yogurt.";
const char string_9[] PROGMEM = "My bracelet is made out of carboplatin?";
const char string_10[] PROGMEM = "I'll have to check with Tony for that";
const char string_11[] PROGMEM = "Maybe Brenda knows.";
const char string_12[] PROGMEM = "Can we take all human consciousness and cram it into a dandelion?";
const char string_13[] PROGMEM = "Rap battle in the hospital waiting room.";
const char string_14[] PROGMEM = "Costco is having a discount sale on MRI machines and dinosaur bones.";
const char string_15[] PROGMEM = "What are the demographics of the forest elf village";
const char string_16[] PROGMEM = "When I was 7 I dry humped all my stuffed animals.";
const char string_17[] PROGMEM = "Do you want to go to Ikea tomorrow? I need to buy particle board for a physics experiment.";
const char string_18[] PROGMEM = "On Tuesday we have to go to Costco to save the universe.";
const char string_19[] PROGMEM = "I'm microdosing Aquafina.";
const char string_20[] PROGMEM = "At work yesterday we had a meeting with the vice president of the Kali Yuga.";
const char string_21[] PROGMEM = "Why do white people like guitars so much?";
const char string_22[] PROGMEM = "When does a mole decide it’s time to leave home to start his own tunnel?";
const char string_23[] PROGMEM = "Refugee camp by Yves St Laurent.";
const char string_24[] PROGMEM = "What is your art about?";
const char string_25[] PROGMEM = "When you try really hard to not be something you become it.";
const char string_26[] PROGMEM = "My favorite aphorism is the best things happen to those who make the best of what happens.";
const char string_27[] PROGMEM = "The worst definition of art is that it is self expression.";
const char string_28[] PROGMEM = "My favorite art gallery is Hollis Benton in Beverly Hills.";
const char string_29[] PROGMEM = "Sound system under the carbon dioxide clouds of Venus.";
const char string_30[] PROGMEM = "Let's invade the afterlife.";
const char string_31[] PROGMEM = "Part of being human is believing in death.";
const char string_32[] PROGMEM = "Smart cars have formed real estate companies and speculated humans out of their own cities.";
const char string_33[] PROGMEM = "How much did BMW pay you to decorate their car?";
const char string_34[] PROGMEM = "It's been a terrible day.";
const char string_35[] PROGMEM = "My spaceship is a gemzar";

// Then set up a table to refer to your strings.
const char* const string_table[] PROGMEM = {string_0, string_1, string_2, string_3, string_4, string_5, string_6,string_7,string_8,string_9, string_10, string_11, string_12, string_13, string_14, string_15, string_16, string_17, string_18, string_19, string_20, string_21, string_22, string_23, string_24, string_25, string_26, string_27, string_28, string_29, string_30, string_31, string_32, string_33, string_34, string_35};

char buffer[90];    // make sure this is large enough for the largest string it must hold

void setup()
{
  Serial.begin(9600);
  pinMode(OnOffSwitch, INPUT_PULLUP);
  pinMode(solenoid2, OUTPUT);
  pinMode(solenoid1, OUTPUT);
  // randomize
  randomSeed(analogRead(0));
}

void typeTheSentence() {
    
  delayBetweenTyping = random(1000, 2001); //2000, 6001 normally
  
  //pull a sentence from the array
  int randString = random(0, sizeof(string_table) / sizeof(string_table[0]));
  const char * newGuy = strcpy_P(buffer, (char*)pgm_read_word(&(string_table[randString])));
  
  //get the length of the sentence pulled
  int stringSize = strlen(newGuy);
  Keyboard.begin();
  //type out letter by letter
  for (int i = 0; i < stringSize; i++) {
    typeTime = random(20, 201);
    Keyboard.print(newGuy[i]);
    digitalWrite(solenoid1, LOW);
    digitalWrite(solenoid2, HIGH);
    delay(typeTime);
    digitalWrite(solenoid1, HIGH);
    digitalWrite(solenoid2, LOW);
    delay(typeTime);
  }
  //done with that sentence. put hands down and stop typing.
  digitalWrite(solenoid1, LOW);
  digitalWrite(solenoid2, LOW);
  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll();
  Keyboard.end();
  delay(delayBetweenTyping);
}

void loop() {
  if (digitalRead(OnOffSwitch) == HIGH) typeTheSentence();  //do nothing while pin 2 does not go LOW
  delay(30); // wait a bit, not really necessary
}















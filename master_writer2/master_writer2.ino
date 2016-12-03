//test

#include <Keyboard.h>

/****************ALIEN DIALOGUE*****************************/
const char * breakMe[] = {
  "At work today we watched a power point on efficiency.", 
  "I had a dream last night that I was France.", 
  "Excel spreadsheets for kids.",
  "Do you know how many different shirts have been made since Jefferson was president?",
  "I hate cleaning cat litter.",
  "Fifteen holidays about misogyny.",
  "Lets get high and go to spa castle.",
  "What does dango mean?",
  "The ancient tribe of yogurt.",
  "My bracelet is made out of carboplatin?",
  "I’ll have to check with Tony for that.",
  "Maybe Brenda knows.",
  "Can we take all human consciousness and cram it into a dandelion?",
  "Rap battle in the hospital waiting room.",
  "Costco is having a discount sale on MRI machines and dinosaur bones.",
  "What are the demographics of the forest elf village",
  "When I was 7 I dry humped all my stuffed animals.",
  "Do you want to go to Ikea tomorrow? I need to buy particle board for a physics experiment. ",
  "On Tuesday we have to go to Costco to save the universe.",
  "I’m microdosing Aquafina.",
  "At work yesterday we had a meeting with the vice president of the Kali Yuga.",
  “Why do white people like guitars so much?”,
  “When does a mole decide it’s time to leave home to start his own tunnel?”,
  “Refugee camp by Yves St Laurent.”,
   “What is your art about?”,
  “When you try really hard to not be something you become it.”,
  “My favorite aphorism is the best things happen to those who make the best of what happens.”,
  “The worst definition of art is that it is self expression.”,
  “My favorite art gallery is Hollis Benton in Beverly Hills.”,
  “Sound system under the carbon dioxide clouds of Venus.”,
  “Let’s invade the afterlife.”,
  “Part of being human is believing in death.”,
  “Smart cars have formed real estate companies and speculated humans out of their own cities.”,
  “How much did BMW pay you to decorate their car?”
  “It’s been a terrible day.”
  “My spaceship is a gemzar”
  “
  
};
/***************END ALIEN DIALOGUE****************************/


unsigned int typeTime; //how much time between keystrokes
unsigned int delayBetweenTyping; //how much time between sentences


void typeTheSentence() {
  delayBetweenTyping = random(2000, 6001);
  //pull a sentence from the array
  const char * newGuy = breakMe[random(0, sizeof(breakMe) / sizeof(breakMe[0]))];
  //get the length of the sentence pulled
  int stringSize = strlen(newGuy);
  Keyboard.begin();
  //type out letter by letter
  for (int i = 0; i < stringSize; i++) {
    typeTime = random(20, 201);
    Keyboard.print(newGuy[i]);
    digitalWrite(8, LOW);
    digitalWrite(9, HIGH);
    delay(typeTime);
    digitalWrite(8, HIGH);
    digitalWrite(9, LOW);
    delay(typeTime);
  }
  //done with that sentence. put hands down and stop typing.
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll();
  Keyboard.end();
  delay(delayBetweenTyping);
}


void setup() {
  pinMode(2, INPUT_PULLUP);
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
  // randomize
  randomSeed(analogRead(0));
}


void loop() {
  if (digitalRead(2) == LOW) typeTheSentence();  //do nothing while pin 2 does not go LOW
  delay(30); // wait a bit, not really necessary
}


















//Uses an arduino leonardo to type random strings into a chat app while turning solenoids 
//on and off to make a life sized alien look like he's typing on a laptop
//2016-2017 part of Alien Afterlife show at Yours Mine and Ours
//jeremy couillard
//////////////////////////////ALIEN TWO////////////////////////////
#include <avr/pgmspace.h>
#include <Keyboard.h>

const byte solenoid1 = 8;
const byte solenoid2 = 9;
const byte OnOffSwitch = 2;

//const int list[49];

unsigned int typeTime; //how much time between keystrokes
unsigned int delayBetweenTyping; //how much time between sentences

//alien dialogue
const char string_0[] PROGMEM = "Two toucans applying for jobs on Nanortalik island.";   // Strings to store
const char string_1[] PROGMEM = "When I wear a bathrobe I feel like the heroin dealer in Pulp Fiction.";
const char string_2[] PROGMEM = "I saw a picture of myself in Isortoq but I've never been there.";
const char string_3[] PROGMEM = "You are beautiful and I love you.";
const char string_4[] PROGMEM = "Jogging group of anarcho-syndicalists.";
const char string_5[] PROGMEM = "HDMI - Halifax Disco Mountain Ideology";
const char string_6[] PROGMEM = "USB - Uncle Sad Bedroom";
const char string_7[] PROGMEM = "URL - Ulster Regional Lapdance ";
const char string_8[] PROGMEM = "Airport security dancehall reggae every Thursday at 5.";
const char string_9[] PROGMEM = "The grass is always greener on Kepler 186-f";
const char string_10[] PROGMEM = "Let's get hi and play putt putt golf.";
const char string_11[] PROGMEM = "What does sudo apt-get mean?";
const char string_12[] PROGMEM = "Rap battle at the car dealership.";
const char string_13[] PROGMEM = "When I was 8 I thought I could control my dog with my mind.";
const char string_14[] PROGMEM = "When I finished off-gassing my girlfriend bought me a new shirt.";
const char string_15[] PROGMEM = "I have a netflix account for my dreams.";
const char string_16[] PROGMEM = "Did New Amsterdam have a baseball team?";
const char string_17[] PROGMEM = "My press release is the Sonian Forest.";
const char string_18[] PROGMEM = "I’ll write you a check for five hundred elephants.";
const char string_19[] PROGMEM = "I had a dream last night that I was Costco.";
const char string_20[] PROGMEM = "My drug dealer sleeps at Ikea.";
const char string_21[] PROGMEM = "What do you want for dinner?";
const char string_22[] PROGMEM = "My fantasy breakfast is a Ferrari.";
const char string_23[] PROGMEM = "I’m trying to get our company a grant for a new jet ski";
const char string_24[] PROGMEM = "My cat’s mom is an asshole.";
const char string_25[] PROGMEM = "The war is over and wasn’t worth it at all.";
const char string_26[] PROGMEM = "Poland Springs is mind control water given to us by aliens so we mine gold for them.";
const char string_27[] PROGMEM = "I guess the Great Gatsby really wasn’t great and just a metaphor for dickheads.";
const char string_28[] PROGMEM = "When we were 16 we invaded the dreams of babies.";
const char string_29[] PROGMEM = "Robert wore 15 collared shirts at once to a dance.";
const char string_30[] PROGMEM = "I think Sam knows how to do that.";
const char string_31[] PROGMEM = "Do you have any environmentally friendly cleaners?";
const char string_32[] PROGMEM = "I don’t recycle but my shoes are morally ok.";
const char string_33[] PROGMEM = "500 years ago I was an advertising executive on the edge of the galaxy.";
const char string_34[] PROGMEM = "My landlord is a lizard dedicated to the destruction of everything I cherish.";
const char string_35[] PROGMEM = "For 10 dollars I will draw you a picture of a cactus.";
const char string_36[] PROGMEM = "I just finished Moby Dick. It was ok.";
const char string_37[] PROGMEM = "Dandelion mansions and pineapple pudding. Metallic peacocks and neon watering juggs.";
const char string_38[] PROGMEM = "My computer wrote an algorithm for peyote and became a smart car.";
const char string_39[] PROGMEM = "A bird that farts pastel lasers into space.";
const char string_40[] PROGMEM = "4,939,230 ants coming together to create an image of a formula for infinite energy.";
const char string_41[] PROGMEM = "The medium is the massage parlors.";
const char string_42[] PROGMEM = "I got my black belt in the dojo next to the dollar store.";
const char string_43[] PROGMEM = "Does your dad know you smoke?";
const char string_44[] PROGMEM = "If you don’t update your software a black hole will consume five million civilizations.";
const char string_45[] PROGMEM = "300 kittens in an art gallery pooping and peeing all over each other.";
const char string_46[] PROGMEM = "My least favorite thing is washing dishes.";
const char string_47[] PROGMEM = "A chair and a television and a video game.";
const char string_48[] PROGMEM = "Two cats smoking crack and talking politics.";
const char string_49[] PROGMEM = "Buddha and Jesus and Hitler french kissing while watching Star Wars.";

// Then set up a table to refer to your strings.
const char* const string_table[] PROGMEM = {string_0, string_1, string_2, string_3, string_4, string_5, string_6, string_7, string_8, string_9, string_10, string_11, string_12, string_13, string_14, string_15, string_16, string_17, string_18, string_19, string_20, string_21, string_22, string_23, string_24, string_25, string_26, string_27, string_28, string_29, string_30, string_31, string_32, string_33, string_34, string_35, string_36, string_37, string_38, string_39, string_40, string_41, string_42, string_43, string_44, string_45, string_46, string_47, string_48, string_49};
char buffer[95];    // make sure this is large enough for the largest string it must hold

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
  
//make an ordered list
int list[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49};
//and then shuffle it
  for (int a = 0; a < 49; a++){
    int r = random(a, 49);
    int temp = list[a];
    list[a] = list[r];
    list[r] = temp;
    }
//pull from the list in the order      
  for (int i = 0; i < 49; i++){
    const char * newGuy = strcpy_P(buffer, (char*)pgm_read_word(&(string_table[list[i]])));
  
    //get the length of the sentence pulled
    int stringSize = strlen(newGuy);
     Keyboard.begin();
    //type out letter by letter
      for (int i2 = 0; i2 < stringSize; i2++) {
        typeTime = random(20, 201);
        Keyboard.print(newGuy[i2]);
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
    
     //if off switch is hit break the list loop 
     if (digitalRead(OnOffSwitch) == HIGH){
      break; 
    }
  } //end for loop of list
 
 
} //end function


void loop() {
  if (digitalRead(OnOffSwitch) == LOW) { //do nothing while pin 2 does not go LOW
    typeTheSentence();  
  }
  delay(30); // wait a bit, not really necessary
}

const int countNote = 11;
int toneCounter = 0;

class note
{
  public: 
    int mgc;
    bool active;

    note()
    {
      active = false;
    }
    
    note(int Mgc)
    {
      mgc = Mgc;
      active = false;
    }
};

note h[countNote];
int help = 0;

void setup()
{  
  for (int i = 2; i < 13; i++)
    pinMode(i, INPUT_PULLUP);

  for (int i = 0; i < countNote; i++)
  {
    h[i] = note(300 + (100 * (i + 1)));  
    help += h[i].mgc;
  }     

  pinMode(13, OUTPUT);

  Serial.begin(9600);             
}

void loop()
{
  for (int i = 2; i < 13; i++)
  {
    if (digitalRead(i) == 0 && h[i - 2].active == false)
    {
      h[i - 2].active = true;
      toneCounter += h[i - 2].mgc;
      tone (countNote + 2, toneCounter); 
      Serial.print("Pressed D"); Serial.print(i); Serial.print(" Tone Counter "); Serial.print(toneCounter); Serial.print(" Tone "); Serial.println(h[i - 2].mgc);

      analogWrite(A4, 250); 
    }
    else if(digitalRead(i) != 0 && h[i - 2].active == true)
    {
      h[i - 2].active = false;
      toneCounter -= h[i - 2].mgc;
      if (toneCounter == 0)
      {
        noTone(countNote + 2);
        analogWrite(A4, 0); 
      }      
      else
        tone (countNote + 2, toneCounter); 
      Serial.print("UPressed D"); Serial.println(i);     
    }
  } 
}

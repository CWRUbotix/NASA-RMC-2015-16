


void setup() {

  Serial.begin(9600);

  //Right
  pinMode(22, INPUT); //Back wheel angle limit switch        Brown
  pinMode(24, INPUT); //Back wheel straight limit switch     Red
  pinMode(26, INPUT); //Arm storing position limit switch    Orange
  pinMode(28, INPUT); //Arm hard stop limit switch           Pink
  pinMode(30, INPUT); //Arm translational angle limit switch Yellow
  pinMode(32, INPUT); //Front wheel angle limit switch       Blue
  pinMode(34, INPUT); //Front wheel straight limit switch    Purple

  //Left
  pinMode(23, INPUT); //Back wheel angle limit switch
  pinMode(25, INPUT); //Back wheel straight limit switch
  pinMode(27, INPUT); //Arm sotring position limit switch
  pinMode(29, INPUT); //Arm hard stop limit switch
  pinMode(31, INPUT); //Arm translational angle limit switch
  pinMode(33, INPUT); //Front wheel angle limit switch
  pinMode(35, INPUT); //Front wheel straight limit switch

}

void loop() {

  //Right
  Serial.println("Right:");
  Serial.print("Back wheel angle limit switch: ");
  Serial.println(digitalRead(22));
  Serial.print("Back wheel straight limit switch: ");
  Serial.println(digitalRead(24));
  Serial.print("Arm soring position limit switch: ");
  Serial.println(digitalRead(26));
  Serial.print("Arm hard stop limit switch: ");
  Serial.println(digitalRead(28));
  Serial.print("Arm translational angle limit switch: ");
  Serial.println(digitalRead(30));
  Serial.print("Front wheel angle limit switch: ");
  Serial.println(digitalRead(32));
  Serial.print("Front wheel straight limit switch: ");
  Serial.println(digitalRead(34));

  Serial.println();
  //Left
  Serial.println("Left:");
  Serial.print("Back wheel angle limit switch: ");
  Serial.println(digitalRead(23));
  Serial.print("Back wheel straight limit switch: ");
  Serial.println(digitalRead(25));
  Serial.print("Arm soring position limit switch: ");
  Serial.println(digitalRead(27));
  Serial.print("Arm hard stop limit switch: ");
  Serial.println(digitalRead(29));
  Serial.print("Arm translational angle limit switch: ");
  Serial.println(digitalRead(31));
  Serial.print("Front wheel angle limit switch: ");
  Serial.println(digitalRead(33));
  Serial.print("Front wheel straight limit switch: ");
  Serial.println(digitalRead(35));

  Serial.println();
  Serial.println();
  delay(1000);

}



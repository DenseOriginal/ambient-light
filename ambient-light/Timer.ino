unsigned long endTime = 0;

void setupTimer() {

}

void updateTimer() {
  if (endTime == 0) return;
  
  if (millis() > endTime) {
    onTimerEnd();
    Serial.println("[Timer] END");
    endTime = 0;
  }
}

void startTimer(unsigned long durationSeconds) {  
  if (durationSeconds <= 0) return;
  if (durationSeconds > 10000) return; // Something might be wrong if the durationSeconds is that great lol
  endTime = millis() + (durationSeconds * 1000);
  Serial.print("[Timer] millis() = ");
  Serial.println(millis());
  Serial.print("[Timer] endTime = ");
  Serial.println(endTime);
  Serial.print("[Timer] durationSeconds = ");
  Serial.println(durationSeconds);
  Serial.print("[Timer] durationSeconds * 1000 = ");
  Serial.println(durationSeconds * 1000);
}

void stopTimer() {
  endTime = 0;
}
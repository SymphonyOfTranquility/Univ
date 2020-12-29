public class Results {
  public String schedulingType;
  public String schedulingName;
  public int compuTime;
  public int idleCounter;
  public int timeInIdle;

  public Results (String schedulingType, String schedulingName, int compuTime, int idleCounter, int timeInIdle) {
    this.schedulingType = schedulingType;
    this.schedulingName = schedulingName;
    this.compuTime = compuTime;
    this.idleCounter = idleCounter;
    this.timeInIdle = timeInIdle;
  } 	
}

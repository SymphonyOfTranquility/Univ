public class sProcess {
  public int id;
  public int cputime;
  public int ioblocking;
  public int cpudone;
  public int ionext;
  public int numblocked;
  public int userid;
  public int ioblockingDuration;
  public int lastBlockingTime;

  public sProcess (int id, int userid, int cputime, int ioblocking,
                   int ioblockingDuration, int lastBlockingTime, int cpudone, int ionext,
                   int numblocked) {
    this.id = id;
    this.userid = userid;
    this.cputime = cputime;
    this.ioblocking = ioblocking;
    this.cpudone = cpudone;
    this.ionext = ionext;
    this.numblocked = numblocked;
    this.ioblockingDuration = ioblockingDuration;
    this.lastBlockingTime = lastBlockingTime;
  }

  public int getTimeLeftToUnblock(int comptime)
  {
    return Math.max(0, ioblockingDuration - (comptime - lastBlockingTime));
  }

  public String toString(String opType)
  {
    return "\tProcess: " + id + ", " + opType + "... ( CPU time: " + cputime + ", CPU done: " + cpudone + ")";
//            "Time to I/O blocking: " + ioblocking + ", Duration of I/O blocking: " + ioblockingDuration + " )";
  }
}

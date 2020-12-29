// Run() is called from Scheduling.main() and is where
// the scheduling algorithm written by the user resides.
// User modification should occur within the Run() function.

import java.util.*;
import java.io.*;

public class SchedulingAlgorithm {
  private SchedulingAlgorithm (){ }

  enum State{
    BLOCKED,
    RUNNING
  };

  private final static int INF = (int) 1e9;

  private static sProcess nextProcessInQueue(List<Queue<sProcess>> usersQueue, int currentUser, int comptime)
  {
    sProcess lessBlocked = usersQueue.get(currentUser).remove();
    int minBlockingTimeLeft = lessBlocked.getTimeLeftToUnblock(comptime);
    int n = usersQueue.get(currentUser).size();
    for (int i = 0; i < n && minBlockingTimeLeft > 0; ++i) {
      sProcess curProcess = usersQueue.get(currentUser).remove();
      int curBlockingTimeLeft = curProcess.getTimeLeftToUnblock(comptime);
      if (curBlockingTimeLeft < minBlockingTimeLeft) {
        usersQueue.get(currentUser).add(lessBlocked);
        lessBlocked = curProcess;
        minBlockingTimeLeft = curBlockingTimeLeft;
      }
      else{
        usersQueue.get(currentUser).add(curProcess);
      }
    }
    return lessBlocked;
  }

  private static sProcess nextProcess(List<Queue<sProcess>> usersQueue, int currentUser, int previousUser,
                                      int comptime, int usernum, sProcess process){
    sProcess minProcessToUnblock = null;
    int minTime = INF;
    boolean flag = false;

    while (minTime > 0) {
      if (flag)
        usersQueue.get(currentUser).add(process);

      currentUser = nextUser(currentUser, usernum);
      if (!usersQueue.get(currentUser).isEmpty()) {
        flag = true;
        process = nextProcessInQueue(usersQueue, currentUser, comptime);
        if (minProcessToUnblock == null ||
                process.getTimeLeftToUnblock(comptime) < minTime) {
          if (minProcessToUnblock != null)
            usersQueue.get(minProcessToUnblock.userid).add(minProcessToUnblock);
          minProcessToUnblock = process;
          minTime = process.getTimeLeftToUnblock(comptime);
        }
      }
      else
        flag = false;

      if (currentUser == previousUser)
        break;
    }
    if (flag)
      usersQueue.get(currentUser).add(process);

    usersQueue.get(minProcessToUnblock.userid).remove(minProcessToUnblock);

    return minProcessToUnblock;
  }

  private static int nextUser(int id, int usernum){
    return (id + 1)%usernum;
  }

  private static String systemIdle() { return "System idle...";  }

  private static void checkPreviousUser(int previousUser, int currentUser, int comptime, PrintStream out) {
    if (currentUser != previousUser) {
      out.println("\n\nTime " + comptime);
      out.println("Change user " + previousUser + " to " + currentUser);
    }
  }

  private static State nextProcessState(sProcess process, int previousUser, int currentUser, int comptime,
                                        PrintStream out) {
    if (process.getTimeLeftToUnblock(comptime) > 0) {
      out.println(systemIdle());
      return State.BLOCKED;
    } else {
      checkPreviousUser(previousUser, currentUser, comptime, out);
      out.println(process.toString("registered"));
      return State.RUNNING;
    }
  }

  public static Results Run(int runtime, Vector processVector, Results result, int usernum, int maxTimeForUser){
    List<Queue<sProcess>> usersQueue = new ArrayList<>();
    for (int id = 0;id < usernum; ++id) {
      usersQueue.add(new LinkedList<>());
    }
    for (int i = 0;i < processVector.size(); ++i) {
      sProcess curProcess = (sProcess) processVector.elementAt(i);
      usersQueue.get(curProcess.userid).add(curProcess);
    }

    int numberOfUsersLeft = 0;
    for (int i = 0;i < usernum; ++i) {
      if (!usersQueue.get(i).isEmpty())
        ++numberOfUsersLeft;
    }

    int i = 0;
    int comptime = 0;
    int currentUser = 0;
    int size = processVector.size();
    int completed = 0;
    int currentUserWorkTime = 0;
    int previousUser = 0;
    int idleCounter = 0;
    int timeInIdle = 0;
    processVector.clear();
    String resultsFile = "Summary-Processes";

    result.schedulingType = "Interactive (Preemptive)";
    result.schedulingName = "Fair-share";
    result.compuTime = 0;
    try {
      //BufferedWriter out = new BufferedWriter(new FileWriter(resultsFile));
      //OutputStream out = new FileOutputStream(resultsFile);
      PrintStream out = new PrintStream(new FileOutputStream(resultsFile));
      while (currentUser < usernum && usersQueue.get(currentUser).isEmpty())
        ++currentUser;
      if (currentUser == usernum) {
        out.close();
        return result;
      }
      out.println("Time " + comptime);
      out.println("Current user " + currentUser);
      sProcess process = usersQueue.get(currentUser).remove();
      out.println(process.toString("registered"));
      State processState = State.RUNNING;
      while (comptime < runtime) {
        if (process.cpudone == process.cputime && processState == State.RUNNING) {
          processVector.add(process);
          ++completed;
          out.println(process.toString("completed"));
          if (completed == size) {
            result.compuTime = comptime;
            result.timeInIdle = timeInIdle;
            result.idleCounter = idleCounter;
            out.close();
            return result;
          }
          if (usersQueue.get(currentUser).isEmpty())
            --numberOfUsersLeft;
          else {
            process = nextProcessInQueue(usersQueue, currentUser, comptime);
          }

          previousUser = currentUser;
          if (process.getTimeLeftToUnblock(comptime) > 0 ||
                  usersQueue.get(currentUser).isEmpty() && process.cpudone == process.cputime ||
                  currentUserWorkTime == maxTimeForUser) {
            if (process.getTimeLeftToUnblock(comptime) > 0)
              usersQueue.get(currentUser).add(process);
            currentUserWorkTime = 0;

            process = nextProcess(usersQueue, currentUser, previousUser, comptime, usernum, process);
            currentUser = process.userid;
          }

          processState = nextProcessState(process, previousUser, currentUser, comptime, out);
        }

        if (process.ioblocking == process.ionext && processState == State.RUNNING) {
          out.println(process.toString("I/O blocked"));
          process.numblocked++;
          process.ionext = 0;
          process.lastBlockingTime = comptime;

          usersQueue.get(currentUser).add(process);
          process = nextProcessInQueue(usersQueue, currentUser, comptime);
          previousUser = currentUser;

          if (process.getTimeLeftToUnblock(comptime) > 0) {
            currentUserWorkTime = 0;
            usersQueue.get(currentUser).add(process);
            process = nextProcess(usersQueue, currentUser, previousUser, comptime, usernum, process);
            currentUser = process.userid;
          }

          processState = nextProcessState(process, previousUser, currentUser, comptime, out);
        }

        if (currentUserWorkTime >= maxTimeForUser && numberOfUsersLeft > 1 && processState == State.RUNNING)
        {
          out.println(process.toString("blocking by changing user"));

          currentUserWorkTime = 0;
          previousUser = currentUser;
          usersQueue.get(currentUser).add(process);

          process = nextProcess(usersQueue, currentUser, previousUser, comptime, usernum, process);
          currentUser = process.userid;

          processState = nextProcessState(process, previousUser, currentUser, comptime, out);
        }

        if (processState == State.BLOCKED)
        {
          int blockingTimeLeft = process.getTimeLeftToUnblock(comptime);
          ++timeInIdle;
          if (blockingTimeLeft == 0)
          {
            checkPreviousUser(previousUser, currentUser, comptime, out);
            out.println(process.toString("registered"));
            processState = State.RUNNING;
            ++idleCounter;
          }
        }
        else {
          process.cpudone++;
          if (process.ioblocking > 0) {
            process.ionext++;
          }
        }
        ++currentUserWorkTime;
        ++comptime;
      }
      processVector.add(process);
      if (processState == State.RUNNING)
        out.println(process.toString("blocked due to closing"));
      else
        ++idleCounter;
      for (i = 0;i < usernum; ++i) {
        while (!usersQueue.get(i).isEmpty()) {
          sProcess curProcess = usersQueue.get(i).remove();
          processVector.add(curProcess);
        }
      }
      out.println("Program closed. Working time: " + comptime);
      out.close();
    } catch (IOException e) { /* Handle exceptions  */}
    result.compuTime = comptime;
    result.idleCounter = idleCounter;
    result.timeInIdle = timeInIdle;
    return result;
  }
}

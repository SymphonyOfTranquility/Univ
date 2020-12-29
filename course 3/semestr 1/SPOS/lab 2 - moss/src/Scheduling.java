// This file contains the main() function for the Scheduling
// simulation.  Init() initializes most of the variables by
// reading from a provided file.  SchedulingAlgorithm.Run() is
// called from main() to run the simulation.  Summary-Results
// is where the summary results are written, and Summary-Processes
// is where the process scheduling summary is written.

// Created by Alexander Reeder, 2001 January 06

import java.io.*;
import java.util.*;

public class Scheduling {

  private static final int INF = (int) 1e9;
  private static int processnum = 5;
  private static int meanDev = 1000;
  private static int standardDev = 100;
  private static int runtime = 1000;
  private static int usernum = 1;
  private static int maxTimeForUser = meanDev;
  private static Vector processVector = new Vector();
  private static Results result = new Results("null","null",0, 0, 0);
  private static String resultsFile = "Summary-Results";

  private static void Init(String file) throws Exception {
    File f = new File(file);
    String line;
    String tmp;
    int cputime = 0;
    int ioblocking = 0;
    int userid = 0;
    int ioblockingDuration = 0;
    double X = 0.0;

    try {   
      //BufferedReader in = new BufferedReader(new FileReader(f));
      DataInputStream in = new DataInputStream(new FileInputStream(f));
      while ((line = in.readLine()) != null) {
        if (line.startsWith("numprocess")) {
          StringTokenizer st = new StringTokenizer(line);
          st.nextToken();
          processnum = Common.s2i(st.nextToken());
        }
        if (line.startsWith("meandev")) {
          StringTokenizer st = new StringTokenizer(line);
          st.nextToken();
          meanDev = Common.s2i(st.nextToken());
        }
        if (line.startsWith("standdev")) {
          StringTokenizer st = new StringTokenizer(line);
          st.nextToken();
          standardDev = Common.s2i(st.nextToken());
        }
        if (line.startsWith("process")) {
          if (processVector.size() > processnum)
            throw new Exception("Cannot add process. Stack is full. There is only " + processnum + " process(es).");
          StringTokenizer st = new StringTokenizer(line);
          st.nextToken();
          ioblockingDuration = Common.s2i(st.nextToken());
          ioblocking = Common.s2i(st.nextToken());
          userid = Common.s2i(st.nextToken());
          if (userid >= usernum)
            throw new Exception("Cannot add user: " + userid + ". There is only " + usernum + " user(s).");
          X = Common.R1();
          while (X == -1.0) {
            X = Common.R1();
          }
          X = X * standardDev;
          cputime = (int) X + meanDev;
          processVector.addElement(new sProcess(processVector.size(), userid, cputime, ioblocking, ioblockingDuration,-INF,0, 0, 0));
        }
        if (line.startsWith("runtime")) {
          StringTokenizer st = new StringTokenizer(line);
          st.nextToken();
          runtime = Common.s2i(st.nextToken());
        }
        if (line.startsWith("numuser"))
        {
          StringTokenizer st = new StringTokenizer(line);
          st.nextToken();
          usernum = Common.s2i(st.nextToken());
        }
        if (line.startsWith("maxusertime")) {
          StringTokenizer st = new StringTokenizer(line);
          st.nextToken();
          maxTimeForUser = Common.s2i(st.nextToken());
        }

      }
      in.close();
    } catch (IOException e) {
      throw new Exception("IOException");
    }
    catch (Exception e)
    {
      throw e;
    }
  }

  private static void debug() {
    int i = 0;

    System.out.println("processnum " + processnum);
    System.out.println("meandevm " + meanDev);
    System.out.println("standdev " + standardDev);
    int size = processVector.size();
    for (i = 0; i < size; i++) {
      sProcess process = (sProcess) processVector.elementAt(i);
      System.out.println("process " + process.id + " " + "userId " + process.userid + " " + process.cputime + " " + process.ioblocking + " " + process.cpudone + " " + process.numblocked);
    }
    System.out.println("runtime " + runtime);
  }

  private static void setMaxTimeForUser()
  {
    double X = Common.R1();
    while (X == -1.0) {
      X = Common.R1();
    }
    X = X * standardDev;
    maxTimeForUser = (int) X + meanDev;
    return;
  }

  public static void main(String[] args) {
    int i = 0;

    if (args.length != 1) {
      System.out.println("Usage: 'java Scheduling <INIT FILE>'");
      System.exit(-1);
    }
    File f = new File(args[0]);
    if (!(f.exists())) {
      System.out.println("Scheduling: error, file '" + f.getName() + "' does not exist.");
      System.exit(-1);
    }
    if (!(f.canRead())) {
      System.out.println("Scheduling: error, read of " + f.getName() + " failed.");
      System.exit(-1);
    }
    System.out.println("Working...");
    try {
      Init(args[0]);
    } catch (Exception e){
      System.out.println(e);
      System.out.println("Stopped due to errors.");
      return;
    }
    if (processVector.size() < processnum) {
      i = 0;
      while (processVector.size() < processnum) {
        double X = Common.R1();
        while (X == -1.0) {
          X = Common.R1();
        }
        X = X * standardDev;
        int cputime = (int) X + meanDev;
        int userid = ((int) X + meanDev) % usernum;
        X = Common.R1();
        while (X == -1.0) {
          X = Common.R1();
        }
        X = X * standardDev;
        int ioblocking = (int)Math.sqrt(X + meanDev);
        int ioblockingDuration = (int) Math.sqrt(cputime) / 2;
        processVector.addElement(new sProcess(processVector.size(), userid, cputime, ioblocking, ioblockingDuration,-INF, 0, 0, 0));
        i++;
      }
    }
    //setMaxTimeForUser();
    result = SchedulingAlgorithm.Run(runtime, processVector, result, usernum, maxTimeForUser);
    try {
      //BufferedWriter out = new BufferedWriter(new FileWriter(resultsFile));
      PrintStream out = new PrintStream(new FileOutputStream(resultsFile));
      out.println("Scheduling Type: " + result.schedulingType);
      out.println("Scheduling Name: " + result.schedulingName);
      out.println("Simulation Run Time: " + result.compuTime);
      out.println("Mean: " + meanDev);
      out.println("Standard Deviation: " + standardDev);
      out.println("Number of users: " + usernum);
      out.println("Maximum time for each user: " + maxTimeForUser);
      out.println("Number of all system idles: " + result.idleCounter);
      out.println("Time in system idles: " + result.timeInIdle);
      out.println("Process #\tUser Id\tCPU Time\tIO Blocking\tIO Blocking duration\tCPU Completed\tCPU Blocked");
      for (i = 0; i < processVector.size(); i++) {
        sProcess process = (sProcess) processVector.elementAt(i);
        out.print(Integer.toString(process.id));
        if (i < 100) { out.print("\t\t\t"); } else { out.print("\t\t"); }
        out.print(Integer.toString(process.userid));
        if (i < 100) { out.print("\t\t"); } else { out.print("\t"); }
        out.print(Integer.toString(process.cputime));
        if (process.cputime < 100) { out.print(" (ms)\t\t"); } else { out.print(" (ms)\t"); }
        out.print(Integer.toString(process.ioblocking));
        if (process.ioblocking < 100) { out.print(" (ms)\t\t"); } else { out.print(" (ms)\t"); }
        out.print(Integer.toString(process.ioblockingDuration));
        if (process.ioblockingDuration < 100) { out.print(" (ms)\t\t\t\t\t"); } else { out.print(" (ms)\t\t\t\t"); }
        out.print(Integer.toString(process.cpudone));
        if (process.cpudone < 100) { out.print(" (ms)\t\t\t"); } else { out.print(" (ms)\t\t"); }
        out.println(process.numblocked + " times");
      }
      out.close();
    } catch (IOException e) { /* Handle exceptions */ }
  System.out.println("Completed.");
  }
}


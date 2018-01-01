// TalkClient.java
// Mitchell Wade
// April 25, 2015

package jtalk;

import java.io.*;
import java.net.*;

public class TalkClient {

    boolean interrupted = false;

    class WriterThread extends Thread {
        Socket sock;
        String hostName;
        BufferedReader serverOutput;

        WriterThread(Socket s, String host, BufferedReader in) {
            sock = s;
            hostName = host;
            serverOutput = in;
        }

        public void run() {
            String nextChatLine;

            try {
                while ((nextChatLine = serverOutput.readLine()) != null) {
                    System.out.println(nextChatLine);
                }
                interrupted = true;
            }
            catch (IOException e) {
                System.err.println("Couldn't connect IO for " +
                        hostName);
                System.exit(1);
            }
        }
    }

    void printChatRooms(BufferedReader in) {
        String chatRoom;
        String participantName;

        System.out.format("Chat Rooms: %n%n");

        try {
            while ((chatRoom = in.readLine()) != null) {
                if (chatRoom.equals("endRooms"))
                    break;
                System.out.format("%s:", chatRoom);
                while ((participantName = in.readLine()) != null) {
                    if (participantName.equals("endParticipants"))
                        break;
                    System.out.format(" %s", participantName);
                }
                System.out.println();
            }
            System.out.println();
        } catch (IOException e) {
            e.printStackTrace();
            System.exit(1);
        }
    }

    public static void main(String[] args) throws IOException {
        new TalkClient(args);
    }

    public TalkClient(String[] args) throws IOException {
        if (args.length != 3) {
            System.err.println(
                    "Usage: java TalkClient host port userName");
            System.exit(1);
        }

        String hostName = args[0];
        int portNumber = Integer.parseInt(args[1]);
        String userName = args[2];
        String chatRoom;

        Socket sock;
        PrintWriter out;
        BufferedReader in;
        BufferedReader stdIn;


        sock = new Socket(hostName, portNumber);
        out = new PrintWriter(sock.getOutputStream(), true);
        in =  new BufferedReader(
                new InputStreamReader(sock.getInputStream()));
        stdIn = new BufferedReader(new InputStreamReader(System.in));

        try {
            String userInput;
            String chatRoomAccepted;
            out.println(userName);
            printChatRooms(in);
            do {
                System.out.println("Enter chat room:");
                chatRoom = stdIn.readLine();
                out.println(chatRoom);
                chatRoomAccepted = in.readLine();
            } while (chatRoomAccepted.equals("false"));

            Thread writer = new WriterThread(sock, hostName, in);
            writer.start();

            while ((userInput = stdIn.readLine()) != null) {
                if (interrupted)
                    break;
                out.println(userInput);
            }

        } catch (UnknownHostException e) {
            System.err.println("Couldn't connect to " + hostName);
            System.exit(1);
        } catch (IOException e) {
            System.err.println("Couldn't connect IO for " +
                    hostName);
            System.exit(1);
        } 
        finally {
            if (sock != null) sock.close();
            if (in != null) in.close();
            if (out != null) out.close();
            if (stdIn != null) stdIn.close();
        }
    }
}

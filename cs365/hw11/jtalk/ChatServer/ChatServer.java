// ChatServer.java
// Mitchell Wade
// April 25, 2015

package jtalk;

import java.net.*;
import java.io.*;
import java.util.SortedMap;
import java.util.TreeMap;
import java.util.InputMismatchException;

public class ChatServer {

    public static void main(String[] args) throws IOException {

        int port = 0;
        ServerSocket sock = null;
        boolean listening = true;
        int i;

        // Process input
        if (args.length < 2) {
            System.err.println("Usage: java ChatServer port chatroom1 chatroom2...");
            System.exit(1);
        }

        try {
            port = Integer.parseInt(args[0]);
            if (port <= 5000) {
                throw new InputMismatchException();
            }
        }
        catch (InputMismatchException e) {
            System.out.println("port number must be an integer greater than 5000");
            System.exit(1);
        }

        SortedMap<String, ChatData> chatroomMap = new TreeMap<String, ChatData>();

        // Create chatrooms
        for (i = 1; i < args.length; i++) {
            chatroomMap.put(args[i], new ChatData(args[i]));
        }

        // Wait for connections
        try {
            sock = new ServerSocket(port);
            while (listening) {
                new TalkServerThread(sock.accept(), chatroomMap).start();
            }
        } catch (IOException e) {
            System.err.println("Could not listen on port " + port);
            System.exit(-1);
        }
        finally {
            if (sock != null)
                sock.close();
        }
    }
}

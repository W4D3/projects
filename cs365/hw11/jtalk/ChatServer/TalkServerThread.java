// TalkServerThread.java
// Mitchell Wade
// April 25, 2015

package jtalk;

import java.net.*;
import java.io.*;
import java.util.SortedMap;
import java.util.Map.Entry;

public class TalkServerThread extends Thread {
    
    private SortedMap<String, ChatData> chatRoomMap;
    private Socket sock = null;
    private ChatData chatData;

    public TalkServerThread(Socket sock, SortedMap<String, ChatData> map) {
        this.sock = sock;
        chatRoomMap = map;
    }

    String getChatRoomName(BufferedReader in, PrintWriter out) throws IOException {
        
        String selectedRoomName;
        boolean validRoomName = false;

        // Print the chatrooms and the people in each room
        for (Entry<String, ChatData> entry : chatRoomMap.entrySet()) {
            String roomName = entry.getKey();
            ChatData chatRoomData = entry.getValue();
            out.println(roomName);
            chatRoomData.broadcastMembers(out);
            out.println("endParticipants");
        }
        out.println("endRooms");
        do {
            selectedRoomName = in.readLine();
            validRoomName = chatRoomMap.containsKey(selectedRoomName);
            if (validRoomName) {
                out.println("true");
            }
            else {
                out.println("false");
            }
        } while (!validRoomName);

        return selectedRoomName;
    }

    public void run() {
        BufferedReader in = null;
        PrintWriter out = null;
        String userName = null;

        try {
            in = new BufferedReader(
                    new InputStreamReader(sock.getInputStream()));
            out = new PrintWriter(sock.getOutputStream(), true);

            userName = in.readLine();
            String chatroomName = getChatRoomName(in, out);
            chatData = chatRoomMap.get(chatroomName);
            chatData.addClient(userName, sock);
            String inputLine;

            while ((inputLine = in.readLine()) != null) {
                chatData.distributeMessage(userName + ": " + inputLine);
            }
            chatData.deleteClient(sock);
        } catch (IOException e) {
            e.printStackTrace();
        }
        try {
            sock.close();
            if (in != null)
                in.close();
        } catch (IOException e) {
            System.out.println(userName + "I/O error");
            e.printStackTrace();
        }
    }
}

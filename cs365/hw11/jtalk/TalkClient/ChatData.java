// ChatData.java
// Mitchell Wade
// April 25, 2015

package jtalk;

import java.util.ArrayList;
import java.net.*;
import java.io.*;

class ChatData {
    
    class ClientData {
        String clientName;
        Socket client;
        PrintWriter clientWriter;

        ClientData(String name, Socket sock, PrintWriter out) {
            clientName = name;
            client = sock;
            clientWriter = out;
        }
    }

    ArrayList<ClientData> clientList = new ArrayList<ClientData>();
    String chatRoomName;

    public ChatData(String roomName) {
        chatRoomName = roomName;
    }

    synchronized public void addClient(String name, Socket client) {
        try {
            PrintWriter out = new PrintWriter(client.getOutputStream(), true);
            ClientData newClient = new ClientData(name, client, out);
            clientList.add(newClient);
            distributeMessage(name + " has joined");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    synchronized public void deleteClient(Socket client) {
        ClientData data = null;
        for (ClientData c : clientList) {
            if (c.client == client)
                data = c;
        }
        distributeMessage(data.clientName + " has left");
        clientList.remove(data);
    }

    synchronized public void distributeMessage(String message) {
        for (ClientData s : clientList) {
            s.clientWriter.println(message);
        }
    }

    synchronized public void broadcastMembers(PrintWriter out) {
        for (ClientData c : clientList) {
            out.println(c.clientName);
        }
    }
}

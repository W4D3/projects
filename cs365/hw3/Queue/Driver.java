class Driver {
    public Driver() {
        Queue q = new ArrayQueue();
        q.add(new Integer(3));
        q.add(new Integer(10));
        q.add(new Integer(5));
        System.out.println((Integer)(q.remove()));
        System.out.println((Integer)(q.remove()));
        q.add(new Integer(6));
        q.add(new Integer(9));
        q.add(new Integer(12));
        while (!q.isEmpty()) 
            System.out.println((Integer)(q.remove()));
    }
    public static void main(String args[]) {
        new Driver();
    }
}

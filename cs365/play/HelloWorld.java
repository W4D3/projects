class HelloWorld {
    public HelloWorld() {
        System.out.println("Hello World");
    }

    static public void main(String args[]) {
        //int i;
        new HelloWorld();
        
        for (int i: args.length) {
            System.out.println(args[i]);
        }
    }
}

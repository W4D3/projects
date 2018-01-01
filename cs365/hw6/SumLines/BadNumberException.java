class BadNumberException extends Exception {
    int bad_num = 0;

    public BadNumberException(int num) {
	bad_num = num;
    }
    public String getMessage() {
	return new String(bad_num + " must be positive");
    }
}

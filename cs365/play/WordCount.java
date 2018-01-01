import java.util.*;

class WordCount {
	public WordCount() {
		Vector<String> words = new Vector<String>();
		Scanner console = new Scanner(System.in);

		while (console.hasNextLine()) {
			String line = console.nextLine();
			Scanner tokenizer = new Scanner(line);
			while (tokenizer.hasNext()) {
				String word = tokenizer.next();
				words.add(word);
			}
			tokenizer.close();
		}
		console.close();
		countWordFrequencies(words);
	}

	void countWordFrequencies(Vector<String> words) {
        // YOUR CODE GOES HERE
		/* Code you may need
		   Set<Map.Entry<String, Integer>> wordSet = frequencyCount.entrySet();
		   List<Map.Entry<String, Integer>> wordList = new ArrayList<Map.Entry<String, Integer>>(wordSet);
		 */

        int i, j, index;
        // Create the hash table
		Set<Map.Entry<String, Integer>> wordSet = frequencyCount.entrySet();

        for (i : words) {
            for (j : wordSet) {
                if (words[i] != wordSet[j]) wordSet[index]
        }

        // Read through words
            // Store words into table
        // Read through table
            // Dump into a list
            // Sort list

        // Output
	}

	public static void main(String args[]) {
		new WordCount();
	}
}

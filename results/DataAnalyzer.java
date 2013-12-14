import java.io.IOException; 
import java.io.File; 
import java.io.FileReader; 
import java.io.BufferedReader; 

/**
 * Analyzer class that analyze results. 
 */ 
public class DataAnalyzer {
    public static void main(String [] args) throws IOException {
        File currDir = new File("out_3");
        File[] files = currDir.listFiles(); 
        
        // Loop all the files 
        for (File file : files) {
            if (file.isFile() && file.length() > 0) {
                FileReader fileReader = new FileReader(file);
                BufferedReader bufReader = new BufferedReader(fileReader);
                
                // Read input file
                String origin = bufReader.readLine(); 
                String oracle = bufReader.readLine(); 
                int num = Integer.parseInt(bufReader.readLine());
                boolean found = false; 
                String line = bufReader.readLine(); 

                while (line != null) {
                    if (line.equalsIgnoreCase(oracle)) {
                        found = true; 
                        break; 
                    }

                    line = bufReader.readLine(); 
                }

                System.out.println(found ? "true" + origin + "," + oracle + "," + line : "false"); 

                bufReader.close(); 
            }
        }
    }
}

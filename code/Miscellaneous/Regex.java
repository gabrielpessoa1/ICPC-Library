import java.util.*;
import java.util.regex.*;

public class Main {
  public static String BuildRegex (){
    return "^" + sentence + "$";
  }
  public static void main (String args[]){
    String regex = BuildRegex();
    // check pattern documentation
    Pattern pattern = Pattern.compile (regex);
    Scanner s = new Scanner(System.in);
    String sentence = s.nextLine().trim();
    boolean found = pattern.matcher(sentence).find()
  }
}
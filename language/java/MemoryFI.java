//import java.util.regex;
import java.util.regex.Pattern;
import java.util.regex.Matcher;

import java.lang.*;

public class MemoryFI
{

    void Test( )
    {
        String str = "[2016-1-26 23:26:5]Process 18556 termed with signal 11(SIGSEGV)";

        String reStr = "(/d{4}-/d{1,2}-/d{1,2} /d{1,2}:/d{1,2}:/d{1,2})]Process (/d{1,5}) (exited with code /d|termed with signal /d{1,2}/((.*?)/))";
        Pattern pattern = Pattern.compile(reStr);
        Matcher matcher = pattern.matcher(str);

        if(matcher.find())
        {
            System.out.println(matcher.group(0));
        }
        else
        {
            System.out.println("ono data...");
        }
    }


    public static void main(String argv[])
    {
        //System.out.println("Hello");
        MemoryFI mem = new MemoryFI();
        mem.Test();

    }
}

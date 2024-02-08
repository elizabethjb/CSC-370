/**
 *
 * @author eliza
 */

import javax.swing.JOptionPane;
public class AccessLevel 
{
    //method to determine access level based on right(s) and minPermission inputs
    private static String canAccess(int[] rights, int minPermission)
    {
        StringBuilder accessLevel = new StringBuilder();
        
        //for loop through each of user's rights
        for(int i = 0; i < rights.length; i++)
        {
            int j = rights[i];
            //checking if user's right meets minPermission
            if(j >= minPermission)
            {
                //access granted
                accessLevel.append("A");
            }
            else
            {
                //access denied
                accessLevel.append("D");
            }
        }
        return accessLevel.toString();
        
    }
    
    //JDialog Box for user, asking for size of users with validation
    private static Integer getUserSize(String message, int min, int max)
    {
        Integer input = null;
        String user;
        
        //looping until valid based on constraints
        while(input == null || input < min || input > max)
        {
            user = JOptionPane.showInputDialog(null, message);
            if(user == null)
            {
                return null; //constraint
            }
            try
            {
                input = Integer.valueOf(user);
                
                if(input < min || input > max) //constraints
                {
                    JOptionPane.showInputDialog(null, "Invalid. Must be between 0-50");
                }
            }
            catch(NumberFormatException i)
            {
                JOptionPane.showInputDialog(null, "Invalid entry. Please enter a valid integer.");
            }
        }
        
        return input;
    }

    //method to get users rights for each with input validation
    private static int[] getUserElements(int size)
    {
        int[] rights = new int[size];
        String message = "Please enter the " + size + " privlige levels of each user: "
                + "\n Starting from the Left";
        for (int i = 0; i < size; i++)
        {
            rights[i] = getUserSize(message + "\n User #" + (i+1) + "): ", 0,100);
        }
        return rights;
    }

    //minPermission value from user with input validation
    private static int getUserPermissionValue(String message, int min, int max)
    {
        int input;
        String user;
        do
        {
            user = JOptionPane.showInputDialog(null, message);
            if(user == null)
            {
                return 0; //constraint
            }
            input = Integer.parseInt(user);
        } while (input < min || input > max); //constraints
        
        return input;
    }
    
    //print function:
    private static void Print(String message)
    {
        JOptionPane.showMessageDialog(null, message);
    }
    
    
    public static void main(String[] args) 
    {
        //getting size of users
        int size = getUserSize("Please enter the size of the users: ", 0, 50);

        //storing the user's privilege level into an array for each
        int[] rights = getUserElements(size);

        //getting minPermission value
        int minPermission = getUserPermissionValue("Please enter the minPermission Value: ", 0, 100);

        //will see who can and cannot access based on rights and minPermission
        String accessLevel = canAccess(rights, minPermission);

        //displaying results
        Print("'A' indicates access granted, 'D' indicates access denied"
                    + "\nRead from left to right --> left being 1st user"
                + "\n\nAccess Evalutation: \n" + accessLevel);
 
    }
}

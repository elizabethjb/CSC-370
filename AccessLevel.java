/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 */

package com.mycompany.accesslevel;

/**
 *
 * @author eliza
 */

import javax.swing.JOptionPane;
public class AccessLevel 
{
    private static String canAccess(int[] rights, int minPermission)
    {
        StringBuilder accessLevel = new StringBuilder();
        
        for(int i = 0; i < rights.length; i++)
        {
            int j = rights[i];
            
            if(j >= minPermission)
            {
                accessLevel.append("A");
            }
            else
            {
                accessLevel.append("D");
            }
        }
        return accessLevel.toString();
        
    }
    
    //JDialog Box for user, asking for size of users
    private static Integer getUserSize(String message, int min, int max)
    {
        Integer input = null;
        String user;
        
        while(input == null || input < min || input > max)
        {
            user = JOptionPane.showInputDialog(null, message);
            if(user == null)
            {
                return null;
            }
            try
            {
                input = Integer.valueOf(user);
                
                if(input < min || input > max)
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
    
    private static int getUserPermissionValue(String message, int min, int max)
    {
        int input;
        String user;
        do
        {
            user = JOptionPane.showInputDialog(null, message);
            if(user == null)
            {
                return 0;
            }
            input = Integer.parseInt(user);
        } while (input < min || input > max);
        
        return input;
    }
    
    //print function:
    private static void Print(String message)
    {
        JOptionPane.showMessageDialog(null, message);
    }
    
    
    public static void main(String[] args) 
    {
        int size = getUserSize("Please enter the size of the users: ", 0, 50);
        
        int[] rights = getUserElements(size);
        
        int minPermission = getUserPermissionValue("Please enter the minPermission Value: ", 0, 100);
        
        String accessLevel = canAccess(rights, minPermission);
        
        Print("'A' indicates access granted, 'D' indicates access denied"
                    + "\nRead from left to right --> left being 1st user"
                + "\n\nAccess Evalutation: \n" + accessLevel);
 
    }
}

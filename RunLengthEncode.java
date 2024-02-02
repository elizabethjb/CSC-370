/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 */

package com.mycompany.runlengthencode;

/**
 *
 * @author eliza
 */
import javax.swing.JOptionPane;

/**
 *
 * @author eliza
 */
public class RunLengthEncode
{
    public static String encode(String input) throws IllegalArgumentException
    {
        //string validation:
        string_validation(input);
         
        return codeCH(input);
    }
    
    private static void string_validation(String input) throws IllegalArgumentException
    {
        //constraints check:
        
        //1. if the string is empty, return empty
        if(input.isEmpty())
        {
            return;
        }
        
        //2. check if length of string is between 0 <= 50:
        if(!(input.length() >= 0 && input.length() <= 50))
        {
            throw new IllegalArgumentException("The length of the string"
                    + " must be between 0 and 50 characters please:)");
        }
        
        //3. 'a-z' and 'A-Z' allowed, but can accept special characters and digits:
        if(!input.matches("[a-zA-Z0-9 {}\\[\\]():;'+=.,]*"))
        {
            throw new IllegalArgumentException("Please input valid characters. Thank you.");
        }
    }
    
    public static String codeCH(String input)
    {
        //sequence of characters
        StringBuilder chList = new StringBuilder();
        //num of consecutive characters
        int num_consecutive_ch = 1;
                
        //looping:
        for(int i = 1; i <= input.length(); i++)
        {
            //if current ch == before ch
            if(i < input.length() && input.charAt(i) == input.charAt(i-1))
            {
                num_consecutive_ch++; //increment
            }
            else
            {
                //if # of consecutive ch is > 4:
                if(num_consecutive_ch > 4)
                {
                    chList.append(String.format("/%02d%c", num_consecutive_ch, input.charAt(i-1)));
                }
                else
                {
                    //# of consecutive ch is 4 or less
                    for (int j = 0; j < num_consecutive_ch; j++)
                    {
                        chList.append(input.charAt(i-1));
                    }
                }
                //reset
                num_consecutive_ch = 1;
            }
        }
        
        
        return chList.toString();
    }
    
    
    
    public static void main(String[] args)
    {
        String input = UserInput();
        String codestring = encode(input);
        Print(codestring);
        
    }
    
    //JDialog Box for user input
    private static String UserInput()
    {
        return JOptionPane.showInputDialog(null, "Please enter "
                + "a string to encode: ");
        
    }
    
    //print function:
    private static void Print(String codestring)
    {
        JOptionPane.showMessageDialog(null, "The encoded "
                + "string is: " + codestring);
    }
}


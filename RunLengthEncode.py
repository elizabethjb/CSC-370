class RunLengthEncode:
    @staticmethod
    #define a function
    def encode(string_input):
        #function for string input validation
        def string_validation(string_input):
            #check the constraints of the input code:
            #1. if the string is empty, return empty string
            if not string_input:
                return ""

            #2. string_input length must be between 0-50 characters:
            if not 0 <= len(string_input) <= 50:
                raise ValueError("String input length must be between 0 and 50, no more.")

            #3. string_input can only consists of letters 'a-z' and 'A-Z' but can also accept digits, special characters, and white space:
            ch_allowed = set("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 {}[]():;'+=.,")
            if not all(char in ch_allowed for char in string_input):
                raise ValueError("There are invalid characters in the string_input")
        #check input
        string_validation(string_input)

        def character_encode(string_input):
            #creating a list to store ch
            ch_list = []

            #count of num of consecutive characters
            num_consecutive_ch = 1

            #check if string input is empty:
            if not string_input:
                return ""

            #loop
            for i in range(1, len(string_input)):
                #if current ch is equal to the before
                if string_input[i] == string_input[i-1]:
                    #increment by 1
                    num_consecutive_ch +=1

                else:
                    #num of consecutive character is greater than 4
                    if num_consecutive_ch > 4:
                        #add the format to list
                        ch_list.append(f"/{num_consecutive_ch:02d}{string_input[i-1]}")

                    else: #if num of consecutive character is 4 or less
                        ch_list.append(string_input[i-1] * num_consecutive_ch)
                    num_consecutive_ch = 1
            #last ch of string input
            if num_consecutive_ch > 4:
                ch_list.append(f"/{num_consecutive_ch:02d}{string_input[-1]}")
            else:
                ch_list.append(string_input[-1] * num_consecutive_ch)

            return ''.join(ch_list)

        return character_encode(string_input)


#asking user for string input:
def user_in():
    return input("Please enter a string to encode: ")

#code the input to the class
def code_string():
    in_userstring = user_in()
    codestring = RunLengthEncode.encode(in_userstring)
    return codestring

#print result
def print_string(codestring):
    print("The encoded string is: " , codestring)

codestring = code_string()
print_string(codestring)

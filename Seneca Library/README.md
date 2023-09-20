## Purpose

This application was built to simulate the workings of a library i.e. publication management. 

## Programming Language
C

## How to Run 
Copy all the files into your local drive. The text files provide the program with the necessary data about books and users. Use an IDE (e.g. Visual Studio Code) to see the program in more action as you could use breakpoints to see the inner workings of the code. 


## Navigating

![main menu](https://github.com/ArashTechDev/Projects/assets/144269515/6780a9db-6382-48bd-ae0d-54186d178d2b)

This is the main screen and is the central point from where we can interact with the program. I have attached two text files with this program - LibRecsSmall.txt and LibRecs.txt for a better demonstration of the project. Upon starting the program, it asks which text file to run the program on. 

### Adding a Publication

![addPub](https://github.com/ArashTechDev/Projects/assets/144269515/190bf6da-08b5-4dfd-92ed-321ad3d73028)

We added a book publication to our library data! 

### Checking out a Publication

![checkoutPub](https://github.com/ArashTechDev/Projects/assets/144269515/64aa1a7f-8baf-452a-91d2-abc11182a362)

We now checked out the publication that we first created. To find the publication we want to check out, the program asks the user to enter the title. The entered text does not have to match the title completely but rather partially, for ease of use. The program loops through our entire dataset and prints the matching data.

It only displays those publications that have not been loaned out to members. 

The user then selects the desired publication by entering the row number. The program then asks the user for their membership ID before completing the task. 

### Returning a Publication

![returnPub](https://github.com/ArashTechDev/Projects/assets/144269515/56626c1e-00c7-4f45-b0ce-420884e53a40)

Here, the user tells the program which publication to return. The program asks for the publication title and then searches its dataset to find publications that have been checked out with the same title name. The publication is then returned to the library. 

### Removing a Publication

![removePub](https://github.com/ArashTechDev/Projects/assets/144269515/1ee179e4-e2d7-4854-a5a6-cd7daa0807a6)

It displays all the publications that match the entered text and then removes the one decided by the user. 

## Exit

Upon exiting, it displays the entire content of the text file.

If the user any changes, the program asks if we wish to save the changes. If chosen yes, it saves the changes made and then displays the content.

To demonstrate, I again added a new publication and then exited the application. 

### Adding Publication 
![exit1](https://github.com/ArashTechDev/Projects/assets/144269515/f2fa1d94-11d5-4013-b8f1-47227a8a11a9)


### Exiting Application
![exit2](https://github.com/ArashTechDev/Projects/assets/144269515/d01d581d-ce0d-470f-bf29-bcfc57493bf7)

 










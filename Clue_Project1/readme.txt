How to compile the code:
    Type 'make' in the TERMINAL.

Overview/Description of overall board game structure:
    It follows the concept of a 3x3 grid using pointers to
    North, South, East, and West directions. The room in the 
    2x2(middle of the board) place will have pointers
    towards rooms in all directions(North, South, East, West). 
    However, the room where the Avatar starts in the 1x1(top left) 
    place in the grid will only have pointers to South and East.

    Each room also holds pointers to characters and items,
    as well as names which are randomly assigned when boardGen()
    is called.

    When the game is over all allocated space in the beginning
    gets deallocated.

How to manage user input/play game:
    The game progression is moved by user input only. The
    user moves the Avatar along making guesses about the game
    and the user is challenged to gather the clues on their own
    so that they can beat the game before they run out of their
    10 guesses.

    The bulk of main is a large while loop that keeps asking for
    user input while the game is not over(or unless 'quit' command
    is called). These commands help perform actions like 'clue'
    which then prompts the user make guesses that ask for example
    which character the user believes was the culprit:

        "What character do you guess commited the crime?"

    to which the user may type:

        "Colonel_Mustard"~(a.k.a. No.1 Player Hater)

    As long as the input matches one of the options for characters
    or weapons, the input is taken. Otherwise, the user will 
    continue to be prompted an appropriate answer until one is
    typed.

    For other commands and their definitions, the user may type
    'help' which prints each possible command and what actions
    they perform.
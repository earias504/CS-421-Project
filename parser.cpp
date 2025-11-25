#include<iostream>
#include<fstream>
#include<string>
using namespace std;

/* INSTRUCTION:  Complete all ** parts.
   You may use any method to connect this file to scanner.cpp
   that you had written.  
  e.g. You can copy scanner.cpp here by:
          cp ../ScannerFiles/scanner.cpp .  
       and then append the two files into one: 
          cat scanner.cpp parser.cpp > myparser.cpp
*/

//so we can use the same tokentype from scanner.cpp
typedef tokentype token_type;
typedef bool boolean;


//=================================================
// File parser.cpp written by Group Number: 3
//=================================================

// ----- Four Utility Functions and Globals -----------------------------------

// ** Need syntaxerror1 and syntaxerror2 functions (each takes 2 args)
//    to display syntax error messages as specified by me.  

// expecting one token type but found another
// Done by: Kaden
void syntaxerror1(string lexeme, tokentype expected)
{
  cout << "SYNTAX ERROR: expected "
       << tokenName[expected] << " but found " << lexeme << endl;

  // bail out
  exit(1);
}






// Type of error: unexpected tolen inside of the parser function
// Done by: Eric
void syntaxerror2(string lexeme, string function_name)
{

  cout << "SYNTAX ERROR: unexpected " << lexeme << " found in " << function_name << endl;
  
  exit(1);
}
// ** Need the updated match and next_token with 2 global vars
// saved_token and saved_lexeme

tokentype saved_token;
string saved_lexeme;
bool token_available = false;




// look at next token from scanner (cache until match() eats it)
// Done by: Kaden
token_type next_token()
{
  // check for avaiable token before calling scanner
  if (!token_available)
  {
    // grab token/lexeme from scanner
    scanner(saved_token, saved_lexeme);

    // mark token cached
    token_available = true;
  }

  // return the saved token
  return saved_token;
}





// Purpose: Checks and eats up the expected token. On mismatch, produces syntax error.
// Done by: Daniel

boolean match(tokentype expected)
{
  if (next_token() != expected)        // mismatch has occurred
  
  {
    syntaxerror1(saved_lexeme, expected);
    return false; // won't reach here (exit in syntaxerror1)
  }

  else// match occurred
  {
   
   cout << "Matched " << tokenName[expected] << endl;
    token_available = false;           // eat the token so scanner is called again next time
    return true;

  }
}






// ----- RDP functions - one per non-term -------------------

// ** Make each non-terminal into a function here
// ** Be sure to put the corresponding grammar rule above each function
// ** Be sure to put the name of the programmer above each function

void story();
void s();
void afterSubject();
void afterNoun();
void afterObject();
void noun();
void verb();
void be();
void tense();


string filename;

// Grammar: <story> ::= <s> { <s> }
// Done by: Kaden
void story()
{
  cout << "Processing <story>" << endl << endl;

  // first <s>
  s();

  // continue reading sentences as long as we see CONNECTOR, WORD1, or PRONOUN
  while (true)
  {
    tokentype t = next_token();

    // look for either CONNECTOR, WORD1 or PRONOUN
    if (t == CONNECTOR || t == WORD1 || t == PRONOUN)
      s();
    else
      break;   // story is done
  }
}

// Grammar: <s> ::= [CONNECTOR] <noun> SUBJECT <afterSubject>
// Done by: Daniel
void s()
{
  cout << "Processing <s>" << endl;

  if (next_token() == CONNECTOR)
  match(CONNECTOR);

  noun();
  match(SUBJECT);
  afterSubject();
   
}





// Grammar: <afterSubject> ::= <verb> <tense> PERIOD | <noun> <afterNoun>
// Done by: Kaden
void afterSubject()
{
  cout << "Processing <afterSubject>" << endl;

  tokentype t = next_token();

  // FIRST(<verb>) = WORD2 in this grammar
  if (t == WORD2)
  {
    verb();
    tense();
    match(PERIOD);
  }

     
  // FIRST(<noun>) = WORD1 or PRONOUN
  else if (t == WORD1 || t == PRONOUN)
  {
    noun();
    afterNoun();
  }
  else
  {
    // throw syntax error for any other token
    syntaxerror2(saved_lexeme, "afterSubject");
  }
}







// Grammar: <afterNoun> ::= <be> PERIOD
//                        | DESTINATION <verb> <tense> PERIOD
//                        | OBJECT <afterObject>
// Done by: Daniel
void afterNoun()
{
  cout << "Processing <afterNoun>" << endl;

  tokentype t = next_token();

  if (t == IS || t == WAS)
  {
     
    be();
    match(PERIOD);
     
  }

     
  else if (t == DESTINATION)
  {
    match(DESTINATION);
    verb();
    tense();
    match(PERIOD);
  }
     
  else if (t == OBJECT)
  {
    match(OBJECT);
    afterObject();
  }
     
  else
  {
    syntaxerror2(saved_lexeme, "afterNoun");
  }
}

// Grammar: <afterObject> ::= <verb> <tense> PERIOD
// | <noun> DESTINATION <verb> <tense> PERIOD
// Done by: Eric
void afterObject()
{
  cout << "Processing <afterObject>" << endl;

  tokentype t = next_token();

  if (t == WORD2)   // FIRST(<verb>)
  {
      
    verb();
    tense();
    match(PERIOD);
      
  }


      
  else if (t == WORD1 || t == PRONOUN)   // FIRST(<noun>)
  {
      
    noun();
    match(DESTINATION);
    verb();
    tense();
    match(PERIOD);
      
  }
  else
  {
    syntaxerror2(saved_lexeme, "afterObject");
  }
}

// Grammar: <noun> ::= WORD1 | PRONOUN
// Done by: Daniel
void noun()
{
  cout << "Processing <noun>" << endl;

  tokentype t = next_token();

  if (t == WORD1)
      match(WORD1);
  else if (t == PRONOUN)
   match(PRONOUN);
     
  else
      syntaxerror2(saved_lexeme, "noun");
}




// Grammar: <verb> ::= WORD2
// Done by: Eric
void verb()
{
    
  cout << "Processing <verb>" << endl;

  if (next_token() == WORD2)
      match(WORD2);

      
  else
      syntaxerror2(saved_lexeme, "verb");

    
}



// Grammar: <be> ::= IS | WAS
// Done by: Kaden
void be()
{
  cout << "Processing <be>" << endl;

  tokentype t = next_token();

  if (t == IS)
    match(IS);
     
  else if (t == WAS)
    match(WAS);
  else
    syntaxerror2(saved_lexeme, "be");
}

// Grammar: <tense> ::= VERBPAST | VERBPASTNEG | VERB | VERBNEG
// Done by: Eric
void tense()
{
    
  cout << "Processing <tense>" << endl;

  tokentype t = next_token();

  if (t == VERBPAST)
      match(VERBPAST);

  else if (t == VERBPASTNEG)
      match(VERBPASTNEG);

      
  else if (t == VERB)
      match(VERB);

      
  else if (t == VERBNEG)
      match(VERBNEG);
      
  else
      syntaxerror2(saved_lexeme, "tense");
    
}





//----------- Driver ---------------------------

extern ifstream fin;


// The new test driver to start the parser
// Done by:  Eric
int main()
{
    
  cout << "Enter the input file name: ";
  cin >> filename;
  fin.open(filename.c_str());



    
  //** calls the <story> to start parsing
  story();
    
  //** closes the input file 
fin.close();
}// end



//** require no other input files!
//** syntax error EC requires producing errors.txt of error messages
//** tracing On/Off EC requires sending a flag to trace message output functions



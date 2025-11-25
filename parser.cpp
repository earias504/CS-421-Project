#include <iostream>
#include <fstream>
#include <string>
using namespace std;
//=====================================================
// File scanner.cpp written by: Group Number: 3
//=====================================================

// --------- Two DFAs ---------------------------------
// WORD DFA
// Done by: Eric Arias-López
// RE: (vowel | vowel n | consonant vowel | consonant vowel n |
// consonant-pair vowel | consonant-pair vowel n)^+
// Where vowels = {a,i,u,e,o,I,E}, pairs = {by,gy,hy,ky,my,ny,py,ry,ch,sh,ts}
bool word(string s)
{
    // (Eric) I created this enum so we can keep track of the states more easily.
    enum State { q0, q0q1, q0qy, qsa, qy, qc, qt, qs };

    // Start in state q0
    State state = q0;

    // Current character position in the string
    int charpos = 0;

    // Run until we reach the end of the string
    while (charpos < (int)s.size())
    {
        // Get the current character
        char c = s[charpos];

        // Determine the next state
        switch (state)
        {

        case q0:
            switch (c)
            {
            case 'a':
            case 'i':
            case 'u':
            case 'e':
            case 'o':
            case 'I':
            case 'E':
                state = q0q1;
                break;
            case 'd':
            case 'w':
            case 'z':
            case 'y':
            case 'j':
                state = qsa;
                break;
            case 'b':
            case 'g':
            case 'h':
            case 'k':
            case 'm':
            case 'p':
            case 'r':
                state = qy;
                break;
            case 'c':
                state = qc;
                break;
            case 't':
                state = qt;
                break;
            case 's':
                state = qs;
                break;
            case 'n':
                state = qy;
                break;
            default:
                return false;
            }
            break;

        case q0q1:
            switch (c)
            {
            case 'a':
            case 'i':
            case 'u':
            case 'e':
            case 'o':
            case 'I':
            case 'E':
                state = q0q1;
                break;
            case 'd':
            case 'w':
            case 'z':
            case 'y':
            case 'j':
                state = qsa;
                break;
            case 'b':
            case 'g':
            case 'h':
            case 'k':
            case 'm':
            case 'p':
            case 'r':
                state = qy;
                break;
            case 'c':
                state = qc;
                break;
            case 't':
                state = qt;
                break;
            case 's':
                state = qs;
                break;
            case 'n':
                state = q0qy;
                break;
            default:
                return false;
            }
            break;

        case q0qy:
            switch (c)
            {
            case 'a':
            case 'i':
            case 'u':
            case 'e':
            case 'o':
            case 'I':
            case 'E':
                state = q0q1;
                break;
            case 'd':
            case 'w':
            case 'z':
            case 'y':
            case 'j':
                state = qsa;
                break;
            case 'b':
            case 'g':
            case 'h':
            case 'k':
            case 'm':
            case 'p':
            case 'r':
                state = qy;
                break;
            case 'c':
                state = qc;
                break;
            case 't':
                state = qt;
                break;
            case 's':
                state = qs;
                break;
            case 'n':
                state = qy;
                break;
            default:
                return false;
            }
            break;

        case qsa:
            switch (c)
            {
            case 'a':
            case 'i':
            case 'u':
            case 'e':
            case 'o':
            case 'I':
            case 'E':
                state = q0q1;
                break;
            default:
                return false;
            }
            break;

        case qy:
            switch (c)
            {
            case 'a':
            case 'i':
            case 'u':
            case 'e':
            case 'o':
            case 'I':
            case 'E':
                state = q0q1;
                break;
            case 'y':
                state = qsa;
                break;
            default:
                return false;
            }
            break;

        case qc:
            switch (c)
            {
            case 'h':
                state = qsa;
                break;
            default:
                return false;
            }
            break;

        case qt:
            switch (c)
            {
            case 'a':
            case 'i':
            case 'u':
            case 'e':
            case 'o':
            case 'I':
            case 'E':
                state = q0q1;
                break;
            case 's':
                state = qsa;
                break;
            default:
                return false;
            }
            break;

        case qs:
            switch (c)
            {
            case 'a':
            case 'i':
            case 'u':
            case 'e':
            case 'o':
            case 'I':
            case 'E':
                state = q0q1;
                break;
            case 'h':
                state = qsa;
                break;
            default:
                return false;
            }
            break;
        }

        // Increment character position
        ++charpos;
    }

    // Any state with a q0 is an accepting state per our DFA
    return (state == q0 || state == q0q1 || state == q0qy);
}

// PERIOD DFA
// Done by: Eric Arias-López
bool period(string s)
{
    // RE: \.
    // Accepts exactly one character which must be '.'
    return (s.size() == 1 && s[0] == '.');
}

// ------ Three Tables -------------------------------------
// TABLES Done by: Daniel Esparza
// ** Update the tokentype to be WORD1, WORD2, PERIOD, ERROR, EOFM, etc.
enum tokentype
{
    WORD1,
    WORD2,
    PERIOD,
    ERROR,
    EOFM,
    VERB,
    VERBNEG,
    VERBPAST,
    VERBPASTNEG,
    IS,
    WAS,
    OBJECT,
    SUBJECT,
    DESTINATION,
    PRONOUN,
    CONNECTOR
};

// ** For the display names of tokens - must be in the same order as the tokentype.
// This is exactly the same as tokentype but with double quotes for printing.
string tokenName[30] = {
    "WORD1", "WORD2", "PERIOD", "ERROR", "EOFM",
    "VERB", "VERBNEG", "VERBPAST", "VERBPASTNEG",
    "IS", "WAS",
    "OBJECT", "SUBJECT", "DESTINATION",
    "PRONOUN", "CONNECTOR"};

// ** Need the reservedwords table to be set up here.
// ** Do not require any file input for this. Hard code the table.
// ** a.out should work without any additional files.
struct Reserved
{
    const char *lexeme;
    tokentype type;
};
static const Reserved RESERVED[] = {
    {"masu", VERB},
    {"masen", VERBNEG},
    {"mashita", VERBPAST},
    {"masendeshita", VERBPASTNEG},
    {"desu", IS},
    {"deshita", WAS},
    {"o", OBJECT},
    {"wa", SUBJECT},
    {"ni", DESTINATION},
    {"watashi", PRONOUN},
    {"anata", PRONOUN},
    {"kare", PRONOUN},
    {"kanojo", PRONOUN},
    {"sore", PRONOUN},
    {"mata", CONNECTOR},
    {"soshite", CONNECTOR},
    {"shikashi", CONNECTOR},
    {"dakara", CONNECTOR},
    {"eofm", EOFM} // special; scanner will also short-circuit on this
};
static const int RESERVED_COUNT = sizeof(RESERVED) / sizeof(RESERVED[0]);

// ------------ Scanner and Driver -----------------------
ifstream fin; // global stream for reading from the input file
// Scanner processes only one word each time it is called
// Gives back the token type and the word itself
// ** Done by: Kaden Campbell
int scanner(tokentype &tt, string &w)
{
    // ** Grab the next word from the file via fin
    // 1. If it is eofm, return right now.
    /* **
    2. Call the token functions (word and period)
    one after another (if-then-else).
    Generate a lexical error message if both DFAs failed.
    Let the tokentype be ERROR in that case.
    3. If it was a word,
    check against the reservedwords list.
    If not reserved, tokentype is WORD1 or WORD2
    decided based on the last character.
    4. Return the token type & string (pass by reference)
    */
    {
        // 1) get the next space-delimited string
        if (!(fin >> w))
        { // defensive: in case file ends unexpectedly
            tt = EOFM;
            w = "eofm";
            return 0;
        }

        // print
        cout << "Scanner called using word: " << w << endl;

        // (If it is eofm, return right now.)
        if (w == "eofm")
        {
            tt = EOFM;
            return 0;
        }

        // 2) run DFAs in if-else order: word, then period
        if (word(w))
        {
            // 3) See if it is a reserved word (using the table)
            for (int i = 0; i < RESERVED_COUNT; ++i)
            {
                if (w == RESERVED[i].lexeme)
                {
                    tt = RESERVED[i].type;
                    return 0;
                }
            }
            // If not reserved, determine if tokentype is WORD1 or WORD2
            char last = w[w.size() - 1];
            if (last == 'I' || last == 'E')
                tt = WORD2;
            else
                tt = WORD1;
            return 0;
        }
        else if (period(w))
        {
            tt = PERIOD;
            return 0;
        }
        else
        {
            // lexical error
            cout << "Lexical error: " << w << " is not a valid token" << endl;
            tt = ERROR;
            return 0;
        }
    }
} // the end of scanner

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
    return false;                      // won't reach here (exit in syntaxerror1)
  }

  else 
                                  // match occurred
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
//                          | <noun> DESTINATION <verb> <tense> PERIOD
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
// Done by:  Daniel
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

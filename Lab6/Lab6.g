// The name of the grammar. The name here needs to match the name of the
// file, including capitalization.
grammar Lab6;



// Define literals, keywords or operators, here as tokens.
tokens {
	PLUS = '+';
	MINUS = '-';
	MULTI = '*';
	DIV = '/';
	EXP = '^';
	LOG = 'log';  
	SIN = 'sin';
	COS = 'cos';
	TAN = 'tan';
}

// Written in the target language. The header section can be
// used to import any Java classes that may be required.
@header {
	import java.lang.*;
	import java.io.*;
}

// A main function to the parser. This function will setup the
// parsers input stream and execute the rule named "top".
@members {
    public static void main(String[] args) throws Exception {
        Lab6Lexer lex = new Lab6Lexer(new ANTLRInputStream(System.in));
       	CommonTokenStream tokens = new CommonTokenStream(lex);
        Lab6Parser parser = new Lab6Parser(tokens);

        try {
            parser.top();
        } catch (RecognitionException e)  {
            e.printStackTrace();
        }
    }
}

// Some example lexer fragments. These fragments don't produce any
// tokens themselves but can be used inside of other lexer rules.
fragment DEC: '0' .. '9';
fragment BIN: '0' .. '1';
fragment OCT: '0' .. '7';
fragment HEX: ('0' .. '9' | 'A' .. 'F' | 'a' .. 'f');
fragment START: '1' .. '9';


// The white space lexer rule. Match any number of white space characters
// and hide the values from the parser.
WS : (' ' | '\t' | '\r' | '\n')+ { $channel=HIDDEN; };

// The decimal value lexer rule. Match one or more decimal digits.
REAL : DEC+ '.' DEC+;
BINARY : '0b' BIN+;
OCTAL : '0' OCT+;
DECIMAL : DEC+;
HEXDECIMAL : '0x' HEX+;


// The top rule. You should replace this with your own rule definition to
// parse expressions according to the assignment.
top : evaluate EOF 
	| EOF
	;

evaluate : term {System.out.println($term.value);};

term returns [double value]: term_result1 = multiply {$value = $term_result1.value;}
	                     (PLUS term_result2 = multiply {$value = $value + $term_result2.value;}
                   	     |MINUS term_result2 = multiply {$value = $value - $term_result2.value;})*;



multiply returns [double value]: mul_result1 = exponential {$value = $mul_result1.value;}
		      		 (MULTI mul_result2 = exponential {$value *= $mul_result2.value;}
		  		 |DIV mul_result2 = exponential
		   		 {
				 //Also, be sure to make your calculator print an error message when encountering any divide-by-zero attempts
                   			if(mul_result2 == 0)
					{
						$value = 0;
                    				System.out.println("You cannot divide by zero!");
                  			}
                			else
					{
                    				$value /= $mul_result2.value;
                			}
            	  		 })*;



exponential returns [double value]: exp_result1 = log {$value = $exp_result1.value;}
		  		    (EXP exp_result2 = log {$value = Math.pow(exp_result1, exp_result2);})*;



expression returns [double value]: DECIMAL {$value = (double)Integer.parseInt($DECIMAL.getText(), 10);}

				   |BINARY {String newStr = $BINARY.getText();
                    			    newStr = newStr.substring(2, newStr.length());
                    			    $value = (double)Integer.parseInt(newStr, 2);}

				   |OCTAL {String newStr = $OCTAL.getText();
					   newStr = newStr.substring(1, newStr.length());
                    			   $value = (double)Integer.parseInt(newStr, 8);}

				   |HEXDECIMAL {String newStr = $HEXDECIMAL.getText();
                    				 newStr = newStr.substring(2, newStr.length());
                   				 $value = (double)Integer.parseInt(newStr, 16);}

				   |REAL {$value = Double.parseDouble($REAL.text);}

				   |'(' term ')' {$value = $term.value;};



log returns [double value]: log_result1 = expression {$value = $log_result1.value;}
		 	    |LOG expression {$value = Math.log($expression.value);}
		 	    |SIN expression {$value = Math.sin($expression.value);}
		 	    |COS expression {$value = Math.cos($expression.value);}
			    |TAN expression {$value = Math.tan($expression.value);};




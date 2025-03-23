grammar myGrammar;

types: bool_var types
     | int_var types
     | EOF          
     ;

var_name: NAME (',' NAME)*
     	;

bool_var: BOOL var_name ASSIGN bool_expr SEMI
        ;

int_var: INT var_name ASSIGN int_expr SEMI
       ;

int_expr: NUM int_expr_tail
        ;

int_expr_tail: int_oper NUM int_expr_tail
             | 
             ;

int_oper: '+' 
        | '-'
        ;

bool_expr: bool_val bool_expr_tail
         ;

bool_expr_tail: bool_oper bool_val bool_expr_tail
              | 
              ;

bool_val: 'TRUE' 
        | 'FALSE' 
        ;

bool_oper: '||'
         ;


// Lexer rules
NUM: [0-9]+;
INT: 'int';
BOOL: 'bool';
ASSIGN: '=';
SEMI: ';';
NAME: [a-zA-Z][a-zA-Z0-9]*;
WS: [ \t\r\n]+ -> skip; 



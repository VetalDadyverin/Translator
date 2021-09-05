# Simple translator of SIGNAL programming language
# Variant 6  

```
1. <signal-program> --> <program>
2. <program> --> PROGRAM <procedure-identifier> ; <block>.
3. <block> --> <declarations> BEGIN <statementslist> END
4. <statements-list> --> <empty>
5. <declarations> --> <constant-declarations>
6. <constant-declarations> --> CONST <constantdeclarations-list> | <empty>
7. <constant-declarations-list> --> <constantdeclaration> <constant-declarationslist> | <empty>
8. <constant-declaration> --> <constantidentifier> = <constant>;
9. <constant> --> '<complex-number>'
10. <complex-number> --> <left-part> <right-part>
11. <left-part> --> <unsigned-integer> | <empty>
12. <right-part> --> ,<unsigned-integer> | $EXP( <unsigned-integer> ) | <empty>
13. <constant-identifier> --> <identifier>
14. <procedure-identifier> --> <identifier>
15. <identifier> --> <letter><string>
16. <string> --> <letter><string> | <digit><string> | <empty>
17. <unsigned-integer> --> <digit><digits-string>
18. <digits-string> --> <digit><digits-string> | <empty>
19. <digit> --> 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9
20. <letter> --> A | B | C | D | ... |Z
```

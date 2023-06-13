Girleanu Andrei Alexandru-313CC - Banda Magica

Timp de implementare : 24 de ore

Punctaj obtinut la testele rulate pe propriul calculator : 120(100+20)

Problema realizeaza mai multe tipuri de operatii asupra unei benzi:
    -operatii de tip UPDATE, ce sunt introduse intr-o coada si sunt realizate
    doar la intalnirea lui EXECUTE : 
        MOVE_LEFT, MOVE_RIGHT, MOVE_LEFT_CHAR <C>, MOVE_RIGHT_CHAR <C>,
        WRITE <C>, INSERT_LEFT <C>, INSERT_RIGHT <C>
    -operatii de tip QUERY :
        SHOW_CURRENT, SHOW
    -operatii de tip UNDO/REDO
    -operatii de tip EXECUTE.

Banda este implementata printr-o lista dublu inlantuita cu santinela, definita
prin structura TList ce contine un pointer catre primul nod al listei(santinela),
definit prin structura nodeList, si unul catre nodul curent al listei, marcat in nodul
respectiv prin |c|. UNDO si REDO sunt executate cu ajutorul a 2 stive. De asemenea,
toate operatiile de tip UPDATE sunt introduse intr-o coada si extrase pe rand atunci
cand intalnim EXECUTE. Am realizat functii pentru fiecare operatie de tip UPDATE.
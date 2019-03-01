inherit ROOM;
#include <ansi.h> 

void create()
{
        set("short", "分天淵側");
        set("long", @LONG
過了分天崖，回頭望望，白雲寥寥，雲氣彌漫，想想還有點
後怕，但畢竟過來了。往前看，就是凌霄城了，這座武林中傳說
的名城，終于出現在你面前了，趕快進去看看吧。  
LONG);
        set("outdoors", "lingxiao");
        set("exits", ([
                    "north" : __DIR__"shanya",
                    "south" : __DIR__"bingqiao",
        ]));
        setup();
        replace_program(ROOM);
}


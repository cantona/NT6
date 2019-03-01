// Room /d/heimuya/midao5.c
// By haiyan

#include <room.h>
inherit ROOM;

void create()
{
     set("short", "秘道");
        set("long", @LONG
這是日月神教極其秘密的通道。是黑木崖與中原教眾取得聯系的
捷徑。
LONG );
     set("exits", ([
         "north"     : __DIR__"midao4",
         "southup"   : __DIR__"midao6",
     ]));
     set("no_clean_up", 0);
     setup();
     replace_program(ROOM);
}

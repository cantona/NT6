inherit ROOM;
#include <ansi.h> 

void create()
{
        set("short","走廊");
        set("long",@LONG 
這是一條安靜的走廊。上下都是凌霄弟子的居所，北邊是耿
鐘的居室，聽說他目前正在廣收門徒。南邊是汪萬翼的房間。西
邊是一個安靜的小間，可以在那睡覺休息。
LONG);
        set("outdoors", "lingxiao");
        set("exits", ([
                    "west"  : __DIR__"sleep",
                    "north" : __DIR__"roomgeng",  
                    "south" : __DIR__"roomwang", 
                    "east"  : __DIR__"zhongting",
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);

}

inherit ROOM;
#include <ansi.h> 

void create()
{
        set("short","走廊");
        set("long",@LONG 
這是一條安靜的走廊。上下都是凌霄弟子的居所，北邊是柯
萬仞的居室，最近似乎忙着收徒弟。南邊是凌霄城的物資室，由
張萬年主管。東邊是個廚房，飄來一陣陣飯菜的香味。
LONG);
        set("outdoors", "lingxiao");
        set("exits", ([
            "east"  : __DIR__"cook",
            "north" : __DIR__"roomke",  
            "south" : __DIR__"roomzhang", 
            "west"  : __DIR__"zhongting",
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);

}

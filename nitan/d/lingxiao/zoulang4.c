inherit ROOM;
#include <ansi.h> 

void create()
{
        set("short","走廊");
        set("long",@LONG 
這是一條安靜的走廊，北面是齊自勉的居室，南面是成自學
的房間。長老們向來除了授徒傳藝，少有外出，這裡一向少有人
來，只有凌霄弟子每日前來打掃。
LONG);
        set("outdoors", "lingxiao");
        set("exits", ([
                    "north"  : __DIR__"cheng",  
                    "south"  : __DIR__"qi", 
                    "southwest"  : __DIR__"houyuan2", 
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);

}

inherit ROOM;
#include <ansi.h> 

void create()
{
        set("short","走廊");
        set("long",@LONG 
這是一條安靜的走廊，少有閒人走動，凌霄城四位五代長老
就居住在此周圍。四老不喜花雪，是以深居此處。但聽説由於六
代弟子中白萬劍最為出色，甚至隱隱有壓倒四位長老之勢。四老
心中不喜，已不收弟子。
LONG);
        set("outdoors", "lingxiao");
        set("exits", ([
                    "north"  : __DIR__"liao",  
                    "south"  : __DIR__"liang", 
                    "southeast"  : __DIR__"houyuan2", 
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);

}

inherit ROOM;

#include <ansi.h> 

void create()
{
        set("short", "分天崖");
        set("long", @LONG 
這裏就是凌霄城的天險—分天崖。往外望去，只見萬丈深谷
上，橫着一座又窄又滑的冰梯，雪花飄落，更是滑溜，在強勁的
罡風中，給人一種搖搖欲墜的感覺。
LONG);
        set("outdoors", "lingxiao");
        set("exits", ([
                    "southdown" : __DIR__"sroad6",
                    "up" : __DIR__"bingti",
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}


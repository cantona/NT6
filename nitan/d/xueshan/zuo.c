// room: liang.c

#include <room.h>

inherit ROOM;

void create()
{ 
       set("short","金剛座");
        set("long", @LONG
你踩在金剛座上，密集金剛的臉龐近在咫尺，對著你默默微笑。
LONG );
        set("exits", ([
                "down" : "/d/xueshan/hongdian",
        ]));       
        set("objects", ([
                "/d/xueshan/obj/klguan" : 2,
                "/d/xueshan/obj/rtlian" : 2,
                "/d/xueshan/obj/lubo" : 2,
        ]));
        set("cost", 1);
        setup();
}



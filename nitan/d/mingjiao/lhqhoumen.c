//lhqhoumen.c

inherit ROOM;
#include <ansi.h>
void create()
{
        set("short", "烈火旗後門");
        set("long", @LONG
這裏就是烈火旗的後門，後面就是明教總舵所在，門宇軒大，教
眾出入紛紛。由於地處緊要，這裏的關防也很嚴密。
LONG );
        set("exits", ([
                "northup"   : __DIR__"zhandao1",
                "southdown" : __DIR__"lhqyuan",
        ]));
        set("objects", ([
                __DIR__"npc/tuoba" : 1,

        ]));
        set("outdoors", "mingjiao");
        set("no_clean_up", 0);
        setup();
}
int valid_leave(object me, string dir)
{
        me = this_player();
        if( objectp(me) && (query("family/family_name", me) != "明教") && 
            (dir=="northup") &&
            (objectp(present("tuoba", environment(me)))))
            return notify_fail("拓跋攔住你説：此處乃明教重地，請止步。\n");
        return ::valid_leave(me, dir);
}

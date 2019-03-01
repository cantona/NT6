// Room: /heizhao/shanlu4.c
// Date: Dec. 8 1999 by Winder

inherit ROOM;
#include <ansi.h>;
void create()
{
        set("short", "密林矮樹");
        set("long", @LONG
黑森森的四下裡都是樹木，無法直行，林中小路東盤西曲，密
林中難辨方向，你樹林之中來回奔行。這時你已知林中道路，乃是
由人工布置，這般時而向左，時而轉右，有時更倒退斜走數步，似
乎越行越是迂回迢遙。
LONG );
        set("outdoors", "heizhao");
        set("no_clean_up", 0);

        set("exits", ([
                "east"       : __DIR__"shanlu3",
                "west"       : __FILE__,
                "north"      : __FILE__,
                "south"      : __FILE__,
                "northwest"  : __FILE__,
                "southwest"  : __FILE__,
                "northeast"  : __FILE__,
                "southeast"  : __FILE__,
        ]));
        set("coor/x", -4000);
        set("coor/y", -1500);
        set("coor/z", 0);
        setup();
}

int valid_leave (object who, string dir)
{
        if(dir != "northeast")
        {
                addn_temp("heizhao3", -1, who);
                return ::valid_leave(who, dir);
        }
        else
        {
                if( query_temp("heizhao3", who)<26 )
                {
                        addn_temp("heizhao3", 1, who);
                        return ::valid_leave(who, dir);
                }
                else
                {
                        who->move(__DIR__"shanlu5");
                        return notify_fail(HIR"好辛苦哦！總算走過一程了！\n"NOR);
                }
        }
}
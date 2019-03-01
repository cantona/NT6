// Room: /heizhao/shanlu2.c
// Date: Dec. 8 1999 by Winder

inherit ROOM;
#include <ansi.h>;
void create()
{
        set("short", "密林矮樹");
        set("long", @LONG
往前苦苦走了二裡有余，但見黑森森的四下裡都是樹木，一入
林中，再也無法直行，林中小路東盤西曲，密林中難辨方向，忙躍
上樹去眺望，無論你往那邊望，都找不到出路。
LONG );
        set("outdoors", "heizhao");
        set("no_clean_up", 0);

        set("exits", ([
                "east"       : __DIR__"shanlu1",
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
                addn_temp("heizhao1", -1, who);
                return ::valid_leave(who, dir);
        }
        else
        {
                if( query_temp("heizhao1", who)<34 )
                {
                        addn_temp("heizhao1", 1, who);
                        return ::valid_leave(who, dir);
                }
                else
                {
                        who->move(__DIR__"shanlu3");
                        return notify_fail(HIR"好辛苦哦！總算走過一程了！\n"NOR);
                }
        }
}
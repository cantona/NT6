// Room: /heizhao/shanlu3.c
// Date: Dec. 8 1999 by Winder

inherit ROOM;
#include <ansi.h>;
void create()
{
        set("short", "密林矮樹");
        set("long", @LONG
黑森森的四下裏都是樹木，無法直行，林中小路東盤西曲，密
林中難辨方向，忙躍上樹去眺望，無論你往那邊望，都找不到出路。
欲待從樹頂上蹤躍過去，黑暗中卻看不清落足之處。
LONG );
        set("outdoors", "heizhao");
        set("no_clean_up", 0);

        set("exits", ([
                "east"       : __FILE__,
                "west"       : __FILE__,
                "north"      : "/d/npc/m_weapon/lianfushi",
                "south"      : __FILE__,
                "northwest"  : __FILE__,
                "southwest"  : __DIR__"shanlu2",
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
        if(dir != "west")
        {
                addn_temp("heizhao2", -1, who);
                return ::valid_leave(who, dir);
        }
        else
        {
                if( query_temp("heizhao2", who)<16 )
                {
                        addn_temp("heizhao2", 1, who);
                        return ::valid_leave(who, dir);
                }
                else
                {
                        who->move(__DIR__"shanlu4");
                        return notify_fail(HIR"好辛苦哦！總算走過一程了！\n"NOR);
                }
        }
}
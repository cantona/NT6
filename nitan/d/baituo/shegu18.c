// Code of ShenZhou
// shegu.c 蛇谷
// maco 7/15/2000

#include <ansi.h>
inherit ROOM;
string look_crack();

void create()
{
        set("short", "蛇谷樹林");
        set("long", @LONG
這是白駝山蛇谷中的一處密林，雜草叢生，樹木枝椏茂密，幽暗
陰森，古木盤根錯節，有些樹根間的裂縫 (crack)中響着細碎的聲音。
東北方地勢略高，是一處坡地。西南方是大片荒地，是蛇谷中最危險
的地帶。
LONG );

        set("exits", ([ 
            "east" : __DIR__"shegu17",
            "northeast" : __DIR__"shegu19",
            "southwest" : __DIR__"shegu_maze1",
        ]));

        set("item_desc", ([
        "crack" : (: look_crack :),
        ]));

        set("objects", ([
            __DIR__"npc/bt_snake" : 1,
        ]));

        set("hide_snake", 1+random(3));
        set("grass", 1);
        set("crack", 1);

        set("cost", 2);
        set("outdoors","baituo");
        set("shegu", 1);
        set("coor/x", -49950);
        set("coor/y", 20180);
        set("coor/z", 20);
        setup();
}

int valid_leave(object me, string dir)
{
        if (dir == "southwest") {
                if( query("family/family_name", me) == "白駝山"
                 && !query_temp("shegu/warning_18", me)){
                        set_temp("shegu/warning_18", 1, me);
                        return notify_fail( HIR"西南邊是蛇谷中大型蛇類出沒的荒地，你心裏暗自警惕，必需小心謹慎。\n"NOR+"做好心理準備的話，就再次前進吧。\n");
                }
        }
        return ::valid_leave(me,dir);
}


#include "snake_room.h"
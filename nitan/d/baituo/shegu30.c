// Code of ShenZhou
// shegu.c 蛇谷
// maco 7/15/2000

#include <ansi.h>
inherit ROOM;
string look_cave();

void create()
{
        set("short", "山壁");

        if(random(3) != 0 ) {
        set("long", @LONG
這是白駝山的蛇谷之中，附近緊鄰山壁，到處都是石礫。石壁上
稀稀疏疏地長著幾棵小樹，風吹過來，不時有一些小石頭從壁上滑落
下來。山壁一角有個小洞(cave)。
LONG );

                set("item_desc", ([
                "cave" : (: look_cave :),
                ]));

                set("hide_snake", 1);
                set("cave", 1);
        }
        else {
                set("long", @LONG
這是白駝山的蛇谷之中，附近緊鄰山壁，到處都是石礫。石壁上
稀稀疏疏地長著幾棵小樹，風吹過來，不時有一些小石頭從壁上滑落
下來。
LONG
                );
        }

        set("exits", ([ 
            "northeast" : __DIR__"shegu23",
        ]));

        set("cost", 2);
        set("outdoors","baituo");
        set("shegu", 1);
        set("coor/x", -50030);
        set("coor/y", 20200);
        set("coor/z", 20);
        setup();
}

#include "snake_room.h"
//Room: /d/dali/qingzhulin.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","青竹林");
        set("long",@LONG
一大片茂密的青竹林向西面山裏蔓延出去。此間竹子青嫩，竹筍
遍地，附近盧鹿族的台夷婦女常前來採摘竹筍為食，另外也砍伐些青
竹用來製做竹筒和編織的竹篾筐簍。
LONG);
        set("objects", ([
           __DIR__"npc/caisunren": 1,
        ]));
        set("outdoors", "dalis");
        set("exits",([ /* sizeof() == 1 */
            "east"   : __DIR__"wuding",
        ]));
	set("coor/x", -19160);
	set("coor/y", -6970);
	set("coor/z", 0);
	setup();
}

void init()
{
        object me = this_player();
        if( query_temp("xuncheng", me) )
        {
                set_temp("dali_xc/qzl", 1, me);
        }
}
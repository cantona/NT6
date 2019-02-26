//Room: /d/dali/nongtian.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","農田");
        set("long",@LONG
一小片在山坡下的竹林裏開墾出來的農田，臨有溪流，種植着水
稻。台夷生活很大程度上依靠農業，從事農業的卻基本上是婦女。男
子大都專司狩獵和捕魚。
LONG);
        set("objects", ([
           __DIR__"npc/nongfu1": 1,
        ]));
        set("outdoors", "dalis");
        set("exits",([ /* sizeof() == 1 */
            "north"      : __DIR__"wuding",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19150);
	set("coor/y", -6980);
	set("coor/z", 0);
	setup();
}

void init()
{
        object me = this_player();
        if( query_temp("xuncheng", me) )
        {
                set_temp("dali_xc/nt1", 1, me);
        }
}
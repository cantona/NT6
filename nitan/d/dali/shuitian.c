//Room: /d/dali/shuitian.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","水田");
        set("long",@LONG
這是一片低窪平地的農田，除了田埂，全部都被水淹沒著，一些
普麼部的婦女赤著腳在田裡插秧。這個地區雨水充足，雖然沒有江河
流過，無需特別的灌溉，每至春夏田裡自然雨水溢滿。
LONG);
        set("objects", ([
           __DIR__"npc/cow": 1,
           __DIR__"npc/nongfu1": 1,
        ]));
        set("outdoors", "dalis");
        set("exits",([ /* sizeof() == 1 */
            "north"      : __DIR__"luwang",
        ]));
	set("coor/x", -19120);
	set("coor/y", -6970);
	set("coor/z", 0);
	setup();
}

void init()
{
        object me = this_player();
        if( query_temp("xuncheng", me) )
        {
                set_temp("dali_xc/st", 1, me);
        }
}
//Room: /d/dali/minadian.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","蜜納甸");
        set("long",@LONG
這裡是烏夷分支烏蒙族闊部聚居的鎮子，闊部領蜜納甸和闊州。
附近有溪流匯入瀘水，灌溉頗便利，因而農業相對谷中其他地區較發
達。鎮中盡是些簡陋的民居，也無甚客商過往。
LONG);
        set("objects", ([
           __DIR__"npc/shaonu": 1,
        ]));
        set("outdoors", "daliw");
        set("exits",([ /* sizeof() == 1 */
            "west"      : __DIR__"gelucheng",
            "southwest" : __DIR__"zhenxiong",
        ]));
	set("coor/x", -19200);
	set("coor/y", -6850);
	set("coor/z", 20);
	setup();
}

void init()
{
        object me = this_player();
        if( query_temp("xuncheng", me) )
        {
                set_temp("dali_xc/mnd", 1, me);
        }
}
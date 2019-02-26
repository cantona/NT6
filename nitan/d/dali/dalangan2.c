//Room: /d/dali/dalangan2.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","杆欄中層");
        set("long",@LONG
這個杆欄的中層面積頗大，寬敞開闊。正中的香案古色古香，貢
着的神像雕制精細，顯得與眾不同，大盤的貢品正飄出香味，尤其當
中的一個羊頭特別搶眼。看來這裏是本村的祭祀所。
LONG);
        set("objects", ([
           __DIR__"npc/jisi1": 1,
        ]));
        set("exits",([ /* sizeof() == 1 */
            "down"  : __DIR__"dalangan1",
        ]));
	set("coor/x", -19000);
	set("coor/y", -6870);
	set("coor/z", 20);
	setup();
}

void init()
{
        object me = this_player();
        if( query_temp("xuncheng", me) )
        {
                set_temp("dali_xc/dlg2", 1, me);
        }
}
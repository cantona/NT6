//Room: /d/dali/langan2.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","桿欄中層");
        set("long",@LONG
這裡是桿欄的中層，從樓梯一上來就是祭所。南詘蠻夷大多信奉
自己部族特有的神明，家家戶戶都居中室設案供奉。中層的其余房間
則為寢所。
LONG);
        set("objects", ([
           __DIR__"npc/kid": 1,
        ]));
        set("exits",([ /* sizeof() == 1 */
            "down"      : __DIR__"langan1",
        ]));
	set("coor/x", -19060);
	set("coor/y", -6880);
	set("coor/z", 20);
	setup();
}
void init()
{
        object me = this_player();
        if( query_temp("xuncheng", me) )
        {
                set_temp("dali_xc/lg2", 1, me);
        }
}
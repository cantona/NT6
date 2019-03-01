// Room: fuheqiaon.c
// Date: Feb.14 1998 by Java

inherit ROOM;
void create()
{
        set("short","府河橋");
        set("long", @LONG
這裡是成都北門外府河橋。成都雖是川中首府，卻無險可守，一
旦敵方兵至成都平原，即使府南兩河水漲，也就只有禱告對方慈悲的
選擇了。
LONG );
        set("outdoors", "chengdu");
        set("exits",([ /* sizeof() == 1 */
            "north"  : "/d/qingcheng/qcroad1",
            "south"  : __DIR__"northgate",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -15220);
	set("coor/y", -1790);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
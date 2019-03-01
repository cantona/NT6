// Room: fuheqiaoe.c
// Date: Feb.14 1998 by Java

inherit ROOM;
void create()
{
        set("short","府河橋");
        set("long", @LONG
這裡是成都東門外府河橋。成都自古就是川中首府，府河和南河
夾城而過，成為天然的護城河。由于四川外有峽江，秦嶺之險，內仗
綿渝堅城之固，成都卻因之自來無坐守成功之績。往往兵到城下，降
旗高扯了。
LONG );
        set("outdoors", "chengdu");
        set("exits",([ /* sizeof() == 1 */
            "east"  : __DIR__"road2",
            "west"  : __DIR__"eastgate",
        ]));
        set("objects", ([
                "/clone/npc/walker"  : 1,
        ]));
        set("no_clean_up", 0);
        set("coor/x", -15180);
	set("coor/y", -1830);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
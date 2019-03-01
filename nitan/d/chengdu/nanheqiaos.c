// Room: nanheqiaos.c
// Date: Feb.14 1998 by Java

inherit ROOM;
void create()
{
        set("short","南河橋");
        set("long", @LONG
這裏是成都南門外南河橋。府河和南河夾城流過，成為天然的護
城河，滋潤着這個天府之國的川中首府。向北就進城了，向南又是一
條小路。
LONG );
        set("outdoors", "chengdu");
        set("exits",([ /* sizeof() == 1 */
            "south"  : "/d/xuedao/sroad1",
            "north"  : __DIR__"southgate",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -15220);
	set("coor/y", -1870);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
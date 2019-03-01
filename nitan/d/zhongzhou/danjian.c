inherit ROOM;

void create()
{
        set("short", "鴉片館");
        set("long", @LONG
這是鴉片館內的一個小單間，有幾個人正在打麻將。看上
去這個鴉片館就是他們開的。
LONG);
        set("exits", ([
                 "west" : __DIR__"yanguan",                 
        ]));

        set("coor/x", -9040);
	set("coor/y", -1020);
	set("coor/z", -10);
	setup();
        replace_program(ROOM);
}
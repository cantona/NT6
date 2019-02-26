// Room: /d/suzhou/dongting.c
// Last Modified by winder on Mar. 8 2001

inherit ROOM;

void create()
{
        set("short", "東廳");
        set("long", @LONG
這裏是衙門東廳，是知府招待客人的所在。廳中擺着一張杉木圓桌
和幾張椅子，桌上是一套精緻的宜興瓷器。牆上掛着一幅中堂，畫的是
猛虎下山，乃是知府的手筆。
LONG
        );
        set("exits", ([
                "west" : __DIR__"yamen",
        ]));
        set("no_clean_up", 0);
	set("coor/x", 1110);
	set("coor/y", -1040);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
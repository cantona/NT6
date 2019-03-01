//Room: tuchangguan.c

inherit ROOM;

void create()
{
        set("short", "土娼館");
        set("long", @LONG
還沒想好呢！呵呵！
LONG );
        set("exits", ([ /* sizeof() == 1 */
                "south" : "/d/changan/huarui6",
        ]));
        set("objects", ([
                "/d/changan/npc/jinu" : 1,
        ]) );

        set("coor/x", -10690);
	set("coor/y", 1910);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
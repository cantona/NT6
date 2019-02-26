// Room: /d/xiangyang/duchang.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "賭場");
        set("long", @LONG
這裏本是襄陽最大的賭場。可是大戰當前，為免守軍軍心動搖、
軍紀敗壞，郭大俠早已下令關閉了賭場。門可羅雀的大院，可以想象
當時的規模，閒置破敗的賭具，也不知道在無聲地訴説什麼。
LONG );
        set("no_clean_up", 0);

        set("exits", ([
                "east" : __DIR__"southjie2",
        ]));
        set("coor/x", -7830);
	set("coor/y", -790);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
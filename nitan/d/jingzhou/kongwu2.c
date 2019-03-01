//Edited by fandog, 01/31/2000

inherit ROOM;

void create ()
{
        set ("short", "空屋");
        set ("long", @LONG
一間空盪盪的屋子，連桌椅也沒一張。可是瞧那模樣，卻又不是新
近搬走了家庭用具，而是許多年來一直便如此空無所有。
LONG);
        set("exits", ([ 
                "north" : __DIR__"kongwu1",
        ]));
        set("objects", ([ 
                __DIR__"obj/greenflower" : random(2),
        ]));
        set("no_clean_up", 0);
        set("coor/x", -7110);
	set("coor/y", -2100);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}
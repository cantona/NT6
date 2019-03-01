inherit ROOM;

void create()
{
        set("short", "湖邊小路");
        set("long", @LONG
這是聖湖邊的小路。路側長草沒足， 青綠可喜。
LONG );
        set("outdoors", "xuedao");
        set("exits", ([
                "north" : __DIR__"shanjiao",
                "south" : __DIR__"hubian3",
        ]));
        set("objects", ([
                "/clone/npc/walker" : 1,
        ]));
        setup();
        replace_program(ROOM);
}
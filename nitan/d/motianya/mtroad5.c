inherit ROOM;

void create()
{
        set("short", "樹林");
        set("long", @LONG
這裡是茂密的森林。四周都是數不清的長草，一股陰森恐怖的氣
氛。遠處不時傳來野獸的嚎叫，你實在不想在這裡多留。
LONG );
        set("outdoors", "motianya");
        set("exits", ([
                "east"  : __DIR__"mtroad4",
                "west"  : __FILE__,
                "north" : __FILE__,
                "south" : __FILE__,
        ]));
        set("objects", ([
                "/clone/quarry/zhu2" : 1,
        ]));
        setup();
        replace_program(ROOM);
}
// mtroad2.c  樹林

inherit ROOM;

void create()
{
        set("short", "樹林");
        set("long", @LONG
這裏是茂密的森林。四周都是數不清的長草，一股陰森恐怖的氣
氛。遠處不時傳來野獸的嚎叫，你實在不想在這裏多留。
LONG );
        set("outdoors", "motianya");
        set("exits", ([
            "east"  : __DIR__"mtroad1",
            "west"  : __FILE__,
            "south" : __FILE__,
            "north" : __DIR__"mtroad3",
        ]));

        setup();
        replace_program(ROOM);
}
// mtroad1.c  樹林

inherit ROOM;

void create()
{
        set("short", "樹林");
        set("long", @LONG
這裏是茂密的森林。四周都是數不清的長草，一股陰森恐怖的
氣氛。遠處不時傳來野獸的嚎叫，你實在不想在這裏多留。
LONG );
        set("outdoors", "motianya");
        set("exits", ([
            "east"  : "/d/henshan/hsroad5",
            "west"  : __DIR__"mtroad",
            "north" : __FILE__,
            "south" : __DIR__"mtroad2",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -2000);
        set("coor/y", -1600);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
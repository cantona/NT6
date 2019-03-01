// /d/xiakedao/mtroad5.c  樹林
// Modified by Zeratul Jan 11 2001

inherit ROOM;

void create()
{
        set("short", "樹林");
        set("long", @LONG
這裡是茂密的森林。四周都是數不清的長草，一股陰森恐怖的
氣氛。遠處不時傳來野獸的嚎叫，你實在不想在這裡多留。
LONG );
        set("outdoors", "motianya");
        set("exits", ([
            "east"  : __DIR__"mtroad4",
            "west"  : __FILE__,
            "north" : __FILE__,
            "south" : __FILE__,
        ]));
/*        set("objects", ([
            __DIR__"npc/yezhu" : 1,
        ]));*/
        setup();
        replace_program(ROOM);
}

// tongmen.c
// Modified by Winder June.25 2000

inherit ROOM;

void create()
{
        set("short", "銅門");
        set("long", @LONG
這是一個月形的銅門，門旁的壁上鑿著“琅環福地”四個大字。
LONG );
        set("exits", ([
                "south" : __DIR__"shiji3",
                "west" : __DIR__"fangjian3",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -50000);
        set("coor/y", -21020);
        set("coor/z", -40);
        setup();
        replace_program(ROOM);
}
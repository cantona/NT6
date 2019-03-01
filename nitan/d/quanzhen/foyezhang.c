// foyezhang.c
// Java Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "佛爺掌");
        set("long", @LONG
只見此處頗為荒涼，是一處寺院的遺址。四周青松翠柏環繞，寺
院的斷垣殘璧依稀可見，似乎還是一座不小的寺院。往北是一片平原。
LONG
        );
        set("outdoors", "zhongnan");
        set("exits", ([
                "east"  : __DIR__"shenheyuan",
        ]));

        set("coor/x", -3180);
        set("coor/y", 70);
        set("coor/z", 90);
        setup();
        replace_program(ROOM);
}
// Room: /d/hengshan/cuiping1.c
// Date: Oct. 2 1997 by That

inherit ROOM;

void create()
{
        set("short", "翠屏山道");
        set("long", @LONG
你爬在翠屏山道上，石階陡峭，近在目前。回頭外望，恆山重巒疊
嶂，林木幽深，倍感靜謐。
LONG
        );
        set("exits", ([
                "westup"  : __DIR__"cuiping2",
                "down"    : __DIR__"cuipinggu2",
        ]));

        set("outdoors", "hengshan");
        set("no_clean_up", 0);
        set("coor/x", 0);
        set("coor/y", 3180);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}

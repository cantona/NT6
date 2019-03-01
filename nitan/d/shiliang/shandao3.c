// Feb. 6, 1999 by Winder
inherit ROOM;
void create()
{
        set("short", "山洞口");
        set("long", @LONG
你來到一個大山洞的面前，裡面黑乎乎的，怪嚇人的，還
是不要進去的好。
LONG
        );
        set("outdoors", "shiliang");
        set("exits", ([
                "southdown" : __DIR__"shandao2",
                "north"     : __DIR__"shandong1",
        ]));
        set("coor/x", 1590);
        set("coor/y", -1970);
        set("coor/z", 20);
        setup();
        replace_program(ROOM);
}
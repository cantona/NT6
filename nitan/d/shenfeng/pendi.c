inherit ROOM;

void create()
{
        set("short", "盆地");
        set("long", @LONG
這地方是個盆地，四周高山拱衞，以致風雨不侵，千百年
之物仍能如此完好，實是罕見罕聞，沿路只見遍地白骨，刀槍
劍戟，到處亂丟。城中道路也是如迷宮，令人眼花繚亂。
LONG);
        set("outdoors", "gaochang");

        set("exits", ([
                "east" : __DIR__"feixu2",
                "north" : __DIR__"shanjiao",
        ]));

        setup();
        replace_program(ROOM);
}
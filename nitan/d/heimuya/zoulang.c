inherit ROOM;

void create()
{
        set("short", "走廊");
        set("long", @LONG
這是成德殿內的一條木製的走廊，紅漆地面很是光滑，整個走廊
被打整得一塵不染。你不時能夠看到幾個成德殿的侍女在此走動，忙
碌個不停。
LONG );
        set("exits", ([
                "north"  : __DIR__"huoting",
                "south"  : __DIR__"chengdedian",
        ]));
        set("objects", ([
                __DIR__"npc/zish" : 1,
        ]));
        setup();
        replace_program(ROOM);
}
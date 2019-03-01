inherit ROOM;

void create()
{
        set("short", "帕米爾高原");
        set("long", @LONG
翻過天山頂峰，便來到帕米爾高原。真是天外有天，你仿
佛來到另一個世界。這兒冰雪消融，春意盎然。從那雪峰直垂
下來的溪澗裡，長滿了野果樹。山風習習，空氣清涼如水。山
花爛漫, 幾裡地外也能聞到馥鬱的花香。
LONG);
        set("outdoors", "gaochang");
        set("exits", ([
            "southdown" : __DIR__"huijiang2",
        ]));

        set("objects", ([
                "clone/quarry/lang"  : 1,
        ]));

        set("quarrys", ([
                "gou"   : 100000,
                "lang"  : 80000,
                "lang2" : 50000,
        ]));

        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
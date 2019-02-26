// Room: /d/village/eroad1.c

inherit ROOM;

void create()
{
        set("short", "碎石路");
        set("long", @LONG
這是一個寧靜的小村子，稀稀落落的分佈着幾十間土坯泥房，看
來村中人家不多，而且大都生活很艱辛。一條碎石路，往西通向村子
的中心，往東就是出村的路了。南面是一間很簡陋的草棚。
LONG );
        set("exits", ([ /* sizeof() == 3 */
            "south" : __DIR__"ehouse1",
            "east"  : __DIR__"eexit",
            "west"  : __DIR__"eroad2",
        ]));

        set("outdoors", "village");

        setup();
        replace_program(ROOM);
}


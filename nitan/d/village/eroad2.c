// Room: /d/village/eroad2.c

inherit ROOM;

void create()
{
        set("short", "碎石路");
        set("long", @LONG
這是一個寧靜的小村子，稀稀落落的分佈着幾十間土坯泥房，看
來村中人家不多，而且大都生活很艱辛。這是一條東西向的碎石路，
北面是間結實的民宅。
LONG );
        set("exits", ([ /* sizeof() == 3 */
            "east"  : __DIR__"eroad1",
            "west"  : __DIR__"eroad3",
            "north" : __DIR__"ehouse2",
        ]));

        set("outdoors", "village");

        setup();
        replace_program(ROOM);
}

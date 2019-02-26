// Room: /d/village/sroad2.c

inherit ROOM;

void create()
{
        set("short", "碎石路");
        set("long", @LONG
這是一個寧靜的小村子，稀稀落落的分佈着幾十間土坯泥房，看
來村中人家不多，而且大都生活很艱辛。這是一條南北向的碎石路，
東面是一間小土房。
LONG );
        set("exits", ([ /* sizeof() == 3 */
            "north" : __DIR__"sroad3",
            "south" : __DIR__"sroad1",
            "east"  : __DIR__"shouse",
        ]));
        set("outdoors", "village");

        setup();
        replace_program(ROOM);
}

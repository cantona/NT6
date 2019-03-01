// Room: /d/village/nwroad1.c

inherit ROOM;

void create()
{
        set("short", "碎石路");
        set("long", @LONG
這是一個寧靜的小村子，稀稀落落的分布著幾十間土坯泥房，看
來村中人家不多，而且大都生活很艱辛。東北邊有間小廟，廟匾上的
字早已模糊不清，看不出是什麼廟了。
LONG );
        set("exits", ([ /* sizeof() == 3 */
            "west"      : __DIR__"wexit",
            "southeast" : __DIR__"nwroad2",
            "northeast" : __DIR__"temple1",
        ]));
        set("outdoors", "village");

        setup();
        replace_program(ROOM);
}

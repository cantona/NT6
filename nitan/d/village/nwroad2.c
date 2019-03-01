// Room: /d/village/nwroad2.c

inherit ROOM;

void create()
{
        set("short", "碎石路");
        set("long", @LONG
這是一個寧靜的小村子，稀稀落落的分布著幾十間土坯泥房，看
來村中人家不多，而且大都生活很艱辛。東南邊就是村子中心的打谷
場了，西南是間民房。
LONG );
        set("exits", ([ /* sizeof() == 3 */
            "northwest" : __DIR__"nwroad1",
            "southeast" : __DIR__"square",
            "southwest" : __DIR__"nwhouse",
        ]));
        set("outdoors", "village");

        setup();
        replace_program(ROOM);
}


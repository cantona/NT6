// Room: /d/village/eroad3.c

inherit ROOM;

void create()
{
        set("short", "碎石路");
        set("long", @LONG
這是一個寧靜的小村子，稀稀落落的分佈着幾十間土坯泥房，看
來村中人家不多，而且大都生活很艱辛。這是一條東西向的碎石路，
往西就是村子中心的打穀場了，南面是一間鐵匠鋪子，北面是家雜貨
店。
LONG );
        set("exits", ([ /* sizeof() == 4 */
            "north" : __DIR__"shop",
            "south" : __DIR__"smithy1",
            "east"  : __DIR__"eroad2.c",
            "west"  : __DIR__"square",
        ]));
        set("objects", ([
            __DIR__"npc/girl": 1
        ]) );

        set("outdoors", "village");

        setup();
        replace_program(ROOM);
}

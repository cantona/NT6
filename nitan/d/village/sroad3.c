// Room: /d/village/sroad3.c

inherit ROOM;

void create()
{
        set("short", "碎石路");
        set("long", @LONG
這是一個寧靜的小村子，稀稀落落的分佈着幾十間土坯泥房，看
來村中人家不多，而且大都生活很艱辛。這是一條南北向的碎石路，
西邊有一條黑黑暗暗的小巷子。
LONG );
        set("exits", ([ /* sizeof() == 3 */
            "north" : __DIR__"sroad4",
            "south" : __DIR__"sroad2",
            "west"  : __DIR__"alley1",
        ]));
        set("objects", ([
            __DIR__"npc/boy": 3,
        ]));
        set("outdoors", "village");

        setup();
        replace_program(ROOM);
}

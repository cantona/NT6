inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
這裡是靠近川西的崇山峻嶺，怪石嶙峋。再往東去就是川西邊緣
了。往西有一座雪山高聳入雲。路邊上有個雪坑。
LONG );
        set("exits", ([
                "east"      : __DIR__"sroad2",
                "southdown" : __DIR__"hollow",
                "north"     : __DIR__"sroad0",
                "westup"    : __DIR__"sroad4",
        ]));
        set("objects", ([
                "/clone/npc/walker"  : 1,
        ]));
        set("outdoors", "xuedao");
        setup();
}

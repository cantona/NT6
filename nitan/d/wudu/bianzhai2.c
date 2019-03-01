inherit ROOM;

void create()
{
        set("short", "邊寨風情");
        set("long", @LONG
這裡已是苗疆地界，只覺得山清水秀，風景與中原大不相同。你
走在路上，不時會碰到少男少女在路邊田野裡載歌載舞，頓時覺得心
情舒暢，但願終老此鄉。
LONG);
        set("outdoors", "wudujiao");

        set("exits", ([
                "east" : __DIR__"bianzhai1",
                "south" : __DIR__"bianzhai3",
        ]));
        set("objects", ([
                 __DIR__"npc/youngboy": 1,
        ]));

        setup();
        replace_program(ROOM);
}

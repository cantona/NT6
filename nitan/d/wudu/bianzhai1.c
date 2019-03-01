inherit ROOM;

void create()
{
        set("short", "邊寨風情");
        set("long", @LONG
這裡已是苗疆地界，只覺得山清水秀，風景與中原大不相同。你
走在路上，不時會碰到少男少女在路邊田野裡載歌載舞，頓時只覺心
情舒暢，但願終老此鄉。南面就是有名的黑森林了。
LONG);
        set("outdoors", "wudujiao");

        set("exits", ([
                "south" : __DIR__"milin8",
                "west" : __DIR__"bianzhai2",
                "southwest" : __DIR__"bianzhai3",
        ]));
        set("objects", ([
                "/clone/npc/walker" : 1,
        ]));
        setup();
}

inherit ROOM;

void create()
{
        set("short", "巖洞");
        set("long", @LONG
這裡是一個大巖洞，在白駝山特殊的地質條件下經過漫長的年代
形成的。洞內蜿蜒曲折，也不知延伸到了何處。
LONG );
        set("exits", ([
                "enter"     : __DIR__"cave1",
                "southdown" : __DIR__"zhulin",
        ]));
        set("objects", ([
                "/clone/beast/mangshe" : 1,
        ]));
        set("outdoors", "baituo");
        set("coor/x", -50000);
        set("coor/y", 20050);
        set("coor/z", 40);
        setup();
}

int valid_leave(object me, string dir)
{
        if (dir == "enter"
           && objectp(present("mang she", environment(me))))
                        return notify_fail("蟒蛇盤在巖洞口，將路封了個嚴實。\n");

        return ::valid_leave(me, dir);
}
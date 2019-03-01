inherit ROOM;

void create()
{
        set("short", "青石大道");
        set("long", @LONG
你走在一條青石大道上，南邊隱約可見到洛陽城的城牆。北面兩
條土路分岔通向山裡。
LONG );
        set("outdoors", "village");
        set("exits", ([
                "south"     : __DIR__"hsroad1",
                "northwest" : __DIR__"hsroad3",
                "northeast" : "/d/huashan/jzroad1",
        ]));

        setup();
        replace_program(ROOM);
}

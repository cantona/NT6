// road2.c
// by Xiang

inherit ROOM;

void create()
{
        set("short", "黃土路");
        set("long", @LONG
你走在一條黃土路上。西南是一個小高崗，地勢險惡，客旅斷絕。
東面隱隱可以看到平定州城。
LONG );
        set("outdoors", "heimuya");
        set("exits", ([
            "southwest" : __DIR__"road1",
            "east" : __DIR__"pingdingzhou",
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
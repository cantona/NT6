inherit ROOM;

void create()
{
        set("short", "小溪");
        set("long",@LONG
這是神龍島東南的一處小溪。
LONG);

        set("exits", ([
                "north"  : __DIR__"xiaoxi1",                 
                "south" : __DIR__"guanlongting",

        ]));

        set("outdoors", "shenlong");
        setup();
}

inherit ROOM;

void create()
{
        set("short", "青石大道");
        set("long", @LONG
你走在一條青石大道上，四周靜悄悄的。西邊是一條大道，
東邊是好大的一片樹林。往南還有一條大道，卻掩映在了密密
的樹林中。
LONG );
        set("outdoors", "sanbuguan");
        set("exits", ([
                "west"    : __DIR__"wdroad5",
                "east"    : "/d/xiaoyao/shulin3",
                "southwest" : "/d/henshan/hsroad1",
                "north"   : __DIR__"wdroad3",
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}

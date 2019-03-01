inherit ROOM;

void create()
{
        set("short", "東大街");
        set("long", @LONG
你走在東大街上，踩著堅實的青石板地面。東邊不遠是東城門，
可以聽到守城官兵的吆喝聲，與西邊朗朗的讀書聲混雜在一起。北邊
是一家小小的雜貨舖。
LONG );
        set("outdoors", "jingzhou");
        set("exits", ([
                "east" : __DIR__"jzdongmen",
                "west" : __DIR__"dongdajie1",
                "north" : __DIR__"shop",
                "south" : __DIR__"xxiang",
        ]));
        set("objects", ([
                "/d/beijing/npc/boy3" : 1,
                  "/d/jingzhou/npc/langzhong" : 1,
        ]));
        set("coor/x", -7080);
	set("coor/y", -2050);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
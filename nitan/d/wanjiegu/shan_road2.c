inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
這是一條山間小路，兩邊山坡上張了許多樹木，北風吹過發出沙
沙的響聲。路上張着許多雜草，看來很少有人走動。
LONG );
        set("outdoors", "wanjiegu");
        set("exits", ([
            "westdown" : __DIR__"shan_road3",
            "eastdown" : __DIR__"shan_road1",
        ]));
        set("objects", ([
            "/d/wanjiegu/npc/haoke" : 2,
            "/d/wanjiegu/npc/bee" : 2,
        ]));
        setup();
        replace_program(ROOM);
}
// Room: /t/wanjiegu/shan_road4.c

inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
這是一條山間小路，兩邊山坡上張了許多樹木，北風吹過，發出
沙沙的響聲。路上張着許多雜草，看起來這裏很少有人走動。往西看，
遠遠可見黑壓壓一片大森林。
LONG );
        set("outdoors", "wanjiegu");
        set("exits", ([ /* sizeof() == 2 */
            "west" : __DIR__"entrance",
            "southup" : __DIR__"shan_road3",
        ]));
        set("no_clean_up", 0);

        setup();
        replace_program(ROOM);
}
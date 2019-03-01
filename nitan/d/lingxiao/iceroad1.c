inherit ROOM;

void create()
{
        set("short", "冰道");
        set("long", @LONG
這裡是一片冰雕玉砌的世界。走在路上，低頭一看，路面是
用萬載不化的寒冰所制，晶瑩剔透，足可映物，照理說走在這樣
的冰上，應該滑溜不堪，但仔細一看，每處冰道上，都雕有細細
的花紋，而且做工精細，顯然耗費了大量人力。
LONG);
        set("outdoors", "lingxiao");
        set("exits", ([
                    "south" : __DIR__"gate",
                    "north" : __DIR__"iceroad2",
                    "west"  : __DIR__"hotel",
                    "east"  : __DIR__"sell",
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}

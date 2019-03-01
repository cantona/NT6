// Room: /d/shaolin/hsyuan1.c
// Date: YZC 96/01/19

inherit ROOM;

void create()
{
        set("short", "和尚院一部");
        set("long", @LONG
這裡是和尚院待客的地方，靠牆左右兩側擺著一溜太師椅。牆角
一幾，放著幾個茶壺。有個茶壺壺身上題了『碧螺春』三個篆字，壺
嘴熱氣騰騰，似乎是剛沏的新茶。一位小沙彌在一邊垂手站立。
LONG );
        set("exits", ([
                "west" : __DIR__"wuchang3",
                "east" : __DIR__"zhulin1",
                "south" : __DIR__"zoulang7",
                "north" : __DIR__"hsyuan2",
        ]));
        set("objects",([
                CLASS_D("shaolin") + "/hui-he" : 1,
        ]));
//        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}

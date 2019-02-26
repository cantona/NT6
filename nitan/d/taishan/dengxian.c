// Room: /d/taishan/dengxian.c
// Last Modified by winder on Aug. 25 2001

inherit ROOM;

void create()
{
        set("short", "登仙橋");
        set("long", @LONG
登仙橋，俗稱東西橋子，就在天紳巖北。橋西南遍地紅沙石，名紅
沙嶺。橋北東側有古洞如棚，可以容馬，明代吳維嶽大書“歇馬崖”。
舊傳呂洞賓曾在此崖上留墨。
LONG );
        set("exits", ([
                "south" : __DIR__"tianshen",
                "north" : __DIR__"baidong",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "taishan");
        set("coor/x", 70);
	set("coor/y", 150);
	set("coor/z", 60);
	setup();
        replace_program(ROOM);
}
// Room: /d/taishan/baozang.c
// Last Modified by Winder on Aug. 25 2001

inherit ROOM;

void create()
{
        set("short", "寶藏嶺");
        set("long", @LONG
這裡是泰山的又一個名勝。嶺上有一座狀似獅子的巨石，稱為獅子
崖。最出名的還是要數在東北面的東岳廟，也稱上岳廟，是古代封禪的
地方，那裡有一塊唐玄宗的紀泰山銘。
LONG );
        set("exits", ([
                "northwest" : __DIR__"bixia",
        ]));
        set("outdoors", "taishan");
        set("no_clean_up", 0);
        set("coor/x", 70);
	set("coor/y", 290);
	set("coor/z", 210);
	setup();
        replace_program(ROOM);
}
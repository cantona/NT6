// Room: /d/suzhou/shijianshi.c
// Date: May 31, 98  Java

inherit ROOM;

void create()
{
        set("short", "試劍石");
        set("long", @LONG
在山道東側是試劍石，呈橢圓形，正中有條深而齊裂的裂縫，相傳
吳王得“干將”、“莫邪”二劍後，為試其鋒利，將石劈開。石旁刻着
元代顧瑛的詩句：“劍試一痕秋，崖傾水斷流，如何百年後，不斬趙高
頭？”的詩句。
LONG );
        set("outdoors", "suzhou");
        set("no_clean_up", 0);
        set("exits", ([
                "northeast" : __DIR__"zhenniang",
                "south"     : __DIR__"qianrenshi",
                "north"     : __DIR__"zhenshi",
                "westdown"  : __DIR__"wanjing",
        ]));
        set("objects", ([
                "/d/taishan/npc/jian-ke" : 1,
        ]));
	set("coor/x", 1100);
	set("coor/y", -1030);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}
//Room: /d/dali/paifang.c
//Date: June. 29 1998 by Java

inherit ROOM;

void create()
{
        set("short", "牌坊");
        set("long", @LONG
這是大理城的牌坊，正中一個牌坊上寫着四個金色大字： 聖道廣
慈。西邊是皇宮，東邊是一條青石大道，由於大理國主體民如子，雖
皇宮近在咫尺，但金吾不禁，百姓往來如潮。
LONG );
        set("outdoors", "dali");
        set("exits", ([
                "east"  : "/d/dali/wangfulu",
                "west"  : "/d/dali/yujie",
                "south" : "/d/dali/taihejiekou",
                "north" : "/d/dali/northgate",
        ]));
        set("objects", ([
                CLASS_D("hu") + "/huyizhi" : 1
        ]));
	set("coor/x", -19130);
	set("coor/y", -6870);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
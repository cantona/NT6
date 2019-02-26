// Room: /city/beidajie1.c
// YZC 1995/12/04 

inherit ROOM;
void create()
{
        set("short", "北大街");
        set("long", @LONG
你走在一條繁忙的街道上，看着操着南腔北調的人們行色匆匆，
許多人都往南邊走去，那裏有一個熱鬧的廣場。東邊是一家生意興隆
的客棧，來自各地的人們進進出出，據説也是情人們的幽會地點。西
邊是一家錢莊，可以聽到叮叮噹噹的金銀聲音。
LONG );
        set("outdoors", "city");
        set("objects", ([
                CLASS_D("ouyang") + "/ouyangke" : 1,
        ]));
        set("exits", ([
                "east"  : "/d/city/kedian",
                "south" : "/d/city/guangchang",
                "west"  : "/d/city/qianzhuang",
                "north" : "/d/city/beidajie2",
        ]));

	set("coor/x", 0);
	set("coor/y", 10);
	set("coor/z", 0);
	setup();
}
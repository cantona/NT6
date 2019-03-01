inherit ROOM;

void create()
{
        set("short", "市中心");
        set("long", @LONG
這是中州的市中心，兩條街道在這裡劃個大十字。整個中
州就數著兩條街道最熱鬧了。其間三教九流，行行色色的人來
來往往。南北一條寬敞的街道，一看就是剛剛修建好不久，路
牌清楚的寫著「文定街」。東西那條街道要陳舊一點，一塊路
牌上的字已看不太清，依稀刻著「延陵路」三個字。
LONG);
        set("outdoors", "zhongzhou");
        set("exits", ([
                  "east" : __DIR__"yanlingdong",
                  "south" : __DIR__"wendingnan1",
                  "west" : __DIR__"yanling",
                  "north" : __DIR__"wendingbei1",
        ]));
        set("objects", ([
                "/clone/npc/walker" : 1,
        ]));
        set("coor/x", -9040);
	set("coor/y", -1000);
	set("coor/z", 0);
	setup();
}
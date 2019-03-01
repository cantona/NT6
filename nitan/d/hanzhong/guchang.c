// guchang.c 曬谷場
// Winder Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "曬谷場");
        set("long", @LONG
這裡是村莊中心的曬谷場，地方不大，不過村裡也就五、六戶人
家，種的谷子也夠曬了。現在正是收獲的季節，谷場中堆滿了谷子，
幾個男女童子正在場中嬉鬧，不時地揚起一捧谷子相互撒去。
LONG
        );
        set("outdoors", "hanzhong");
        set("exits", ([
                "southeast" : __DIR__"xiaocun",
                "north" : __DIR__"cunzhangjia",
                "northwest" : __DIR__"minju3",
                "southwest" : __DIR__"minju4",
        ]));
        set("objects", ([
                __DIR__"npc/boy" : 2,
                __DIR__"npc/girl" : 1,
        ]));

        set("coor/x", -12270);
	set("coor/y", 840);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}
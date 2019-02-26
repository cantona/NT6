// Room: /d/jiaxing/nanhu1.c
// Last Modified by winder on Nov. 17 2000

inherit ROOM;

void init();
int do_out();

void create()
{
        set("short", "嘉興南湖");
        set("long", @LONG
這裏是煙波浩淼的南湖。湖上幾隻畫舫在遊蕩，船上的遊客和青樓
女子在嘻笑。湖水很深，沒有船是渡不過去的。但不知是誰在湖底釘了
一些木樁。樁頂潛在水面之下一兩寸的地方。即使是不懂輕功的人走上
去也像是水上漂的樣子。
LONG );
        set("exits", ([
                "south"     : __DIR__"yanyu",
                "northwest" : __DIR__"nanhu",
                "southeast" : __DIR__"road",
        ]));
        set("outdoors", "jiaxing");
        set("objects", ([
                "/clone/medicine/vegetable/heye" : random(2),
        ]));
        set("resource/fish", ({ "/clone/fish/liyu",
                                "/clone/fish/jiyu",
                                "/clone/fish/qingyu",
                                "/clone/fish/caoyu", }));

	set("coor/x", 1210);
	set("coor/y", -1780);
	set("coor/z", 0);
	setup();
}
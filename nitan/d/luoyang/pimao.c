inherit ROOM;

void create()
{
        set("short", "皮貨店");
        set("long", @LONG
這是洛陽的一家皮貨店，專賣各式各樣的皮貨。據説店主自開店以來
很少賣出什麼真正的皮貨，倒是傳聞他總是零星地高價出售一些書畫名家
曾經用過的筆硯。店內正堂掛有一滿是塵土的細字長匾，匾上書有“童叟
無欺”四字。
LONG);
        set("no_clean_up", 0);
        set("exits", ([
                  "east" : __DIR__"nroad4",
        ]));
        set("objects", ([
                "/d/kaifeng/npc/huizhang" : 1,
        ]));
	set("coor/x", -7000);
	set("coor/y", 2220);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
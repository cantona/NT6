// Room: /d/taishan/riguan.c
// Last Modified by Winder on Aug. 25 2001

inherit ROOM;

void create()
{
        set("short", "日觀峰");
        set("long", @LONG
日觀峰位于玉皇頂東南，古稱介丘巖，因可觀日出而名。相傳在峰
巔西可望秦，南可望越，故又稱秦觀峰、越觀峰。這裡怪石攢簇，最高
的地方一石卓立，名為君子峰。往東走便是通往泰山東天門的山路。
LONG );
        set("exits", ([
                "south"     : __DIR__"aishen",
                "eastup"    : __DIR__"tanhai",
                "eastdown"  : __DIR__"riguanroad1",
                "northwest" : __DIR__"yuhuang",
        ]));
        set("objects", ([
                CLASS_D("taishan")+"/tianmen" : 1,
        ]));
        set("valid_startroom", 1);
        set("outdoors", "taishan");
        set("coor/x", 40);
	set("coor/y", 300);
	set("coor/z", 210);
	setup();
        "/clone/board/taishan_b"->foo();
}

int valid_leave(object me, string dir)
{
        if (dir != "northwest" &&
                query("family/family_name", me) != "泰山派" && 
                present("tianmen daoren", environment(me)) &&
                living(present("tianmen daoren", environment(me))))
        {
                return notify_fail("天門道人喝道：後面是本派重地，這位" + RANK_D->query_respect(me) + "請止步。\n");
        }
        else return ::valid_leave(me, dir);

}
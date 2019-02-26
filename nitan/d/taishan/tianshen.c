// Room: /d/taishan/tianshen.c
// Last Modified by winder on Aug. 25 2001

inherit ROOM;

void create()
{
        set("short", "天紳巖");
        set("long", @LONG
鬥母宮北行不遠，漸入空山，山路越來越不好走了。忽見前有石橋
橫跨，名注水流橋。橋西北危崖聳立，飛瀑散珠，如帶若簾，名天紳巖，
俗稱水簾洞。巖頂山坳北側有明代鍾惺、林古度、吳惟明三人即興合作
《水簾詩》摩刻。天紳巖東北有羣石峭列如筍，題刻“萬笏朝天”，鋭
鋒叢生，景觀獨特。
LONG );
        set("exits", ([
                "north"     : __DIR__"dengxian",
                "southdown" : __DIR__"doumo",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "taishan");
        set("coor/x", 70);
	set("coor/y", 140);
	set("coor/z", 60);
	setup();
        replace_program(ROOM);
}
// Room: /d/yueyang/xiaoqiaomu.c
// Last Modifyed by Winder on Dec. 4 2001

inherit ROOM;

void create()
{
        set("short", "小喬墓");
        set("long", @LONG
小喬墓位於岳陽樓東北隅，墓北小廟，內供小喬像，據明《一統志
》載：賓孫策攻皖，得喬公二女，自納大喬，而以小喬歸周瑜，後卒葬
於此。如今青冢草長，蝶飛蜂嬉，玉人如夢了。
LONG );
        set("outdoors", "yueyang");
        set("no_clean_up", 0);
        set("exits", ([
                "southwest" : __DIR__"yueyanglou1",
        ]));
	set("coor/x", -6230);
	set("coor/y", -2990);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}
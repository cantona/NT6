// Room: /d/taishan/lianhua.c
// Last Modified by Winder on Aug. 25 2001
inherit ROOM;

void create()
{
        set("short", "蓮花峰");
        set("long", @LONG
蓮花峰其實是由五座山峰攢簇而成，狀如蓮花，因以為名。東面有
危崖萬仞，叫五花崖。登上蓮花峰後，可看到在盤道中的遊人如小蟻般
往來穿梭，故此蓮花峰又叫望人峰。往上走便是蓮花峰的峰頂。
LONG );
        set("exits", ([
                "northup" : __DIR__"shixin",
                "westup"  : __DIR__"tianjie",
        ]));
        set("outdoors", "taishan");
        set("no_clean_up", 0);
        set("coor/x", 50);
	set("coor/y", 300);
	set("coor/z", 200);
	setup();
        replace_program(ROOM);
}
// Room: /d/taishan/lianhua.c
// Last Modified by Winder on Aug. 25 2001
inherit ROOM;

void create()
{
        set("short", "蓮花峯");
        set("long", @LONG
蓮花峯其實是由五座山峯攢簇而成，狀如蓮花，因以為名。東面有
危崖萬仞，叫五花崖。登上蓮花峯後，可看到在盤道中的遊人如小蟻般
往來穿梭，故此蓮花峯又叫望人峯。往上走便是蓮花峯的峯頂。
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
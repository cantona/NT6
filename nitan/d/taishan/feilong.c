// Room: /d/taishan/feilong.c
// Last Modified by winder on Aug. 25 2001

inherit ROOM;

void create()
{
        set("short", "飛龍澗");
        set("long", @LONG
鬥母宮東有聽泉山房及龍泉亭，供遊人小憩賞景。亭下澗內“三潭
疊瀑”如龍飛舞，名飛龍澗。遊人立于潭間，流水聲似絲竹奏鳴。
LONG );
        set("exits", ([
                "northwest" : __DIR__"doumo",
        ]));
        set("outdoors", "taishan");
        set("no_clean_up", 0);
        set("coor/x", 80);
	set("coor/y", 120);
	set("coor/z", 50);
	setup();
        replace_program(ROOM);
}
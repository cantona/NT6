// Room: /d/taishan/fengyue.c
// Last Modified by winder on Aug. 25 2001

inherit ROOM;

void create()
{
        set("short", "風月無邊");
        set("long", @LONG
鬥母宮南西崖有“蔚然深秀”、“洞天福地”、“膚寸升雲”及“
蟲二”諸刻，與山色輝映。“蟲二”字謎即“風月”二字拆去邊框，意
為風月無邊，景色秀麗。
LONG );
        set("exits", ([
                "northeast" : __DIR__"doumo",
        ]));
        set("outdoors", "taishan");
        set("no_clean_up", 0);
        set("coor/x", 60);
	set("coor/y", 120);
	set("coor/z", 50);
	setup();
        replace_program(ROOM);
}
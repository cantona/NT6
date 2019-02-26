// Room: /d/taishan/taishanjiao.c
// Last Modified by Winder on Aug. 25 2001

inherit ROOM;

void create()
{
        set("short", "泰山腳下");
        set("long", @LONG
泰山古稱岱山，為五嶽的東嶽，為道教第二小洞天，向有“五嶽獨
尊”之稱譽，以“泰山天下雄”名聞域內。往北就到進入岱宗坊的前庭
遙參亭了。
LONG );
        set("exits", ([
                "north" : __DIR__"yaocan",
                "south" : __DIR__"yidao3",
                "east"  : __DIR__"kedian",
        ]));
        set("objects", ([
                CLASS_D("misc") + "/shanzheng" : 1,
        ]));
        set("no_clean_up", 0);
        set("outdoors", "taishan");
        set("coor/x", 70);
	set("coor/y", 30);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
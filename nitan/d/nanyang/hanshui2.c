// This program is a part of NT MudLIB

inherit RIVER;

void create()
{
        set("short", "漢水北岸");
        set("long", @LONG
漢水北岸也是相當熱鬧，自北岸渡口往北，一條筆直的官道直通南
陽。此地民風淳樸，路旁夾柳成陰，酒廝林立，且都有一面大大的「酒
」旗迎風飄揚，蔚為壯觀。也有不少小販沿路叫買，語多難辨，卻也令
人盛情難卻。
LONG );

        set("outdoors", "nanyang");
        set("region", "nanyang_zone");
        set("to", __DIR__"hanshui1");

        set("exits", ([
                "north" : __DIR__"nanmen",
        ]));

        set("objects", ([
                __DIR__"npc/chuanfu2" : 1,
        ]));

        set("resource/fish", ({ "/clone/fish/liyu",
                                "/clone/fish/jiyu",
                                "/clone/fish/qingyu",
                                "/clone/fish/caoyu", }));
        set("no_clean_up", 0);
	set("coor/x", -6940);
	set("coor/y", 740);
	set("coor/z", 0);
	setup();
        replace_program(RIVER);
}

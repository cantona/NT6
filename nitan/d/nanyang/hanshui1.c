// This program is a part of NT MudLIB

inherit RIVER;

void create()
{
        set("short", "漢水南岸");
        set("long", @LONG
面前是一條波濤翻滾的大江 (river)。濁流滾滾，萬舟競發。兩岸
渡船來來往往，江邊一長溜擺滿了魚攤，漁家就將船泊在岸邊，幾個破
籮筐支一塊木板，板上擺滿了活蹦亂跳的漢江鯉魚。過去不遠，是有名
的老河口，不少過江客都在這裏等待渡船擺渡。
LONG );
        set("outdoors", "nanyang");
        set("region", "nanyang_zone");
        set("to",__DIR__"hanshui2");

        set("exits", ([
                "south" : __DIR__"yidao2",
        ]));

        set("objects", ([
                __DIR__"npc/chuanfu1" : 1,
        ]));

        set("resource/fish", ({ "/clone/fish/liyu",
                                "/clone/fish/jiyu",
                                "/clone/fish/qingyu",
                                "/clone/fish/caoyu", }));

        set("no_clean_up", 0);

        set("coor/x", 0);
	set("coor/y", 70);
	set("coor/z", 0);
	setup();
        replace_program(RIVER);
}

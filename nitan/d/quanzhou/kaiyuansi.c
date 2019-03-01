// Room: /d/quanzhou/kaiyuansi.c
// Last Modified by winder on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "開元寺");
        set("long", @LONG
這是一座規模宏大的千年古剎，蓮宮桂宇，煥彩流金，刺桐掩映，
古榕垂蔭。遊人未抵門前，遠遠可見兩座石塔凌空而起，矗立于千樓萬
舍之上。它建于唐武則天二年，全寺佔地龐大，是福建最大的佛教建築
之一。寺外正面和西面，環立白石欄桿，並植刺桐。大門開啟，接納著
絡繹不絕的虔誠香客。
LONG );
        set("outdoors", "quanzhou");
        set("exits", ([
                "south" : __DIR__"westroad2",
                "north" : __DIR__"tianwangdian",
        ]));
        set("objects", ([
                "/d/wudang/npc/guest" : 2,
        ]));
	set("coor/x", -920);
	set("coor/y", -7660);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
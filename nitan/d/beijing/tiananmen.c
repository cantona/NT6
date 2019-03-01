#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "天安門廣場");
        set("long", @LONG
這裡就是天安門廣場，灰色的城牆給人以莊嚴肅穆之感，再往北
通過金水橋就是皇宮紫禁城了。遠遠望去，紫禁城的輪廓益發顯得雄
偉高大，一條護城河繞城而過。一條筆直的青石大道橫貫東西，東邊
是東長安街廣場，西邊是西長安街廣場。南邊是寬闊繁華的長安街廣
場，往南經過凡陛橋一直延伸至天壇和永定門。
LONG );
        set("exits", ([
                "south" : "/d/beijing/cagc_s",
                "north" : "/d/beijing/qiao",
               "west" : "/d/beijing/cagc_w",
              "east" : "/d/beijing/cagc_e",
        ]));
        set("objects", ([
                "/d/beijing/npc/maiyi2" : 1,
                "/d/beijing/npc/bing1" : 2,
                "/d/beijing/npc/old2" : 1,
                "/d/beijing/npc/kid1" : 1,
                "/clone/npc/walker"  : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2800);
	set("coor/y", 7670);
	set("coor/z", 0);
	setup();
}


void init()
{
        MYGIFT_D->check_mygift(this_player(), "newbie_mygift/rideto");
}


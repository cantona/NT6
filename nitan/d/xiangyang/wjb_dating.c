#include <ansi.h>

inherit ROOM;

#define PLACE "xy"
#define TYPE  "good"

int sort_by_id(mapping quest1, mapping quest2);

void create()
{
        set("short", "無極幫總舵");
        set("long", @LONG
這裏是無極幫的大廳，只見代表無極幫威望的那塊橫匾高高的懸
 掛着。那只是上好松木做成的橫匾，黑漆金字，寫着無極幫三個大字。
 木匾下面的署名，包括了少林、武當、華山掌門人，慕容世家主人、
 丐幫幫主，五個江湖上最具權勢的人物。也正因為有了這塊橫匾，近
 年來無極幫聲勢大盛，許多江湖兒女紛紛慕名而來，無極幫儼然一派
 武林第一幫的氣勢。牆上掛着一個任務牌（paizi）。 
LONG );

        set("objects", ([
               __DIR__"npc/boss-jin"   : 1,
        ]));

        set("no_fight",1);

        set("exits", ([
                "south" : __DIR__"wjb_damen",
        ]));

        set("coor/x", -7780);
	set("coor/y", -720);
	set("coor/z", 0);
	setup();
}
#include <bang_good.h>
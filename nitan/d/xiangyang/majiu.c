#include <room.h>
inherit TRANS_ROOM;

void create()
{
        set("short", "馬廄");
        set("long", @LONG
這裡是襄陽城內唯一一家車馬行。你可花錢租輛馬車到各個地方
去，能節約不少體力。近來因為郭夫人──黃蓉正在組織人力四處搜
集防城材料，馬夫積極響應，免費提供推車來運送各種防城材料。雨
檐下釘著塊木牌(paizi)。
LONG );
        set("outdoors", "xiangyang");
        set("exits", ([
                "south"  : __DIR__"northroad2",
                "up"     : "/clone/shop/xiangyang_shop",
        ]));
        set("no_fight", 1);
        set("objects", ([
                "/clone/horse/zaohongma": 1,
                "/clone/horse/huangbiaoma": 1,
                "/clone/horse/ziliuma": 1,
                "/clone/npc/mafu": 1,
        ]));
        set("coor/x", -7800);
	set("coor/y", -730);
	set("coor/z", 0);
	setup();
        replace_program(TRANS_ROOM);
}
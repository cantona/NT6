// This program is a part of NT MudLIB

#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", "花店");
        set("long", @LONG
這裡是新近開張的一家鮮花店，店內百花齊放，清香滿室。花兒雖
非名種，卻也朵朵嬌艷欲滴。她們是期待、是問候、是默默的祝福、是
深深的思念……這裡的鮮花不知是從一些保密的地方運來？但都是十分
鮮艷而且供貨充足。因為是分店，也見不到老板。一個伙計手持花洒，
在花間輕輕走動，精心照料著每朵鮮花。價目表(sign)就掛在牆上。
LONG );
        set("region", "yangzhou");
        set("no_fight", "1");
        set("no_steal", "1");
        set("no_sleep_room", "1");
        set("item_desc", ([
                "sign" :
"┌────────────"+HIG"購花須知"NOR+"──────────────┐\n"
"│ 一、花店裡花兒的價格用(list)查看                           │\n"
"│ 二、買花可直接向伙計購買(buy)：buy <數量> <花草代號>       │\n"
"│ 三、本鮮花店提供送花，送花服務：send <花草代號> to <玩家id>│\n"
"│ 四、請用(help flower)來查詢花朵含義和資料。                │\n"
"└──────────────────────────────┘\n"
        ]));
        set("objects", ([
                __DIR__"npc/huoji3" : 1,
        ]));
        set("exits", ([
                "north" : __DIR__"xiaohuayuan",
                "south" : __DIR__"dongdajie3",
        ]));
	set("coor/x", 30);
	set("coor/y", 10);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
// Room: /d/wuxi/huishanquan.c
// Winder 2000/02/22 

inherit ROOM;
#include <ansi.h>;
void create()
{
        set("short", "天下第二泉");
        set("long", @LONG
眼前已經來到惠山山腳，只見青鬆蔽日，耳竹林哨響。上山石階
之旁，有一圓一方兩池，圓池在上，方池在下。池西頭雕有螭首，造
型古樸，泉水(quan)從龍口出。向北即可上得惠山。
LONG );
        set("outdoors", "wuxi");
        set("no_clean_up", 0);
        set("exits", ([
                "south"     : __DIR__"road14",
                "northup"  : __DIR__"road15",
        ]));
        set("objects", ([
                "/d/huashan/npc/youke" : 2,
        ]));
        set("item_desc", ([
                "quan" : "眼前一泓清泉清鑒肌骨，池底凈石，清晰可見。\n",
        ]));
        set("coor/x", 990);
	set("coor/y", -720);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
//Edited by fandog, 02/15/2000

#include <room.h>
inherit ROOM;
void create()
{
        set("short", "四季美");
        set("long", @LONG
提起“四季美”江陵一帶無人不知。這裏各式菜餚均是武漢一絕。
南來北往的客人們都會來這裏嚐嚐。整個大堂鬧哄哄的，擠得滿滿登登。
店裏的夥計跑來跑去，忙着招呼客人。牆上掛着價格牌子(paizi)。
LONG);
        set("exits", ([
                "west"  : __DIR__"hzjie1",
        ]));
        set("objects", ([
                __DIR__"npc/huoji" : 1,
        ]));
        set("item_desc", ([
                "paizi" : "
冬瓜鼈裙羹(Donggua)        ：五兩白銀
猴頭芙蓉(Houtou)           ：五兩白銀
龍鳳配(Longfeng)           ：五兩白銀
天麻銀耳湯(Tianma soup)    ：五兩白銀
松子武昌魚(Wuchang yu)     ：五兩白銀
香菇燒板栗(Xianggu banli)  ：五兩白銀
珍珠甲魚湯(Zhenzhu soup)   ：五兩白銀\n",
        ]));

	set("coor/x", -5080);
	set("coor/y", -1860);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
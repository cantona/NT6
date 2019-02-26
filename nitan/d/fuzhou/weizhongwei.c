// jiulou.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "味中味");
        set("long", @LONG
提起“樓外樓”方圓百里無人不知。這裏的各式閩菜均是福州一絕。
來遊湖的人們都一定會來這裏嚐嚐。整個大堂裏鬧哄哄的擠滿了各式人
等。店小兒跑來跑去，忙着招呼客人。
    牆上掛着價格牌子(paizi)。
LONG);
        set("exits", ([
                "west"  : __DIR__"nandajie",
        ]));
        set("objects", ([
                __DIR__"npc/xiaoer3" : 1,
        ]));
        set("item_desc", ([
                "paizi" : "
佛跳牆(Fotiaoqiang)   ：五兩白銀
福建老酒(Jiuping)     ：二兩白銀\n",
        ]));
	set("coor/x", -70);
	set("coor/y", -6190);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
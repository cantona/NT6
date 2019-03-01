// jiulou.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "樓外樓");
        set("long", @LONG
提起“樓外樓”方圓百里無人不知。這裏各式名菜是杭州一絕。
來遊湖的人們都一定會來這裏嚐嚐。整個大堂鬧哄哄的擠滿了各式人
等。店小兒跑來跑去，忙着招呼客人。牆上掛着價格牌子(paizi)。
LONG);
        set("exits", ([
            "west"      : __DIR__"road10",
            "east"      :"/d/hangzhou/chufang",
            "up"        : __DIR__"loveroom",
        ]));
        set("objects", ([
            __DIR__"npc/xiaoer2" : 1,
        ]));
        set("item_desc", ([
            "paizi" : "
東坡肉(Pork)      ：一兩白銀又二十文銅板
西湖醋魚(Fish)    ：一兩白銀又二十文銅板
百果油包(Baozi)   ：七十文銅板
龍井蝦仁(Shrimp)  ：五十文銅板
叫化童雞(Chicken) ：一兩白銀又二十文銅板
桂花鮮慄羹(Guihua geng)：一兩白銀又二十文銅板
酒瓶(Jiuping)     ：十六兩白銀\n",
        ]));
//        set("no_clean_up", 0);
	set("coor/x", 840);
	set("coor/y", -2040);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
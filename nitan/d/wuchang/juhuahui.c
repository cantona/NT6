//Edited by fandog, 01/31/2000
#include <ansi.h>
inherit ROOM;

void create ()
{
        set ("short", "菊花會");
        set ("long","正是菊花盛開時節，這裡擺放了各處的名貴菊花。黃菊有"HIY"都勝、金
芍藥、黃鶴翎、報君知、御袍黃、金孔雀、側金盞、鶯羽黃"NOR"。白菊有"HIW"月
下白、玉牡丹、玉寶相、玉玲瓏、一團雪、貂蟬拜月、太液蓮"NOR"。紫菊有
"MAG"碧江霞、雙飛燕、翦霞綃、紫玉蓮、紫霞杯、瑪瑙盤、紫羅撒"NOR"。紅菊有
"HIR"美人紅、海雲紅、醉貴妃、繡芙蓉、胭脂香、錦荔枝、鶴頂紅"NOR"。淡紅色
的有"HIM"佛見笑、紅粉團、桃花菊、西施粉、勝緋桃、玉樓春"NOR"。只可惜沒有
"HIG"綠菊"NOR"。\n");
        set("objects", ([
                __DIR__"npc/yahuan" : 1,
                __DIR__"npc/lingshuanghua" : 1,
                "/clone/medicine/vegetable/jugeng" : random(2),
        ]));

        set("exits", ([ 
                "east" : __DIR__"hzjie3",
        ]));
  
	set("coor/x", -5100);
	set("coor/y", -1890);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
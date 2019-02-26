// Room: /yangzhou/taohuawu.c
// Last Modified by Winder on Jul. 20 2000

inherit ROOM;

void create()
{
        set("short", "桃花塢");
        set("long", @LONG
長堤春柳北端，為桃花塢故址，可惜此塢久廢。廢墟上新築徐園，
園中有黃石迭砌的荷池，外有曲水，內有池塘，池水與湖水相通。過池
是館軒，取杜甫“兩個黃鸝鳴翠柳，一行白鷺上青天”之意，而稱聽鸝
館。館內遍種松柏、桃柳、紅楓、紫薇，花壇滿栽芍藥。館門抱柱懸掛
同治狀元陸潤庠楹聯(lian)，外柱懸掛阮元楹聯 (lian2)。北面澄鮮水
榭為畫舫靠泊處，亦為遠眺小金山最佳處。繞過徐園，立於小紅橋，小
金山聳立，湖面陡然放開。
LONG );
        set("no_sleep_room",1);
        set("outdoors", "shouxihu");
        set("no_clean_up", 0);
        set("item_desc", ([
                "lian" : "
        綠        紅
        印        流
        苔        花
        痕        韻
        留        愛
        鶴        鶯
        篆        簧
\n",
                "lian2" : "
        江        山
        波        色
        蘸        迎
        綠        人
        岸        秀
        堪        可
        染        餐
\n",
        ]));
        set("exits", ([
                "northwest" : __DIR__"ouxiangqiao",
                "southdown" : __DIR__"pingtai",
                "south"     : __DIR__"changdi2",
                "north"     : __DIR__"xiaohongqiao",
                "west"      : __DIR__"yinxie",
                "east"      : __DIR__"chunboqiao",
        ]));
        set("objects", ([
                "/d/city/npc/lady" : 1,
        ]));
        set("coor/x", 0);
        set("coor/y", 40);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
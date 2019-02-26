// Room: /d/xingxiu/jiayuguan.c
// Last Modified by winder on Feb. 28 2001

inherit ROOM;

void create()
{
        set("short", "嘉峪關");
        set("long", @LONG
這是長城最西的關隘。歲月滄桑，仍掩不住它的風采。羣山環抱之
下，更顯它的雄渾。由於西域安定，久無戰事，邊關守軍已大為減少。
一條大道向東延伸通向中原，萬里長城由此往東北方蜿蜒而去。出關向
西，便是著名的“絲綢之路”。
LONG );
        set("outdoors", "silu");
        set("exits", ([
                "eastup"    : __DIR__"xxroad3",
                "west"      : __DIR__"silk1",
                "north"     : "/d/dragon/spiritgate",
                "southup"   : "/d/qilian/tanglangling",
                "northeast" : "/d/qilian/yumen",
                "northwest" : "/d/qilian/danshan",
                "southwest" : "/d/qilian/shalu1",
                "up"        : "/d/changcheng/jiayuguan",
        ]));
        set("objects", ([
                __DIR__"npc/wujiang1" : 1,
                __DIR__"npc/bing1" : 2,
        ]));
//        set("no_clean_up", 0);
        set("coor/x", -18000);
        set("coor/y", 3000);
        set("coor/z", 0);
        setup();
}
#include "/d/xingxiu/job2.h";

// Room: /d/taishan/nantian.c
// Last Modified by Winder on Aug. 25 2001

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "南天門");
        set("long", @LONG
走完了十八盤，便到南天門。南天門又稱“三天門”，門為城樓式
建築，門邊有一副對聯(lian)，上覆摩空閣，是泰山頂的入口處。從這
裡附視山下，群山如龜伏地，河流如蚓纏繞，天地空闊，無可名狀。從
這裡往東北走就是天街，往西走便是月觀峰，往北走則是到玉皇頂之路。
LONG );
        set("exits", ([
                "west"      : __DIR__"yueguan",
                "eastup"    : __DIR__"tianjie",
                "northup"   : __DIR__"yuhuang",
                "southdown" : __DIR__"jin18",
        ]));
        set("item_desc", ([
                "lian" : "
門辟九霄，仰步三天勝跡  階崇萬級，俯臨千嶂奇觀\n",
        ]));
        set("objects",([
                CLASS_D("taishan")+"/tianbai" : 1,
                __DIR__"npc/wei-shi3" : 2,
        ]));
        set("outdoors", "taishan");
        set("coor/x", 30);
	set("coor/y", 300);
	set("coor/z", 200);
	setup();
        replace_program(ROOM);
}
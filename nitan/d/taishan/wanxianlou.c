// Room: /d/taishan/wanxianlou.c
// Last Modified by winder on Aug. 25 2001

inherit ROOM;

void create()
{
        set("short", "萬仙樓");
        set("long", @LONG
萬仙樓為跨道門樓式建築。殿內祀王母，配以列仙，後增祀元君。
殿牆四周鑲明代朝山進香碑六十三塊。門洞東側有隱真洞，為舊時道人
修煉處。門洞後額書“謝恩處”，傳古帝王登山時，地方官員送駕至此
而謝歸。或稱舊時香客登岱回歸至此無恙，即叩謝元君保佑之恩。
LONG );
        set("exits", ([
                "north" : __DIR__"taohua",
                "south" : __DIR__"sanyibai",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 70);
	set("coor/y", 110);
	set("coor/z", 40);
	setup();
        replace_program(ROOM);
}
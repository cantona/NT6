//Room: /d/dali/shanjian.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","林中山澗");
        set("long",@LONG
密林深處豁然開朗，一道激流從上上飛濺下來，山澗並不寬，更
談不上深，行人盡可徒步通過。澗水清涼幹凈，路人往往停下來用竹
筒裝水解渴。四面皆是青竹林，竹葉隨山風沙沙作響。有些擺夷村民
不遠數裡上山來採新鮮竹筍為食。
LONG);
        set("objects", ([
           __DIR__"npc/caisunren1": 1,
        ]));
        set("outdoors", "dalie");
        set("exits",([ /* sizeof() == 1 */
            "northdown"  : __DIR__"milin",
            "southdown"  : __DIR__"banshan",
        ]));
	set("coor/x", -19030);
	set("coor/y", -6900);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}
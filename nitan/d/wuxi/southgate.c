// Room: /d/wuxi/southgate.c
// Winder 2000/02/22 

inherit ROOM;

string look_gaoshi();
void create()
{
        set("short", "朝京門");
        set("long", @LONG
這是南城門，城門的名稱是從古漢之時就傳下來了。城牆外就是清
名橋，這裡住了不少小商小販，周圍貼滿了花花綠綠各行各業的廣告，
官府的告示(gaoshi)夾在中間倒也不太顯目。
LONG );
        set("outdoors", "wuxi");
        set("no_clean_up", 0);
        set("item_desc", ([
                "gaoshi" : (: look_gaoshi :),
        ]));
        set("exits", ([
                "north"  : __DIR__"southroad2",
                "south"  : __DIR__"qingmingqiao",
        ]));
        set("objects", ([
                "/d/city/npc/wujiang" : 1,
                "/d/city/npc/bing" : 2,
        ]));
        set("coor/x", 1040);
	set("coor/y", -770);
	set("coor/z", 0);
	setup();
}

string look_gaoshi()
{
        return FINGER_D->get_killer() + "\n無錫知府\n晨宜\n";
}
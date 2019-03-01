// Room: /d/wuxi/westgate.c
// Winder 2000/02/22 

inherit ROOM;

string look_gaoshi();
void create()
{
        set("short", "樑溪門");
        set("long", @LONG
城門的來由是和門外的樑溪河有關，因此樑溪也常常成為無錫的別
稱，但老百姓還是習慣叫這西門。城牆上貼著幾張通緝告示(gaoshi)。
這裡是無錫通向北方的必經之地，官兵們戒備森嚴，動不動就截住行人
盤問。西邊是跨越樑溪河跨溪橋，騎馬的、坐轎的、走路的，行色匆匆。
東邊是熱熱鬧鬧的城裡。
LONG );
        set("outdoors", "wuxi");
        set("no_clean_up", 0);
        set("item_desc", ([
                "gaoshi" : (: look_gaoshi :),
        ]));
        set("exits", ([
                "west"  : __DIR__"kuaxiqiao",
                "east"  : __DIR__"westroad2",
        ]));
        set("objects", ([
                "/d/city/npc/wujiang" : 1,
                "/d/city/npc/bing" : 2,
        ]));
        set("coor/x", 1010);
	set("coor/y", -730);
	set("coor/z", 0);
	setup();
}

string look_gaoshi()
{
        return FINGER_D->get_killer() + "\n無錫知府\n晨宜\n";
}
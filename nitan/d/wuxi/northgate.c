// Room: /d/wuxi/northgate.c
// Winder 2000/02/22 

inherit ROOM;

string look_gaoshi();
void create()
{
        set("short", "蓮蓉門");
        set("long", @LONG
北城門叫蓮蓉門，從此向北去是就江陰的長江要塞，官府為此將大
道一直修到了江邊。因為在要塞處的江面上禁止通船，所以從這裏出城
的普通百姓少，和南邊熱熱鬧鬧的景象組成了明顯的反差。城牆上有一
張白紙黑字的官府告示(gaoshi)。
LONG );
        set("outdoors", "wuxi");
        set("no_clean_up", 0);
        set("item_desc", ([
                "gaoshi" : (: look_gaoshi :),
        ]));
        set("exits", ([
                "south"  : __DIR__"northroad2",
                "north"  : __DIR__"lianrongqiao",
        ]));
        set("objects", ([
                "/d/city/npc/wujiang" : 1,
                "/d/city/npc/bing" : 2,
        ]));
        set("coor/x", 1040);
	set("coor/y", -690);
	set("coor/z", 0);
	setup();
}

string look_gaoshi()
{
        return FINGER_D->get_killer() + "\n無錫知府\n晨宜\n";
}
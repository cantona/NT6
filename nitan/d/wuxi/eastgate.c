// Room: /d/wuxi/eastgate.c
// Winder 2000/02/22 

inherit ROOM;

string look_gaoshi();
void create()
{
        set("short", "熙春門");
        set("long", @LONG
這是無錫的東城門，城門正上方刻着“熙春門”三個楷書大字，城
牆上貼着幾張官府告示(gaoshi)。護城河水一刻不停地流着，過了吊橋
便是一條筆直的大道向東方延伸，那是去蘇州的驛道，常有驛使的快馬
疾馳而過。西邊是城裏。
LONG );
        set("outdoors", "wuxi");
        set("no_clean_up", 0);
        set("item_desc", ([
                "gaoshi" : (: look_gaoshi :),
        ]));
        set("exits", ([
                "north" : __DIR__"xinlin1",
                "east"  : __DIR__"road1",
                "west"  : __DIR__"eastroad2",
        ]));
        set("objects", ([
                "/d/city/npc/wujiang" : 1,
                "/d/city/npc/bing" : 2,
        ]));
        set("coor/x", 1070);
	set("coor/y", -730);
	set("coor/z", 0);
	setup();
}

string look_gaoshi()
{
        return FINGER_D->get_killer() + "\n無錫知府\n晨宜\n";
}
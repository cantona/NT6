//guangchang.c

inherit ROOM;

void create()
{
        set("short", "大廣場");
        set("long", @LONG
這個大廣場的地面鋪的石磚橫七豎八, 共一十五層. 是皇帝為防有
人挖地道入宮特地設計的. 可想皇城的戒備森嚴之至.
LONG
        );
        set("outdoors", "huanggong");
        set("no_clean_up", 0);
        set("exits", ([
                "east"  : __DIR__"wenhua",
                "west"  : __DIR__"wuying",
                "south" : __DIR__"taihemen",
                "north" : __DIR__"taiji",
        ]));
        set("objects", ([
                __DIR__"npc/eshuo" :1,
        ]));
	set("coor/x", -2800);
	set("coor/y", 7721);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
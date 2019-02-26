inherit ROOM;

void create()
{
        set("short", "八寶琉璃殿");
        set("long", @LONG
這座大殿相對於大雄殿來説要小得多，但卻是顯得富麗精緻無比，
大殿的檐面是用琉璃瓦鋪的，四面的牆壁上都鏤刻了佛經故事，正中
的彌勒佛像用黃金，翡翠，寶石，珍珠等裝飾稱八寶佛像。
LONG );
        set("objects", ([
                __DIR__"npc/jiansi" : 1,
                __DIR__"npc/obj/milexiang" : 1,
        ]));

        set("exits", ([
                "south" : __DIR__"houyuan",
                "northdown" : __DIR__"gongmen",
        ]));
        set("no_clean_up", 0);

	set("coor/x", -5040);
	set("coor/y", 2230);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}
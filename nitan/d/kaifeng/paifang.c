inherit ROOM;

void create()
{
        set("short", "牌坊");
        set("long", @LONG
穿過一道照壁，走上一條青石小道，眼前不遠就是一道牌坊。通
用紅漆過了一邊，看不出原來的底色，倒是跟關帝爺的臉色很像，北
面鬧轟轟的是座戲樓，東面就是關帝廟。
LONG );
        set("outdoors", "kaifeng");
        set("exits", ([
                  "north" : __DIR__"xilou",
                  "east" : __DIR__"guandi",
                  "west" : __DIR__"huiguan",
        ]));
        set("no_clean_up", 0);
        set("objects", ([
                  __DIR__"npc/huizhang" : 1,
                  __DIR__"npc/pihuoshang" : 1,
        ]));

	set("coor/x", -5010);
	set("coor/y", 2240);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
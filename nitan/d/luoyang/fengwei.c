inherit ROOM;

void create()
{
        set("short", "風味小吃");
        set("long", @LONG
你的眼前突然出現了一家小吃店，大門外掛着一塊牌子，牌子上寫着
“風味小吃”四個字，到小吃店裏來吃東西的人絡繹不絕，在這家店裏你
能吃到全國各地的風味小吃，南洋的小籠，天津的狗不理包子，北京的烤
鴨，嘉興的五香豆，鄭州的拉麪等等，快來品嚐一下吧！
LONG);
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
        set("exits", ([
                "north" : __DIR__"zashua",
                "east" : __DIR__"wanju",
        ]));
        set("objects", ([
                __DIR__"npc/xiaoer" : 1,
        ]));
	set("coor/x", -6960);
	set("coor/y", 2170);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
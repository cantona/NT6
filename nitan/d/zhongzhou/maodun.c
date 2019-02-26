inherit ROOM;

void create()
{
        set("short", "甲胄店");
        set("long", @LONG
這是間小小的店鋪，鋪中的主人據説有一手修補甲胄的絕
藝，只要你需要，可以隨時給錢修補。一些還沒修理過的鐵甲
銅盔之類的東西胡亂扔在地上，看上去很雜亂。
LONG);
        set("objects", ([
                  __DIR__"npc/smith" : 1,
        ]));
        set("no_clean_up", 0);
        set("exits", ([
                  "west" : __DIR__"wendingnan2",
        ]));

        set("coor/x", -9030);
	set("coor/y", -1020);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
inherit ROOM;

void create()
{
        set("short", "望星樓");
        set("long", @LONG
望星樓共四層，高達三十余米，乃洛陽城中的一絕。方圓數百裡內提
起望星樓可以說是無人不知，無人不曉。樓下為望星樓的大廳，非常的寬
廣，玲瓏八角，青磚砌地，好不氣派。大廳西首一檀木制階梯直通望星樓
的樓上的雅座。
LONG);
        set("no_clean_up", 0);
        set("exits", ([
                "up" : __DIR__"zuixianlou2",
                "west" : __DIR__"nroad1",
        ]));
        set("objects", ([
                __DIR__"npc/xiaoer" : 1,
        ]));
	set("coor/x", -6980);
	set("coor/y", 2190);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
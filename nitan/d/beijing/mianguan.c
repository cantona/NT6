inherit ROOM;

void create()
{
        set("short", "面館");
        set("long", @LONG
這裡是虎坊路盡頭的一家小面館，幾個皇宮裡的摔跤手擁在裡面。
面館的掌櫃和伙計威于他們的勢頭，連大氣也不敢出一聲。
LONG );
        set("exits", ([
                "north" : "/d/beijing/fu_1",
        ]));
        set("objects", ([
                "/d/beijing/npc/zhanggui":1,
                "/d/beijing/npc/mianhuoji":1,
                "/d/beijing/npc/jiao1":3,
                "/d/beijing/npc/jiao2":1,
              "/clone/npc/walker"  : 1, 
        ]));
	set("coor/x", -2820);
	set("coor/y", 7640);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
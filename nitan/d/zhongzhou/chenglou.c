inherit ROOM;

void create()
{
        set("short", "西城樓");
        set("long", @LONG
不覺你已到了中州的西城門。高高的城樓看上去堅不可摧。
西面有一樓梯可以上城樓的二層。據說這裡守城的將軍武功不
俗，而卻很好比武。
LONG);
        set("no_clean_up", 0);
        set("exits", ([
                  "west" : __DIR__"xijiao",
                  "east" : __DIR__"yanling2",
                  "up" : __DIR__"chenglouup",
        ]));
        set("objects", ([
                "/d/kaifeng/npc/guanbing" : 4,
                "/d/city/npc/wujiang" : 1,
                "/clone/npc/walker" : 1,
        ]));
        set("outdoors", "zhongzhou");

        set("coor/x", -9080);
	set("coor/y", -1000);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
inherit ROOM;

void create()
{
        set("short", "中州北門");
        set("long", @LONG
這裏已經到了中州的北門了，高高的城牆的磚縫裏長滿了
草。走過城門，再過了護城河，就是城外了。
LONG);
        set("outdoors", "zhongzhou");
        set("exits", ([
                //"north" : __DIR__"to_zhongzhou3",
                  "south" : __DIR__"wendingbei4",
        ]));
        set("objects", ([
                "/clone/npc/walker" : 1,
                  "/d/city/npc/bing" : 4,
                  "/d/city/npc/wujiang" : 1,
        ]));
        set("no_clean_up", 0);

        set("coor/x", -9040);
	set("coor/y", -950);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
inherit ROOM;

void create()
{
        set("short", "藏經樓");
        set("long", @LONG
藏經樓是一棟兩層小樓，閣樓中都是佛家經典，名貴稀少的都用
檀木盒盛放了。收藏在樓上，派有專人職司。你滿眼看去，到處是高
低的書架，
LONG );
        set("objects", ([
                  __DIR__"npc/zhifa" : 1,
        ]));

        set("no_clean_up", 0);
        set("exits", ([
                  "west" : __DIR__"houyuan",
                  "up" : __DIR__"cangjing2",
                  "east" : __DIR__"xiaoyuan",
        ]));

	set("coor/x", -5030);
	set("coor/y", 2220);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}
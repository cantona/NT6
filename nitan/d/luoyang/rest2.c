inherit ROOM;

void create()
{
        set("short", "女休息室");
        set("long", @LONG
這裏是供洗完澡的客人休息的地方，整個房間寬敞整潔，有次序的放
置了許多靠椅，旁邊放有熱毛巾，自己取用，而且這裏還提供茶水服務。
LONG);
        set("no_clean_up", 0);
        set("exits", ([
                "east" : __DIR__"nvyuchi",
                "down" : __DIR__"yuchi",
        ]));

	set("coor/x", -6980);
	set("coor/y", 2150);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}
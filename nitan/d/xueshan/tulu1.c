inherit ROOM;

void create()
{
        set("short", "土路");
        set("long", @LONG
這是一條不起眼的土路，不寬卻也不窄，鬆散的浮塵顯露出來往
行商的頻繁。它是連接雪山寺與中原的必經之路。
LONG );
        set("outdoors", "xuedao");
        set("exits", ([
                "east" : __DIR__"caoyuan",
                "west" : __DIR__"tulu2",
        ]));
        setup();
        replace_program(ROOM);
}
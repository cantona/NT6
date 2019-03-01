inherit ROOM;

void create()
{
        set("short", "素齋廳");
        set("long", @LONG
這是寺廟中的大小僧人用餐的地方，當然方丈的素齋是專門有人
送過去的，平時相國寺的僧人聽鐘吃飯，等他們吃完了也經常把剩下
的素齋舍給窮人吃。逢塑望，十五也經常作些齋席請大施主，高官富
貴們品嘗，所以素齋廚的僧人是最忙的。
LONG );
        set("exits", ([
                  "north" : __DIR__"chufang2",
                  "west" : __DIR__"zhongyuan",
        ]));

        set("no_clean_up", 0);
        set("objects", ([
                  __DIR__"npc/liucaizhu" : 1,
                  __DIR__"npc/kong" : 1,
        ]));

	set("coor/x", -5030);
	set("coor/y", 2200);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}
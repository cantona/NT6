inherit ROOM;

void create()
{
        set("short", "小衚衕");
        set("long", @LONG
這裏是洛陽城內老百姓的居住區。衚衕內很安靜，沒有什麼雜聲。一
些居民從這裏進進出出。越往衚衕裏走，一些全身穿着白色長衣的人就越
多了，只見這些人鬼鬼祟祟，眼神恍惚，行蹤可疑，讓人猜不透是幹什麼
的。
LONG);
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
        set("exits", ([
                  "north" : __DIR__"suanming",
                  "south" : __DIR__"hutong2",
                  "west" : __DIR__"roudian",
        ]));
        set("objects", ([
                "/d/kaifeng/npc/qigai" : 1,
        ]));
	set("coor/x", -6940);
	set("coor/y", 2180);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
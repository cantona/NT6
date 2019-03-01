inherit ROOM;

void create()
{
        set("short", "蘭薪寺");
        set("long", @LONG
這座寺廟剛剛建成不久，一切都是嶄新的，就連寺裡的老主持也是剛
從京城定國寺請來的。寺裡有兩個小和尚正在掃地，因為是新廟，所以來
祭拜的人很少。
LONG);
        set("no_clean_up", 0);
        set("exits", ([
                  "west" : __DIR__"xiaoxiang2",
        ]));
        set("objects", ([
                "/d/kaifeng/npc/oldwomen" : 1,
                "/d/kaifeng/npc/zhike" : 1,
                "/clone/npc/walker" : 1,
        ]));

	set("coor/x", -6960);
	set("coor/y", 2220);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
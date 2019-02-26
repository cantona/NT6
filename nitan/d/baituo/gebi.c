inherit ROOM;

void create()
{
        set("short", "戈壁");
        set("long", @LONG
這裏是臨近沙漠的戈壁灘，荒無人煙。東邊是一望無際的大沙漠，
西北方可以看見一座小鎮。
LONG );
        set("outdoors", "baituo");
        set("no_clean_up", 0);
        set("exits", ([
                "east"      : "/d/xingxiu/shamo4",
                "northwest" : __DIR__"dongjie",
        ]));
        set("objects", ([
                "/clone/npc/walker" : 1,
        ]));
        set("coor/x", -40000);
        set("coor/y", 20000);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
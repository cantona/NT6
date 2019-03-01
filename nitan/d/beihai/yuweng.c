// /d/beihai/yuwen.c
// Last Modified by winder on May. 22 2002

inherit ROOM;

void create()
{
        set("short", "玉甕亭");
        set("long", @LONG
這裡是殿之正南的一座石亭，內置元代玉甕。此玉甕通體晶瑩剔透，
為一整塊墨玉雕刻而出。玉質如此之美，體積如此之大，實是不可多得
之物。卻不知道這玉甕是用來做什麼的。
LONG
        );
        set("exits", ([
                "north" : __DIR__"chengguang",
        ]));
        set("outdoors", "beihai");
        set("no_clean_up", 0);

        set("coor/x", -180);
        set("coor/y", 4040);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}

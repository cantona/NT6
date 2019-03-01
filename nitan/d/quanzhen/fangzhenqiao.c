// fangzhenqiao.c 訪真橋
// Winder Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "訪真橋");
        set("long", @LONG
跨過石階，眼前是一座石頭砌成的小小拱橋。橋上欄杆上雕龍描
鳳，栩栩如生。這裏的山勢非常陡峻，往下一看，懸崖壁立，腳下白
雲飄過，真不知身在何境。
LONG
        );
        set("outdoors", "zhongnan");
        set("exits", ([
                "north" : __DIR__"yuzhengong",
                "southdown" : __DIR__"shijie7",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -3140);
        set("coor/y", 140);
        set("coor/z", 190);
        setup();
        replace_program(ROOM);
}
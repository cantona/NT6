// guanritai.c 觀日台
// Winder Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "觀日台");
        set("long", @LONG
這裡是終南山上的觀日台，不知哪朝哪代何人在這裡修築了這個
平台，用來觀瞻日出的美景。這裡的山勢非常陡峻，往下一看，懸崖
壁立，腳下白雲飄過，真不知身在何境。
LONG
        );
        set("outdoors", "zhongnan");
        set("exits", ([
                "north" : __DIR__"shijie9",
        ]));
        set("objects",([
                __DIR__"npc/youke" : 1,
                __DIR__"npc/xiangke" : 1,
        ]));
        set("coor/x", -3150);
        set("coor/y", 80);
        set("coor/z", 180);
        setup();
        replace_program(ROOM);
}
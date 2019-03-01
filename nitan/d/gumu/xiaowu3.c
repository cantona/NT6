// xiaowu3.c 孫婆婆小屋
// Java Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "小屋");
        set("long", @LONG
這裡是遠離正廳的一間小屋，收拾得整整潔潔一塵不染。擺設就如
普通人家一般，紅木的桌椅，細磁的杯壺，沉香的大床。你簡直想象不
到這幽深的古墓之中還有這等擺設。
LONG        );
        set("exits", ([
                "west" : __DIR__"mudao13",
        ]));
        set("objects", ([
                //CLASS_D("gumu")+"/sun" : 1,
                __DIR__"obj/ping" : 1,
        ]));
        set("coor/x", -3170);
        set("coor/y", -30);
        set("coor/z", 90);
        setup();
        replace_program(ROOM);
}
inherit ROOM;

void create()
{
        set("short", "洞口");
        set("long", @LONG
山谷裏積雪被攏成幾個雪堆，這裏時常有人掃除積雪。你前面的
峭壁下隱隱約約有一個山洞。南北兩旁都是崖壁，東面則是一處峭壁，
非常險要。
LONG );
        set("exits", ([
                "enter" : __DIR__"shandong3",
                "west"  : __DIR__"sroad9",
        ]));
        set("objects", ([
                CLASS_D("xuedao") + "/baoxiang" : 1,
        ]));
        set("outdoors", "xuedao");
        setup();
}

int valid_leave(object me, string dir)
{
        object guarder;

        if (dir == "west" ||
            ! objectp(guarder = present("bao xiang", this_object())) ||
            ! living(guarder))
                return ::valid_leave(me, dir);

        return guarder->permit_pass(me, dir);
}
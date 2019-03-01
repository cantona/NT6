//room: mtdating.c

inherit ROOM;

void create()
{
        set("short", "崖頂");
        set("long", @LONG
這就是摩天崖了。上面光禿禿的，連一棵小樹也沒有，峰頂到也
十分開闊，但身周雲霧繚繞，當真是置身雲端之中，使人心驚肉跳。
東面有一個小木屋。
LONG );
        set("outdoors", "xiakedao");
        set("exits",([
                "east" : __DIR__"mtxiaowu",
                "down" : __DIR__"mtyadi",
        ]));
        set("objects",([
                __DIR__"npc/xieyan" : 1,
        ]));

        set("outdoors", "motianya");
        setup();
}

int valid_leave(object me, string dir)
{
        object ob;

        if (dir == "east" &&
            objectp(ob = present("xie yanke", this_object())) &&
            living(ob))
                return notify_fail("謝煙客把手一攔，喝道：“給我回來！”\n");

        return ::valid_leave(me, dir);
}
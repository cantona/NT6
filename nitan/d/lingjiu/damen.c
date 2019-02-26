inherit ROOM;

void create()
{
        set("short", "獨尊廳大門");
        set("long", @LONG
這就是通向「靈鷲宮」獨尊廳的大門。大門左右各有一頭石雕的
猛鷲，高達三丈有餘，尖喙巨爪，神駿非凡，似乎隨時要騰空而去。
LONG );
        set("outdoors", "lingjiu");
        set("exits", ([
                "north" : __DIR__"dating",
                "south" : __DIR__"dadao2",
        ]));
        set("objects",([
                CLASS_D("lingjiu") + "/meijian" : 1,
                CLASS_D("lingjiu") + "/lanjian" : 1,
        ]));
        setup();
}

int valid_leave(object me, string dir)
{
        object guarder;

        if (dir != "north")
                return 1;

        if (objectp(guarder = present("mei jian", environment(me))))
                return guarder->permit_pass(me, dir);

        if (objectp(guarder = present("lan jian", environment(me))))
                return guarder->permit_pass(me, dir);

        return 1;
}
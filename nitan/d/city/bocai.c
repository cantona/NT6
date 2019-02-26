//Room: bocai.c

inherit ROOM;

void create ()
{
        set ("short", "博彩店");
        set("long", @LONG
這裏是提供彩票服務的博彩娛樂場所。牆上掛着曾開出過的歷史
號碼。店內人聲鼎沸，人們相互交流着下次的中獎號碼。有人臉上掛
着淺笑，也有人面目通紅，激動不已。喜歡博彩的玩家在這裏可以向
店老闆詢問。
LONG );
        set("exits",  ([
                "south" : "/d/city/daxiao",
        ]));

        set("objects", ([
                // "/adm/npc/lottery" : 1,
        ]));
        set("no_fight", 1);

	set("coor/x", -20);
	set("coor/y", 0);
	set("coor/z", 0);
	setup();
}

void init()
{
        add_action("do_getnum", "getnum");
}

int do_getnum()
{
        object me = this_player();
        int i, n;
        string num = "機選號碼：";

        if (me->is_busy())
              return notify_fail("你正在分析號碼。\n");

        for (i = 0; i < 5; i++)
        {
              n = random(10);
              num += sprintf("%d", n);
        }
        num += "\n";
        tell_object(me, num);
        me->start_busy(1);
        return 1;
}
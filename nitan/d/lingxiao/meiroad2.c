inherit ROOM;
#include <ansi.h> 

void create()
{
        set("short","梅道");
        set("long",@LONG 
這也是一條充滿梅花清香的小道。與殿外不同的是，這兒
種滿了梅樹，而且全是如鮮血般燦爛的紅梅，花瓣片片飄落到
潔白的雪地上，就如一個温婉和順的美人，在給自己的心上人
刺繡時，不小心刺破了手指而流出的一滴血，浸到了白絹上樣。
一隻通體雪白的雪鶴在地上翩然起舞，逍遙自得。
LONG);
        set("outdoors", "lingxiao");
        set("exits", ([
                    "west"  : __DIR__"stone",
                    "east"  : __DIR__"meiroad1",
        ]));
        set("objects", ([
                "/clone/quarry/he2" : 1,
                __DIR__"obj/ban" : 1,
        ]));
        setup();
}

void init()
{
        add_action("do_pick","pick");
}

int do_pick(string arg)
{
        object me = this_player();
        object ob;

        if (arg == "mei hua" || arg == "meihua")
        {
                if (query("count") < -5)
                        return notify_fail("這裏的梅花已經被摘光了。\n");

                ob = new(__DIR__"obj/mei");
                ob->move(me, 1);
                addn("count", -1);

                message_vision("$N從路旁的樹上摘了一朵" +
                               query("name", ob)+"。\n",me);
                return 1;
        } else
                return notify_fail("你要摘什麼？\n");
}
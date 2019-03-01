#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "甬道");
        set("long", @LONG
這個山洞裡伸手不見五指，黑沉沉的甚麼也瞧不見。
LONG);
        set("exits", ([
                "out" : __DIR__"shenfeng",
        ]));
        setup();
}

void init()
{
        add_action("do_use", "use");
        add_action("do_tiao", "tiao");
        add_action("do_tiao", "jump");
}

int do_use(string arg)
{
        object me = this_player();

        if (! arg || arg == "" ) 
                return 0;

        if (! present("fire", me))
                return 0;

        if( query("mark/light", this_object()) )
                return notify_fail("你已經點著火折了。\n");

        if (arg == "fire")
        {
                     message_vision(HIR "\n$N" HIR "取出火折一晃，發現從這下去離地"
                               "面至少有十七八丈，峰內地面遠比外面的為低。\n"
                               "\n" NOR, me);

                set("long", "憑借火折的微光，你可以看到從這下去離地面至少有十"
                            "七\n八丈高，峰內地面遠比外面的為低。\n");

                addn("mark/light",query("id", me));
                return 1;
       }
}

int do_tiao(string arg)
{
        object ob, me = this_player();

        if( !query("mark/light", this_object()) )
                return notify_fail("洞裡一片漆黑，你根本探不清方向。\n");

               if (! arg || arg != "down")
                return notify_fail("你要往哪跳？\n");

        message_vision(HIY "\n$N" HIY "豫了一下，鼓氣勇氣，跳了下去。\n\n" NOR, me);

        // 判斷是誰點燃的火折，如果持火折者跳了下去，則恢復黑暗。
        if( query("mark/light", this_object()) == query("id", me) )
        {
                delete("mark/light");
                       set("long", "山洞裡伸手不見五指，黑沉沉的甚麼也瞧不見。\n");

                message("vision", HIR + me->name() + HIR "徑自拿著火折跳了下去"
                        "，洞內隨即又是一片漆黑。\n" NOR, environment(me), ({me}));
        }

            if ((int)me->query_skill("dodge", 1) < 150 )
        {
                me->move(__DIR__"shishi");
                me->receive_wound("qi", 300);
                me->unconcious();
                message("vision", HIR "\n突然聽得「砰」的一聲，只見一個人從上"
                                  "面的山峰上墜了下來，真是壯觀。\n" NOR,
                                  environment(me), ({me}));

                if (objectp(ob = present("fire", this_player())))
                               destruct(ob);

        } else
        {
                me->move(__DIR__"shishi");
                message("vision", HIY + me->name() + HIY "從上面跳了下來。\n" NOR,
                                  environment(me), ({me}));

                if (objectp(ob = present("fire", this_player())))
                {
                        message_vision(HIR "\n突然間$N" HIR "手一鬆，火折子不"
                                       "知掉到哪裡去了。\n", me);
                        destruct(ob);
                }
        }
               return 1;
}
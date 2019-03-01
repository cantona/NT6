#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "石室");
        set("long", @LONG
這個山洞裡伸手不見五指，黑沉沉的甚麼也瞧不見。
LONG);
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
                message_sort(HIR "\n$N" HIR "取出火折一晃，火光下只見四"
                             "面石壁都是晶瑩白玉，地下放著幾張桌椅，伸手"
                             "在桌上一按，桌子居然仍是堅牢完固，原來山洞"
                             "密閉，不受風侵，是以洞中物事並不朽爛。\n\n"
                             NOR, me);

                set("long", @LONG
借著微弱的火光，只見四面石壁(wall)都是晶瑩白玉，地
下放著幾張木制桌椅。你伸手在桌上一按，桌子居然仍是堅牢
完固，原來山洞密閉，不受風侵，是以洞中物事並不朽爛。

LONG);

                set("item_desc", ([
                        "wall" : WHT "只見石壁上有一大裂縫，從黑□□的裂"
                                 "縫裡飄出陣陣的陰風。\n" NOR, 
                ]));
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
                me->move(__DIR__"yongdao2");
                me->receive_wound("qi", 300);
                me->unconcious();
                message("vision", HIR "\n突然聽得「砰」的一聲，只見一個人從上"
                                  "面的山峰上墜了下來，真是壯觀。\n" NOR,
                                  environment(me), ({me}));
        } else
        {
                me->move(__DIR__"yongdao2");
                message("vision", HIY + me->name() + HIY "從上面跳了下來。\n" NOR,
                                  environment(me), ({me}));
        }
        return 1;
}
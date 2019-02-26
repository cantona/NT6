#include <ansi.h>
inherit ROOM;

#define HUANGJINFU    "/clone/lonely/huangjinfu"

void create()
{
        set("short", "甬道");
        set("long", @LONG
前面山石阻路，已到盡頭。只見盡頭處閃閃生光，走近看
時，卻是一玉石巨門。這門高達丈許，那裏像門，直是一塊巨
大的巖石。石門(gate)上下左右還有四個門環，均有兩尺多長
的粗大鐵鈕緊緊扣住。
LONG);
        set("exits", ([ 
                "south" : __DIR__"yongdao2",
        ]));
        setup();
}

void init()
{
        object ob;

        ob = find_object(HUANGJINFU);
        if (! ob) ob = load_object(HUANGJINFU);

        if (! environment(ob))
        {
                set("item_desc",([
                        "gate": WHT "\n兩扇厚厚的大石門，似乎不可能打破它。只見"
                                "石門的門環上插\n着一把" NOR + YEL "黃金斧" NOR
                                + WHT "(huangjin fu)" WHT "。\n\n" NOR,

                        "huangjin fu" : YEL "這是一柄純黃鑄造的大斧，斧柄末端似"
                                        "乎有些鬆動。\n" NOR,

                        "fu"          : YEL "這是一柄純黃鑄造的大斧，斧柄末端似"
                                        "乎有些鬆動。\n" NOR,

                        "huangjin"    : YEL "這是一柄純黃鑄造的大斧，斧柄末端似"
                                        "乎有些鬆動。\n" NOR,
                ]));
                add_action("do_get", "get");
             } else
        {
                set("item_desc",([
                        "gate": WHT "兩扇厚厚的大石門，似乎不可能打破它。\n" NOR,
                ]));
        }
               add_action("do_break", "break");
}

int do_get(string arg)
{
        object me, ob;

        me = this_player();
        ob = find_object(HUANGJINFU);
        if (! ob) ob = load_object(HUANGJINFU);

        if (environment(ob)) return 0;

        if (! arg || arg == "" ) return 0;

        if (arg == "huangjin fu from gate"
           || arg == "huangjin from gate"
           || arg == "fu from gate")
        {
                if ((int)me->query_skill("force", 1) > 200)
                {
                        ob->move(me, 1);
                             message_vision(HIY "\n$N" HIY "「噗」的一聲，從石門上拔"
                                       "出一柄黃金斧，只激得塵土飛揚。\n\n" NOR,
                                       me);

                             set("item_desc",([
                                     "gate": WHT "兩扇厚厚的大石門，似乎不可能打破它"
                                        "。\n" NOR,
                        ]));

                     } else
                {
                             message_vision(WHT "\n$N" WHT "使出了吃奶的力，可是門環"
                                       "上的" NOR + YEL "黃金斧" NOR "(huangjin"
                                       " fu)" WHT "依然紋絲不動。\n" NOR, me);
                     }
                     return 1;
        }
        return 0;
}

int do_break(string arg)
{
        object me, ob;
        object room;

        me = this_player();
        ob=query_temp("weapon", me);

            if (! arg || arg != "gate")
                return notify_fail("你要毀掉什麼？\n");

        if (query("exits/north"))
                return notify_fail("石門已經被劈開了，還劈什麼？\n");

            if (! ob)
        {
                message_vision(HIY "\n$N" HIY "氣沉丹田扎穩馬步，大吼一聲，雙拳"
                               "猛的擊向石門！\n" NOR, me);

                    if ((int)me->query_skill("force", 1) < 200)
                {
                        message_vision(HIR "結果只聽$N" HIR "一聲悶哼，被石門的"
                                       "反彈力震得飛了出去。\n\n" NOR, me);
                        me->receive_wound("qi", 300);
                        set("neili", 0, me);
                        me->unconcious();
                } else
                {
                        message_vision(HIR "結果只聽轟的一聲悶響，那石門卻是紋"
                                       "絲未動。\n\n" NOR, me);
                        set("neili", 0, me);
                }
                return 1;
            }

               message_vision(HIY"\n$N"HIY"高高舉起手中的"+query("name", ob)+HIY
                       "，朝石門猛劈而去！\n" NOR, me);

            if ((int)me->query_skill("force", 1) < 200
           || base_name(ob) != HUANGJINFU)
        {
                message_vision(HIR "結果只聽「鐺」的一聲，$N" HIR "虎口一震，"
                               +query("name", ob)+HIR"禁不住脱手飛出。\n\n"
                               NOR, me);
                ob->move(environment(me));
                return 1;
            }

            if (! (room = find_object(__DIR__"yongdao4")))
                room = load_object(__DIR__"yongdao4");

        if (! query("exits/north"))
        {
                message_vision(HIY "只聽「轟」的一聲巨響，石門已被$N" HIY "劈得"
                               "粉碎，露出一個洞口。\n\n" NOR, me);

                set("exits/north", __DIR__"yongdao4");
                set("exits/south", __FILE__, room);

                message("vision", HIY "\n只聽外面「轟」的一聲巨響，石門被人劈開"
                                  "了。\n" NOR, room);
        }
            return 1;
}

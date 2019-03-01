#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "神峰");
        set("long", @LONG
這裡是神峰的山腰，四周均有斧鑿痕跡，察看峰壁發現洞
口的痕跡很是明顯，只是年深月久，洞門(gate)的四周都已被
沙子(sand)牢牢堵塞住了。
LONG);
        set("outdoors", "gaochang");
        set("item_desc", ([
                "gate" : WHT "嵌在神峰山腰的巨大厚重的石門，看起來很難"
                         "推動。\n" NOR,
                "sand" : HIY "巨大的石門由于時間過長，已被沙子堵得嚴嚴"
                         "實實。\n如果要想打開石門，看來非得將這些沙子"
                         "移開才行。\n" NOR,
        ]));
        setup();
}

void init()
{
        add_action("do_climb", "climb");
        add_action("do_push", "push");
        add_action("do_move", "move");
}

int do_climb(string arg)
{
        object me = this_player();

        if (! arg || arg != "down")
                return notify_fail("你要往哪個方向爬？\n");

        message("vision", HIW "只見" + me->name() + HIW "戰戰兢兢地往神"
                          "峰下爬去。\n" NOR, environment(me), ({me}));

        me->move(__DIR__"shanjiao");

        tell_object(me, HIW "\n你順著神峰山腰的斧鑿痕跡慢慢地爬了下來。"
                          "\n\n" NOR);
        message("vision", HIW "只見" + me->name() + HIW "戰戰兢兢地從神"
                          "峰上爬了下來。\n", environment(me), ({me}));
        return 1;
}

int do_move(string arg)
{
        object me = this_player();

        if (! arg || arg != "sand")
                return notify_fail("你要幹什麼？\n");

        if( query("mark/sand", this_object())>5 )
                return notify_fail("石門上現在已經沒有沙子了。\n");

        if (me->is_busy())
                return notify_fail("你正忙著呢。\n");

        if( query("mark/sand", this_object())<5 )
                message_vision(HIC "$N" HIC "仔細地清除著覆蓋在石門周圍"
                               "的沙子。\n" NOR, me);
        else
                message_vision(HIC "$N" HIC "終于將覆蓋在石門周圍的沙子"
                               "除得幹幹凈凈。\n" NOR, me);
        addn("mark/sand", 1);
        me->start_busy(2);
        return 1;
}

int do_push(string arg)
{
        object room, me = this_player();

        if (! arg || arg != "gate")
                return notify_fail("你要推什麼？\n");

        if (query("exits/enter"))
                return notify_fail("石門已經是開著的了，還推什麼？\n");

        message_vision(HIY "\n$N" HIY "凝神聚氣，雙臂陡然向石門猛擊而去"
                       "。\n" NOR, me);

        if ((int)me->query_skill("force") < 300
            || query("mark/sand", this_object())<5
            || query("neili", me)<1500 )
        {
                write(HIR "結果「轟」的一聲悶響，你被石壁的反彈力震得飛"
                      "了出去。\n\n" NOR);

                message("vision", HIR "卻見" + me->name() + HIR "身體猛"
                                  "然一晃，被震得飛了出去，墜到了山腳下"
                                  "。\n\n" NOR, environment(me), ({me}));

                me->move(__DIR__"shanjiao");
                me->receive_wound("qi", 200);
                me->unconcious();
                message("vision", HIR "\n突然聽得「砰」的一聲，只見一個"
                                  "人從上面的山峰上墜了下來，真是壯觀。"
                                  "\n" NOR, environment(me));
                return 1;
        }

        if (! (room = find_object(__DIR__"yongdao1")))
                room = load_object(__DIR__"yongdao1");

        if (! query("exits/enter"))
        {
                message_vision(HIY "$N" HIY "將石門震到一邊，露出一個洞"
                               "口，可是洞內一片漆黑，甚麼也瞧不見。\n"
                               NOR, me);

                set("exits/enter", __DIR__"yongdao1");
                    set("exits/out", __FILE__, room);
                addn("neili", -1000, me);

                    message("vision", HIY "\n只聽外面傳來一陣移動石門的隆隆"
                                  "的響聲。\n" NOR, room);
                    return 1;
            }
        return 1;
}
// river.c
// by vin

#include <room.h>
#include <ansi.h>

inherit ROOM;

void setup()
{
        set("item_desc/river", HIC "\n只見近岸處有一葉小舟，也許大聲喊("
                               HIY "yell" HIC ")一聲船家(" HIY "boat" HIC
                               ")就\n能聽見。倘若你自負輕功絕佳,也可直接"
                               "渡水(" HIY "cross" HIC ")踏江而過。\n" NOR);
        ::setup();
}

void init()
{
        add_action("do_yell", "yell");
        add_action("do_cross", "cross");
}

int do_yell(string arg)
{
        object *obs;
        object me, arrive, boat;
        string msg;
        string to;

        me = this_player();
        to = query("arrive_room");
        if( !to ) to = query("to");
        arrive = find_object(to);

        if (! arrive)
                arrive = load_object(to);

        if (! arg || arg == "" )
                return 0;

        if (strlen(arg) > 15)
                return notify_fail("你清了清嗓子，發現自己似乎無法"
                                   "吼出那麼長一段話。\n");

        if (arg == "boat")
                arg = "船家";

        msg = WHT "\n$N" NOR + WHT "鼓足中氣，高喊一聲：「" +
              arg + "」聲音遠遠傳了出去。\n" NOR;

        if (arg != "船家" || ! arrive)
        {
                msg += HIY "突然江面上遠遠傳來一陣回聲：「" +
                       arg + "～～～」\n" NOR;
                message_vision(msg, me);
        } else
        {
                msg += HIY "\n只見一葉扁舟緩緩地駛了過來，艄公隨手"
                       "將一塊踏腳板搭上堤岸，以便乘客上下。$N" HIY
                       "見後趕忙快步踏上。艄公待$P上船後隨即便將踏"
                       "腳板收起來，竹篙一點向江心駛去。\n\n" NOR;
                message_sort(msg, me);

                boat = new("/clone/misc/river_boat");

                obs = filter_array(all_inventory(), (: $1 == $(me)
                                   || $1->query_leader() == $(me)
                                   && ! playerp($1)
                                   && ! $1->is_killing(query("id", $(me))) :));
                obs->move(boat);

                me->start_call_out((: call_other, __FILE__, "arrival",
                                      me, boat, arrive :), 3);
        }
        return 1;
}

void arrival(object me, object boat, object arrive)
{
        object *obs;

        if (! objectp(me) || ! objectp(boat))
                return;

        if (environment(me) != boat)
                return;

        obs = filter_array(all_inventory(boat), (: $1 == $(me)
                           || $1->query_leader() == $(me)
                           && ! playerp($1)
                           && ! $1->is_killing(query("id", $(me))) :));

        tell_object(me, CYN "\n艄公說道：「到啦，上岸吧。」隨即把"
                        "一塊踏腳板搭上堤岸。\n\n" NOR);

        obs->move(arrive);
        message("vision", HIY "\n只見一艘小船緩緩向岸邊靠近，還未"
                          "泊穩，便有人急急跳了下來。\n\n" NOR,
                          environment(me), ({ me }));

        if (sizeof(obs = all_inventory(boat)) > 0)
        {
                message("vision", WHT "只聽撲通撲通幾聲，從渡船上"
                                  "扔下一堆東西來。\n" NOR, me);
                obs->move(arrive);
        }

        if (objectp(boat))
                destruct(boat);
}

int do_cross()
{
        object me, arrive;
        string msg;
        string to;

        me = this_player();
        to = query("arrive_room");
        if( !to ) to = query("to");
        arrive = find_object(to);

        if (! arrive)
                arrive = load_object(to);

        if (! arrive)
        {
                tell_object(me, "你舉目望去，發現水面霧氣極濃，什"
                                "麼都看不清。\n");
                return 1;
        }

        if (! me->query_skill("dodge", 1))
        {
                tell_object(me, "你大眼一瞪？幹什麼，跳河自殺麼？\n");
                return 1;
        }

        if (me->query_skill("dodge") < 270)
        {
                tell_object(me, "你掂量了一下，覺得自己的輕功似乎"
                                "還沒煉到家。\n");
                return 1;
        }

        if( query("neili", me)<300 )
        {
                tell_object(me, "你的內力不夠，還是先休息一下吧。\n");
                return 1;
        }

        addn("neili", -200, me);

        msg = HIW "\n只見$N" HIW "身形微微一晃，已然飄出丈許，以"
              "足尖輕點水面向對岸踏波掠去，漾起層層微瀾。身形洋洋"
              "洒洒，若彩蝶飛揚，甚是逍遙。便在眾人驚嘆輕功絕妙間"
              "，早已沒了蹤影。\n\n" NOR;
        message_sort(msg, me);

        me->move(arrive);
        message("vision", HIW "\n忽見水面上霧氣散開，一人踏波"
                          "逐浪，竟大踏步掠過江來！\n\n" NOR,
                          environment(me), ({ me }));
        return 1;
}

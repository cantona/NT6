// Code of ShenZhou
// /d/zhongnan/obj/qz_force.c 玄門內功心法
/*
        修正內力計算方法
        修正使用者躲於safe room使用避免使者的不當之使用方式
        修正使用者在坐騎上修煉內力亦可行動之BUG
        mantian /may/1/2001
*/


inherit ITEM;
string *koujue = ({
                                         "《修真活計有何憑，心死羣情今不生》",
                                         "《精氣充盈功行具，靈光照耀滿神京》",
                                         "《祕語師傳悟本初，來時無久去無餘》",
                                         "《歷年塵垢揩磨盡，偏體靈明耀太虛》"
});

int do_dazuo(string arg);
int exercising(object me);
int halt_exercise(object me);


void setup()
{}

/*
void init()
{
        add_action("do_dazuo", "lianqi");
}
*/

void create()
{
        set_name("玄門內功心法", ({ "neigong xinfa", "xinfa" }));
        set_weight(600);
        if( clonep() )
        set_default_object(__FILE__);
        else
        {
                set("unit", "本");
                set("long", "這是一本線裝書，上書《玄門內功心法》，原來是全真教的練氣(lianqi)祕籍。\n");
                set("value", 5000);
                set("material", "paper");
                set("skill", ([
                        "name":                        "force",        // name of the skill
                        "exp_required":        0,                        // minimum combat experience required
                        "jing_cost":        30,                        // jing cost every time study this
                        "difficulty":        10,                        // the base int to learn this skill
                        "max_skill":        150                        // the maximum level you can learn
                        ]) );
        }
}

int do_dazuo(string arg)
{
        object me = this_player();
        int exercise_cost;
        object where;

        seteuid(getuid());
        where = environment(me);

        if (!present("neigong xinfa", me))
                return 0;

        if( query("pigging", where) )
                return notify_fail("你還是專心拱豬吧！\n");

        if( query("sleep_room", where) )
                return notify_fail("不能在睡房裏修煉內功，這會影響他人。\n");

        if( query("no_fight", where) )
                return notify_fail("你不能集中精神，只感體內真氣亂竄，無法專心修練內功。\n");

        if( query("name", where) == "大車裏" )
                return notify_fail("車裏太顛簸, 修練內功會走火入魔. \n");

        if( me->is_busy() || query_temp("pending/exercising", me) )
                return notify_fail("你現在正忙着呢。\n");

        if( me->is_fighting() )
                return notify_fail("戰鬥中不能練內功，會走火入魔。\n");

        if( query("rided", me) )
                return notify_fail("在坐騎上修練內功，會走火入魔。\n");

        if( !stringp(me->query_skill_mapped("force")) )
                return notify_fail("你必須先用 enable 選擇你要用的內功心法。\n");

        if( !arg || !sscanf(arg, "%d", exercise_cost))
                return notify_fail("你要花多少氣練功？\n");
        if (exercise_cost < 10)
                return notify_fail("你的內功還沒有達到那個境界！\n");

        if( query("qi", me)<exercise_cost )
                return notify_fail("你現在的氣太少了，無法產生內息運行全身經脈。\n");

        if( query("jing", me)*100/query("max_jing", me)<70 )
                return notify_fail("你現在精不夠，無法控制內息的流動！\n");

        write("你按着玄門內功心法的氣訣坐下來運氣用功，一股內息開始在體內流動。\n");

        set_temp("pending/exercise", 1, me);
        set_temp("exercise_cost", exercise_cost, me);
        message_vision("$N盤膝坐下，開始修煉內力。\n", me);
        me->start_busy((: exercising :), (:halt_exercise:));
        return 1;
}

int exercising(object me)
{
        int cost;
        object  where = environment(me);
        int exercise_cost=query_temp("exercise_cost", me);
         int neili_gain = 1 + (int)me->query_skill("force") / 2.5;
        if (exercise_cost < 1)
                return 0;
        addn("neili", neili_gain, me);
        set_temp("exercise_cost", exercise_cost-=neili_gain, me);

        //me->addn("qi", -neili_gain);
        cost = neili_gain*3/2;
        if( base_name(where) == "/d/quanzhen/yangxin" )
                cost = cost/3*2;

        if( me->query_skill_mapped("force") == "xiantian-gong" )
        {
                write("你默唸着"+koujue[random(4)]+"，只覺得一股內息在體內迅速流動，全身都感到舒暢無比。\n");

                me->receive_damage("qi", cost);
                me->receive_damage("jing", cost/10);
                set_temp("die_reason", "打坐走火入魔死了", me);
        }
        else
        {
                if( random(6)==3 )
                {
                        if(me->query_skill_mapped("force") == "bitao-xuangong")
                        {
                                write("你默唸着"+koujue[random(4)]+"，只覺得一股內息在體內竄來竄去，讓你覺得不對勁，難道是走火入魔的前兆？\n");
                                cost = neili_gain + random(neili_gain*100);
                        }
                        else
                        {
                                write("你默唸着"+koujue[random(4)]+"，只覺得一股內息在體內竄來竄去，讓你覺得不對勁。\n");
                                cost = neili_gain + random(neili_gain*10);
                                me->receive_damage("qi", cost);
                                set_temp("die_reason", "打坐走火入魔死了", me);
                        }
                        }
                        else
                        {
                        write("你念着"+koujue[random(4)]+"，似乎有點體會，只覺得一股內息在體內迅速流動，全身都感到舒暢無比。\n");

                        me->receive_damage("qi", cost, "打坐走火入魔死了");
                        me->receive_damage("jing", cost/10, "打坐走火入魔死了");
                        }

                }
        if (exercise_cost > 0)
                return 1;

        set_temp("pending/exercise", 0, me);
        message_vision("$N運功完畢，深深吸了口氣，站了起來。\n", me);
        if( query("neili", me)<query("max_neili", me)*2 )
                 return 0;
        else
        {
                if( query("max_neili", me)>me->query_skill("force")*query("con", me)*2/3 )
                {
                        write("你的內力修為似乎已經達到了瓶頸。\n");
                        set("neili",query("max_neili",  me), me);
                        return 0;
                }
                else
                {
                        addn("max_neili", 1, me);
                        set("neili",query("max_neili",  me), me);
                        write("你的內力增加了！！\n");
                        return 0;
                }
        }
}

int halt_exercise(object me)
{
        if( query("neili", me)>query("max_neili", me)*2 )
                set("neili",query("max_neili",  me)*2, me);
                set_temp("pending/exercise", 0, me);
                return 1;
}

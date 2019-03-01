// diaogan.c 釣竿

#include <ansi.h>

inherit ITEM;

void init()
{
        if (interactive(this_player()) &&
            environment() == this_player())
        {
                add_action("do_fish", "fish");
                add_action("do_draw", "draw");
        }
}

void create()
{
        set_name(HIG "釣竿" NOR, ({ "diao gan", "gan" }));
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("unit", "根");
                set("long", "這是一根釣魚者常用的釣竿，常用它來釣魚(fish)。\n");
                set("value", 2000);
        }

        setup();
}

int do_fish()
{
        object yr;
        object ob;
        object me = this_player();

        if (! arrayp(query("resource/fish", environment(me))))
                return notify_fail("這裡看不出有魚的樣子。\n");

        if (! objectp(yr = present("yu er", me)) || yr->query_amount() < 1)
                return notify_fail("你身上沒有魚餌了。\n");

        if (me->is_busy() || me->is_fighting())
                return notify_fail("你還是忙完手頭上的事情再說吧。\n");

        message_vision("$N掏出一點魚餌，仔細的放在釣鉤上，輕輕一甩桿，只見水面上盪起了\n"
                       "一個個圓圈，中間只有一個白色的浮子在隨著水波盪漾。\n", me);
        yr->add_amount(-1);
        me->start_busy((: call_other, __FILE__, "finishing" :),
                       (: call_other, __FILE__, "halt_finishing" :));
        set_temp("owner", me);
        set_temp("fishing", 0, me);
        set_temp("fishing_env", environment(me), me);
        return 1;
}

int finishing(object me)
{
        int stage;

        if( environment(me) != query_temp("fishing_env", me) )
        {
                delete_temp("fishing", me);
                delete_temp("fishing_env", me);
                return 0;
        }

        switch(stage=query_temp("fishing", me) )
        {
        case 1:
                if (random(4))
                {
                        message_vision("$N的浮子輕輕的震動，一上"
                                       "一下的搖晃個不停。\n", me);
                        break;
                }

                message_vision("$N的浮子忽然劇烈的震盪起來。\n", me);
                stage++;
                break;

        case 2:
        case 3:
                message_vision(random(2) ? "$N的浮子忽左忽右搖擺個不停。\n"
                                         : "$N的浮子猛然向下一竄，然後又跳出水面。\n",
                               me);
                stage++;
                break;
        case 4:
                message_vision(random(2) ? "一陣劇烈的搖擺過後，浮子安靜"
                                           "下來，$N連忙拉起釣竿，一看鉤上空空如也。\n"
                                         : "浮子猛然的左右擺動，忽然又安靜了下了，$N疑惑的"
                                           "拉起釣竿，除了閃亮\n的魚鉤，上面什麼也沒有。\n",
                               me);
                tell_object(me, CYN "看來是拉桿(draw)拉晚了，白白的賠了一個魚餌！\n" NOR);
                delete_temp("fishing", me);
                delete_temp("owner");
                return 0;

        default:
                if (random(5))
                {
                        if (random(3)) return 1;
                        tell_object(me, random(2) ? "水面波瀾不驚，沒有什麼變化。\n"
                                                  : "微風輕輕的吹，水面盪起一層層細浪，就是沒有魚上鉤。\n");
                        break;
                }
                message_vision("忽然$N的浮子震動了一下。\n", me);
                stage = 1;
                break;
        }

        set_temp("fishing", stage, me);
        return 1;
}

int halt_finishing(object me)
{
        delete_temp("owner");
        delete_temp("fishing", me);
        message_vision("$N收起釣竿，看樣子是不想再釣了。\n",  me);
        return 1;
}

int do_draw(string arg)
{
        string *fish;
        object ob;
        object me;
        int stage;
        int exp;
        int pot;

        if (! arg || ! id(arg))
                return notify_fail("你要拉什麼？\n");

        me = this_player();

        if (query_temp("owner") != me)
                return notify_fail("你又沒在釣魚，拉桿幹什麼？\n");

        if( environment(me) != query_temp("fishing_env", me) )
                return 0;

        stage=query_temp("fishing", me);
        if (stage < 2)
        {
                message_vision("$N連忙一拉釣竿，高高的舉了起來，卻見上面魚餌依然，還"
                               "是老樣子，只好\n垂頭喪氣的重新把桿甩了出去。\n", me);
                set_temp("fishing", 0, me);
                return 1;
        }

        fish=query("resource/fish", environment(me));
        if (sizeof(fish) < 1)
                log_file("log", sprintf("variable: resource/fish error in %s.\n",
                                        base_name(environment(me))));
        ob = new(fish[random(sizeof(fish))]);

        message_vision(random(2) ? "$N手急眼快，猛地一收釣竿，只見上面掛著一" +
                                   query("unit", ob)+"扭來扭去的"+
                                   ob->name() + "。\n"
                                 :"$N順勢一拉桿，登時把一"+query("unit", ob)+
                                   ob->name() + "釣了上來。\n", me);
        tell_object(me,HIG"你釣到了一"+query("unit", ob)+
                        ob->name() + HIG + "。\n" NOR);
        ob->move(me, 1);

        delete_temp("owner");
        delete_temp("fishing", me);
        delete_temp("fishing_env", me);

        if( query("total_hatred", me)>10 )
                addn("total_hatred", -10, me);
        else
                set("total_hatred", 0, me);

        if( query("combat_exp", me)<300000 || 
            query("combat_exp", me)>1200000 )
                return 1;

        exp = 50 + random(100);
        pot = exp / 3;
        GIFT_D->work_bonus(me, ([ "exp" : exp, "pot" : pot ]));
        tell_object(me, HIC "你心中微微一動，對武學的理解又深了一層。\n" NOR);
        return 1;
}

int move(mixed dest, int raw)
{
        object me;

        if (me = query_temp("owner"))
                me->interrupt_me();

        return ::move(dest, raw);
}

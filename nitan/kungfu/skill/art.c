// This program is a part of NITAN MudLIB
// art.c 琴棋書畫

inherit SKILL;

int do_play(string arg);

void create() { seteuid(getuid()); }

string type() { return "knowledge"; }

int valid_learn(object me)
{
        if( query("int", me)<24 && me->query_int()<32 )
                return notify_fail("琴棋書畫乃是極其風雅之事，" + 
                       RANK_D->query_respect(me) + "似乎太過於俗氣了些。\n");

        if( query("shen", me)<-10000 )
                return notify_fail("你殺人如麻，倘若不能先平息了心頭魔念，哪裏又會有心思彈琴下棋？\n");

        if( query("family/master_name", me) != "何足道" )
                return notify_fail("你一個練武的粗人，學這些酸腐文人的東西幹什麼？\n");

        return 1;
}

int practice_skill(object me)
{
        return notify_fail("琴棋書畫只能靠學(learn)來提高。\n");
}

void init()
{
        add_action("do_play", "play");
}

int do_play(string arg)
{
        object me = this_player();

        if (! arg && (arg != "music") && (arg != "zheng") && (arg != "gu zheng")
        &&  (arg != "wei qi") && (arg != "qi") && (arg != "go") )
                return notify_fail("你要做什麼？\n");

        if (present("gu zheng", this_player()) &&
            ((arg == "music") || (arg == "zheng") || (arg == "gu zheng")))
        {
                if (me->query_skill("art", 1) < 30)
                {
                        message_vision("$N擺出一張古箏，錚錚琮琮彈了幾聲，只聽得曲調雜亂無章，宛如鬼哭狼號。\n", me);
                        me->receive_damage("jing", random(20) );
                        me->receive_damage("qi", random(20) );
                        return 1;
                }
                if (me->query_skill("art", 1) > 100)
                {
                        message_vision("$N擺出一張古箏，錚錚琮琮彈了幾聲，只聽得曲調平和，洋洋灑灑，頗有佳意。\n", me);
                        return 1;
                }
                me->receive_damage("jing", 10);
                me->receive_damage("qi", 10);
                me->improve_skill("art", (int)me->query_int() / 4 + (int)me->query_skill("art", 1) / 10);
                tell_object(me, "你擺出一張古箏，調了調絃，彈了起來，你只覺得連日來煩燥的心情好了許多。\n");

                message_vision("只見"+query("name", me)+
                               "雅興大發，竟彈起曲子來，你只覺得時而金戈鐵馬、大漠平沙。。。。。。\n"
                               "時而小橋流水、幾户人家。。。。。。萬般氣象，你心情頓時寧靜了許多。\n",
                                environment(me), ({me}));
                return 1;
        }
        if (present("wei qi", this_player()) && ((arg == "wei qi") || (arg == "qi") || (arg == "go")))
        {
                if ((me->query_skill("art", 1) < 40))
                {
                        message_vision("$N擺出一張棋盤，想研究圍棋，卻總覺得心煩意亂，定不下神來。\n", me);
                        me->receive_damage("jing", random(20));
                        me->receive_damage("qi", random(20) );
                        return 1;
                }
                if (me->query_skill("art", 1) > 100)
                {
                        message_vision("$N擺出一張棋盤，只覺棋面佈局盡在籌幄只之中，無密可研。\n", me);
                        return 1;
                }

                me->receive_damage("jing", 10);
                me->receive_damage("qi", 10);
                me->improve_skill("art", (int)me->query_int() / 4 + (int)me->query_skill("art", 1) / 10);
                tell_object(me, "你擺出一張棋盤，研究起圍棋來，只覺得心平氣和，很快就彷彿入定了。\n");

                message_vision("只見"+query("name", me)+
                               "雅興大發，竟打起棋譜來，對外界彷彿不聞不問，一副莫測高深的模樣。\n",
                               environment(me), ({me}));

        }
        return 1;
}
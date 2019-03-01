#include <ansi.h>
#include "duan.h"

inherit NPC;
inherit F_MASTER;

mixed ask_skill1();

void create()
{
        set_name("朱丹臣", ({ "zhu danchen", "zhu", "danchen" }));
        set("title", "大理國護衛" );
        set("nickname", CYN "筆硯生" NOR);
        set("long", "他是大理國四大護衛之一。一副書生酸溜溜的打扮行頭。\n");
        set("gender", "男性");
        set("age", 40);
        set("class", "officer");
        set("attitude", "friendly");
        set("shen_type", 1);
        set("str", 30);
        set("int", 20);
        set("con", 25);
        set("dex", 25);

        set("max_qi", 1800);
        set("max_jing", 1000);
        set("neili", 2200);
        set("max_neili", 2200);
        set("jiali", 50);
        set("combat_exp", 500000);
        set("score", 5000);

        set_skill("force", 120);
        set_skill("duanshi-xinfa", 120);
        set_skill("dodge", 120);
        set_skill("tiannan-bu", 120);
        set_skill("cuff", 120);
        set_skill("jinyu-quan", 120);
        set_skill("strike", 120);
        set_skill("wuluo-zhang", 120);
        set_skill("dagger", 140);
        set_skill("qingliang-daxuefa", 140);
        set_skill("parry", 120);
        set_skill("literate", 100000);
        set_skill("martial-cognize", 140);

        map_skill("force", "duanshi-xinfa");
        map_skill("dodge", "tiannan-bu");
        map_skill("cuff", "jinyu-quan");
        map_skill("strike", "wuluo-zhang");
        map_skill("dagger", "qingliang-daxuefa");
        map_skill("parry", "qingliang-daxuefa");

        prepare_skill("cuff", "jinyu-quan");
        prepare_skill("strike", "wuluo-zhang");

        set("inquiry", ([
                "透骨釘"   : (: ask_skill1 :),
        ]));

        create_family("段氏皇族", 15, "家臣");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "dagger.ding" :),
                (: perform_action, "cuff.man" :),
                (: perform_action, "strike.bian" :),
                (: exert_function, "recover" :),
        }));

        set("master_ob", 3);
        setup();
        carry_object("/d/dali/npc/obj/junfu")->wear();
        carry_object("/d/meizhuang/obj/panguanbi")->wield();
        add_money("silver", 10);
}

void init()
{
        ::init();
        add_action("do_learn","learn");
        add_action("do_learn","xue");
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        command("smile");
        command("say 世子殿下何需如此，只要有事吩咐在下一聲便是。");
        command("say 若世子不嫌棄，我這裡倒是有一套筆法可以傳授予你。");

        return;
}

int recognize_apprentice(object ob, string skill)
{
        if( query("family/family_name", ob) != "段氏皇族" )
        {
                command("sneer");
                command("say 我與閣下素不相識，不知閣下此話從何說起？");
                return -1;
        }

        if (skill != "qingliang-daxuefa" && skill != "dagger")
        {
                command("say 朱某生平只對筆法一項有所研究，其它功夫所知甚淺。");
                return -1;
        }

        if( !query_temp("can_learn/zhudanchen", ob) )
        {
                command("hehe");
                command("say 既然世子有心習武，在下理當竭盡所能傳授。");
                set_temp("can_learn/zhudanchen", 1, ob);
        }
        return 1;
}

mixed ask_skill1()
{
        object me;

        me = this_player();
        if( query("can_perform/qingliang-daxuefa/ding", me) )
                return "我不是已經教給你了嗎？";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "和我素無瓜葛，何出此言？";

        if (me->query_skill("qingliang-daxuefa", 1) < 1)
                return "你連我清涼打穴法都未學，怎麼來絕招一說？";

        if( query("family/gongji", me)<400 )
                return "恕在下無禮，王爺吩咐過，不得傳功給無功子弟。";

        if (me->query_skill("force") < 150)
                return "你的內功修為太差，學不了這一招。";

        if( query("max_neili", me)<1200 )
                return "你的內力修為太差，學不了這一招。";

        if (me->query_skill("qingliang-daxuefa", 1) < 100)
                return "你清涼打穴法的火候還不夠，回去練練再來吧。";

        message_sort(HIY "\n$n" HIY "微微一笑，伸手將$N" HIY "招到身前，低"
                     "聲在$N" HIY "耳旁嘀咕了半天。然後又拔出腰間鐵扇翻轉數"
                     "下，斜刺而出。似乎是一種頗為獨特的打穴法。\n\n" NOR,
                     me, this_object());

        command("smile");
        command("say 這招並不難練，依世子的悟性很快就可以熟練運用了。");
        tell_object(me, HIC "你學會了「透骨釘」。\n" NOR);
        if (me->can_improve_skill("dagger"))
                me->improve_skill("dagger", 1500000);
        if (me->can_improve_skill("qingliang-daxuefa"))
                me->improve_skill("qingliang-daxuefa", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/qingliang-daxuefa/ding", 1, me);
        addn("family/gongji", -400, me);
        return 1;
}

int accept_object(object who, object ob)
{
        int learn;

        learn=who->query_skill("literate",1);
        learn= learn?learn*10:500;

        if( !query("money_id", ob) )
                return 0;

        if( query("dushu", who) + 1 < 1 )
        {
                say(this_object()->name()+"笑道：“這怎麼好意思，您上次給的錢還沒讀完呢！”\n");
                return 0;
        }

        if( ob->value()/15 + query("dushu", who) < 0 )
        {
                say(this_object()->name()+"受寵若驚地說：“這麼多錢我可不敢收呀！”\n");
                return 0;
        }

        if( !query("dushu", who) )
        {
                if( ob->value() >= learn )
                {
                        say(this_object()->name()+"點了點頭，說道：哦，像你這麼有心的學生還真是不多見，好好努力\n可以向我請教讀書寫字(literate)的任何問題。\n");
                        set("dushu", ob->value()/15, who);
                        return 1;
                }
                else
                {
                        say(this_object()->name()+"說道：你的誠意不夠，這錢還是拿回去吧。\n");
                        return 0;
                }
        }
        else if(ob->value())
        {
                if( ob->value() >= learn )
                {
                        say(this_object()->name()+"點了點頭，說道：哦，像你這麼有心的學生還真是不多見，好好努力將來必定前途無量，謝了。\n");
                        addn("dushu", ob->value()/15, who);
                        return 1;
                }
                else
                {
                        say(this_object()->name()+"說道：你的誠意不夠，這錢還是拿回去吧。\n");
                        return 0;
                }
        }
        return 1;
}

int do_learn(string arg)
{
        string skill, teacher;
        object me,ob,room;
        int learn,times,i;
        int master_skill, my_skill, gin_cost, my_combat_exp,grade;
        int t1,t2,t3,t4,lvl,neili_cost;
        string *args;
        int c, r, rand;

        me = this_player();
        ob = this_object();

        if (me->is_busy())
                return notify_fail("你現在正忙著呢。\n");

        if(!arg || arg=="?" || arg=="/?")
                return notify_fail("指令格式：learn <某人> [about] <技能> <次數>\n");

        /*
        if ((sscanf(arg, "%s about %s %d", teacher,skill,times)!=3 ))
        if ((sscanf(arg, "%s %s %d", teacher, skill,times)!=3 ))
                return notify_fail("指令格式：learn <某人> [about] <技能> <次數>\n");
        */

        if( (i = sizeof(args = explode(arg, " "))) < 2 )
                return notify_fail("指令格式：learn|xue <某人> <技能> <次數>\n");

        i--;
        if( i >= 2 && sscanf(args[i], "%d", times) && times )
                i--;
        else
                times = 1;
        skill = args[i--];
        if( args[i] == "about" && i >= 1 )
                i--;
        teacher = implode(args[0..i], " ");

        if (!ob->id(teacher))
                return 0;

        if( me->is_fighting() )
                return notify_fail("臨陣磨槍？來不及啦。\n");

        c = 200 + query_temp("apply/learn_times", me);
        if( present("learn emblem", me) )
                c += 1000;

        if( present("learn emblem2", me) )
                c += 1500;

        if( query("special_skill/wisdom", me) )
                c += 1000;

        if( times < 1 || times > c ) {
                write("學習次數最少一次，最多也不能超過" + chinese_number(c) +"次。\n");
                return 1;
        }

        if ((int)times<1) {
                write("你要學幾次？\n");
                return 1;
        }

        if( !living(ob) )
                return notify_fail("嗯....你得先把" + ob->name() + "弄醒再說。\n");

        if (me->query_skill("literate",1) >=ob->query_skill("literate", 1) && query("dushu",me))
        {
                command("say 嗯...."+me->name()+"，你學習很用功，但我只能教你到這了。天底下已經無人可以教你了。\n");
                return 1;
        }

        learn=me->query_skill("literate",1);

        if( !query("dushu", me) )
        {
                command("say 咦？"+me->name()+"，我不記得收過你這個學生啊....\n");
                return 1;
        }

        if( query("dushu", me)<times ) {
                command("say 咦？"+me->name()+"，你交的錢已經不夠學這麼多次了啊....\n");
                return 1;
        }

        if (!learn)     learn=10;
        if (skill!="literate") {
                write("這項技能你恐怕必須找別人學了。\n");
                return 1;
        }
        if (! room=find_object(query("startroom",ob)))
                room=load_object(query("startroom",ob));
        if (room!=environment()){
                command("say 我出來辦點事，等我回去再說吧！");
                return 1;
        }
        /*
        if (ob->query("jing<30"))
        {
                 ob->set("env/no_teach",1);
                command("say 我今天累了，我要去休息了！");
                return 1;
        }
        */
        my_skill = me->query_skill(skill, 1);
        master_skill = ob->query_skill(skill, 1);
        if( my_skill >= master_skill ) {
                write("這項技能你的程度已經不輸你師父了。\n");
                return 1;
        }

        if( (query("level", me) < 60 && my_skill > 10000) ||
            (query("level", me) < 80 && my_skill > 20000) ||
            (query("level", me) < 100 && my_skill > 30000) ) {
                write("這項技能你的程度已經達到封頂上限了。\n");
                return 1;
        }

        if( (query("potential", me) - query("learned_points",me)) < times )
                return notify_fail("你的潛能不夠學習這麼多次了。\n");

        gin_cost = 150 / (int)me->query_int() + 1;
        if( !my_skill ) {
                gin_cost *= 2;
                me->set_skill(skill,0);
        }
        printf("你向%s請教有關「%s」的疑問。\n", ob->name(), to_chinese(skill));

        t1 = query("jing",me) / gin_cost;
        t2 = times - t1;
        if( t2 > 0 ) {
                lvl = me->query_skill("force");
                if( lvl <= 0 ) lvl = 1;

                neili_cost =  gin_cost * 60 / lvl;
                if( query("breakup", me) )
                        neili_cost = neili_cost * 7 / 10;

                if( neili_cost < 20 ) neili_cost = 20;

                if( (int)query("neili",me) >= neili_cost * t2 ) {
                        t4 = times;
                        addn("neili", -neili_cost * t2, me);
                }
                else {
                        t3 = (int)query("neili",me) / neili_cost;
                        t4 = t1 + t3;
                        if( t4 == 0 ) {
                                write("然而你今天太累了，無法再進行任何學習了。\n");
                                return 1;
                        }

                        set("neili", 0, me);
                }
        } else
                t4 = times;

        if( times > t1 )
                me->receive_damage("jing", gin_cost * t1);
        else
                me->receive_damage("jing", gin_cost * times);

        if( query("env/auto_regenerate", me) )
                SKILL_D("force/regenerate")->exert(me, me);

        my_combat_exp = (int)query("combat_exp",me);
        if(my_combat_exp < 10000)
                grade = 1;
        else if(my_combat_exp < 80000)
                grade = 3;
        else if(my_combat_exp < 500000)
                grade = 7;
        else
                grade = 13;
        if ( grade < 1 )
                grade = 1;

        rand = 10 + random((int)me->query_int() - 9);
        if( my_skill >= 20000 ) rand /= 4;
        else if( my_skill >= 15000 ) rand /= 3;
        else if( my_skill >= 10000 ) rand /= 2;
        else if( my_skill >= 5000 ) rand = rand * 2 / 3;

        if( intp(r = query_temp("apply/learn_effect",me)) )
                rand += rand * r / 100;

        if( query("time_reward/study",me) )
                rand += rand * 50 / 100;

        if( query("special_skill/wisdom",me) )
                rand += rand * 50 / 100;

        printf("你聽了%s的指導，似乎有些心得。\n", ob->name());
        addn("learned_points", t4, me);
        // me->improve_skill(skill, t4*grade * (10 + random((int)me->query_int() - 9)));
        me->improve_skill(skill, t4*grade*rand);

        if( t4 > 0 && t4 < times )
                write("但是你今天太累了，學習了" + chinese_number(t4) +
                      "次以後只好先停下來。\n");

        addn("dushu", -t4, me);
        return 1;
}

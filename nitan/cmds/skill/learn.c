// Written by Lonely@ChinaMUD.cn
// learn.c

#include <ansi.h>
#include <skill.h>

inherit F_CLEAN_UP;

int can_learn(object me, string skill);

string *reject_msg = ({
        "説道：您太客氣了，這怎麼敢當？\n",
        "像是受寵若驚一樣，説道：請教？這怎麼敢當？\n",
        "笑着説道：您見笑了，我這點雕蟲小技怎夠資格指點您什麼？\n",
});

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        object where = environment(me);
        string *args;
        string *fams;
        string skill, teacher, master, skill_name;
        object ob;
        mixed flag;
        int master_skill, my_skill, jing_cost, times, i;
        int lvl, neili_cost, t1, t2, t3, t4, exp;
        int rand;
        int diff;
        int c;
        int r;
        int n;
        int t = time();

        if( query("pigging", where) )
                return notify_fail("你還是專心拱豬吧！\n");

        if( me->is_busy() )
                return notify_fail(BUSY_MESSAGE);

        if( t == query_temp("time/learn", me) )
                return notify_fail("你剛剛才學習過（如果你要連續學習，可以指明學習的次數）。\n");

        if( !arg || (i = sizeof(args = explode(arg, " "))) < 2 )
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

        c=200+query_temp("apply/learn_times", me);
        if( query("special_skill/clever", me) ) 
                c += 50;

        if( present("learn emblem", me) )
                c += 300;

        if( present("learn emblem2", me) )
                c += 500;

        if( query("special_skill/wisdom", me) )
                c += 800;

        if( n = ACTION_D->query_action("xuexi_times") )
                c *= n;

        if( times < 1 || times > c )
                return notify_fail("學習次數最少一次，最多也不能超過" + chinese_number(c) +"次。\n");

        if( me->is_fighting() )
                return notify_fail("臨陣磨槍？來不及啦。\n");

        if( !(ob = present(teacher, environment(me))) || !ob->is_character() )
                return notify_fail("你要向誰求教？\n");

        if( !living(ob) )
                return notify_fail("嗯……你得先把" + ob->name() +
                                   "弄醒再説。\n");

        if( !me->is_apprentice_of(ob) &&
            (!(fams=query("reborn/fams", me)) || member_array(ob->query_family(), fams) == -1) ||
            playerp(ob) || ob->is_first() || ob->is_baby() ) {
                switch( ob->recognize_apprentice(me, skill) ) {
                case 0:
                        return notify_fail(CYN + ob ->name() + CYN +
                                           reject_msg[random(sizeof(reject_msg))]
                                           + NOR);
                case -1:
                        return 1;
                }
        }

        if( !master_skill = ob->query_skill(skill, 1) )
                return notify_fail("這項技能你恐怕必須找別人學了。\n");

        if( ob->is_fighting() )
                return notify_fail(ob->name() + "忙着料理別人，沒空理你耶。\n");

        flag = query("no_teach/"+skill, ob);
        if( functionp(flag) ) 
                flag = evaluate(flag, ob);  
        if( stringp(flag) ) {
                message_vision(CYN "$N" CYN "搖搖頭，説道：" + flag + "\n" NOR, ob);
                return 1;
        } else if( intp(flag) && flag ) {
                if( flag != -1 )
                        // show the messaeg if the result was not -1
                        write(CYN + ob->name() + CYN "説道：對不起，" +
                              to_chinese(skill) + "可不能隨便傳授。\n" NOR);
                return 1;
        }

        if( /*me->is_apprentice_of(ob) &&*/
            SKILL_D(skill)->type() == "martial" &&
            me->query_skill(skill, 1) >= SKILL_D(skill)->valid_learn_level() ) {
                write(ob->name() + "説：嗯.... 你的" + to_chinese(skill) +
                      "功力已經是非同凡響了，我就不再教你，你自己多研究吧。\n");
                return 1;
        }

        my_skill = me->query_skillo(skill, 1);
        if( my_skill >= master_skill )
                return notify_fail("這項技能你的程度已經不輸你師父了。\n");

        if( my_skill >= (master_skill-query("betrayer/times", me)*20) )
                return notify_fail(CYN + ob->name() + CYN "皺了皺眉頭，不禁想"
                                   "起你過去的叛師經歷。\n" NOR);

        if( !can_learn(me, skill) )
                return 0;

        notify_fail("依你目前的能力，沒有辦法學習這種技能。\n");
        if( !SKILL_D(skill)->valid_learn(me) ) return 0;

        jing_cost = 150 / (int)me->query_int() + 1;
        if( !my_skill ) {
                jing_cost *= 2;
                me->set_skill(skill, 0);
        }

        if( (query("potential", me)-query("learned_points", me))<times )
                return notify_fail("你的潛能不夠學習這麼多次了。\n");

        if( SKILL_D(skill)->is_fmsk() && query("family/gongji", me) < times )
                return notify_fail("你的門派貢獻點數不夠學習這麼多次了。\n");

        write(sprintf(HIC "你開始向%s請教" + chinese_number(times) +
                      "句有關「%s」的疑問。\n" NOR,
                      ob->name(),
                      to_chinese(skill)));

        if( query("env/no_teach", ob)){
                write("但是" + ob->name() + "現在並不準備回答你的問題。\n");
                return 1;
        }

        tell_object(ob, sprintf("%s向你請教有關「%s」的問題。\n",
                    me->name(), to_chinese(skill)));

        if( !me->can_improve_skill(skill) ) {
                write("也許是缺乏實戰經驗，你對" +
                      ob->name() + "的回答總是無法領會。\n");
                return 1;
        }

        set_temp("time/learn", t, me);

        t1=query("jing", me)/jing_cost;
        t2 = times - t1;
        if( t2 > 0 ) {
                lvl = me->query_skill("force");
                if( lvl <= 0 ) lvl = 1;

                neili_cost =  jing_cost * 60 / lvl;
                if( query("breakup", me) )
                        neili_cost = neili_cost * 7 / 10;

                if( neili_cost < 20 ) neili_cost = 20;

                if( query("neili", me) >= neili_cost*t2){
                        t4 = times;
                        addn("neili", -neili_cost*t2, me);
                }
                else {
                        t3=query("neili", me)/neili_cost;
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
                me->receive_damage("jing", jing_cost * t1);
        else
                me->receive_damage("jing", jing_cost * times);

        if( query("env/auto_regenerate", me) )
                SKILL_D("force/regenerate")->exert(me, me);

        addn("learned_points", t4, me);
        if( SKILL_D(skill)->is_fmsk() )
                addn("family/gongji", -t4, me);
        rand = me->query_int() + my_skill / 5;
        rand *= 5;

        if( intp(r=query_temp("apply/learn_effect", me)) )
                rand += rand * r / 100;

        if( query("time_reward/study", me) )
                rand += rand * 50 / 100;

        if( query("special_skill/wisdom", me) )
                rand += rand * 50 / 100;

        diff = SKILLS_D->query_skill_difficult(skill);
        if( !diff ) diff = SKILL_D(skill)->difficult_level();
        rand /= (diff / 100 + 1);

        // me->improve_skill(skill, 4 + random(rand));
        me->improve_skill(skill, t4 * (4 + rand));

        if( skill_name = SKILL_D(skill)->query_skill_name(my_skill) )
                write(sprintf("你聽了%s的指導，對「%s」"
                              "這一招似乎有些心得。\n",
                              ob->name(), skill_name));
        else
                write(sprintf("你聽了%s的指導，似乎有些"
                              "心得。\n", ob->name()));

        if( t4 > 0 && t4 < times )
                write("但是你今天太累了，學習了" + chinese_number(t4) +
                      "次以後只好先停下來。\n");

        return 1;
}

int can_learn(object me, string skill)
{
        string skill_name;
        mapping skills;
        string mskill;
        int tmp;
        int i;

        if( stringp(mskill = SKILL_D(skill)->main_skill()) &&
            mskill != skill &&
            me->query_skill(mskill, 1) > 0 )
                return notify_fail("你現在沒有必要再單獨學習" + to_chinese(skill) + "了。\n");

        skills = me->query_skills();
        if( !mapp(skills) )
                return 1;

        if( !SKILL_D(skill)->valid_enable("force") ||
             SKILL_D(skill)->valid_force("*") )
                return 1;

        foreach (skill_name in keys(skills) ) {
                if( file_size(SKILL_D(skill_name) + ".c") == -1 ) {
                        // No such skill
                        continue;
                }

                if( !SKILL_D(skill_name)->valid_enable("force") ||
                     skill_name == skill )
                        continue;

                if( !SKILL_D(skill_name)->valid_force(skill) )
                        return notify_fail(HIR "你發現自身所學的" HIY +
                                           to_chinese(skill_name) + HIR
                                           "和" HIY + to_chinese(skill) +
                                           HIR "衝突不已，根本沒辦法並"
                                           "存。\n" NOR);
        }

        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : learn|xue <某人> [about] <技能> <次數>

這個指令可以讓你向別人請教有關某一種技能的疑難問題，當然，你請教的對象在這
項技能上的造詣必須比你高，而你經由這種方式學習得來的技能也不可能高於你所請
教的人，然而因為這種學習方式相當於一種「經驗的傳承」，因此學習可以説是熟悉
一種新技能最快的方法。

此外學習也需要消耗一些精力，而消耗的精力跟你自己、與你學習對象的悟性有關。

其他相關指令 : apprentice, practice, skills, study
HELP
        );
        return 1;
}

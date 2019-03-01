// Written by Lonely@ChinaMUD.cn
// study.c

#include <skill.h>
#include <command.h>

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        object where = environment(me);
        object ob;
        string zhao_name, book_name;
        mixed sname;
        string *args;
        string *fams;
        mapping skill, needs;
        string *need_sk;
        mixed need_lvl;
        int my_skill, cost, times, i;
        int lvl, neili_cost, t1, t2, t3, t4;
        int c, r;
        int t = time();

        if( !arg )
                return notify_fail("你要讀什麼？\n");

        if( query("pigging", where) )
                return notify_fail("你還是專心拱豬吧！\n");

        if( me->is_busy() )
                return notify_fail(BUSY_MESSAGE); 
        
        if( t == query_temp("time/study", me) )
                return notify_fail("你剛剛才讀過書（如果你要連續讀書，可以指明讀書的次數）。\n");
        
        if( me->is_fighting() )
                return notify_fail("你無法在戰鬥中專心下來研讀新知！\n");

        if( !arg || (i = sizeof(args = explode(arg, " "))) < 1)
                return notify_fail("指令格式：study|du <書籍> <次數>\n");

        i--;
        if( i >= 1 && sscanf(args[i], "%d", times) && times)
                i--;
        else
                times = 1;
        if( args[i] == "with" && i >= 1 )
                i--;
        book_name = implode(args[0..i], " ");

        c=200+query_temp("apply/study_times", me);
        if( present("study emblem", me) ) 
                c += 300;

        if( query("special_skill/wisdom", me) )
                c += 800;
                
        if( times < 1 || times > c)
                return notify_fail("讀書次數最少一次，最多也"
                                   "不能超過" + chinese_number(c) + "次。\n");

        if( !objectp(ob = present(book_name, me)) )
                return notify_fail("沒這本書可讀啊？\n");

        if( !mapp(skill=query("skill", ob)) )
                return notify_fail("你無法從這樣東西學到任何東西。\n");

        if( !me->query_skill("literate", 1) )
                return notify_fail("你是個文盲，先學點文化(literate)吧。\n");

        if( query("no_fight", environment(me)) && 
            //(query("doing", me) != "scheme" || this_player(1)) )
            (query("doing", me) != "scheme") )
                return notify_fail("你無法在這個地方安心讀書。\n");

        message("vision", me->name() + "正專心地研讀" + ob->name() +
                "。\n", environment(me), me);

        if( query("combat_exp", me)<skill["exp_required"]){
                write("你的實戰經驗不足，再怎麼讀也沒用。\n");
                return 1;
        }

        if( !undefinedp(skill["family_name"]) ) {
                fams = query("reborn/fams", me);
                if( !me->query_family() || (me->query_family() != skill["family_name"] && 
                    (!arrayp(fams) || member_array(skill["family_name"], fams) == -1)) )
                {
                        write("你對" + skill["family_name"] + "的練功心法不了解，再怎麼讀也沒用。\n");
                        return 1;
                }
        }

        if( skill["difficulty"] - (int)me->query_int() > 0 )
                return notify_fail("以你目前的能力，還沒有辦法學這個技能，你還是多學點文化吧。\n");
             
        cost = skill["jing_cost"] + skill["jing_cost"] 
                * (skill["difficulty"] - (int)me->query_int())/12;
        if( cost < 1 ) cost = 1;

        if( mapp(needs=query("skill/need", ob))){
                foreach( need_sk in keys(needs) ) {
                        // check all skills
                        need_lvl = needs[need_sk];
                        if( functionp(need_lvl) )
                                need_lvl = evaluate(need_lvl);
                        else
                        if( !intp(need_lvl) )
                                need_lvl = 0;

                        if( me->query_skill(need_sk, 1) < need_lvl )
                                // not reach the line
                                return notify_fail("你研讀了一會兒，發現如果不通曉" +
                                                   to_chinese(need_sk) +
                                                   "的話，恐怕難以領會上面的含義。\n");
                        // check next skill
                }
        }

        sname=query("skill/name", ob);
        if( functionp(sname) )
                sname = evaluate(sname, ob);  
        notify_fail("以你目前的能力，還沒有辦法學這個技能。\n");
        if( !SKILL_D(sname)->valid_learn(me) )
                return 0;

        if( !XUE_CMD->can_learn(me, sname) )
                return 0;

        if( me->query_skill(sname, 1) > skill["max_skill"] )
                return notify_fail("你研讀了一會兒，但是發現"
                                   "上面所說的對你而言都太淺"
                                   "了，沒有學到任何東西。\n");

        if( me->query_skill(sname, 1) < skill["min_skill"] )
                return notify_fail("你研讀了一會兒，但是卻發現"
                                   "你對這門技能的理解還太淺"
                                   "，結果毫無收獲。\n");

        if( !me->query_skill(sname, 1) )
                me->set_skill(sname, 0);

        my_skill = me->query_skill(sname, 1);
        if( !me->can_improve_skill(sname) ) {
                return notify_fail("也許是缺乏實戰經驗，你對" +
                                   ob->name() + "上面所說的"
                                   "東西總是無法領會。\n");
        }

        set_temp("time/study", t, me);
        r = (int)me->query_skill("literate", 1) / 2 + 1;
        r+=r*query_temp("apply/study_effect", me)/100;
        if( query("time_reward/study", me) )
                r += r * 50 / 100; 
                
        t1=query("jing", me)/cost;
        t2 = times - t1;
        if( t2 > 0 ) {
                lvl = me->query_skill("force");
                if( lvl <= 0 ) lvl = 1;

                neili_cost =  cost * 60 / lvl;
                if( query("breakup", me) )
                        neili_cost = neili_cost * 7 / 10;

                if( neili_cost < 20 ) neili_cost = 20;

                if( query("neili", me) >= neili_cost*t2){
                        t4 = times;
                        addn("neili", -neili_cost*t2, me);
                } else {
                        t3=query("neili", me)/neili_cost;
                        t4 = t1 + t3;
                        if( t4 == 0 ) {
                               write("你現在太累了，結果一行也沒有看下去。\n");
                                return 1;
                        }

                        set("neili", 0, me);
                }
        } else
                t4 = times;

        if( times > t1 )
                me->receive_damage("jing", cost * t1);
        else
                me->receive_damage("jing", cost * times);

        if( query("env/auto_regenerate", me) )
                SKILL_D("force/regenerate")->exert(me, me);

        me->improve_skill(sname, r * t4);

        if( zhao_name = SKILL_D(sname)->query_skill_name(my_skill) )
                write(sprintf("你研讀了" + chinese_number(t4) +
                      "行有關%s的技巧，對「%s」這一招似乎有些心得。\n",
                      to_chinese(sname), zhao_name));
        else
                write(sprintf("你研讀了"+chinese_number(t4) +
                      "行有關%s的技巧，似乎有點心得。\n",
                      to_chinese(sname)));

        if( t4 < times )
                write("你現在已經過于疲倦，無法繼續研讀新知。\n");

        return 1;
}

int help(object me)
{
        write( @HELP
指令格式: study|du <物品名稱> [次數]
          study|du <物品名稱> with [次數]

這個指令使你可以通過閱讀秘笈或其他物品自學某些技巧, 但前提
是: 你不能是個『文盲』。並且你不能在不能戰鬥的地方讀書。

see also : learn
HELP );
        return 1;
}

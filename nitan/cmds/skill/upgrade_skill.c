// upgrade

#include <ansi.h>

inherit F_CLEAN_UP;

#define PERIOD          864
#define PERIOD_POT      20000
#define PERIOD_MAR      12000

int clossing(object me);
int halt_closing(object me);

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        int exercise_cost;
        object where;
        
        seteuid(getuid());
        where = environment(me);
        
        if (! arg)
               return notify_fail("你要閉關鑽研什麼武功？\n");
        
        if (! me->query_skill(arg) || 
            file_size(SKILL_D(arg) + ".c") < 0)    
               return notify_fail("你要鑽研的武功不存在或你不會該武功。\n");
        
        //if (! SKILL_D(arg)->is_invent_skill())
        if (me->query_skillo(arg, 1) < 4600 )
               return notify_fail("你對" + to_chinese(arg) + "的領悟還不夠，無法提升其COMBAT威力。\n");  
               
        if( query("pigging", where) )
                return notify_fail("你還是專心拱豬吧！\n");

        if( !query("no_fight", where) )
                return notify_fail("在這裡閉關鑽研？不太安全吧？\n");

        if( !query("sleep_room", where) )
                return notify_fail("你得找一個能夠休息的地方閉關鑽研。\n");

        if (me->is_busy())
                return notify_fail("你現在正忙著呢。\n");
                        
        if( query("potential", me)-query("learned_points", me)<1000000 )
                return notify_fail("你的潛能不夠，沒法閉關鑽研。\n");

        if( query("experience", me)<query("learned_experience", me)+600000 )
                return notify_fail("你現在積累的實戰體會還太少。\n"); 
        
        if( query("qi", me)*100/query("max_qi", me)<90 )
                return notify_fail("你現在的氣太少了，無法靜心鑽研。\n");

        if( query("jing", me)*100/query("max_jing", me)<90 )
                return notify_fail("你現在的精太少了，無法靜心鑽研。\n");

        if( query("max_neili", me)<4000 )
                return notify_fail("你覺得內力頗有不足，看來目前還難以"
                                   "進行長時間的閉關鑽研。\n");

        if( query("neili", me)*100/query("max_neili", me)<90 )
                return notify_fail("你現在的內力太少了，無法靜心鑽研。\n");

        message_vision("$N盤膝坐下，開始冥神運功，閉關鑽研" + to_chinese(arg) + "。\n", me);
        set("startroom", base_name(where), me);
        set("doing", "invent", me);
        set("upgrade", arg, me);
        CLOSE_D->user_closed(me, "invent");
        me->start_busy(bind((:call_other, __FILE__, "closing" :), me),
                       bind((:call_other, __FILE__, "halt_closing" :), me));
        CHANNEL_D->do_channel(this_object(), "rumor",
                              sprintf("大宗師%s(%s)開始閉關修煉鑽研%s。",
                              me->name(1),query("id", me),to_chinese(arg)));

        return 1;
}

int continue_uping(object me)
{
        me->start_busy(bind((:call_other, __FILE__, "closing" :), me),
                       bind((:call_other, __FILE__, "halt_closing" :), me));
        CLOSE_D->user_closed(me);
        tell_object(me,HIR"\n你繼續閉關修煉鑽研"+to_chinese(query("upgrade", me))+"...\n"NOR);
        return 1;
}

int closing(object me)
{
        int t;
        int tn;
        mixed pot, mar;
        int r;
        int exp_inc;
        string skill;
        
        skill=query("upgrade", me);
        pot=query("potential", me);
        mar=query("experience", me);

#ifdef DB_SAVE
        if (! interactive(me) && 
            !MEMBER_D->is_valid_member(query("id", me)) && 
            query("online_time", me) <= query("offline_time", me)*3 )
        {
                CLOSE_D->user_opened(me);
                call_out("user_quit", 0, me);
                return 0;
        }
#endif

        if( pot <= query("learned_points", me )
         || mar <= query("learned_experience", me) )
        {
                tell_object(me, "你的潛能或體會耗盡了。\n");
                message_vision("$N睜開雙目，緩緩吐了一口氣，站了起來。\n", me);
                CLOSE_D->user_opened(me);
                CHANNEL_D->do_channel(this_object(), "rumor",
                                      sprintf("聽說%s(%s)修煉鑽研%s功德圓滿。",
                                      me->name(1),query("id", me),to_chinese(skill)));
                if (! interactive(me))
                {
                        me->force_me("chat* haha");
                        call_out("user_quit", 0, me);
                }

                return 0;
        }

        if( me->add("learned_points",PERIOD_POT/2+random(PERIOD_POT))>pot )
                set("learned_points", pot, me);

        if( me->add("learned_experience",PERIOD_MAR/2+random(PERIOD_MAR))>mar )
                set("learned_experience", mar, me);
                
        t=query_temp("last_closing", me);
        tn = time();
        if (tn - t < 0)
        {
                set_temp("last_closing", tn, me);
                return 1;
        }

        if (tn - t < PERIOD)
                return 1;

        set_temp("last_closing", tn, me);
                
        if (random(10) == 0)
                //tell_object(me, "閉關修煉" + to_chinese(skill) + "中...\n");
                tell_object(me, "你閉關鑽研" + to_chinese(skill) + "，似有所思。\n");
        
        /*
        if ((random(100) < 3) && me->can_improve_neili())
        {
                tell_object(me, HIR "你對內功有所領悟，感到內力進步了！\n" NOR);
                addn("improve/neili", 1, me);
                me->improve_neili(10 + random(20));
        }

        if ((random(100) < 3) && me->can_improve_jingli())
        {
                tell_object(me, HIM "你對神通有所領悟，感到精力進步了！\n" NOR);
                addn("improve/jingli", 1, me);
                me->improve_jingli(5 + random(10));
        }
        */

        exp_inc = 50 + random(100);
        exp_inc = exp_inc * (100 + me->query_skill("martial-cognize", 1)) / 500;
        exp_inc=exp_inc*(100+query("int", me))/100;
        addn("combat_exp", exp_inc, me);
        me->improve_skill("martial-cognize", 800 + random(800));

        tell_object(me, HIM "你腦中突然靈光一閃，你對" + to_chinese(skill) + "有了更深的領悟！\n" NOR); 
        me->improve_skill(skill, 5000 + random(1000));
        SKILLS_D->upgrade_skill_power(skill); 
        CHANNEL_D->do_channel(find_object(SKILLS_D), "rumor", 
                              "江湖傳言，武學大宗師" + me->name(1) + "閉關修煉鑽研" + 
                              to_chinese(skill) + "，終于完善其破綻之處，並廣為流傳。"); 

        return 1;
}

int halt_closing(object me)
{
        CLOSE_D->user_opened(me);
        tell_object(me,"你中止了閉關修煉"+to_chinese(query("upgrade", me))+"。\n");
        message_vision(HIY "$N" HIY "大喝一聲，睜開眼來，一股氣流登時"
                       "將眾人迫退四步。\n\n" NOR, me);

        CHANNEL_D->do_channel(this_object(), "rumor", "聽說" + me->name(1) +
                              "修煉"+to_chinese(query("upgrade", me))+"中途突然復出。");
        return 1;
}

protected void user_quit(object me)
{
        if (! objectp(me) || interactive(me))
                return;

        me->force_me("quit");
}

int help(object me)
{
        write(@HELP
指令格式 : upskill

閉關修煉研究武功，只有你武功達到4600級以後才能夠閉關修煉研究提升你的武功
的COMBAT數值，要求必須在一個安全並且可以休息的地方才能修煉，修煉前需要有
一百萬點潛能及六十萬體會，閉關開始以後，玩家離線以後其角色將仍然在線修行，
直到玩家中止修煉(halt)或是潛能或體會耗盡。期間內玩家的經驗、修煉武功、武
學修養、以及修煉武功威力將會提升。

HELP );
        return 1;
}

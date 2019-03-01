// /quest/shan.c
//last modified by sega 4/13/2000,取消錢的功用
// Modified by Zeratul Jan 5 2001


inherit NPC;
#include <ansi.h>;
#include "quest.h"

int time_period(int timep,object me);
void create()
{
        set_name("單正", ({ "shan zheng", "shan", "zheng" }));
        set("nickname", HIB"鐵面判官"NOR);
        set("age", 63);
        set("str", 25);
        set("dex", 16);
        set("per", 22);
        set("long", 
"他生平嫉惡如仇，只要知道江湖上有什麼不公道之事，定然伸手
要管。他滿臉紅光，當得起“童顏鶴發”四字，神情卻甚謙和，
不似江湖上傳說的出手無情。\n");
        set("combat_exp", 300000);
        set("shen_type", 1);
        set("attitude", "peaceful");

        set_skill("unarmed", 80);
        set_skill("force", 80);
        set_skill("dodge", 80);
        set_skill("parry", 80);
        set_temp("apply/attack", 100);
        set_temp("apply/defense", 100);
        set_temp("apply/armor", 100);
        set_temp("apply/damage", 100);

        set("neili", 800); 
        set("max_neili", 800);
        set("jiali", 50);

        setup();
        carry_object("/clone/misc/cloth")->wear();
}

void init()
{
        add_action("give_quest", "quest");
        add_action( "cancel_quest", "cancel" );
}

int cancel_quest()
{
        object me = this_player();
        
        if ( !me->query( "quest/shan" ) || me->query( "quest/shan/finished" ) )
                return notify_fail( "什麼？\n" );
        if ( me->query( "quest/shan/lock" ) )
                return notify_fail( "你已經取消任務了！\n" );
        switch ( random(3) )
        {
                case 0 :
                        lock_quest( me, "shan", "wei" ); 
                        tell_object( me, "單正說道：也好，你就先去服侍韋爵爺吧。\n" );
                        break;
                case 1 :
                        lock_quest( me, "shan", "book" );
                        tell_object( me, "單正說道：既然你不願為老夫效力，就回去幫貴派掌門尋找秘籍吧。\n" );
                        break;
                case 2 :
                        lock_quest( me, "shan", "betrayer" );                
                        tell_object( me, "單正說道：貴派掌門捎來口信，要你速回本門清除叛徒，老夫亦不敢留你了。\n" );
                        break;
        }
        return 1;
}

int give_quest()
{
        mapping quest ;
        object me = this_player();
        int j, combatexp, timep,factor;
        int *levels = ({
                1000,
                1500,
                2000,
                3000,
                5000,
                8000,
                10000,
                13000,
                17000,
                22000,
                30000,
                45000,
                60000,
                80000,
                100000,
                200000,
                350000,
                600000,
                1000000,
                5000000,
                9999999,
                100000000,
                
                
        });
        int *expright = ({
                4,
                6,
                8,
                12,
                16,
                20,
                24,
                30,
                40,
                50,
                60,
                70,
                80,
                100,
                120,
                140,
                160,
                180,
                200,
                250,
                350,
                0,
                
                
        });
        int *potright = ({
                2,
                2,
                3,
                4,
                5,
                6,
                7,
                8,
                9,
                10,
                11,
                12,
                13,
                14,
                15,
                16,
                19,
                23,
                25,
                30,
                38,
                0,
                
                
        });
        combatexp = (int) (me->query("combat_exp"));
        
        //Modified by zeratul 2000-12-24
        if( combatexp<10000 )
        {
                tell_object(me,"單正對你哼了一聲道：“這種小角色還想除暴安良？”\n");
                return 1;
        }
/*        if(combatexp>10000000)
        {
                tell_object(me,"單正躬身道：“這種小事怎敢勞煩您。”\n");
                return 1;
        } */
/*
        if ( islocked( me, "shan" ) )
                return 1;
*/
        if( me->query("quest/shan") && !me->query( "quest/shan/finished" ) )
        {
                if( ((int) me->query("quest/shan/time")) > time() )
//                if( ((int) me->query("last_quest_time")+30) > time() )
                {
//                        tell_object(me,"單正對你冷冷一笑道：讓你辦的事如何了？\n");
                        tell_object(me,"單正瞟了你一眼說道：你要是沒本事，就拿點兒費用出來我讓別的人去申張正義。\n");
                        return 1;
                }
                else
                {
                        tell_object(me,"單正對著你嘆了一口氣：哎，我就再給你一次機會吧。\n");
                        quest_failed( me, "shan" );
/*                        switch ( random(3) )
                        {
                                case 0 :
                                        lock_quest( me, "shan", "wei" ); 
                                        tell_object( me, "單正說道：我這裡人手已夠，你去韋爵爺那裡看看吧。\n" );
                                        break;
                                case 1 :
                                        lock_quest( me, "shan", "book" );
                                        tell_object( me, "單正說道：你還是先找秘籍熟悉一下地形再說吧。\n" );
                                        break;
                                case 2 :
                                        lock_quest( me, "shan", "betrayer" );                
                                        tell_object( me, "單正說道：鏟除叛徒的活兒比老夫這裡更適合你。\n" );
                                        break;
                        }*/

                        me->add("qi",-(int)(me->query("qi")/10));
//                        return 1;
                }
        }

        factor=10;
        for (j=0; j<sizeof(levels); j++)
        {
                if (levels[j] > combatexp) break;
        }
        while (1 == 1)
        {
                quest = __DIR__"qslist"->query_quest();
                quest["quest_type"] = "殺";
                quest["exp_bonus"] = expright[j];
                quest["pot_bonus"] = potright[j];
                quest["score"] =  100 + random(50);
                me->set("quest/shan", quest);
                if (quest["shen"] >= 0) continue;
                if (combatexp < quest["exp"]*3 && combatexp*3 > quest["exp"])
                        break;
                if (combatexp > 1000000 && quest["exp"] > 300000) break;
        }
        timep = random(60) * 10 + 600;

        time_period(timep, me);
        tell_object(me,"先替我把『"+quest["quest"]+"』給我殺了，以張武林正義。\n" NOR);

        me->set("quest/shan/time", (int)time()+timep);
        me->set("quest/shan/factor",factor);
        me->delete( "quest/shan/finished" );
        me->set("quest/shan/last_time",(int)time());
        if ( !me->query("quests",1))
        {
                me->set("quests/require", 1);
                me->set("quests/abandon", 1);
        }
        else me->add("quests/require", 1);
        return 1;
}

int time_period(int timep, object me)
{
        int t, d, h, m, s;
        string time;
        t = timep;
        s = t % 60; t /= 60;
        m = t % 60; t /= 60;
        h = t % 24; t /= 24;
        d = t;

        if(d) time = chinese_number(d) + "天";
        else time = "";

        if(h) time += chinese_number(h) + "小時";
        if(m) time += chinese_number(m) + "分";
        time += chinese_number(s) + "秒";

        tell_object(me,HIW "單正吩咐道：給你在" + time + "內");
        return 1;
}

int accept_object(object who, object ob)
{
        int balance, require, abandon, num;
//        int bonus, exp, pot, score, factor, balance, require, abandon;
        mapping quest;

        if ( !ob->query("money_id") ) return 0;
        if ( !who->query("quest/shan") ||
                who->query("quest/shan/finished") || ob->value() < 10000 )
                tell_object(who,"單正笑道：那我可就不客氣了。\n");
        else
        {
                require = who->query("quests/require");
                abandon = who->query("quests/abandon");
                if(require == 0) require = 1;
                if(abandon == 0) abandon = 1;

//                balance = (int) (abandon/(require-abandon+1));
                balance=(int)(require-abandon+200);

                if (abandon>(int)(balance*3/2)) num=1;
                else num=0;
                if (abandon>(int)(balance+balance)) num=2;

                who->set("quests/num",num);
                if(num==2 && ob->value() < 1000000)
                {
                        tell_object(who, "單正一雙尖針般的眼睛直盯著你：我實在不想給你任務！十項完成不了一項。如果你不想完成這次的任務，拿一百兩違約金來！\n");
                        return 1;
                }
                if(num==1 && ob->value() < 100000)
                {
                        tell_object(who, "單正一雙尖針般的眼睛直盯著你：你的任務資信太差，要新任務，先拿十兩黃金來！\n");
                        return 1;
                }
                if( ob->value() < 10000)
                {
                        tell_object(who, "單正一雙尖針般的眼睛直盯著你：這點錢可不夠我們的開銷！\n");
                        return 1;
                }
                else
                {
                        tell_object(who, "單正笑道：那好，咱們買賣不成仁義在。想討差使再找我吧！\n");
                        who->set( "quest/shan/finished", 1 );
                        who->delete( "quest/shan/last_time" );
                        who->add("quests/abandon", 1);
                        return 1;
                }
        }
/*
        if(!(quest = who->query("quest/shan")))
        {
                tell_object(who,"單正說道：這不是我想要的。\n");
                return 0;
        }

        write( ob->query("name") );
        if( ob->query("name") != quest["quest"])
        {
                tell_object(who, "單正說道：這是什麼東西？我叫你辦的差使你就這樣糊弄？！\n");
                return 0;
        }

        if ((int) who->query("quest/shan/time") < time() )
        {
                tell_object(who, "單正說道：真是廢物！你沒有在指定的時間內回來！\n");
                destruct(ob);
                return 0;
        }
        else
        {
                tell_object(who,"單正讚許地點頭說道：不錯！差使辦得還不錯！\n");
                exp = quest["exp_bonus"]/2 + random(quest["exp_bonus"]/2);
                pot = quest["pot_bonus"]/2 + random(quest["pot_bonus"]/2);
                score = quest["score"]/2 + random(quest["score"]/2);
                factor=who->query("quest/shan_factor");
                destruct(ob);

                if (factor)
                {
                        exp=exp*factor/10;
                        pot=pot*factor/10;
                        score=score*factor/10;
                }
                bonus = (int) who->query("combat_exp");
                bonus += (int) (exp/3);
                who->set("combat_exp", bonus);
                bonus = (int) who->query("potential");
                bonus = bonus - (int) who->query("learned_points");
                bonus = bonus + (int) (pot/2);
//                if( bonus > 300) bonus = 300;
                bonus += (int) who->query("learned_points");
                who->set("potential", bonus );
                bonus = (int) who->query("score");
                bonus += score;
                who->set("score", bonus);
                tell_object(who,HIW"你被獎勵了：" + chinese_number(exp)
                        + "點實戰經驗，"+ chinese_number(pot) + "點潛能，"
                        + chinese_number(score)+"點江湖閱歷。\n"NOR);
                who->set("quest/shan", 0 );
                tell_object(who,HIW"恭喜你完成一個差使！\n"NOR);
                return 0;
        }
*/
        return 1;
}

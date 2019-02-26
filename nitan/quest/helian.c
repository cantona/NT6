//quest/helian.c
// Modified by Zeratul May 2,2001 增加兩個任務之間的時間限制，恢復用錢取消的功能

inherit NPC;
#include <ansi.h>;

int time_period(int timep,object me);
void create()
{
        set_name("赫連鐵樹", ({ "helian tieshu", "helian", "tieshu" }));
        set("title", HIY"西夏國徵東大將軍"HIM"西夏一品堂"HIR"總管"NOR);
        set("gender", "男性");
        set("age", 35);
        set("str", 25);
        set("dex", 26);
        set("per", 16);
        set("long", "他身穿大紅錦袍，三十四五歲年紀，鷹鈎鼻、八字須。\n");

        set("combat_exp", 500000);
        set("shen_type", -1);
        set("attitude", "peaceful");
        set("max_qi",2500);
        set("max_jing",1000);
        set("neili", 2500);
        set("max_neili", 2500);
        set("jiali", 200);

        set_skill("claw", 80);
        set_skill("force", 80);
        set_skill("parry", 80);
        set_skill("dodge", 40);
        set_skill("jiuyin-baiguzhao", 90);
        set_skill("bibo-shengong", 90);
        set_skill("lingxu-bu", 90);

        map_skill("force", "bibo-shengong");
        map_skill("parry", "luoying-shenjian");
        map_skill("dodge", "lingxu-bu");
        map_skill("claw", "jiuyin-baiguzhao");
        prepare_skill("claw", "jiuyin-baiguzhao");
        set("inquiry", ([
                "一品堂": "一品堂就是要和中原武林做對！\n",
        ]) );

        setup();
        carry_object(CLOTH_DIR"jinduan")->wear();
}

int accept_fight(object me)
{
        command("say 你敢來一品堂撒野！不要命了！");
        return 0;
}

void init()
{
        add_action("give_quest", "quest");
}

int give_quest()
{
        mapping quest ;
        object me = this_player();
        int j, combatexp, timep, factor;
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
                100000000
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
                0
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
                25,
                26,
                30,
                33,
                0
        });
        combatexp = (int) (me->query("combat_exp"));
        if( !(int)me->query("yipin/joined"))
        {
                tell_object(me,"赫連鐵樹對你哼了一聲道：“你不是本堂的吧？來這湊什麼熱鬧！”\n");
                return 1;
        }
        //Modified by zeratul 2000-12-25
        if(combatexp<10000)
        {
                tell_object(me,"赫連鐵樹對你哼了一聲道：“這種小角色還想投機一品堂？”\n");
                return 1;
        }
/*        if(combatexp>10000000)
        {
                tell_object(me,"赫連鐵樹躬身道：“這種小事怎敢勞煩您。”\n");
                return 1;
        } */
        if( me->query("quest/helian") && !me->query( "quest/helian/finished" ) )
        {
                if( ((int) me->query("/quest/helian/time")) > time() )
                {
//                        tell_object(me,"赫連鐵樹對你冷冷一笑道：讓你辦的事如何了？\n");
                        tell_object(me,"赫連鐵樹很不屑地瞟了你一眼説道：你要是沒本事，就拿點兒費用出來我讓別的人去。\n");
                        return 1;
                }
                else
                {
                        tell_object( me, "赫連鐵樹對着你歎了一口氣：哎，我就再給你一次機會吧。\n" );
                        me->delete( "quest/helian/finished" );
                        me->add("qi",-(int)(me->query("qi")/10));
                        me->add("quests/abandon", 1);
                }
        }
        else
                if (me->query("/quest/helian/last_time")+60+random(60) > time())
                {
                        tell_object(me,"赫連鐵樹對你笑道：你過於勞累，歇息會兒再上路吧。\n");
                        return 1;
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
                quest["score"] = 150 + random(50);
                me->set("quest/helian", quest);
                if (quest["shen"] < 0) continue;
                if (combatexp < quest["exp"]*3 && combatexp*3 > quest["exp"])
                        break;
                if (combatexp > 1000000 && quest["exp"] > 300000) break;
        }
        timep = random(60) * 10 + 600;

        time_period(timep, me);
        tell_object(me,"先替我把『"+quest["quest"]+"』給我殺了，看那些南蠻又能把一品堂怎麼着？！\n" NOR);

        me->set("/quest/helian/time", (int)time()+timep);
        me->set("/quest/helian/factor",factor);
        me->delete( "quest/helian/finished" );
        me->set("quest/helian/last_time",(int)time());
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
        s = t % 60;        t /= 60;
        m = t % 60;        t /= 60;
        h = t % 24;        t /= 24;
        d = t;

        if(d) time = chinese_number(d) + "天";
        else time = "";

        if(h) time += chinese_number(h) + "小時";
        if(m) time += chinese_number(m) + "分";
        time += chinese_number(s) + "秒";

        tell_object(me,HIW "赫連鐵樹吩咐道：給你在" + time + "內");
        return 1;
}

int accept_object(object who, object ob)
{
        int balance, require, abandon, num;

        if ( !ob->query("money_id") ) return 0;
        if ( !who->query("quest/helian") ||
                who->query("quest/helian/finished") || ob->value() < 10000 )
                tell_object(who,"赫連鐵樹笑道：那我可就不客氣了。\n");
        else
        {
                require = who->query("quests/require");
                abandon = who->query("quests/abandon");
                if(require == 0) require = 1;
                if(abandon == 0) abandon = 1;

                balance=(int)(require-abandon+200);

                if (abandon>(int)(balance*3/2)) num=1;
                else num=0;
                if (abandon>(int)(balance+balance)) num=2;

                who->set("quests/num",num);
                if(num==2 && ob->value() < 1000000)
                {
                        tell_object(who, "赫連鐵樹一雙尖針般的眼睛直盯着你：我實在不想給你任務！十項完成不了一項。如果你不想完成這次的任務，拿一百兩違約金來！\n");
                        return 1;
                }
                if(num==1 && ob->value() < 100000)
                {
                        tell_object(who, "赫連鐵樹一雙尖針般的眼睛直盯着你：你的任務資信太差，要新任務，先拿十兩黃金來！\n");
                        return 1;
                }                
                if( ob->value() < 10000)
                {
                        tell_object(who, "赫連鐵樹一雙尖針般的眼睛直盯着你：這點錢可不夠我們的開銷！\n");
                        return 1;
                }
                else
                {
                        tell_object(who, "赫連鐵樹笑道：那好，咱們買賣不成仁義在。想討差使再找我吧！\n");
                        who->set( "quest/helian/finished", 1 );
                        who->delete( "quest/helian/last_time" );
                        who->add("quests/abandon", 1);
                        return 1;
                }
        }        
        return 1;
}

// 劫鏢ＮＰＣ
// Updated by Lonely

inherit CLASS_D("generate") + "/chinese";
#include <ansi.h>
#define DIAM_DIR         "/clone/tessera/"

int do_nod(string arg);

void create()
{
        mapping my;
        int lvl;

        ::create();
        set("gender", "男性" );
        set("nickname", "劫匪");
        set("age", 30 + random(30));
        set("long", "");
        set("attitude", "friendly");
        set("chat_chance", 30);
        set("scale", 150);
        set_temp("apply/armor", 100);
        set_temp("apply/damage", 50);
        set_temp("born_time", time());

        lvl = lvl = 2 + random(2);
        NPC_D->init_npc_skill(this_object(), lvl);

        // 初始化NPC的能力
        my = query_entire_dbase();
        my["max_qi"] = 1000 + lvl * 300 + random(500);
        my["max_jing"] = my["max_qi"] / 2;
        my["max_neili"] = 1000 + lvl * 500 + random(500);
        my["eff_jing"] = my["max_jing"];
        my["jing"] = my["max_jing"];
        my["eff_qi"] = my["max_qi"];
        my["qi"] = my["max_qi"];
        my["neili"] = my["max_neili"] * 2;
        if (clonep()) keep_heart_beat();
        setup();
}


void init()
{
        object ob, env;
        object killer = this_object();        

        ob = this_player();

        add_action("do_nod", "nod"); 
        add_action("do_nod", "好的"); 
        
        if( !query("want_kill1", this_object()) && !query("want_kill2", this_object()) )
                return;
        if( query("id", ob) == query("want_kill1") || query("id", ob) == query("want_kill2") )
        {
                if (! is_fighting()) 
                {
                        remove_call_out("check_me");
                        call_out("check_me", 0);
                }
        }

        if( query("id", ob) != query("want_kill1") && query("id", ob) != query("want_kill2") )
        {
                add_action("do_kill", "team kill");
                add_action("do_kill", "touxi");   
                add_action("do_kill", "kill");
                add_action("do_kill", "hit");
                add_action("do_kill", "fight");
                add_action("do_kill", "steal");
                add_action("do_kill", "beg");
                add_action("do_kill", "persuade");
                add_action("do_kill", "perform");
        }
}

void kill_ob(object me)
{
        object ob = this_object();

        if( !query_temp("lonely/waiting", ob) )
                return ::kill_ob(me);
        else
        {
                return;
        }
}

string *SM_LIST = ({ "rune01", "rune02", "rune03", "rune04", "rune05", "rune06",
                     "rune07", "rune08", "rune09", "rune10", });

// 如果接受了賄賂
int do_nod(string arg)
{
        object ob = this_object(), obj;
        int amount;
        object me = this_player();

        if( !query_temp("lonely/waiting", me) || !arg || arg != query("id", ob) )
        {
                return 0;
        }

        else {
                me->command("nod");
                if( intp(query_temp("lonely/waiting", me)) )
                {
                        if( query_temp("lonely/diamond", me) )
                        {
                                message_vision(HIW "只見$N" HIW "長笑三聲：“哈哈哈，識時務者為俊傑，" +
                                        RANK_D->query_respect(me) + "果然是明白人，嘿嘿，這區區小寶石" +
                                        "就歸你了，哈哈。”\n\n" NOR,
                                        ob, me);
                                obj = new(DIAM_DIR + SM_LIST[random(sizeof(SM_LIST))]);
          
                                tell_object(me, HIR + ob->name() + "遞給了你" + obj->name() +
                                                HIR "以後，吐出一口鮮血，揚長而去。\n" NOR);
                                obj->move(me, 1);
                                delete_temp("lonely", me);
                                remove_call_out("escape_me");
                                remove_call_out("check_me");
                                destruct(ob);
                                return 1;
                        }       
                        amount=query_temp("lonely/waiting", me);

                        message_vision(HIW "只見$N" HIW "長笑三聲：“哈哈哈，識時務者為俊傑，" +
                                RANK_D->query_respect(me) + "果然是明白人，嘿嘿，這區區" +
                                chinese_number(amount) + "兩白銀就歸你了，哈哈。”\n\n" NOR,
                                ob, me);
                        // 因為是“兩”為單位，所以要 * 100。
                        MONEY_D->pay_player(me, amount * 100);
                        tell_object(me, HIR + ob->name() + "遞給了你" + chinese_number(amount) +
                                        "兩白銀以後，吐出一口鮮血，揚長而去。\n" NOR );
                        delete_temp("lonely", me);
                        remove_call_out("escape_me");
                        remove_call_out("check_me");
                        destruct(ob);
                        return 1;
                }
                else return  0;
        }
}

int check_me()
{
        object ob, me = this_object();
        
        if( query_temp("lonely/waiting", me))return 0;

        if (! present(query("want_kill1"), environment(me))
        &&  ! present(query("want_kill2"), environment(me)))   
        {
                remove_call_out("escape_me");
                destruct(me);
                return 0;
        }

        if (objectp(ob = present(query("want_kill1"), environment(me)))
         && !query("no_fight", environment(me) )
        &&  interactive(ob) && ! ob->is_fighting(me))
                call_out("do_fkill", 0, ob);  
 
        if (objectp(ob = present(query("want_kill2"), environment(me)))
         && !query("no_fight", environment(me) )
        &&  interactive(ob) && ! ob->is_fighting(me))
                call_out("do_fkill", 0, ob); 

        remove_call_out("check_me");
        call_out("check_me", 2);   

        return 1;
}

int do_fkill(object ob)
{
        if( !query_temp("lonely/waiting") && (query("id", ob) == query("want_killer") || query("id", ob) == query("want_kill2")) )
        {
            if (living(this_object()))
                message_sort(HIR "$N大喝道：“此山是我開，此樹是我栽！"+
                               query("name", ob)+"識相的話，留下鏢車立刻滾蛋，或許可以放你一條生路！\n"NOR,
                               this_object());  

                this_object()->kill_ob(ob);
                ob->kill_ob(this_object());        
        }
        return 1;
}

void start_escape(object ob,object me)
{
        call_out("escape_me", 300, ob, me);
}

int do_kill(string arg)
{
        string temp, what, who;
        
        if (! arg) return 0;
        if (this_object()->id(arg))
        {
                write("江湖人士，還是少惹為妙。\n");
                return 1;
        }
        else
        if (sscanf(arg, "%s from %s", what, who) == 2 && this_object()->id(who))
        {
                write("還是到別處去施展你的本事吧。\n");
                return 1;
        }
        else
        if (sscanf(arg, "%s.%s %s", temp, what, who) == 3 && this_object()->id(who))
        {
                write("還是到別處去施展你的本事吧。\n");
                return 1;
        }
        return 0;
}


void escape_me(object ob,object me)
{
        message_vision(
                       "$N獰笑了幾聲：“今天心情好，" + RANK_D->query_self_rude(ob) +
                       "就放過你，不陪你玩了。”説罷，一個筋斗跳出戰圈，不知去向。\n", ob);

        destruct(ob);
}

void unconcious()
{
        object me, ob = this_object();
        int amount = 100 + random(100);
        string *condition = ({
                "氣喘吁吁，就要不支", "頭重腳輕，馬上就倒", 
                "嘔血成升，眼冒金星", "傷痕累累，無力招架", 
        });

        if (objectp(me = query_last_damage_from())
        &&  environment() == environment(me) 
         && !query_temp("lonely/waiting", me) )
        {
                switch (random(15)) 
                {
                        case 1: 
                        {
                                message_vision(HIR "眼見$N" HIR + condition[random(sizeof(condition))]
                                                +"，突然$N大喝一聲，急退幾步，\n“撲通”給$n跪了下來。"
                                                "\n" NOR, ob, me);
                                tell_object(me, HIW + ob->name() + "突然從懷裏掏出一堆白花花的銀子，小聲"
                                                "對你道：“這位" + RANK_D->query_respect(me) + "，\n你"
                                                "就網開一面（nod）如何，這" + chinese_number(amount) +
                                                "兩白銀就歸你了！”\n" NOR);
                                remove_all_enemy(0); 
                                set("qi", 1, ob);
                                set("jing", 1, ob);
                                set_temp("lonely/waiting", amount, ob);
                                set_temp("lonely/waiting", amount, me);
                                return;
                        }
                        case 2:
                        {
                                message_vision(HIR "眼見$N" HIR + condition[random(sizeof(condition))]
                                                +"，突然$N大喝一聲，急退幾步，\n“撲通”給$n跪了下來。"
                                                "\n" NOR, ob, me);
                                tell_object(me, HIW + ob->name() + "突然從懷裏掏出一塊寶石，小聲"
                                                "對你道：“這位" + RANK_D->query_respect(me) + "，\n你"
                                                "就網開一面（nod）如何，這寶石就歸你了！”\n" NOR);
                                remove_all_enemy(0); 
                                set("qi", 1, ob);
                                set("jing", 1, ob);
                                set_temp("lonely/waiting", amount, ob);
                                set_temp("lonely/waiting", amount, me);
                                set_temp("lonely/diamond", 1, me);
                                return;
                        }
                        default: 
                        {
                                // 獎勵
                                ::unconcious();
                                return;
                        }
                }
        }
        if (objectp(me)) 
                delete_temp("lonely", me);
        ::unconcious();
}

varargs void die(object me)
{
        object ob = this_object();
        
        
        message_vision(HIC "$N慘嚎一聲，口噴鮮血，到在地上死了。\n" NOR, ob);
        
        if (! me) me = query_last_damage_from();
        if (objectp(me)
         && (query("id", me) == query("want_kill1", ob )
         || query("id", me) == query("want_kill2", ob)) )
        {
                delete_temp("lonely", me);
                addn_temp("quest_yunbiao/bandit_killed", 1, me);
                if( query_temp("quest_yunbiao/bandit_killed", me)>10 )
                        set_temp("quest_yunbiao/bandit_killed", 10, me);
                addn("experience", random(2), me);
        }        
        remove_call_out("escape_me");
        remove_call_out("check_me");
        ::die();
        return;
}

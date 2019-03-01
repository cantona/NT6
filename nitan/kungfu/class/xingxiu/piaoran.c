// Room: /d/xingxiu/npc/piaoran.c
// Last Modified by Winder on Apr. 25 2001

#include <ansi.h>
inherit NPC;
string ask_job();
void create()
{
        set_name("飄然子", ({ "piaoran zi", "piaoran", "zi" }) );
        set("gender", "男性" );
        set("nickname", "星宿派五弟子");
        set("age", 28);
        set("long", "他生性淫邪，武功高強，經常姦淫良家婦女。
後被正派人士截殺，斷了兩條腿逃回了星宿後，就再沒步出過這個山洞。\n");
        set("env/wimpy", 40);
        set("str", 28);
        set("dex", 10);
        set("con", 25);
        set("int", 22);
        set("shen", -10000);

        set_skill("force", 100);
        set_skill("huagong-dafa", 105);
        set_skill("strike", 100);
        set_skill("chousui-zhang", 105);
        set_skill("poison", 100);
        set_skill("parry", 100);
        set_skill("staff", 100);
        set_skill("tianshan-zhang", 100);
        set_skill("literate", 50);
        map_skill("force", "huagong-dafa");
        map_skill("strike", "chousui-zhang");
        map_skill("parry", "chousui-zhang");
        map_skill("staff", "tianshan-zhang");
        prepare_skill("strike", "chousui-zhang");

        set("max_qi", 1100);
        set("max_jing", 900);
        set("neili", 1500);
        set("eff_jingli", 1100);
        set("max_neili", 1500);
        set("jiali", 50);
        set("combat_exp", 600000);
        set("chat_chance_combat", 5);
        set("chat_msg_combat", ({
                (: exert_function, "powerup" :),
        }));

        create_family("星宿派", 2, "弟子");
        set("inquiry", ([
                "星宿派" : "你想加入，就拜我為師。",
                "星宿海" : "去星宿海幹什麼？拜我為師就夠你學的了。",
                "丁春秋" : "丁春秋是你叫的嗎？沒大沒小的。以後叫老仙！",
                "煉毒"   : (: ask_job :),
                "毒"     : (: ask_job :),
                "poison" : (: ask_job :),
        ]));
        setup();
        carry_object("clone/cloth/dao-cloth")->wear();
        add_money("silver", 10);
}

string ask_job()
{
        object me;
        mapping fam;
        int poison, exp;
        me = this_player();
        fam=query("family", me);
        poison = me->query_skill("poison", 1);
        exp=query("combat_exp", me);

        if(!fam) return "給老子滾一邊去！";
        if( fam["family_name"] != "星宿派" && !query_temp("ding_flatter", me) )
                return "給老子滾一邊去！";
        if(poison < 120) return "哈哈哈，你先學夠了基本的毒技再來吧。";
        if(poison >= 200) return "這個。。。這種腐屍毒對你好象沒什麼用了吧？";
        if(me->query_skill("huagong-dafa", 1) < 100 )
                return "你的化功大法還不純熟，煉毒會很危險的！";
        if(me->query_condition("wait_xx_task"))
                return "你好象把師兄的事情搞砸了吧？這次你就好好等著。";
        if(me->query_condition("xx_task") || me->query_condition("xx_task2"))
                return "你還在為其他師兄弟們做事呢，等完成了再來我這裡吧。";
        if( interactive(me) && query_temp("xx_job", me) )
                return "你怎麼還在這裡發呆？";

        set_temp("promotion_target", 1, me);
        message_vision("\n$N對著$n嘿嘿一笑：“想練毒是吧？先去給你自己找具有用的屍體來。”\n", this_object(), me);
        return "記住，可不是殺個小嘍羅那樣丟人顯眼！\n";
}

/*
void init()
{
        object ob;

        ::init();
        if (interactive(ob = this_player()) && !is_fighting())
        {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}

void greeting(object me)
{
        mapping fam;
        fam=query("family", me);

        if (fam["family_name"] != "星宿派")
        {
                command("say 哪裡跑來的"+RANK_D->query_rude(me)+"！竟敢擅闖星宿禁地！");
                kill_ob(me);
        }
}
*/
void kicking(object who)
{
        if(!who || environment(who) != environment())  return;
        who->move("/d/xingxiu/cave");
        message("vision","只聽“呼”地一聲，緊接著"+query("name", who)+"從黑暗中直飛出來，摔了個四腳朝天！\n",environment(who),who);
        who->receive_wound("jing", 200);
        who->receive_wound("qi", 250);
        who->start_busy(5);
}
int accept_object(object who, object ob,object me)
{
        object obj;
        if(!objectp(obj = present("shi guan", environment()))) return 0;
        if( query_temp("liandu", obj) )
        {
                command("say 石棺正在用呢，你等等吧。");
                return 0;
        }
        if( query("id", ob) != "corpse" )
        {
                command("say 這是什麼東西？？");
                return 0;
        }
        if(userp(ob))
        {
                command("stare"+query("id", who));
                command("say 竟敢來這裡欺騙我，給我滾出去！");
                message_vision("\n說完$N雙掌前推，一股內勁拂出，就將$n震出洞外！\n\n", this_object(), who);
                kicking(who);
                return 0;
        }
        if( !query_temp("promotion_target", who) )
        {
                command("say 你這樣拿具屍體給我幹什麼？");
                return 0;
        }
        if( query("kill_by", ob) != who )
        {
                command("say 嘿嘿，練腐屍毒的屍體是需要自己親自殺的，你另找一具吧。");
                return 0;
        }
        if( (query("victim_user", ob) && 
                query("victim_exp", ob)<query("combat_exp", who)/3) || 
                (!query("victim_user", ob) && 
                query("victim_exp", ob)<query("combat_exp", who)) )
        {
                command("say 嘿嘿，我早就說過太弱的屍體沒用，你另找一具吧。");
                return 0;
        }
        if (interactive(who) && (who->query_condition("xx_task") ||
                who->query_condition("xx_task2")))
        {
                command("pat"+query("id", who));
                command("say 你還在為其他師兄弟們做事呢，等完成了再來我這裡吧。");
                return 0;
        }
        call_out("put_in", 4, ob, this_object(), who, obj);
        return 1;
}

int put_in(object corpse, object ob, object me, object obj)
{
        object *inv;
        int i;
        if(!objectp(present(obj, environment(ob))))
        {
                command("say 咦？石棺怎麼不見了？");
                command("drop corpse");
                return 1;
        }
        if(!objectp(present(me, environment(ob))))
        {
                command("say 耶？那家伙怎麼不見了？");
                command("drop corpse");
                return 1;
        }

        inv = all_inventory(corpse);
        i = sizeof(inv);
        while(i--) destruct(inv[i]);
        corpse->move(obj);
        if( query("victim_user", corpse))set_temp("liandu", 2, obj);
        else set_temp("liandu", 1, obj);
        set_temp("liandu_target",query("id",  me), obj);
        set("arg",query_temp("dest",  ob), obj);
        command("nod"+query("id", me));
        command("say 好吧，你來試著練習(liandu)一下毒技吧。");
}

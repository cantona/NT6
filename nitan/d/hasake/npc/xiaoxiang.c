#include <ansi.h>

inherit NPC;

void create()
{
        set_name("瀟湘子", ({ "xiaoxiang zi", "zi", "xiaoxiang" }));
        set("title", "湘西名宿");
        set("long", "他身材高瘦，臉無血色，形若殭屍。臉上隱隱透著一股青氣，手持一根哭喪棒。\n");
        set("gender", "男性");
        set("rank_info/respect", "道長");
        create_family("丐幫", 15, "弟子");
        set("age", 43);
        set("attitude","heroism");
        set("str", 26);
        set("dex", 20);
        set("con", 23);
        set("int", 22);
        set("shen", -7000);
        set("env/wimpy", 60);
        set_skill("parry", 100);
        set_skill("force", 100);
        set_skill("dodge", 100);
        set_skill("staff", 100);
        set_skill("huntian-qigong", 120);       
        set_skill("tianshan-zhang", 120);  
        set_skill("xiaoyaoyou", 120);
        set_skill("suohou-hand", 120);
        set_skill("hand", 100);
        map_skill("force", "huntian-qigong");
        map_skill("dodge", "xiaoyaoyou");
        map_skill("hand", "suohou-hand");
        map_skill("staff", "tianshan-zhang");
        prepare_skill("hand", "suohou-hand");
        set("combat_exp", 700000);
        set("max_qi", 1500);
        set("max_jing", 1000);
        set("eff_jingli", 1000);
        set("neili", 2000);
        set("max_neili", 2000);
        set("jiali", 50);
        set("inquiry", ([            
            "金輪法王" : "嘿嘿，我遲早會把那個老和尚的國師名號搶過來。",
            "馬光佐" : "那是個莽夫，提他做什？",
            "尹克西" : "這人功夫不錯，就是滿身的金銀太耀眼，不象個武林人士。",
            "尼摩星" : "西域來的，內功不錯。就是，嘿嘿，心眼太小。",            
       ]) );
        setup();
        set("chat_chance", 45);
        set("chat_msg", ({
            "瀟湘子眼睛向你斜望，嘴角邊微微冷笑。\n",
            (: random_move :),  
            "瀟湘子道：「西藏武功傳自天竺，難道世上當真有青出於藍之事麼？兄弟可有點不大相信了 。」\n", 
            (: random_move :),          
        }) );
        carry_object(WEAPON_DIR"gangzhang")->wield();
        carry_object("/d/wudang/obj/greenrobe")->wear();
}

void kill_ob(object me)
{     object ob=this_object();
      command("grin");
      command("say 杖下領死吧！");
      COMBAT_D->do_attack(ob,me,query_temp("weapon", ob));
      COMBAT_D->do_attack(ob,me,query_temp("weapon", ob));
      COMBAT_D->do_attack(ob,me,query_temp("weapon", ob));
      ::kill_ob(me);
}

#include <ansi.h>

inherit NPC;
inherit F_MASTER;
int do_skills(string arg);

void create()
{
        set_name("獨臂神尼", ({ "dubi shenni", "dubi" }));
        set("gender", "女性");
        set("age", 44);
        set("str", 25);
        set("dex", 20);
        set("long", "這是一位白衣女尼，手握拂塵，目視前方。\n"+
                "一只長袖空空如也，顯是斷了一臂，盡管如此，\n"+
                "仍然掩不住她迷人的風採。\n");
        set("combat_exp", 200000);
        set("shen_type", 1);
        set("attitude", "peaceful");

        set_skill("whip", 180);
        set_skill("force", 180);
        set_skill("unarmed", 180);
        set_skill("dodge", 180);
        set_skill("parry", 180);
        set_skill("qiufeng-chenfa", 180);
        set_skill("shenxing-baibian", 180);
        map_skill("whip", "qiufeng-chenfa");
        map_skill("parry", "qiufeng-chenfa");
        map_skill("dodge", "shenxing-baibian");

        set_temp("apply/attack", 100);
        set_temp("apply/defense", 100);
        set_temp("apply/armor", 40);
        set_temp("apply/damage", 100);
        set("neili", 1800); 
        set("max_neili", 1800);
        set("jiali", 100);
        set("inquiry", ([
                "阿珂" : "神尼嘆了一口氣，說道：她是我的得意弟子，\n"
                         "人長得挺美，唉，只可惜被韋小寶騙去了。\n",
        ]) );
        setup();
        carry_object("/d/beijing/npc/obj/fuchen")->wield();
        carry_object("/d/beijing/npc/obj/cloth4")->wear();
        add_money("silver", 2);
}

void init()
{
        ::init();
        if( query("id", this_player()) == "lama" )
        {
                delete_temp("saved_by_others");
        } else
        if (interactive(this_player()))
        {
                remove_call_out("greeting");
                call_out("greeting", 1, this_player());
        }
}

int recognize_apprentice(object ob)
{
        if( !query("can_learn/dubi/shenxing-baibian", ob) )
        {
                message_vision("$N搖了搖頭。\n",this_object());
                command("say 你我素不相識，為什麼我一定要教你呢？"); 
                return -1;
        }
        return 1;       
}

void greeting(object ob)
{
        object man;
        
        if (! ob || environment(ob) != environment()) return;
            
        man = this_object();
        if (! present("la ma"))
        {
                message_vision(HIC "$N踏進屋來，只見地上屍體橫陳，一個女"
                               "尼喘息不止。\n" NOR, ob);               
                if (! query_temp("saved_by_others"))
                {
                        set_temp("saved_by_others", 1);
                        set("can_learn/dubi/shenxing-baibian", 1, ob);
                        message_vision("\n白衣女尼對$N說道：“多謝這位" +
                                       RANK_D->query_respect(ob)+
                                       "拔刀相助，貧尼感激不盡，無以為報。\n"
                                       "這裡有一套神行百變身法，你若願學，貧"
                                       "尼定傾囊以授。”\n", ob);
                        if( query("weiwang", ob)<60 )
                        {
                                addn("weiwang", 10, ob);
                                message_vision(HIC "$N的江湖威望提高了！\n" NOR,ob);
                                return ;
                        }
                        return;
                }
                message_vision(HIC "白衣女尼對$N微微一笑。\n" NOR,ob);
        }
}

// /d/xueshan/npc/fsgelun.c
// Summer 9/26/1996.
// Rama modified for hx

#include <ansi.h>
inherit NPC;

string ask_fashi();
void create()
{
        set_name("祭祀喇嘛", ({ "jisi lama", "jisi", "lama" }));
        set_weight(3000000);
        set("long",
"他是密宗的戒律僧，長得膀大腰，手中提着法器，身着黃袍，頭戴黃帽，\n"
"滿面肅殺之氣。\n");
        set("gender", "男性");
        set("age", 20);
        set("attitude", "heroism");
        set("class","bonze");
        set("shen_type", -1);
        set("str", 50);

        set("max_qi", 500);
        set("max_jing", 450);
        set("neili", 500);
        set("max_neili", 500);
        set("jiali", 40);
        set("combat_exp", 50000);
        set("score", 5000);

        set_skill("force", 50);
        set_skill("dodge", 55);
        set_skill("parry", 60);
        set_skill("staff", 60);
        set_skill("cuff", 60);
        set_skill("hammer", 60);


        set("inquiry", ([
                "準備法事" : (: ask_fashi :),
                "preparation" : (: ask_fashi :),
        ]) );

        setup();
        switch( random(3) )
        {
                case 0:
                         carry_object("/clone/weapon/falun")->wield();
                         break;
                case 1:
                         carry_object("/d/xueshan/obj/fachu")->wield();
                         break;
                case 2:
                         carry_object("/d/xueshan/obj/faling")->wield();
        }
        carry_object("/d/xueshan/obj/lamajiasha")->wear();
}

void init()
{
        object ob;

        ::init();
        if( interactive(ob = this_player()) && !is_fighting() ) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}


void greeting(object ob)
{
        int bonus;
        mixed exp1, exp2;

        exp1=query("combat_exp", ob);
        exp2=query_temp("作法事", ob);
        if( !query_temp("作法事", ob))return ;
        {
message_vision("祭祀喇嘛急急忙忙吩咐小喇嘛們往祭壇裏填柴，倒酥油。\n\n", ob);
message_vision(HIR"$N點燃了祭壇中的木柴與酥油，熊熊烈火沖天而起。\n", ob);
message_vision(HIB"一絲魂魄升出祭壇，冉冉而起。魂魄受$N佛法感召，徘徊不去。\n", ob);
message_vision(RED"$N端起顱缽吸進一口水，「噗」的一聲猛地朝那熊熊火焰噴將過去。\n", ob);

message_vision(HIC"$N盤腿打坐，神光內藴，口中念念有辭，漸漸有一絲魂魄在$N面前凝聚成形。\n", ob);
message_vision(HIG"魂魄越聚越多，竟然呈出人形！$N手指人形，口唸真言，指引往生之路。\n", ob);
message_vision(HIW"$N手持法鈴，邊走變搖，高聲誦讀密傳經咒。突然大喝一聲。聲似雷霆。\n", ob);
message_vision(HIY"大院裏光芒四起，一聲巨響過後，又恢復了平靜。超度完畢。\n"NOR, ob);
                if (exp2 > exp1)
                {
                        bonus= ob->query_skill("lamaism",1) / 2;
                        if( ob->set_temp("玩家法事") )

{
                               addn("combat_exp", random(200)+100, ob);
                               addn("family/gongji", random(8)+4, ob);
                                if( query("potential", ob)>ob->query_potential_limit() )
                                        addn("potential", 1, ob);
                                else
                                        addn("potential", random(30)+50, ob);
                                ob->start_busy(6);
}
                                else
{
                       if (exp2- exp1 > exp1)
             {
                            addn("combat_exp", random(200)+500, ob);
                               addn("max_neili", random(5)+1, ob);
                             addn("family/gongji", random(8)+4, ob);
                                if( query("potential", ob)>ob->query_potential_limit() )
                                        addn("potential", 1, ob);
                                else
                                        addn("potential", random(100)+50, ob);
                               ob->start_busy(6);
                             }
                          else
{
                                addn("combat_exp", random(300)+200, ob);
                               addn("family/gongji", random(8)+4, ob);
                  if( query("potential", ob)>ob->query_potential_limit() )
                                        addn("potential", 1, ob);
                                else
                             addn("potential", random(100)+50, ob);
                                ob->start_busy(6);
}
                }
                 }
                else
message_vision(HIR"\n$N不知道哪裏找了個菜鳥煞有介事地來超度，看來是白忙了。\n"NOR, ob);
                                addn("jing", -20, ob);
                                ob->start_busy(6);
                                delete_temp("作法事", ob);
                command("say 法事已經做完,廟裏有事我先走了");
                ob->apply_condition("gelunbu",1+random(5));
if (present("corpse",this_object()))
destruct(present("corpse",this_object()));
if (present("skeleton",this_object()))
destruct(present("skeleton",this_object()));
                command("go north");
                command("go east");
                command("go east");
                command("go south");
                                        }
}



string ask_fashi()
{
        mapping fam;
        object ob = this_player();

        if( query("short", environment(this_object())) != "前院" )
                return "這裏正在做法事，你沒看見麼？";
        if( !(fam=query("family", ob)) || fam["family_name"] != "雪山寺" )
                return "你是那裏跳出來的毛蟲，也能做個屁法事？";

        if ( ob->query_skill("lamaism",1) < 60)
                return "你的密宗心法還早得很呢，沒法讓你開壇做法事。";
       if( query("max_neili", ob)<300 )
              return "你的內力還不夠呀，沒法讓你開壇做法事。";
       if( query("jingli", ob)<200 )
              return "你的精力還不夠呀，沒法讓你開壇做法事。";
         if(ob->query_condition("gelunbu")>0)
         return "你剛剛做過法事,還跑這裏瞎嚷嚷什麼?";

        set_temp("法事", 1, ob);
        return "這位上人是要給哪位施主做法事呀？";
}

int accept_object(object who, object ob)
{
        object myenv ;
        if( !query_temp("法事", who) )

        {
message_vision("祭祀喇嘛笑着對$N説：這種臭東西給我有什麼用，您還是自己留着吧！\n", who);
                return 0 ;
        }
        if( query("killed_by", ob) != query("id", who) )
{
               message_vision("祭祀喇嘛嚴厲的對$N説：不是自己殺的還來超度?\n", who);
           return 0;
}

        if( query("name", ob) == "無頭屍體" )
{
               message_vision("祭祀喇嘛嚴厲的對$N説：腦袋沒有了還怎麼超度！\n", who);
           return 0;
}
        delete_temp("法事", who);

        if( query("id", ob) == "corpse" )
        {
                message_vision("祭祀喇嘛笑着對$N説：那我們去祭壇吧！\n", who);
                set_temp("作法事",query("combat_exp",  ob), who);
                if( query("userp", ob) )

                        set_temp("玩家法事", 1, who);
//      who->set_leader(this_object());
//                destruct(ob);
                command("go north");
                command("go west");
                command("go west");
                command("go south");
                return 1;
        }
        else
                 message_vision("祭祀喇嘛對$N説：這種東西還能做法事？直接埋了省事。\n", who);
        return 0;
}

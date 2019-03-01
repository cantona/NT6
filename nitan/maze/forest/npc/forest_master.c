inherit NPC;
#include <ansi.h>

void give_reward_forest(object ob, int ref_exp);

mapping itemlist = ([      
        "/maze/forest/npc/obj/bear_dan":1,
        "/maze/forest/npc/obj/bear_hand":5,
        "/maze/forest/npc/obj/bear_skin":10,
        "/maze/forest/npc/obj/snake_egg":1,
        "/maze/forest/npc/obj/snake_dan":5,
        "/maze/forest/npc/obj/snake_skin":10,
        "/maze/forest/npc/obj/tiger_xxx":1,
        "/maze/forest/npc/obj/tiger_bone":5,
        "/maze/forest/npc/obj/tiger_skin":10,
        "/maze/forest/npc/obj/wolf_eye":1,
        "/maze/forest/npc/obj/wolf_meat":5,
        "/maze/forest/npc/obj/wolf_skin":10,
        "/maze/forest/npc/obj/dragon_skin":3,
        "/maze/forest/npc/rabbit":1,
        "/maze/forest/npc/toad":1,
]);

void create()
{
        set_name(HIG "叢林狩獵者" NOR, ({ "forest hunter","hunter" }) );

        set("gender", "男性");
        set("age", 30);
        set("long",
                GRN"\n    這是一個獵物收購者，給他一定數量的獵物，獲取你的獎勵！
                \n      十張狼皮  五塊狼肉  一對狼眼
                \n      十張熊皮  五只熊掌  一只熊膽    
                \n      十張虎皮  五具虎骨  一根虎鞭
                \n      十張蛇皮  五個蛇膽  一個蛇蛋
                \n      三塊龍鱗  一個龍蛋
                \n      一只流氓兔
                \n"NOR);
        set("attitude", "peaceful");
        set("str", 26000);
        set("com", 30);
        set("int", 24);
        set("dex", 30);
        set("per", 50);



        set("chat_chance", 10);
        set("chat_msg", ({
                BLU"叢林狩獵者說道：收購各種獵物。\n"NOR ,
                YEL"叢林狩獵者說道：唉，我那走丟了的孩子啊......\n"NOR ,

        }) );

        set("combat_exp", 11000000);
        set("attitude", "peaceful");

        set_skill("unarmed", 300);
        set_skill("dodge", 300);

        set("max_qi", 4500);
        set("max_jing", 2000);
        set("neili", 4000);
        set("max_neili", 4000);
        set("jiali", 150);

        setup();

}

int accept_object(object me, object obj)
{
        string filename;
        int need_amount,amount,exp;
        filename = base_name(obj);
        
        if (undefinedp(itemlist[filename]))
        {
                command("shake");
                command("say 這是什麼東西，我不需要！");
                return 0;
        }
        
        need_amount = itemlist[filename];
        if (need_amount<=0 )
                return 0;
        if (function_exists("query_amount",obj) && obj->query_amount()<need_amount )
                return 0;

        exp = 200;

        if (function_exists("query_amount",obj))
                amount = obj->query_amount();
        else 
                amount = 1;

        exp = exp/need_amount*amount;

        command("pat "+query("id", me));
        give_reward_forest(me,exp);
        destruct(obj);
        return 1;
}

void give_reward_forest(object ob, int ref_exp) 
{
        //ref_exp是參考經驗，exp不影響gold，高級玩家可以到forest掙錢
        int user_exp;
        int exp,pot,mar,score,gold;
        string reward_msg;
        int gold_times;
        gold = ref_exp/100;
        user_exp=query("combat_exp", ob);
        if( user_exp < 3000000 )
                exp = ref_exp*5/4;
        else if( user_exp < 5000000 )
                exp = ref_exp;
        else if( user_exp < 8000000 )
                exp = ref_exp/2;
        else
                exp = ref_exp/20;;

        pot = exp/2;
        score = exp/500;
        mar = exp/800;
        gold_times = "/adm/daemons/actiond"->query_action("forest_reward"); 
        if( gold_times )
                gold *= gold_times;
        if (gold < 1) gold = 1;
        /*
        reward_msg =GRN"你得到了報酬：\n\t\t" +
        chinese_number(exp) + "點實戰經驗\n\t\t"+
        chinese_number(pot) + "點潛能\n\t\t" +
        chinese_number(mar) + "點體會\n\t\t" +
        chinese_number(score) + "點評價\n\t\t" + 
        chinese_number(gold) + "兩黃金\n"NOR;
        tell_object(ob,reward_msg);

        addn("combat_exp", exp, ob);
        addn("potential", pot, ob);
        addn("experience", mar, ob);
        addn("score", score, ob);
        addn("balance", gold*10000, ob);
        */
        
        GIFT_D->work_bonus(ob, ([ "exp" : exp, "pot" : pot, "mar" : mar,
                                  "score" : score, "gold" : gold ]));
}

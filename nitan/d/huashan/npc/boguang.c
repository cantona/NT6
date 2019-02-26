// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// boguang.c 田伯光

inherit NPC;

int checking(object me, object ob);
void destob(object me);
int fast_attack(object me, object ob);
int climb_tree(object me);

void create()
{
        set_name("田伯光", ({ "tian boguang", "tian", "boguang" }));
        set("nickname", "萬里獨行");
        set("long", 
                "田伯光昔年為江湖中臭名昭彰的採花賊，但結識華山令狐沖後已\n"
                "改邪歸正。一手快刀絕技，天下無雙。輕功在武林中也是一等的。\n");
        set("gender", "男性");
        set("age", 35);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 25);
        set("int", 30);
        set("con", 25);
        set("dex", 30);
        set("shen", 0);
        
        set("max_qi", 2000);
        set("max_jing", 500);
        set("neili", 1000);
        set("max_neili", 1000);
        set("jiali", 50);
        set("combat_exp", 150000);
        set("level", 10);
        set("score", 5000);

        set_skill("force", 80);
        set_skill("dodge", 100);
        set_skill("parry", 80);
        set_skill("luan-blade", 100);
        set_skill("blade", 100);
        set_skill("unarmed", 80);
        set_skill("literate", 50);
        set_skill("ding-dodge", 100);
        set_skill("ding-force", 80);

        map_skill("dodge", "ding-dodge");
        map_skill("force", "ding-force");
        map_skill("parry", "luan-blade");
        map_skill("blade", "luan-blade");
        set("inquiry", ([
                "令狐沖" : "令狐兄是我生平第一知己。\n",
                "風清揚" : "你打得過我，我自然會帶你去見他。\n",
                "風前輩" : "你打得過我，我自然會帶你去見他。\n",
                "風清揚前輩" : "你打得過我，我自然會帶你去見他。\n",
        ]));

        setup();
        carry_object("/clone/weapon/gangdao")->wield();
        carry_object("/clone/cloth/cloth")->wear();
}

void init() 
{
        object ob, me = this_object();

        ::init();
        if (interactive(ob = this_player()) && !is_fighting() &&  
            !query_temp("said", me) )
        {
                set_temp("said", 1, me);
                command("say 想找風前輩？你可得勝過我的快刀再説。");
                remove_call_out("climb_tree");
                call_out("climb_tree", 50, me);         
        }
}

int accept_fight(object ob)
{
        competition_with(ob);
        remove_call_out("checking");
        call_out("checking", 1, this_object(), ob);
        return 1;
}

void lost()
{
        object me, ob;
        
        ob = this_object();
        me = query_competitor();
        
        if( query("short", environment(ob)) == "朝陽峯" )
        {          
                addn("tian_count", 1, environment(ob));
                command( "say " + RANK_D->query_respect(me) + "果然高明，在下多有得罪。在下這便帶你去見風前輩。");
                message("vision", me->name() + "隨着田伯光走進荒山裏。\n", environment(ob), ({ob}));
                ob->move("/d/huashan/yelin1");
                me->move("/d/huashan/yelin1");
                tell_object(me, "田伯光領你走過華山後山的一片荒山野林，你注意到那兒似乎有個山洞。\n");
                ob->move("/d/huashan/xiaojing1");
                me->move("/d/huashan/xiaojing1");
                tell_object(me,"你跟着田伯光走了良久，來到一條小路。\n");
                command( "bow" );
                command( "say 風前輩住處由此路過去便是，在下失陪了。");
                say("田伯光説完便頭也不回地走了。\n");        
                remove_call_out("fast_attack");
                remove_call_out("climb_tree");
                remove_call_out("destob");
                call_out("destob", 2, ob);
        }
                                
        ::lost();
}

void win()
{
        object me = query_competitor();

        if (! objectp(me))
        {
                command("heihei");
                return;
        }

        remove_call_out("fast_attack");
        remove_call_out("climb_tree");
        call_out("climb_tree", 30, this_object());
        ::win();
}

int checking(object me, object ob)
{
        int my_max_qi;
        object weapon;

        if (! objectp(me) || ! objectp(ob)) 
                return 0;
        
        my_max_qi=query("max_qi", me);
        
        if (me->is_fighting()) 
        {
                if( !query_temp("attack_pending", me )
                 && objectp(weapon=query_temp("weapon", me)) )
                {
                           set_temp("attack_pending", 1, me);
                           remove_call_out("fast_attack");
                        call_out("fast_attack", 3, me, ob);
                }

                if( !query_temp("fought", me) )
                {
                        set_temp("fought", 1, me);
                }
                
                return 1;
        }

        if( !present(ob,environment()) && query("attack_pending", me) == 1 )
        {
                delete_temp("attack_pending", me);
                remove_call_out("fast_attack");
                return 1;
        }

        return 1;
}

void destob(object me)
{
        if (! objectp(me)) 
                return 0;
        
        destruct(me);
}

int fast_attack(object me, object ob)
{
        int i, num;

        delete_temp("attack_pending", me);
        num = random(2) + 3;

        message_vision("田伯光大喊一聲，使出其快刀絕技瘋狂般向$N連劈了" + chinese_number(num) + "刀。\n", ob);

        for (i = 1; i < num + 1; i++) {
                COMBAT_D->do_attack(me,ob,query_temp("weapon", me));
        }

        return 1;
}

int climb_tree(object me)
{
        if (! objectp(me)) return 0;
        
        if (me->is_fighting())
        {
                remove_call_out("climb_tree");
                call_out("climb_tree", 50, me);
                return 1;
        }
        
        if( query("short", environment(me)) == "朝陽峯" )
        {
                if( !query_temp("fought", me) )
                {
                        addn("tian_count", 1, environment(me));
                        message_vision("田伯光怒火大漲，潑口大罵道：“你既然無意拜見風前輩，乾巴巴地叫老子下來幹嘛？”\n", me);
                        message_vision("田伯光接着便爬回樹上，拜見周公去了。\n", me);                
                }
                else 
                {
                        message_vision("田伯光打了個呵欠。\n", me);
                        command("say 恕我不能奉陪。");
                        addn("tian_count", 1, environment(me));
                        message_vision("田伯光接着便爬回樹上，拜見周公去了。\n", me);
                }
        }
        else
         {
                message_vision("田伯光匆匆忙忙地離開了。\n", me);
        }

        destruct(me);

        return 1;
} 

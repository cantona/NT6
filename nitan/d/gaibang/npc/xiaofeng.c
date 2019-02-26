// xiaofeng.c 蕭峯(喬峯)

#include <ansi.h>

inherit NPC;

void check_skills(object ob);
int waiting(object me, object dest);
int checking(object me, object dest);
int do_back(object me);
int do_kill(object me, object dest);

void create()
{
        set_name("蕭峯", ({"xiao feng", "xiao", "feng"}));
        set("gender", "男性");
        set("nickname",HIB "鐵掌降龍" NOR);
        set("age", 28);
        set("long", 
                "他就是丐幫前任幫主，因被發現是契丹人而眾叛親離。\n"
                "在江湖上與燕子塢的慕榮復並稱為「北喬峯，南慕榮」。\n"
                "他身穿一件普通的粗布褂子，腰間用一條麻繩隨便一系。\n"
                "他身高六尺有餘，體格十分魁梧，長有一張線條粗曠、十\n"
                "分男性化的臉龐，雙目如電，炯炯有神。\n");
        set("attitude", "peaceful");
        
        set("str", 45);
        set("int", 30);
        set("con", 30);
        set("dex", 30);

        set("chat_chance", 1);
        set("chat_msg", ({
                "蕭峯歎了口氣道：“唉……想不到我蕭峯大好男兒，居然被馬伕人這樣一個女子所騙！\n",
                "蕭峯喃喃道：“我們丐幫的「降龍十八掌」是天下最霸道的掌法。”\n",
                (: random_move :),
        }));
        set("inquiry", ([
                "青竹林" : "東北西北東西北。\n",
                "丐幫"   : "東北西北東西北。\n",
                "拜師"   : "你可以去東城門的我幫總舵拜魯有腳。\n",
        ]));

        set("qi", 4000);
        set("max_qi", 4000);
        set("jing", 1500);
        set("max_jing", 1500);
        set("neili", 4000);
        set("max_neili", 4000);
        set("jiali", 100);
        
        set("combat_exp", 180000);
        set("score", 20000);
         
        set_skill("force", 120);             // 基本內功
        set_skill("huntian-qigong", 120);    // 混天氣功
        set_skill("strike", 120);            // 基本拳腳
        set_skill("dragon-strike", 120);     // 降龍十八掌
        set_skill("dodge", 120);             // 基本躲閃
        set_skill("xiaoyaoyou", 120);        // 逍遙遊
        set_skill("parry", 120);             // 基本招架
        set_skill("begging", 50);            // 叫化絕活
        set_skill("checking", 50);           // 道聽途説
        
        map_skill("force", "huntian-qigong");
        map_skill("strike", "dragon-strike");
        map_skill("dodge", "xiaoyaoyou");
        map_skill("parry", "dragon-strike");
        
        prepare_skill("strike", "dragon-strike"); 
        
        setup();
        
        carry_object("/clone/cloth/cloth")->wear();
}

void init()
{
        object ob;

        ::init();
        if (interactive(ob = this_player()) )
        {
                if( !is_killing(query("id", ob)) && living(this_object()) )
                        remove_call_out("check_skills");
                        call_out("check_skills", 1, ob);
        }
}

void check_skills(object ob)
{
        mapping skl; 
        object  me;
        string *sname;
        int i, counter, ob_shen;

        me = this_object();
        skl = ob->query_skills();
        
        if (! mapp(skl) || sizeof(skl) < 1) return;   
        
        sname  = sort_array( keys(skl), (: strcmp :) );
        ob_shen=query("shen", ob);

        counter = 0;
        for (i = 0; i < sizeof(skl); i++)
        {
                if (skl[sname[i]] >= 100)
                        counter++;
        }

        if ((counter >= 3) && (ob_shen < -1000))
        {
                me->set_leader(ob);
        
                if( !query("no_fight", environment(me)) )
                {
                        call_out("do_kill", 1, me, ob);
                        return ;
                }
                else
                {
                        call_out("waiting", 0, me, ob);
                        return ;
                }
        }
        return ;
}

int do_kill(object me, object dest)
{
        if( !query("yipin/joined", dest) )
                return 1;
                
        if (objectp(dest) && present(dest, environment(me))
         && !query("no_fight", environment(me)) )
        {
                message_vision(HIR "$N對$n説道：老子一見一品堂高手就生氣。"
                        +RANK_D->query_rude(dest)+"，納命來！\n" NOR, me, dest);
                me->set_leader(dest);
                me->kill_ob(dest);
                dest->fight_ob(me);

                call_out("checking", 0,  me, dest);
        }
        else  
                call_out("waiting", 1, me, dest);
        
        return 1;
}

int waiting(object me, object dest)
{
        if (objectp(dest))
        {
                if (dest->is_ghost())
                {
                        call_out("do_back", 1, me);
                        return 1;
                }
                else if (me->is_fighting() && present(dest, environment(me)))
                {
                        call_out("checking", 0, me);
                        return 1;
                }
                else if( living(me) && !query("no_fight", environment(dest)) )
                {
                        call_out("do_chase", 0, me);
                        return 1;
                }
        }               
        
        remove_call_out("waiting");
        call_out("waiting", 60, me);
        return 1;
}

int checking(object me, object dest)
{
        object ob;

        if (me->is_fighting()) 
        {
                call_out("checking", 1, me);
                return 1;
        }

        if (objectp(ob = present("corpse", environment(me)))
         && query("victim_name", ob) == query("name", dest) )
        {
                call_out("do_back", 1, me);
                return 1;
        }
        
        call_out("waiting", 0, me, dest);
        return 1;
}

int do_back(object me)
{

        me->move("/d/city/dongdajie2");
        set("combat_exp", 1000000, me);
        message("vision", "蕭峯走了過來，拍了拍身上的塵土，微微一笑説道：又除了一個壞蛋。\n", 
                environment(), me );

        me->set_leader(0);
        return 1;
}

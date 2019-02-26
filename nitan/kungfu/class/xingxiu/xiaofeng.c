// This program is a part of NT MudLIB
#include <ansi.h>
inherit NPC;

int auto_perform();
void you_out();
void create()
{
        set_name("蕭峯", ({"xiao feng", "xiao", "feng"}));
        set("nickname", "大俠");
        set("gender", "男性");
        set("age", 35);
        set("long",
"身材甚是魁偉，三十來歲年紀，身穿灰色舊布袍，已微有破爛，濃眉大眼，
高鼻闊口，一張四方的國字臉，頗有風霜之色，顧盼之際，極有威勢。\n");
        set("attitude", "peaceful");

        set("str", 30);
        set("int", 24);
        set("con", 40);
        set("dex", 40);

        set("max_qi", 10000);
        set("max_jing", 3000);
        set("neili", 10000);
        set("max_neili", 10000);
        set("jingli", 10000);
        set("max_jingli", 9000);
        set("eff_jingli", 9000);
        set("jiali", 100);

        set("combat_exp", 5400000);
        set("auto_perform",1);

        set("score", 200000);
        set("death_times",200);

        set_skill("force", 200);             // 基本內功
        set_skill("huntian-qigong", 200);    // 混天氣功
        set_skill("strike", 200);            // 基本掌法
        set_skill("dragon-strike", 200);   // 降龍十八掌
        set_skill("dodge", 200);             // 基本躲閃
        set_skill("xiaoyaoyou", 200);        // 逍遙遊
        set_skill("parry", 200);             // 基本招架

        map_skill("force", "huntian-qigong");
        map_skill("strike","dragon-strike");
        map_skill("dodge", "xiaoyaoyou");
        map_skill("parry", "dragon-strike");
        prepare_skill("strike", "dragon-strike");
        create_family("丐幫", 13, "幫主");
        setup();

        carry_object("/clone/cloth/cloth")->wear();
}

int accept_kill(object victim)
{
        object *ob;
        int i;
        object me=this_object();
        if (!living(me)) return 1;
        if( query_temp("azi/killer", victim) != 1 && query_temp("azi/killer2", victim) != 1 )
        {
                command("say 臭賊有幫手，但我蕭某何時怕過人多！\n");
                message_vision(HIY "蕭峯見來了幫手，豪氣頓增,把降龍十八掌發揮到極致,只見蕭峯雙臂劃圈推出，正是一招「亢龍有悔」!\n" NOR,me);
                command("halt");
                ob = all_inventory(environment(me));
                for(i=0; i<sizeof(ob); i++) {
                        if( living(ob[i]) && query_temp("azi/killer2", ob[i]) == 1){
                                tell_object(ob[i], "你感到一陣強烈的氣流湧向胸口，胸口一悶。\n");
                                            ob[i]->unconcious();
                        }
                }
                tell_object(victim, "你感到一陣強烈的氣流湧向胸口，胸口登時一悶。\n");
                if (victim) victim->unconcious();
                call_out("destruct_me",1,me);
                me->start_busy(5);
        }
        return 1;
}

void die()
{
        object  me =this_object();
        object  ob;
        ob = me->query_last_damage_from();
        if( ob)set_temp("xiaofeng/done", 1, ob);
        message_vision(HIR"蕭峯道:阿紫,姐夫無能,保護不了你了！\n" NOR,this_object());
        you_out();
        ::die();
}

void destruct_me(object me)
{
        object obj;
        obj=find_object("a zi");
        if (!obj) obj = present("a zi", me);
        if (!obj) obj = present("a zi", environment(me));
        if (obj)
        {
               destruct(obj);
               message_vision(HIY"蕭峯哈哈大笑，道:今天饒爾等不死。抱住阿紫，幾個起落，便已不見！\n" NOR,this_object());
               destruct(me);
        }
}

void you_out()
{
        object ob1,ob2,player;
        object me=this_object();
        ob1=present("you tanzhi");
        if (!ob1)
        {
                seteuid(getuid());
                ob1=new("/kungfu/class/xingxiu/you.c");
                ob1->move(environment());
        }
}

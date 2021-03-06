//Cracked by Kafei
// Kane

inherit NPC;
#include <ansi.h>
int auto_perform();
string ask_rudao();

void create()
{
        set_name("傻姑", ({ "sha gu", "sha", "gu" }));
        set("long",
"她曲靈風的女兒，幼時似乎受了驚嚇，腦子受損，智力與常人相比差了很多。\n"
"她相貌平平，臉上總帶着天真的傻笑，嘴裏哼着兒歌。\n");
        set("gender", "女性");        
        set("age", 20);
        set("attitude", "heroism");
        set("shen_type", 0);
        set("str", 35);
        set("int", 10);
        set("con", 30);
        set("dex", 10);
        
        set("max_qi", 1100);
        set("max_jing", 800);
        set("neili", 1800);
        set("max_neili", 1800);
        set("jiali", 300);
        set("combat_exp", 50000);
/*
        set_temp("apply/armor", 100);
        set_temp("apply/attack", 100);
        set_temp("apply/defense", 100);
*/        
        set_skill("force", 100);
        set_skill("dodge", 100);
        set_skill("parry", 100);
        set_skill("strike", 100);
        
        set("inquiry", ([
        "玩" : (: ask_rudao :),
        "玩一會" : (: ask_rudao :),
        "玩一會兒" : (: ask_rudao :),
        ]));

        create_family("桃花島", 3, "弟子");
        set("amulet_count", 1);

        setup();
        carry_object("/clone/cloth/cloth")->wear();
        carry_object("/d/taohua/obj/huocha")->wield();
}

void init()
{
        ::init();
        add_action("do_agree", "agree");
}

string ask_rudao()
{
        object me, obj;

        me = this_player();
        
    if( query_temp("play_with_shagu", me)>1+random(2 )
        && query("amulet_count") > 0 ) {
                command("say 你陪我玩得真夠久的，送你樣東西吧。\n");
                obj = new("/d/taohua/obj/amulet");
                obj->move(me);
                delete_temp("play_with_shagu", me);
                addn_temp("amulet_count", -1);
                message_vision("$N遞給$n一個長命鎖。\n", this_object(), me);
        }
                
        if( query("family/master_name", me) == "程英"
         || query("family/master_name", me) == "黃藥師"){
                return "你不是桃花島的人嗎？這裏的人都很聰明，不會和傻姑玩的。\n你真笨，比傻姑還笨！";
        }

        set_temp("pending/rudao", 1, me);
        return "爺爺説不能讓不三不四的人上島，如果你能挨我幾下揍，\n就讓你過去，願意(agree)的話，告訴我。\n"; 
}


int do_agree()
{
        int i, k;

        write(CYN"\n傻姑拍着手高興的跳起來，大叫道：開打啦！開打啦！\n"NOR);
        
        set_temp("apply/armor", 100);
        set_temp("apply/attack", 100);
        set_temp("apply/defense", 100);

        k = 5+random(6);
        if( !query_temp("pending/rudao", this_player()) )
                return 0;
        for (i = 0; i < k; i++) {
                if( query("qi", this_player())<0
                || !present(this_player(), environment())) {
                write(CYN"\n傻姑拍着手高興的跳起來，大叫道：打跑啦！打跑啦！不三不四的傢伙打跑啦！\n"NOR);                        
                        delete_temp("apply/armor");
                        delete_temp("apply/attack");
                        delete_temp("apply/defense");
                        return 1;
                }
                COMBAT_D->do_attack(this_object(), this_player(), query_temp("weapon")); 
        }

        write(CYN"\n傻姑撅了撅嘴，説道：好吧，你就過去吧，記得以後再來找我玩兒。\n"NOR);        
        set_temp("shagu_pass", 1, this_player());

        delete_temp("apply/armor");
        delete_temp("apply/attack");
        delete_temp("apply/defense");
        return 1;
}


int accept_fight(object me)
{
        command("say 好耶！好耶！又有人陪我玩了！\n");
        call_out("play_with_shagu", 10, me);
        return 1;
}

int accept_kill(object me)
{
        if( query("family/family_name", me) == "桃花島"){
        command("say 你我本是同門，如何要加害於我！\n");
        set_temp("th_killer", 1, me);
        kill_ob(me);
        return 1;
        }
        return 0;
}

int play_with_shagu(object me)
{
        if( !me->is_fighting(this_object()) )
                return 1;
        command("say 好玩！好玩！今天真好玩！");
        addn_temp("play_with_shagu", 1, me);
}
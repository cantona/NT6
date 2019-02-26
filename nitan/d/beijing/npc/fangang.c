#include <ansi.h>
inherit NPC;
inherit F_UNIQUE;
inherit F_MASTER;
int ask_weiwang();

void create()
{
        set_name("樊綱", ({ "fan gang", "fan" }));
        set("title", HIR "天地會"HIG"青木堂"NOR"會眾"); 
        set("shen_type", 1);
        set("gender", "男性");
        set("age", 35);
        set("long",
                "\n他就是天地會青木堂的樊綱，和關安基不和。\n");

        set_skill("unarmed", 60);
        set_skill("dodge", 70);
        set_skill("parry", 70);
        set_skill("sword", 80);
        set_skill("force", 70);
        set_skill("huashan-neigong", 50);
        set_skill("huashan-sword", 70);
        set_skill("huashan-shenfa",60);
        map_skill("dodge", "huashan-shenfa");
        map_skill("parry", "huashan-sword");
        map_skill("sword", "huashan-sword");
        map_skill("force", "huashan-neigong");

        set_temp("apply/attack", 35);
        set_temp("apply/attack", 35);
        set_temp("apply/damage", 25);

        set("combat_exp", 50000);
        set("attitude", "friendly");

        set("inquiry", ([
                "陳近南" :  "\n想見總舵主可不容易啊。\n",
                "天地會" :  "\n只要是英雄好漢，都可以入我天地會(join tiandihui)。\n",
                "加入" :  "\n只要入了我天地會，大家就可以一起反青復明。\n",
                "入會" :  "\n只要入了我天地會，大家就可以一起反青復明。\n",
                "反清復明" : "去屠宰場和棺材店仔細瞧瞧吧！\n",
                "威望" :  (: ask_weiwang :),
                "江湖威望" : (: ask_weiwang :),
       ]) );

        setup();
        carry_object("/clone/misc/cloth")->wear();
        carry_object("/clone/weapon/changjian")->wield();
}


void init()
{
add_action("do_join","join");
}

void die()
{
message_vision("\n$N大怒道：“你敢砍老子！兄弟們會替我報仇的！”説完倒地死了。\n", this_object());
::die();
}

int ask_weiwang()
{
command("tell"+query("id", this_player())+"你現在的江湖威望是"+(query("weiwang", this_player())));
say("\n樊綱説：如果你威望值很高，有些人見了你不但不會殺你，還會教你武功，送你寶貝。\n"
+"而且你還可以加入幫會，率領會眾去攻打目標，就連去錢莊取錢也會有利息 。。。。。\n");
say("樊綱又説：殺某些壞人或救某些好人可以提高江湖威望。\n");
return 1;
}
#include "/kungfu/class/yunlong/tiandihui.h";

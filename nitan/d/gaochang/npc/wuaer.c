// wuaer.c 瓦耳拉齊

#include <ansi.h>

inherit NPC;
int ask_baozang();
int ask_back();
int ask_wuaer();

void create()
{
        set_name("瓦耳拉齊", ({ "wuaer laqi", "wuaer"}));
        set("gender", "男性");
        set("age", 45);
        set("long", "他就是裝神弄鬼的瓦耳拉齊。他面容枯槁，由于長期不見陽光，皮膚慘白。\n");

        set("combat_exp", 150000);
        set("shen_type", 1);

        set("max_neili", 500);
        set("neili", 500);
        set("jiali", 10);

        set_skill("force", 40);
        set_skill("sword", 50);
        set_skill("unarmed", 50);
        set_skill("dodge", 50);
        set_skill("parry", 50);

        set("inquiry", ([
                "寶藏" : (: ask_baozang :),
                "回去" : (: ask_back :),
                "瓦耳拉齊" : (: ask_wuaer :),
                "李文秀" : "瓦耳拉齊說道：這是一個好姑娘。何時能再見到她。\n",
        ]) );


        set_temp("apply/attack", 50);
        set_temp("apply/defense", 50);
        set_temp("apply/damage", 15);

        setup();
        carry_object("/clone/weapon/gangjian")->wield();
        carry_object("/clone/misc/cloth")->wear();
}

int ask_back()
{    
        object ob;
        object me=this_player();
        if ( present("map", me))
        {
                say("瓦耳拉齊說道：好吧，這次我送你回去，高昌迷宮你以後再也不要來了。下次來我就要殺了你。\n");
                me->move("/d/gaochang/entrance");
                return 1;
        }
        else
        {
                say("瓦耳拉齊哼道：你是自作自受，在這陪我一輩子吧!\n");
                return 1;
        }
        return 1;
}

int ask_baozang()
{
        say("瓦耳拉齊說道：高昌迷宮一無所有，這一個房間是我住的。說完閃身讓出一條路。\n");
        return 1;
}    
int ask_wuaer()
{
        message("vision", HIY "瓦耳拉齊勃然大怒，喝道：你也佩直呼我的名字？！我要殺了你！\n" NOR, environment(), this_object() );
        this_object()->kill_ob(this_player());
        return 1;
}

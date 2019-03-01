// huo.c 霍青桐

#include <ansi.h>

inherit NPC;
inherit F_MASTER;

void create()
{
        object ma;
        seteuid(getuid());
        set_name("霍青桐", ({ "huo qingtong", "huo","qingtong" }));
        set("long", 
"這女郎秀美中透着一股英氣，光采照人，當真是麗若春梅綻雪，神如
秋蕙披霜，兩頰融融，霞映澄塘，雙目晶晶，月射寒江。腰插匕首，
長辨垂肩，一身鵝黃衫子，頭戴金絲繡的小帽，帽邊插了一根長長的
翠綠羽毛，革履青馬，旖旎如畫。\n");
        set("nickname", HIG"翠羽"HIY"黃衫"NOR);
        set("gender", "女性");
        set("class", "swordsman");
        set("age", 18);
        set("attitude", "friendly");
        set("shen_type", 1);
        set("per", 30);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
        
        set("max_qi", 2000);
        set("max_jing", 1000);
        set("neili", 1000);
        set("max_neili", 1000);
        set("jiali", 100);
        set("combat_exp", 600000);

        set_skill("literate", 120);
        set_skill("force", 120);
        set_skill("dodge", 120);
        set_skill("parry", 120);
        set_skill("sword", 120);
        set_skill("hand", 120);
        set_skill("claw", 120);
        set_skill("yunlong-xinfa", 120);
        set_skill("yunlong-shengong", 120);
        set_skill("yunlong-jian", 120);
        set_skill("yunlong-shenfa", 120);
        set_skill("yunlong-shou", 120);
        set_skill("yunlong-zhua", 120);

        map_skill("dodge", "yunlong-shenfa");
        map_skill("force", "yunlong-shengong");
        map_skill("hand", "yunlong-shou");
        map_skill("parry", "yunlong-shou");
        map_skill("claw", "yunlong-zhua");
        map_skill("sword", "yunlong-jian");

        prepare_skill("hand","yunlong-shou");
        prepare_skill("claw","yunlong-zhua");
        set("env/wimpy", 40);

         setup();
        carry_object(__DIR__"obj/cuiyu")->wear();
        carry_object(__DIR__"obj/huangshan")->wear();
        carry_object(__DIR__"obj/shortsword")->wield();
        //ma = new(__DIR__"obj/horse");
        //ma->move(this_object());
//        carry_object(__DIR__"obj/horse");
        //set_temp("is_riding", ma);
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
        command("ride horse");
}

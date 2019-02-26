// yanqing.c

inherit NPC;

void create()
{
        set_name("段延慶", ({ "duan yanqing", "duan", "yanqing" }));
        set_weight(10000000);
        set("nickname", "惡貫滿盈");
        set("long", 
"此人身形修長，其胸凸出，由如一鼓。長髯垂胸，根根漆黑。但是瘸了雙腿，拄着根鋼製枴杖。\n");
        set("gender", "男性");
        set("age", 55);
        set("attitude", "aggressive");
        set("shen_type", -1);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
        set("max_qi", 2000);
        set("max_jing",1000);
        set("neili", 2000);
        set("max_neili", 2000);
        set("jiali", 150);
        set("combat_exp", 1500000);

        set("apply/armor", 50);
        set_skill("force", 180);
        set_skill("dodge", 180);
        set_skill("parry", 180);
        set_skill("finger", 180);
        set_skill("kurong-changong", 180);
        set_skill("sun-finger", 180);
        set_skill("duanjia-jian", 180);        
        set_skill("strike", 180);
        set_skill("staff", 180);
        set_skill("tiannan-bu", 180);
        map_skill("dodge", "tiannan-bu");
        map_skill("force", "kurong-changong");
        map_skill("finger", "sun-finger");
        map_skill("staff", "duanjia-jian");
        map_skill("parry", "duanjia-jian");
        prepare_skill("finger", "yiyang-zhi");

        setup();
        carry_object("/clone/weapon/gangzhang")->wield();
        carry_object(CLOTH_DIR"cloth")->wear();
}
void init()
{
        object ob;
//      ::init();
        if (interactive(ob = this_player()) &&
                (int)ob->query_condition("xakiller")) {
                remove_call_out("kill_ob");
                call_out("kill_ob", 1, ob);
        }
}

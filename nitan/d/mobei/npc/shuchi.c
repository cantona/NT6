// shuchi.c
// Last Modified by winder on May. 25 2001

inherit NPC;
void create()
{
        set_name("術赤",({"shu chi","shu","chi"}));
        set("gender","男性");
        set("long","鐵木真的大兒子，他臉形瘦削，生性險詐。\n");
        set("combat_exp",150000);
        set("age",39);
        set("qi",1200);
        set("max_qi",1200);
        set("food",250);
        set("water",250);
        set("neili",900);
        set("max_neili",900);
        set_skill("dodge", 60);
        set_skill("force", 60);
        set_skill("parry", 60);
        set_skill("unarmed", 60);
        set_skill("spear", 60);
        set("chat_chance",5);
        set("chat_msg",({
                "術赤嘿嘿冷笑兩聲：察合台是個笨蛋，這[汗]的位置遲早是我的。\n",
                "術赤舉起桌上的金樽，把血色的葡萄酒一飲而盡。\n",
        }));
        setup();
        add_money("silver",30);
        carry_object("/clone/armor/yinjia")->wear();
        carry_object("/clone/weapon/spear/jinqiang")->wield();
}

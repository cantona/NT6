inherit NPC;
void create()
{
        set_name("踏青婦人",({"woman"}));
        set("gender", "女性");
        set("long", "春天出來遊覽的婦人。\n");
           set("combat_exp", 5000);
   
        set("age",34);

        set_skill("dodge",20);
           set_skill("force",20);
           set_skill("parry",20);
           set_skill("unarmed",20);
           set_skill("sword",20);

           setup();
           add_money("silver", 2);
        carry_object("clone/misc/cloth")->wear();
}

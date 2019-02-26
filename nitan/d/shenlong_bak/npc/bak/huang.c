// huang.c 黃龍門弟子
// Last Modified by winder on Jul. 12 2002

inherit NPC;

void create()
{
        set_name("黃龍門弟子", ({ "huanglong dizi","dizi" }) );
        set("gender", "男性");
        set("age", 15+random(10));
        set("long", "這是黃龍門弟子，年紀都很小，似乎不諳世事。\n");
        set("combat_exp", 2000+random(20000));
        set("shen_type", -1);
        set("attitude", "heroism");

        set("apply/attack", 15);
        set("apply/defense", 15);

        set("chat_chance", 5);
        set("chat_msg", ({
                "弟子説道：洪教主身通護佑，眾弟子勇氣百倍，以一當百，以百當萬。\n",
                "弟子説道：洪教主神目如電，燭照四方。\n",
                "弟子説道：我弟子殺敵護教，洪教主親加提拔，升任聖職。\n",
                "弟子説道：我教弟子護教而死，同升天堂。\n",
        }) );

        set_skill("sword", 15+random(50));
        set_skill("unarmed", 15+random(50));
        set_skill("parry", 15+random(50));
        set_skill("dodge", 15+random(50));
        set_skill("strike", 15+random(50));

        create_family("神龍教", 4, "弟子");

        setup();
        switch( random(3) )
        {
                case 0:
                        carry_object(WEAPON_DIR"sword/houjian")->wield();
                        break;
                case 1:
                        carry_object(WEAPON_DIR"sword/changjian")->wield();
                        break;
                case 2:
                        carry_object(WEAPON_DIR"sword/duanjian")->wield();
                        break;
                case 3:
                        carry_object(WEAPON_DIR"sword/kuojian")->wield();
                        break;
                case 4:
                        carry_object(WEAPON_DIR"sword/xijian")->wield();
                        break;
        }

        carry_object(CLOTH_DIR"cloth")->wear();
        add_money("coin", 20);
}
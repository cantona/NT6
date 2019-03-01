// boershu.c
// Last Modified by winder on May. 25 2001

inherit NPC;
void create()
{
        set_name("博爾術",({"bo ershu","bo","ershu"}));
        set("gender","男性");
        set("nickname","蒙古四傑");
        set("long","鐵木真手下四傑之一，勇猛過人！\n");
        set("combat_exp", 300000);
        set("age",45);
        set("qi",2000);
        set("max_qi",2000);
        set("food",250);
        set("water",250);
        set("chat_chance",8);
        set("chat_msg", ({
//                "博爾術偷偷告訴你：只有九天浣花神箭才能對付草原上的鷹鷲。\n",
                "博爾術嘆道：懸崖下的白雕是鷹鷲的天敵。\n",
        }));
        set("neili", 1500);
        set("max_neili", 1500);
        set_skill("dodge", 80);
        set_skill("force", 80);
        set_skill("parry", 80);
        set_skill("unarmed", 80);
        set_skill("spear", 80);

        setup();
        add_money("silver",20);
        carry_object("/clone/armor/tongjia")->wear();
        carry_object("/clone/weapon/spear/tieqiang")->wield();
}
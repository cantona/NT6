// Feb. 6, 1999 by Winder
inherit NPC;
void create()
{
        set_name("大師傅", ({
                "da shifu",
                "shifu",
        }));
        set("long",
                "這是位胖乎乎的大師傅，是陳麻婆一手調教出來的，他要是發現你的偷看他做豆腐，可是會打人的哦。\n"
        );
        set("gender", "男性");
        set("attitude", "peaceful");
        set("class", "bonze");
        set("age", 44);
        set("shen_type", 1);
        set("str", 20);
        set("int", 20);
        set("con", 20);
        set("dex", 20);
        set("max_qi", 400);
        set("max_jing", 200);
        set("neili", 100);
        set("max_neili", 100);
        set("jiali", 10);
        set("combat_exp", 2000);
        set("score", 100);
        set_skill("force", 12);
        set_skill("dodge", 12);
        set_skill("unarmed", 12);
        set_skill("parry", 12);
        setup();
}
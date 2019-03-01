//yayi.c

#include <ansi.h>

inherit NPC;

string *first_name = ({ "趙","錢","孫","李","周","吳","鄭","王","張","陳",
                        "劉","林" });
string *name_words = ({ "順","昌","振","發","財","俊","彥","良","志","忠",
                        "孝","雄","益","添","金","輝","長","盛","勝","進",
                        "安","福","同","滿","富","萬","龍","隆","祥","棟",
                        "國","億","壽" });

varargs void drool(string msg, string who);

void create()
{
        string name, id;
        name = first_name[random(sizeof(first_name))];
        name += name_words[random(sizeof(name_words))];
        name += name_words[random(sizeof(name_words))];
        set_name(name, ({"yayi"}));
        set("title", "衙役");
        set("gender", "男性");
        set("str", 25+random(10));
        set("age", 20+random(10));
        set("attitude", "peaceful");
        set("combat_exp", 40000);
        set_skill("unarmed", 50);
        set_skill("dodge", 50);
        set_skill("parry", 40);
        set_skill("staff", 40);
        set("max_qi", 500);
        set("max_jing", 500);
        set("max_neili", 300);
        set("neili", 300);
        set("jiali", 10);
        set("max_jingli", 300);
        set("jingli", 300);

        setup();
        carry_object("/d/changan/npc/obj/yayifu")->wear();
        carry_object("/d/changan/npc/obj/shawei")->wield();
}

int accept_fight(object me)
{
        command("say 哼！長安府你也敢來鬧事，看打！\n");
        return 1;
}
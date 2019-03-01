// wu-shi1.c 盟主衛士

#include <ansi.h>

inherit NPC;

void create()
{
        set_name("青衣武士", ({ "wei shi", "shi", "guard" }) );
        set("gender", "男性");
        set("age", 35);
        set("long",
                "這是位青衣武士，身披鋼甲，手執長劍，雙目精光炯炯，警惕地巡視著四周的情形。\n");
        set("combat_exp", 60000);
        set("shen_type", 1);
        set("attitude", "heroism");

        set("str", 26);
        set("con", 22);
        set("int", 20);
        set("dex", 24);

        set("max_qi", 400);
        set("eff_qi", 400);
        set("qi", 400);
        set("max_jing", 200);
        set("jing", 200);
        set("neili", 300);
        set("max_neili", 300);
        set("jiali", 20);
        set("shen_type", 0);

        set_temp("apply/attack",  30);
        set_temp("apply/defense", 30);

        set_skill("sword", 60);
        set_skill("unarmed", 50);
        set_skill("parry", 60);
        set_skill("dodge", 60);

        setup();

        carry_object("/d/city/obj/changjian")->wield();
        carry_object("/d/city/obj/tiejia")->wear();
}

void init()
{
        object ob1, ob2, ob3;
        string mengzhu, shangshan, fae;

        if(!( ob1 = find_living("mengzhu")) )
        ob1 = load_object(MENGZHU);
        mengzhu=query("winner", ob1);

        if(!( ob2 = find_living("shangshan")) )
        ob2 = load_object(SHANGSHAN);
        shangshan=query("winner", ob2);

        if(!( ob3 = find_living("fae")) )
        ob3 = load_object(FAE);
        fae=query("winner", ob3);

        if( query("id", this_player()) == mengzhu){
                message_vision(HIY "青衣武士舉起長劍，向$N齊聲大喊：盟主萬歲，萬歲，萬萬歲！\n" NOR,
                this_player());
        }
        else if( query("id", this_player()) == shangshan){
                message_vision(HIY "青衣武士舉起長劍，向$N齊聲大喊：賞善使者好！\n" NOR,
                this_player());
        }
        else if( query("id", this_player()) == fae){
                message_vision(HIY "青衣武士舉起長劍，向$N齊聲大喊：罰惡使者好！\n" NOR,
                this_player());
        }
}
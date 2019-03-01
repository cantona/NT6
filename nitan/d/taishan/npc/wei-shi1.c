// wu-shi1.c 盟主衞士

#include <ansi.h>

inherit NPC;

void create()
{
        set_name("白衣武士", ({ "wei shi", "shi", "guard" }) );
        set("gender", "男性");
        set("age", 35);
        set("long",
                "這是位白衣武士，身披鋼甲，手執長劍，雙目精光炯炯，警惕地巡視着四周的情形。\n");
        set("combat_exp", 100000);
        set("shen_type", 1);
        set("attitude", "heroism");

        set("str", 30);
        set("con", 25);
        set("int", 20);
        set("dex", 30);

        set("max_qi", 500);
        set("eff_qi", 500);
        set("qi", 500);
        set("max_jing", 200);
        set("jing", 200);
        set("neili", 500);
        set("max_neili", 500);
        set("jiali", 30);
        set("shen_type", 0);

        set_temp("apply/attack",  50);
        set_temp("apply/defense", 50);

        set_skill("sword", 100);
        set_skill("unarmed", 80);
        set_skill("parry", 100);
        set_skill("dodge", 100);

        setup();

        carry_object("/d/city/obj/gangjian")->wield();
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
                message_vision(HIY "白衣武士舉起長劍，向$N齊聲大喊：盟主萬歲，萬歲，萬萬歲！\n" NOR,
                this_player());
        }
        else if( query("id", this_player()) == shangshan){
                message_vision(HIY "白衣武士舉起長劍，向$N齊聲大喊：賞善使者好！\n" NOR,
                this_player());
        }
        else if( query("id", this_player()) == fae){
                message_vision(HIY "白衣武士舉起長劍，向$N齊聲大喊：罰惡使者好！\n" NOR,
                this_player());
        }
}
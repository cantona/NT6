// shan.c

#include <ansi.h>

inherit NPC;

void create()
{
        set_name(YEL "判官" NOR, ({ "pan guan","guan" }) );
        set("long", @LONG
地獄陰司中執掌管帶眾鬼，以施獎懲之官，手中拿着記載人壽命的生死簿。
LONG);
        set("gender","男性");
        set("str",1000);
        set("title",HIY "賞善司" NOR);                        
        set("attitude", "peaceful");
        set("age", 1000);
        set("combat_exp", 100000000);
        set("max_jing", 10000);
        set("max_qi", 10000);
        set("max_neili",10000);
        set("neili",10000);
        setup();
        carry_object( __DIR__"obj/shsbu")->wear();
}
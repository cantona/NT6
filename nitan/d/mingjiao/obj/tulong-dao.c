// tulong-dao.c

#include <weapon.h>
#include <ansi.h>
inherit BLADE;

void create()
{

        set_name(HIM"屠龍刀"NOR, ({ "tulong dao","tulong","dao", "blade" }));
        set_weight(35000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("rigidity", 9);
                set("sharpness", 9);
                set("long", "這是一把渾身發黑的屠龍刀，刀刃間隱隱有血光流動，鋒利無匹，
當年江湖中人為此刀，拼得你死我活，是刀中之寶。\n");
                set("value", 1);
                set("weapon_prop/dodge", -10);
                set("weapon_prop/parry", 5);
                set("material", "steel"); 
                set("wield_neili", 500);
                set("wield_maxneili", 1000);;
                set("wield_str", 25);;
                set("wield_msg", HIM"只見黑光一閃，$N手中已提着一把黑沉沉的大刀，正是號稱“武林至尊”的寶刀屠龍！\n"NOR);            
                set("unwield_msg", HIM"黑光忽滅，$n躍入$N懷中。\n"NOR);
                set("treasure",1);
        }
        init_blade(160);
        setup();
}

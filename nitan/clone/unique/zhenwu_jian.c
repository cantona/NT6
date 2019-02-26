// zhenwu-jian.c 真武劍
// Created by Lonely for only one object in mud
#include <ansi.h>
#include <weapon.h>
inherit SWORD;
inherit F_UNIQUE;
void create()
{
        set_name(HIW"真武劍"NOR, ({"zhenwu jian", "sword", "jian"}));
        set_weight(15000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("long", "一把毫不起眼的古劍,劍身不規則的花紋上似乎還帶有些鐵鏽,劍鋒上居然還有幾個缺口。\n");
                set("value", 100000);
                set("material", "blacksteel");
                set("weapon_prop/dodge", -2);
                set("weapon_prop/parry", 3);
                set("unique", 1);
                set("rigidity", 300);
                set("replica_ob","/d/city/npc/obj/changjian");
                set("no_put",1);
                set("no_steal",1);    
                set("wield_neili", 300);
                set("wield_maxneili", 700);
                set("wield_str", 22);        
                set("enchase/flute", 5);        
                set("wield_msg",HIW"$N[噌]的一聲抽出一把真武劍,空氣中頓時充滿了無邊的殺氣。\n"NOR);
                set("unwield_msg",HIW"$N把手中的寶劍插入劍鞘。四周的殺氣也跟着消失了。\n"NOR);
        }
        init_sword(400,2);
        setup();
}       


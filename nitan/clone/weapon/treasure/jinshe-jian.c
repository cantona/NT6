// jinshe-jian.c 金蛇劍
// Last Modified by winder on Sep. 7 2001

#include <weapon.h>;
#include <ansi.h>;
inherit SWORD;
inherit F_UNIQUE;

void create()
{
        set_name(YEL"金蛇劍"NOR, ({ "jinshe jian", "sword", "jian" }));
        set_weight(50000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("long", 
"這劍金光燦爛，握在手中甚是沉重，看來竟是黃金混和了其他五
金所鑄，劍身上一道血痕，發出碧油油的暗光，極是詭異。劍的
形狀甚是奇特，整柄劍就如是一條蛇盤曲而成，蛇尾勾成劍柄，
蛇頭則是劍尖，蛇舌伸出分叉，是以劍尖竟有兩叉。\n");
                set("value", 10000);
                set("material", "gold");
                set("wield_msg", "$N「唰」的一聲抽出一柄$n握在手中，頓時全身涼颼颼地只感寒氣逼人。\n");
                set("unwield_msg", "$N將手中的$n插回劍鞘。\n");
        }
        init_sword(130);
        setup();
}
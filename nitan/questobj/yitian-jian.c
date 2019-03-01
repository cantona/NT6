// yitian-jian 倚天劍

#include <weapon.h>
#include <ansi.h>
inherit SWORD;

void create()
{
        set_name(YEL"倚天劍"NOR,({ "yitian jian", "yitian", "sword", "jian" }));
        set_weight(1000);
        set("taskobj", 1);
        if( clonep() )
                set_default_object(__FILE__);
        else
        {
                set("unit", "把");
                set("value", 0);
                set("material", "steel");
                set("long", "這是一柄四尺來長的古劍，劍鞘上金絲鑲著兩個字“倚天”。\n整個劍身隱隱發出一層青氣，劍未出鞘，已可見其不凡。\n");
                set("wield_msg", HIY "$N“唰”的一聲抽出$n挽了個劍花，只覺淡淡清香，\n劍色淡黃，這把倚天劍竟是檀香木所制。$N一時不知所措。\n"NOR);
                set("unwield_msg", HIY "$N將木劍還入劍鞘。\n" NOR);
        }
        setup();
}
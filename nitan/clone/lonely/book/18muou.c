#include <ansi.h>
 
inherit ITEM;

void create()
{
        set_name("十八木偶", ({ "18 muou", "18", "muou" }));
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__); 
        else {
                set("unit", "盒");
                set("long", NOR + YEL "
這是一個小木盒，盒中墊着棉花，並列着三排木偶，神情或喜
悦不禁，或痛哭流淚，或裂嘴大怒，或慈和可親，竟無一相同。
木偶身上油着層桐油，繪滿黑線，卻無穴道位置。這盒木偶刻
工精巧，面目栩栩如生。竟似一門非常高深的武學。\n" NOR);
                set("value", 100000);
                set("no_sell", "你家的孩子死了？玩具也拿來賣錢。");
                set("material", "wood");
                set("skill", ([
                        "name"         : "luohan-fumogong",
                        "exp_required" : 500000,
                        "jing_cost"    : 150,
                        "difficulty"   : 100,
                        "max_skill"    : 179,
                        "min_skill"    : 0
                ]));
        }
}
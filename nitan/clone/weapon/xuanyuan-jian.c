// 上古十大神器之 軒轅劍
// Create by Rcwiz for Hero.cn 2003/09

#include <ansi.h>

#include <weapon.h>
inherit SWORD;

void create()
{
        set_name(HIY "軒轅劍" NOR, ({ "xuanyuan jian", "xuanyuan", "jian" }) );
        set_weight(200);
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("unit", "把");
                set("long", HIY "此乃上古神器之首，擁有着無窮的力量，據説"
                                "擁有此劍者可馳騁人、魔、神三界，勢不可擋。\n"
                                "上面刻滿了各種奇怪的文字，像是佛教經文。\n" NOR);
                set("material", "tian jing");
                set("wield_msg", HIY "$N" HIY "一聲輕呼，兩條神龍自天而下，擁着一把周身泛着\n"
                                 "金光的神劍，剎那間此劍猶如一道流星劃過，落入$N" HIY "手中。\n" NOR);                               
                set("unwield_msg", HIY "$N" HIY "心意一轉，軒轅劍已歸鞘。\n" NOR);
                set("stable", 100);

        }
        init_sword(1200);
        setup();
}
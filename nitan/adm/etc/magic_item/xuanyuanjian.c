// 上古十大神器之 軒轅劍
// Create by Rcwiz for Hero.cn 2003/09

#include <ansi.h>

#include <weapon.h>
inherit SWORD;

int is_magic_item() { return 1; }

mapping skills = ([
        "egui-dao"     :   "餓鬼道",
        "xiuluo-dao"   :   "修羅道",
        "renjian-dao"  :   "人間道",
        "chusheng-dao" :   "畜生道",
        "tianji-dao"   :   "天極道",
        "diyu-dao"     :   "地獄道",
        "lun"          :   "真·六道輪迴",
]);

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
                                "上面刻滿了各種奇怪的文字，像是佛教經文。\n"
                                "轉世後可從此劍中領悟(lingwu)出轉世奇學—六道輪迴劍。\n"
                                "lingwu ?　可查看可領悟的招式。\n" NOR);
                set("material", "gold");
                set("wield_msg", HIY "$N" HIY "一聲輕呼，兩條神龍自天而下，擁着一把周身泛着\n"
                                 "金光的神劍，剎那間此劍猶如一道流星劃過，落入$N" HIY "手中。\n" NOR);                               
                set("unwield_msg", HIY "$N" HIY "心意一轉，軒轅劍已歸鞘。\n" NOR);
                set("stable", 100);

        }
        init_sword(500);
        setup();
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int n;
        int my_exp, ob_exp;
        
        switch (random(10))
        {
        case 0:
                if (! victim->is_busy())
                victim->start_busy(20 + random(20));
                return HIY "$N" HIY "揮舞着手中的軒轅劍，萬道彩光自中而出，直逼得"
                           "$n" HIY "連連後退。\n" NOR;

        case 1:
                n = me->query_skill("sword");
                victim->receive_damage("qi", n, me);
                victim->receive_wound("qi", n, me);
                return HIR "$N" HIR "反轉手中軒轅劍，猛然間，數道金光划向$n" HIY "，$n" HIY
                           "正驚異間，卻已中劍。\n" NOR;

        }
        return damage_bonus;
}

void init()
{
        add_action("do_lingwu", "lingwu");       
}

int do_lingwu(string arg)
{
        object me;
        int i;
        string *str;        
               
        me = this_player();

        if(! objectp(present("xuanyuan jian", me)))return 0;
 
        // 轉世後才能領悟
        if (! me->query("scborn/ok"))return 0;
                
        if (me->is_fighting() || me->is_busy())
                 return notify_fail("你正忙呢！\n");

        if (! arg)return notify_fail("你要領悟什麼？\n");
        
        str = keys(skills);
        if (arg == "?")
        {
                write(HIC "軒轅劍中記載着以下絕學：\n" NOR);
                for (i = 0; i < sizeof(str); i ++)
                        write(sprintf(HIC "%-20s %s\n", 
                              str[i], skills[str[i]]));
                              
                return 1;
                      
        }
        if (member_array(arg, str) == -1)       
                    return notify_fail("你要領悟什麼(lingwu ?)？\n");

        if (me->query_skill("buddhism", 1) < 200)
                    return notify_fail("你翻來覆去的研究着上面經文，卻始終看不明白。\n");
                                                        
        if (me->query_skill("literate", 1) < 200)
                    return notify_fail("你讀書寫字等級不夠，很多意思你無法理解。\n");

        if (me->query_skill("sword", 1) < 300)
                    return notify_fail("你基本劍法火候不足，無法領悟出什麼。\n");                    

        if (me->query_skill("force", 1) < 300)
                    return notify_fail("你基本內功修為不足，無法領悟出什麼。\n");
                    
        if (me->query_skill("dodge", 1) < 300)
                    return notify_fail("你基本輕功修為不足，無法領悟出什麼。\n");                    

        if (arg == "lun" && me->query_skill("liudao-jian", 1) < 450)
                    return notify_fail("你六道輪迴劍法等級不夠。\n");
                    
        else if (arg == "lun" && me->query_skill("force", 1) < 680)
                    return notify_fail("你內功修為不足。\n");

        else if (arg == "lun" && me->query("max_neili") < 20000)
                    return notify_fail("你內力修為不足。\n");        

        else
        {
                if (me->query_skill(arg, 1))
                       return notify_fail("你不已經會了這招了嗎？\n");

                message_vision(HIM "$N" HIM "聚精會神地參悟着軒轅劍中的奧祕　……\n" NOR, me);
                
                switch(arg)
                {
                        case "lun":
                            write(HIG "你領悟出了絕招　真·六道輪迴劍　。\n" NOR);
                            me->set("can_perform/liudao-jian/lun", 1);
                            destruct(this_object());
                            return 1;
                        
                        default :                            
                            write(HIC "你領悟出 " + skills[arg] + " 。\n" NOR);
                            me->set_skill(arg, 1); // 領悟出一級
                            destruct(this_object());
                            return 1;
                }
        }

        return 1;
}

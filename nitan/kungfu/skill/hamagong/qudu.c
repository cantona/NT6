// qudu.c
// Last Modified by winder on Mar. 10 2000
/* 下列為本泥巴的毒：
白駝派：bt_poison 怪蛇毒
        cold_poison 寒毒
        hot_poison 熱毒
        snake_poison 蛇毒
星宿派：fushi_poison 腐屍毒
        poison_sandu 散毒反噬
        slumber_poison 蒙汗藥
        sanxiao_poison 三笑逍遙散
        xx_poison 星宿掌毒
五毒教：chanchu_poison 蟾蜍毒
        snake_poison 蛇毒
        wugong_poison 蜈蚣毒
        wuxing_poison 無形毒
        xiezi_poison 蠍子毒
        zhizhu_poison 蜘蛛毒
絕情谷：qinghua_poison 情花毒
明教：        ice_poison 寒冰綿掌毒
逍遙派：ss_poison 生死符
古墓派：ice_sting 冰魄銀針毒
雲龍門：zhua_poison 凝血神抓
雪山派：dashouyin 大手印
神龍島：flower_poison 斷腸花毒
杭州：        scorpion_poison 蠍子毒
其他：        ill_dongshan 凍傷
        ill_fashao 發燒
        ill_kesou 咳嗽
        ill_shanghan 傷寒
        ill_zhongshu 中暑
未用：        bing_poison 冰晶毒
        cuff_power 拳後勁
        iceshock 意寒掌毒
        rose_poison 火玫瑰毒
*/
#include <ansi.h>

int exert(object me, object target)
{
  if ( userp(me) && !wizardp(me) && 
  !query("perform/qudu", me) && 
  !query("can_perform/hamagong/qudu", me) && 
  !query_temp("murong/xingyi", me) )
   return notify_fail("你所使用的內功中沒有這種功能。");

        if( me->is_fighting() )
                return notify_fail("戰鬥中運功驅毒？找死嗎？\n");
        if( query("neili", me)<500 )
                return notify_fail("你的真氣不夠。\n");
        if( query("eff_qi", me)<query("max_qi", me)/2 )
                return notify_fail("你已經受傷過重，一運真氣便有生命危險！\n");
        if ((int)me->query_skill("xidu-poison", 1) < 50)
                return notify_fail("你對“西毒毒技”還不是很精通。\n");
        if ((int)me->query_skill("hamagong", 1) < 50)
                return notify_fail("你的蛤蟆功修為還不夠。\n");

        if ((int)me->query_condition("bt_poison") > 0 ||
                me->query_condition("cold_poison") > 0 ||
                me->query_condition("hot_poison") > 0 ||
                me->query_condition("snake_poison") > 0 ||
                me->query_condition("fushi_poison") > 0 ||
                me->query_condition("slumber_poison") > 0 ||
                me->query_condition("xx_poison") > 0 ||
                me->query_condition("chanchu_poison") > 0 ||
                me->query_condition("wugong_poison") > 0 ||
                me->query_condition("xiezi_poison") > 0 ||
                me->query_condition("zhizhu_poison") > 0 ||
                me->query_condition("ice_sting") > 0 ||
                me->query_condition("scorpion_poison") > 0)
        {
                write(HIG"你倒運氣息，頭下腳上，氣血逆行，將毒氣從進入身子之處逼了出去。\n"NOR);
                message("vision", HIW+me->name()+"身上白氣一現即消，張口哼了一聲。\n吐出一口"HIY"金燦燦的瘀血"HIW"，一滴滴"BLK"黑血"HIW"從傷口慢慢滲出。\n"NOR,environment(me));
                me->clear_condition("bt_poison");
                me->clear_condition("cold_poison");
                me->clear_condition("hot_poison");
                me->clear_condition("snake_poison");
                me->clear_condition("fushi_poison");
                me->clear_condition("slumber_poison");
                me->clear_condition("xx_poison");
                me->clear_condition("chanchu_poison");
                me->clear_condition("wugong_poison");
                me->clear_condition("xiezi_poison");
                me->clear_condition("zhizhu_poison");
                me->clear_condition("ice_sting");
                me->clear_condition("scorpion_poison");
                addn("neili", -500, me);
                me->start_busy(6);
                return 1;
        }
        else
        return notify_fail("你深深吸了口氣，口中“咕咕。。。”地叫了幾聲。\n"); 
}

int help(object me)
{
        write(WHT"\n蛤蟆功之驅毒："NOR"\n");
        write(@HELP

        使用功效：
                驅除體內毒素，對下列毒有效：
                白駝怪蛇毒、寒毒、熱毒、蛇毒、腐屍毒、蒙汗藥、
                星宿掌毒、蟾蜍毒、蜈蚣毒、蠍子毒、蜘蛛毒、冰魄銀針毒

        出手要求：
                蛤蟆功50級
                西毒毒技50級
                內力500
HELP
        );
        return 1;
}
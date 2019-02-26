// zhui.c 
#include <weapon.h>
#include <ansi.h>

inherit DAGGER;

void create()
{
        set_name(HIC"鐵錐"NOR, ({ "tie zhui", "zhui" }) );
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("count", 12);
                set("value", 100);
                set("material", "iron");
                set("long", HIC"此鐵錐長六七寸許，錐尖曲了兩曲。裏面共有"+chinese_number(query("count"))+"支青蜂釘可以射出(shoot)。\n"NOR);
                set("wield_msg", HIC"$N將左手伸入右手衣袖，隨即將手伸出，手中已握了一柄鐵錐！\n"NOR);
                set("unwield_msg",HIC"$N將手裏鐵錐往袖中一塞就不見了。\n"NOR);
        }
        init_dagger(5);
        setup();
}

void init()
{
        add_action("do_shoot","shoot");
}

int do_shoot(string arg)
{
        object weapon, obj, me = this_player();
        int attacklvl, dodgelvl, parrylvl, damage;

        if (environment(this_object())!=me)
                return 0;
        if( query("no_fight", environment(me)) )
                return notify_fail("這裏禁止戰鬥。\n");
        if( (me->is_busy() ))
                return notify_fail("你現在正忙着呢，沒得閒用「青蜂釘」。\n");
        if( !arg )
                return notify_fail("你要射擊誰？\n");
        if( !objectp(obj = present(arg, environment(me)) ))
                return notify_fail("這裏沒有這個人！\n");
        if( !obj->is_character() || obj->is_corpse() )
                return notify_fail("看清楚一點，那並不是活物。\n");
        if( !me->is_fighting(obj) )
                return notify_fail("「青蜂釘」只能對戰鬥中的對手使用。\n");
        if( obj == me ) return notify_fail("射自己？別想不開啊。\n");
//        obj = me->select_opponent();

        if( query("count") == 0 )
                return notify_fail("青蜂釘都射光了，收手罷。\n");
        attacklvl = me->query_skill("qingzi9da", 1);
        parrylvl = obj->query_skill("parry", 1);
        dodgelvl = obj->query_skill("dodge", 1);
        damage=query("eff_qi", obj);
        if( query("neili", me)<400 )
                return notify_fail("你的內力不足，無力發出青蜂釘！\n");
        if( me->query_skill("qingming-xuangong", 1) < 30 )
                return notify_fail("你的青冥玄功火候不到，無法發出青蜂釘！\n");
        if( attacklvl < 10 )
                return notify_fail("你的青字九打火候不到，無法發出青蜂釘！\n");

        addn("count", -1);
        addn("neili", -300, me);
        weapon = new(__DIR__"qingfengding");
/* 發射 */
        if( attacklvl < 40 )
        {
                message_vision(HIG"$N在鐵錐後部一敲，一支青蜂釘疾速射出！\n"NOR, me);
        }
        else
                if( attacklvl < 70 )
                {
                        message_vision(HIG"$N在鐵錐後部一敲，一支青蜂釘呼嘯而出！\n"NOR, me);
                }
                else
                        if( attacklvl < 100 )
                        {
                                message_vision(HIG"$N在鐵錐後部一敲，一支青蜂釘破空射出！\n"NOR, me);
                        }
                        else
                        {
                                message_vision(HIG"$N在鐵錐後部一敲，一支青蜂釘電射而出！\n"NOR, me);
                        }

        if(userp(obj)) obj->kill_ob(me);
        else obj->fight_ob(me);

        me->start_busy(2);
/* 不中 */

        if( attacklvl < (int)(dodgelvl/2) + random((int)(dodgelvl/2)) )
        {
                weapon->move(obj);
                message_vision(HIY"$N冷笑一聲，伸出腳丫子只一夾，輕鬆刁住了青蜂釘。\n"NOR, obj);
                return 1;
        }
//        if( attacklvl < (int)(dodgelvl/2) + random(parrylvl))
        if( attacklvl < random(dodgelvl) + random(parrylvl))
        {
                weapon->move(environment(me));
                message_vision(HIY"$N一聲冷哼，抬手聲食指一彈，正好彈在青蜂釘上，青蜂釘一閃落地！\n"NOR, obj);
                return 1;
        }
        if( attacklvl < (int)(parrylvl/2) + random((int)(parrylvl/2)) )
        {
                weapon->move(obj);
                message_vision(HIY"$N嘴角露出一絲冷笑，一抬手便將青蜂釘收籠在衣袖裏。\n"NOR, obj);
                return 1;
        }
        if( attacklvl < dodgelvl )
        {
                message_vision(HIY"$N瀟灑地一轉身，避開了青蜂釘。\n"NOR, obj);
                return 1;
        }
        if( attacklvl < parrylvl )
        {
                weapon->move(obj);
                message_vision("$N躲閃不及，一張嘴，居然咬住了青蜂釘！\n"NOR, obj);
                return 1;
        }

/* 命中 */

        if( attacklvl > parrylvl + dodgelvl + random((parrylvl + dodgelvl) * 2))
        {
                message_vision(HIR"$N一楞神，一聲悶哼，喉頭赫然釘着一支青蜂釘！\n"NOR, obj);
                obj->die();
        }
        else
        if( attacklvl > parrylvl + dodgelvl + random(parrylvl + dodgelvl) )
        {
                message_vision(HIR"$N一個躲閃不及，一聲慘呼，青蜂釘正釘在$N的腦門！\n"NOR, obj);
                obj->unconcious();
        }
        else
        if( attacklvl > random(parrylvl + dodgelvl) )
        {
                message_vision(RED"$N一個躲閃不及，一聲慘呼，青蜂釘正釘在$N的胸口！\n"NOR, obj);
                if(damage < 11) obj->unconcious();
                else obj->receive_wound("qi", damage-10);
                obj->start_busy(3);
        }
        else
        if( attacklvl > parrylvl )
        {
                message_vision(HIM"$N一個鷂子翻身，結果青蜂釘呼地一聲，正釘在$N的大腿上！\n"NOR, obj);
                obj->receive_wound("qi", (int)(damage/2));
                obj->start_busy(3);
        }
        else
        if( attacklvl > dodgelvl )
        {
                message_vision(MAG"$N躲閃不及，青蜂釘呼地一聲釘在$N的胳膊上！\n"NOR, obj);
                obj->receive_wound("qi", (int)(damage/3));
                obj->start_busy(3);
        }
        else
        {
                message_vision(HIW"$N縱身一躍，但青蜂釘在$N的手臂上劃出了一道傷口！\n"NOR, obj);
                obj->receive_wound("qi", (int)(damage/10));
                obj->start_busy(1);
        }
        return 1;
}

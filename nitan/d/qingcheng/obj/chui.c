// chui.c 
#include <weapon.h>;
#include <ansi.h>;
inherit HAMMER;

void create()
{
        set_name(HIC"雷公轟"NOR, ({"leigong hong", "hong", "chui" }) );
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("value", 100);
                set("material", "iron");
                set("long", HIC"雷公轟為一柄八角小錘，錘柄長僅及尺，錘頭還沒常人的拳頭大。\n情況緊急時可以擲(zhi)敵。\n"NOR);
                set("wield_msg", HIC"$N將右手伸入左手衣袖，隨即將手伸出，手中已握了一柄八角小錘！\n"NOR);
                set("unwield_msg",HIC"$N將手裏小錘往袖中一塞就不見了。\n"NOR);
        }
        init_hammer(5);
        setup();
}

void init()
{
        add_action("do_zhi","zhi");
}

int do_zhi(string arg)
{
        object *inv, obj, weapon, me = this_player();
        int attacklvl, dodgelvl, parrylvl, equip;
        string msg;
        object piece;
        
        if (environment(this_object())!=me)
                return 0;
        if( query("no_fight", environment(me)) )
                return notify_fail("這裏禁止戰鬥。\n");
        if( (me->is_busy() ))
                return notify_fail("你現在正忙着呢，沒得閒擲「雷公轟」。\n");
        if( !(me->is_fighting() ))
                return notify_fail("「雷公轟」只能對戰鬥中的對手使用。\n");
        if( !arg )
                return notify_fail("你要擲擊誰？\n");
        if( !objectp(obj = present(arg, environment(me)) ))
                return notify_fail("這裏沒有這個人！\n");
        if( !obj->is_character() || obj->is_corpse() )
                return notify_fail("看清楚一點，那並不是活物。\n");
        if( !me->is_fighting(obj) )
                return notify_fail("「雷公轟」只能對戰鬥中的對手使用。\n");
        if( obj == me ) return notify_fail("擲自己？別想不開啊。\n");
//        obj = me->select_opponent(); 

        attacklvl = me->query_skill("chengzi18po", 1);
        parrylvl = obj->query_skill("parry", 1);
        dodgelvl = obj->query_skill("dodge", 1);
        if( query("neili", me)<500 )
                return notify_fail("你的內力不足，無力擲出雷公轟！\n");
        if( me->query_skill("qingming-xuangong", 1) < 30 )
                return notify_fail("你的青冥玄功火候不到，無法擲出雷公轟！\n");
        if( attacklvl < 10 )
                return notify_fail("你的城字十八破火候不到，無法擲雷公轟！\n");

        addn("neili", -200, me);
        msg = HIY"$N手指一振，八角雷公轟脱手飛出！\n"NOR;

//        if( random(attacklvl) > (int)((parrylvl+dodgelvl)/2))
                if( attacklvl*3/4 > random(parrylvl+dodgelvl))
        {
                inv = all_inventory(obj);
                msg += HIY"$n只覺眼前一股勁風撲來，“轟”的一聲！"NOR;
                for(equip=0; equip<sizeof(inv); equip++)
                {
                        if( query("equipped", inv[equip]) && 
                                !query("weapon_prop", inv[equip]) )
                        {
                                msg += HIY"一些稀稀拉拉的物事掉在了地上！\n"NOR;
        seteuid(getuid());
        piece = new("/clone/misc/piece");
        set("name",query("name",  inv[equip])+"的碎片", piece);
        set("long", "一堆破碎物事，好像是布片鐵片什麼的。\n", piece);
        piece->move(environment(obj));
        destruct(inv[equip]);
                        }
                }
        }
        else
        {
                msg += HIG "只見$n不慌不忙一側身，躲過了飛來的雷公轟！\n"NOR;
                if( userp(me))addn("neili", -400, me);
                me->start_busy(4);
        }
        message_vision(msg, me, obj);

        if(userp(obj)) obj->fight_ob(me);
        else if( !obj->is_killing(me) ) obj->kill_ob(me);
//        destruct(this_object());
        this_object()->move(environment(me));
        return 1;
}

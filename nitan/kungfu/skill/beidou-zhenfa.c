// /kungfu/skill/beidou-zhenfa.c

#include <ansi.h>

inherit SKILL;

int valid_enable(string usage) { return usage=="array"; }

string *position = ({
        "天權","天樞","天璇","天璣","玉衡","開陽","搖光"
});

string *sword = ({
        "踏奇門，走偏鋒，劍尖顫了幾顫，一招巧妙無比的「分花拂柳」，似左實右往空中刺去。",
        "使一招「琴心三疊」，身形向上飄起，手中劍虛虛實實幻出三點寒光射向空中。",
        "身形一轉，猛然一式「罡風掃葉」，舞出滿天劍影，挾著勁風向前掃去。",
        "仰天長笑，身形飄然而起，在半空中身子一旋，一式「狂歌痛飲」狂風般地擊向空中。",
        "左手捏著劍訣，右足踏開一招“定陽針”向上斜刺。",
        "向前邁去一大步，使出「探海屠龍」，手中劍舞成一個光球，迅若奔雷擊出。",
        "運力一抖劍，一時「馬蹴落花」，劍幻出點點劍花，飄然刺出。",
        "手中劍一指，縱起丈余，一時「橫行漠北」，雷霆般擊出。",
        "身形向上飄起，突然一轉身，頭下腳上，手握劍，一招「絮墜無聲」，無聲無息地攻出。",
        "大喝一聲，一招「白虹經天」，劍閃電般劃出一道大圓弧劈下。",
        "忽然身形高高躍起，使出「浪跡天涯」，手中劍幻出漫天花瓣，迅如雷霆射出。"
});

string *zhen =  ({
        "天罡北鬥陣法滾滾推動，攻勢連綿不絕，瞬間將敵人圍在垓心。",
        "天罡北鬥陣氣勢宏大，前攻後擊，連環相接，讓人眼花撩亂，方寸頓失。",
        "只見天罡北鬥陣暗合五行八卦之理，陣中人步法精妙，攻守配合得天衣無縫。",
        "天罡北鬥陣越縮越小，無形劍氣象浪潮一般逼向中央，令人有窒息之感。"
});


void start_beidouzhen(object ob, int mypos,int beidou_time,int bd_power );
int beidouzhen(object me);
int halt_beidou(object me);
void out_beidou(object me);

int valid_learn(object me)
{
        if( query("gender", me) == "無性" && 
        (int)me->query_skill("beidou-zhenfa", 1) > 49)
                return notify_fail("你無根無性，陰陽不調，難以領會高深的天罡北鬥陣法。\n");

        if ((int)me->query_skill("array", 1) <= (int)me->query_skill("beidou-zhenfa",1))
                return notify_fail("你的基本陣法火候還不夠。\n");

            return ::valid_learn(me);
}

int practice_skill(object me)
{
        return notify_fail("天罡北鬥陣法只能用學(learn)的來增加熟練度。\n");
}

int form_array(object me,string arg)
{
        object enemy,*member;
        int beidou_time,i,mypos=0,power,bd_power,level;
        object here;
        string msg;
        float exp_diff;

        here = environment( me );

        if( me->is_busy() )
        {
                return notify_fail("你正忙著呢！\n");
        }

        if( me->query_skill_mapped("array") != "beidou-zhenfa")
                return notify_fail("你還沒有激發好天罡北鬥陣法！\n");

        member = me->query_team();
        level = sizeof(member) *20;

        if (sizeof(member) < 3 || sizeof(member) > 7)
                return notify_fail("天罡北鬥陣最少三個人，最多七個人。\n");

        if( me->query_skill("beidou-zhenfa",1) < level)
                return notify_fail("你的天罡北鬥陣法等級太低！\n");

        if (!arg)
                return notify_fail("指令格式：team form beidou-zhenfa 目標ID \n");

        if (!enemy = present(arg,here))
                return notify_fail("你要擺陣攻擊的"+arg+"不在這裡啊？\n");

        if( query("family/family_name", enemy) == "全真教" )
                return notify_fail("怎麼？你們要同門殘殺麼？\n");

        if( query("race", enemy) != "人類" )
                return notify_fail("怎麼？殺雞還用牛刀麼？\n");

        for( i = 0; i < sizeof(member); i++ )
        {
           if (!objectp(member[i]))
                return notify_fail("你的隊伍有點問題，需要重新組合隊伍。\n");

           if (environment(member[i]) != here)
                return notify_fail("你隊伍中的" + member[i]->name() + "現在不在這裡啊！\n");

           if( query("family/family_name", member[i]) != "全真教" )
                return notify_fail("你隊伍中的" + member[i]->name() + "不是全真教弟子。\n");

           if (member[i]->is_busy())
                return notify_fail("你隊伍中的" + member[i]->name() + "正忙著呢！\n");

           if (member[i]->query_skill_mapped("array") != "beidou-zhenfa")
                return notify_fail("你隊伍中的" + member[i]->name() + "沒有激發好天罡北鬥陣法。\n");

           if (member[i]->query_skill("beidou-zhenfa",1) < level )
                return notify_fail("你隊伍中的" + member[i]->name() + "天罡北鬥陣法等級不夠。\n");

           if ( member[i]->query_skill("quanzhen-jian",1) <60 ||
                query("combat_exp", member[i])<50000 || 
                member[i]->query_skill("dodge") <60)
                return notify_fail("你隊伍中的" + member[i]->name() + "武功太差，不能參加「天罡北鬥陣」。\n");

           if( query("neili", member[i])<500 )
                return notify_fail("你隊伍中的" + member[i]->name() + "內力太差，不能參加「天罡北鬥陣」。\n");

           if( query("jingli", member[i])<300 )
                return notify_fail("你隊伍中的" + member[i]->name() + "精力太差，不能參加「天罡北鬥陣」。\n");

           exp_diff=to_float(query("combat_exp", member[i])-query("combat_exp", me));
           exp_diff/=to_float(query("combat_exp", me));

           if( exp_diff > 0.4 || exp_diff < -0.4 )
                return notify_fail("你隊伍中的" + member[i]->name() + "武功和你差距太大，不能共擺「天罡北鬥陣」。\n");
        }

        power = me->query_skill("force");
        power += me->query_skill("sword");
        power+=query("str", me)*10;
        power += me->queyr("dex")*10;

        bd_power = me->query_skill("beidou-zhenfa",1);

        for (i = 0;i < sizeof(member); i++)
        {
                power += member[i]->query_skill("force");
                power += member[i]->query_skill("sword");
                power+=query("str", member[i])*10;
                power += member[i]->queyr("dex")*10;

                bd_power += member[i]->query_skill("beidou-zhenfa",1);
        }

        power /= 70;
        bd_power /= 35;
        power += bd_power;

        if(power>300)power=300;
        if(power<30)power=30;

        msg = "";

        for (i = 0;i < sizeof(member); i++)
        {
                start_beidouzhen(member[i],0,power/2,power);
                if (member[i] != me)
                {
                        msg += member[i]->name();
                        if (i != sizeof(member) -1)
                                msg += "、";
                }
        }

        message_vision(HIM"$N突然身形移動，發動" + msg +
                        "將" + enemy->name() + "圍在中間，正是擺的「天罡北鬥陣」陣法。\n\n"NOR, me);

        message_vision(HIR"\n$N對$n喝道：" + RANK_D->query_rude(enemy) +
                        "你一向為非作歹，今天本教要替天行道，納命來！\n\n"NOR, me, enemy);

        for (i = 0;i < sizeof(member); i++)
        {
                member[i]->kill_ob(enemy);
                enemy->kill_ob(member[i]);
        }

        return 1;
}

void start_beidouzhen(object ob, int mypos,int beidou_time,int bd_power )
{
        set_temp("pending/beidou", 1, ob);
        set_temp("beidou_time", beidou_time, ob);
        set_temp("bd_pos", mypos, ob);
        set_temp("bd_power", bd_power, ob);
        addn_temp("apply/defense", bd_power, ob);
        addn_temp("apply/parry", bd_power/3, ob);
        addn_temp("apply/dodge", bd_power/3, ob);
        ob->start_busy((: beidouzhen :), (:halt_beidou:));
}

void check_leaving(object me)
{
        string name=query("id", me);

        if( !userp(me) )
                {
                 object enemy = offensive_target(me);
                 if( !objectp(enemy) && !me->is_busy() && !me->is_fighting() )
                 {
                         message_vision(HIY"\n$N作了個楫道：貧道先告退了！說完就快步離開了。\n"NOR, me);
                         call_out("destruct_me",10,me);
                         return;
                  }

                  call_out("check_leaving",5,me);
          }
}

int beidouzhen(object me)
{
        object *member,ob,where;
        int beidou_time,i,power,ok,mypos;
        object room, obj,enemy,weapon;

        enemy = offensive_target(me);
        beidou_time=query_temp("beidou_time", me);
        where = environment(me);
        mypos=query_temp("bd_pos", me);

        if (beidou_time < 1)
        {
                out_beidou(me);
                return 0;
        }

        if (!objectp(enemy) || environment(enemy) != where)
        {
                out_beidou(me);
                return 0;
        }

        if( query("neili", me)<300 || query("jingli", me)<100 )
        {
                out_beidou(me);
                return 0;
        }

        member = me->query_team();

        if (!member || sizeof(member) < 3 || sizeof(member) > 7)
        {
                out_beidou(me);
                return 0;
        }

        ok = 1;

        for ( i = 0;i < sizeof(member);i++)
        {
                if (environment(member[i]) != where)
                {
                        ok = 0;
                        break;
                }

                if( !query_temp("pending/beidou", member[i]) )
                {
                        ok = 0;
                        break;
                }
        }

        if (!ok)
        {
                out_beidou(me);
                return 0;
        }


        beidou_time = beidou_time-1;
        set_temp("beidou_time", beidou_time, me);

        power=query_temp("bd_power", me);

        if( random(6)==1 )
        {
                tell_room(environment(me), HIR"\n" + zhen[(int)random(4)] +"\n"NOR, this_object());
                if( objectp(enemy) &&
                    objectp(present(query("id", enemy),environment(me))) )
                        enemy->start_busy( random(2) );
        }

        if( random(2)==1 )
        {
                if(random(2)==0)
                        message_vision(WHT"\n" + position[mypos] + "位上的$N氣沉丹田，暗運神功，猛然吐氣開聲，身形往前一縱。\n"NOR, me);
                else
                        message_vision(WHT"\n" + position[mypos] + "位上的$N挺身而出，步法精妙，長袖飄飄，攻勢如虹。\n"NOR, me);

                addn_temp("apply/damage", power, me);
                addn_temp("apply/sword", power/2, me);
                addn_temp("apply/attack", power, me);
                addn("jiali", power, me);
                COMBAT_D->do_attack(me,enemy,query_temp("weapon", me));
                addn_temp("apply/damage", -power, me);
                addn_temp("apply/sword", -power/2, me);
                addn_temp("apply/attack", -power, me);
                addn("jiali", -power, me);
                addn("jingli", -15-random(15), me);
                addn("neili", -20-random(20), me);
        }

        return 1;
}

void restart (object me)
{
        start_beidouzhen(me,query_temp("bd_pos", me),query_temp("beidou_time", me),query_temp("bd_power", me));
}

int halt_beidou(object me)
{
        object weapon;
        int beidou_time=query_temp("beidou_time", me);
        if (beidou_time > 0)
        {
                if( !living(me) ) return 1;

                if(random(2)==1)
                {
                        message_vision(HIG"\n$N踉蹌了一步，差點摔出北鬥陣。\n"NOR, me);
                }
                else message_vision(HIG"\n$N被打的晃了幾晃，不過又站穩了步子。\n"NOR, me);
                call_out("restart",4,me);
                return 1;
        }

        out_beidou(me);
        return 1;
}

void out_beidou(object me)
{
        object weapon;
        int bd_power;

        bd_power=query_temp("bd_power", me);

        if( !objectp(weapon=query_temp("weapon", me)) || 
           query("skill_type", weapon) != "sword" )
                message_vision(HIG"\n$N身子向後一縱，使一招『收山式』，右拳劃了一圈，左掌往懷中一抱，退出「天罡北鬥陣」。\n"NOR, me);
        else
                message_vision(HIG"\n$N身子向後一縱，使一招『收劍式』，將劍挽了一個劍花，往懷中一抱，退出「天罡北鬥陣」。\n"NOR, me);

        addn_temp("apply/defense", -bd_power, me);
        addn_temp("apply/parry", -bd_power/3, me);
        addn_temp("apply/dodge", -bd_power/3, me);
        delete_temp("pending/beidou", me);
        delete_temp("beidou_time", me);
        delete_temp("bd_pos", me);
        delete_temp("bd_power", me);
        return;
}

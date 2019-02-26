#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
string name() { return "火牆"; }

#include "/kungfu/skill/eff_msg.h";
int start_huoqiang(object me);
int check_pfm(object me, object target, object ob);

int perform(object me, object target)
{
        object ob;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if(!target->is_character())
                return notify_fail("看清楚一點，那並不是生物。\n");

        if(!living(target))
                return notify_fail(target->name()+"已經無法戰鬥了。\n");

        if(me->is_busy())
                return notify_fail("你先忙完再説拼命的事。\n");

        if( me->query_skill("chousui-zhang", 1) < 150 )
                return notify_fail("你發現自己的星宿毒掌還不夠嫻熟，無法使用「火牆」進行攻擊。\n");

        if( (int)me->query_skill("huagong-dafa",1) < 150 )
                return notify_fail("你發現自己的化功大法修為不夠，無法使用「火牆」進行攻擊。\n");

        if((int)me->query_skill("poison",1) < 120)
                return notify_fail("你發現自己體內聚毒不夠，無法使用「火牆」進行攻擊。\n");

        if (me->query_skill_prepared("strike") != "chousui-zhang"
        ||  me->query_skill_mapped("strike") != "chousui-zhang")
                return notify_fail("你必須用抽髓掌才能使用「火牆」進行攻擊。\n");

        if( me->query_skill_mapped("force") != "huagong-dafa")
                return notify_fail("你發現自己所用的內功無法進行「火牆」攻擊。\n");

        if( query("max_neili", me)<1000)
                return notify_fail("你發現自己內力實在太弱，無法驅動「火牆」進行攻擊。\n");

        if( query("neili", me)<800)
                return notify_fail("你發現自己現在真氣實在太弱，舉不起「火牆」進行攻擊。\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("你必須空手才能使用「火牆」！\n");

        if(!objectp(ob = present("huo yan", environment(me))))
                return notify_fail("沒有火堆怎麼驅動「火牆」進行攻擊？\n");

        if( query_temp("pfm_chousui", me) )
                return notify_fail("你正在驅動火堆進行攻擊！\n");

        if( query("no_fight", environment(me)) )
                return notify_fail("在這裏好像施展不開！\n");

        message_combatd(BLU"\n$N神色慘淡，伸手打開發髻，長髮下垂，覆在臉上，跟着點燃紅磷粉，咬破舌尖，\n"
                "一口"RED"鮮血"BLU"向火焰中噴去。"HIR"火焰忽地一暗，隨即大為"RED"明亮"HIR"，耀得眾人眼睛也不易睜開。\n\n"NOR,me);

       me->start_busy(3);
       set_temp("pfm_chousui", 1, me);
       if(random(me->query_kar()) > 15)
             check_pfm(me, target, ob);
       else call_out("check_pfm", 2, me, target, ob);
       return 1;
}

int check_pfm(object me, object target, object ob)
{
        string msg;
        int p;

        if(!me) return 0;
        delete_temp("pfm_chousui", me);

        if(!living(me) || me->is_ghost()) return 1;

        if( !target || !living(target) || query("no_fight", environment(me) )
        ||  environment(me)!=environment(target)){
                message_combatd(HIY"$N衣袖再拂，將抬起的"HIR"火牆"HIY"壓回火焰之中。\n"NOR,me);
                return 1;
        }
        if(!objectp(present(ob, environment(me)))){
                message_combatd(HIY"$N眼看火堆熄滅，散開內息。\n"NOR,me);
                return 1;
        }
        addn("neili", -100, me);

        msg = BLU"\n$N猛地身子急旋，如陀螺般連轉了十多個圈子，接着$P大袖拂動，"HIR"整個火焰堆陡地撥起，凌空\n"
              "燃燒，便如一座"RED"火牆"HIR"般，夾着排山倒海之勢向$n壓來！\n"NOR;
        //if( !target->is_killing(query("id", me))) target->kill_ob(me);

        if(random(me->query_str()) > target->query_dex()/2){
                msg += HIY"碧焰映照之下$p微一遲疑，那火牆來得快極，便要撲到身上，$p只得雙掌齊出，\n"
                       "兩股輕風向外送出，衣袖鼓風飄起，勁力已推向那堵綠色的光牆！\n\n" NOR;
                set_temp("huoqiang_target",query("id",  target), me);
                set_temp("huoqiang/period", 1, me);
                set_temp("huoqiang_target",query("id",  me), target);
                set_temp("huoqiang/period", 1, target);

                me->start_busy((: start_huoqiang :));
                target->start_busy((: start_huoqiang :));
                message_combatd(msg, me, target);
                return 1;
        }

        else if(random(me->query_str()) > target->query_dex()/3){
                me->start_busy(4);
                target->start_busy(3);
                msg += HIY"\n$n只嚇目瞪口呆，一怔之間，急忙躍起，但一朵"HIW"火花"HIY"已射到身前，嗤的一聲響，\n"
                       "火花已燒上肚腹。$n“啊”的一聲大叫，落了下來。那團"HIR"大火牆"HIY"也即回入火焰堆中。\n" NOR;
                target->receive_damage("qi", me->query_skill("force"), me);
                p=query("qi", target)*100/query("max_qi", target);
                msg += "( $n"+eff_status_msg(p)+" )\n";
                msg = replace_string(msg, "$l", "肚腹");
                msg = replace_string(msg, "$w", HIW"火花"NOR);
        }
        else {
                me->start_busy(3);
                if( query("neili", me)>10)set("neili", 10, me);
                msg += HIY"$n只嚇目瞪口呆，一怔之間，"HIR"火牆"HIY"已射到身前，急忙躍起，"HIR"火牆"HIY"堪堪從$p足底下飛過！\n" NOR;
        }
        message_combatd(msg, me, target);
        return 1;
}

int start_huoqiang(object me)
{
        string msg, tar;
        object target, ob;
        int neili_lost, period, neili, neili2;

        if(!me) return 0;
        tar=query_temp("huoqiang_target", me);
        target = present(tar, environment(me));
        if (! objectp(target)) return 0;
        neili_lost=30+target->query_skill("force")/10+query("jiali", me)/2+query("jiali", target)/2;
        period=query_temp("huoqiang/period", me);
        neili=query("neili", me);
        neili2=query("neili", target);

        addn("neili", -100, me);
        me->improve_skill("force", random(2));

        if(me->is_ghost()) return 0;
        if(!target || target->is_ghost() || environment(me)!=environment(target)){
                message_combatd(CYN"$N當下內勁一收，的一雙衣袖便即垂下，搖搖幌幌地站了起來。\n"NOR, me);
                return 0;
        }
        if(neili < neili_lost){
                message_combatd(HIY"$N內力消耗殆盡，終因不支倒地！\n"NOR, me);
                me->unconcious();
                return 0;
        }
        if(!living(target) && living(me)){
                msg = HIR"$N雙掌拍出，一道"GRN"碧焰"HIR"吐出，射向$n。$p此刻已無絲毫還手餘地，連站起來逃命的力氣也無。\n"
                      GRN"碧焰"HIR"一射到$p身上，霎時間頭髮衫着火，狂叫慘號聲中，全身都裹入"RED"烈焰"HIR"之中。\n"NOR;
                set_temp("last_damage_from", "被"+me->name()+"殺", target);
                msg += "結果只聽見幾聲喀喀輕響，$n一聲慘叫，像灘軟泥般塌了下去！！\n";
                msg += "( "RED"$n受傷過重，已經有如風中殘燭，隨時都可能斷氣。"NOR")\n";
                message_combatd(msg, me, target);
                target->die(me);
                return 0;
        }
        if(!living(me) && !living(target)){
                message_combatd(HIW"此時$N臉上都已無半點血色，看來已經到了油盡燈枯之時！\n"NOR,me);
                set_temp("last_damage_from", "和"+target->name()+"同歸於盡", me);
                me->die();
                return 0;
        }
        if(!objectp(ob = present("huo yan", environment(me)))){
                message_combatd(HIY"$N眼看火堆熄滅，也慢慢收功，站了起來。\n"NOR,me);
                return 0;
        }


        switch(period) {
        case 3:
        case 9:
        case 15:
        case 21:
        case 27:
        case 33:
        case 39:
        case 45:
        case 51:
        case 57:
        case 63:
        case 69:
        case 75:
        case 81:
        case 87:
        case 93:
        case 99:
        case 115:
        case 145:
        case 175:
        case 205:
                if(neili > neili2){
                        msg = random(2)?HIR"碧焰在一點點向$N的方向移動！\n"NOR:HIR"眼看$N使出全力，試圖將那步步逼進的碧炎推擋回去！\n"NOR;
                        message_combatd(msg,target);
                 }
                 break;
        case 12:
        case 24:
        case 42:
        case 60:
        case 78:
        case 96:
        case 125:
        case 155:
        case 185:
                 if(neili > neili2){
                        msg = random(2)?HIR"$N眼看"GRN"碧焰"HIR"$N使出全力，試圖將那步步逼進的碧炎推擋回去！\n"NOR:HIR"$N眼看"GRN"碧焰"HIR"向自己移來，卻不能開口停送真氣，不然碧焰卷將過來，立時會被活活燒死！\n"NOR;
                        message_combatd(msg, target);
                 }
                 break;
        case 36:
        case 54:
        case 72:
        case 90:
        case 105:
        case 135:
        case 165:
        case 195:
                 if( query("jiali", me)>query("jiali", target)){
                        msg = random(2)?HIR"這片"GRN"碧焰"HIR"在空中略一停滯，便緩緩向$N面前退去，$N大驚，又在舌尖\n"
                              "上一咬，一口"RED"鮮血"HIR"再向火焰噴去，火焰一盛，回了過來！\n"NOR:HIW"$N此時臉上已無半點血色，一口口"RED"鮮血"HIW"不住向火焰中吐去，要將火焰逼回！\n"NOR;
                        message_combatd(msg, me);
                 }
                 break;
        }

        period++;
        set_temp("huoqiang/period", period, me);
        return 1;
}

// youming.c

#include <ansi.h>

#define TRAVERSER "/clone/obj/traverser"

void make_youmin_effect(object me, int range);

int exert(object me, object target)
{
        int level = me->query_skill("linji-zhuang", 1);
        int range ;

        if (level < 180) return notify_fail("你的臨濟十二莊修為還不夠。\n");

        if( query("max_neili", me)<15*level )
                return notify_fail("你的內力還不夠強。\n");

        if( query("neili", me)<15*level )
                return notify_fail("你的真氣不夠。\n");

        write(HIY "你凝聚幽冥二氣，口宣佛號: 阿彌陀佛！一股極細密極悠長的內力從心而發, 直上雲霄！\n" NOR);
        message("vision",
                HIY + "只見" + me->name() + "凝聚幽冥二氣，低眉垂首, 口宣佛號: 阿彌陀佛! 語音雖低卻憾人心肺!\n",
                environment(me), me);

        addn("neili", -15*level, me);
        addn("max_neili", -10, me);

           // decide how far this perform can affect:
        range = 1+(level-180)/4;

        make_youmin_effect(me, range);
        return 1;
}

void hitself(object me, object *bad_guys, int degree)
{
    int i,a0,a1,b0,b1;
    object killer,room;

    for (i=0; i<sizeof(bad_guys); i++) {
        killer = bad_guys[i];
         if (killer == 0) continue;
        a0=query("combat/PKS", killer);
        a1=killer->querry("combat/dietimes");
        b0=query("combat/PKS", me);
        b1=me->querry("combat/dietimes");
        if (a1==0) a1=1;
        if (b0==0) b0=1;
        if (b1==0) b1=1;

        if(random(a0/a1)>random(b0/b1))
        {/*success to let this player hit-self*/
        switch (degree) {
        case 1:   // lightest
            message_vision("$n想起自己所做的種種惡行, 羞慚得兩腮發紅, 提手便照自己打去。\n",
                killer, killer);
              addn_temp("apply/defense", -200, killer);
              addn_temp("apply/dodge", -200, killer);
              addn_temp("apply/parry", -200, killer);
            break;
        case 2:   // medium
            message_vision("$n想起自己過去殺人如麻, 心中一凜, 不禁雙手打顫, 緩緩向自己靈台打下。\n",
                killer, killer);
              addn_temp("apply/defense", -200, killer);
              addn_temp("apply/dodge", -200, killer);
              addn_temp("apply/parry", -200, killer);
              addn_temp("apply/attack", 100, killer);
              addn_temp("apply/damage", 50, killer);
            COMBAT_D->do_attack(killer,killer,query_temp("weapon", killer));
            break;
        case 3:   // hardest
            message_vision("$n仰天歎道: 便似我這等孽障, 活在人間作甚！當下回手往自己死穴猛擊！\n",
                killer, killer);
              addn_temp("apply/defense", -200, killer);
              addn_temp("apply/dodge", -200, killer);
              addn_temp("apply/parry", -200, killer);
              addn_temp("apply/damage", 100, killer);
              addn_temp("apply/attack", 200, killer);
            COMBAT_D->do_attack(killer,killer,query_temp("weapon", killer));
            COMBAT_D->do_attack(killer,killer,query_temp("weapon", killer));
            break;
         }
        COMBAT_D->do_attack(killer,killer,query_temp("weapon", killer));
        if( !killer->is_busy() )
        killer->start_busy(3);
        switch (degree) {
        case 1:   // light
              addn_temp("apply/defense", 200, killer);
              addn_temp("apply/dodge", 200, killer);
              addn_temp("apply/parry", 200, killer);
            break;
        case 2:   // medium
              addn_temp("apply/defense", 200, killer);
              addn_temp("apply/dodge", 200, killer);
              addn_temp("apply/parry", 200, killer);
              addn_temp("apply/attack", -100, killer);
              addn_temp("apply/damage", -50, killer);
            break;
        case 3:   // hardest
              addn_temp("apply/defense", 200, killer);
              addn_temp("apply/dodge", 200, killer);
              addn_temp("apply/parry", 200, killer);
              addn_temp("apply/damage", -200, killer);
              addn_temp("apply/attack", -100, killer);
            break;
         }
        }
        else/*fail to effect this player*/
        {
//        room=environment(me);
//        if( (environment(killer)->query("id"))!= (room->query("id")))
//                /*not in same room*/
//                killer->move(room);
        if (present(me,environment(killer))) {
message_vision(HIR"$N衝着$n破口大罵：就憑你這樣的貨色也敢在我面前指手劃腳，還不給我滾得遠遠的！\n"NOR,killer,me);
//        tell_object(me,HIR"你的正氣不夠壓制對方,反而激怒對手!"NOR);
        me->start_busy(1+random(1));
//        if( !killer->is_killing(me) ) killer->kill_ob(me);
        COMBAT_D->do_attack(killer,me,query_temp("weapon", killer));
        }
        }
    }
}

object *find_bad_guys(object me, object room)
{
    int i, n;
    object killer, *inv, *ret;

    inv = all_inventory(room);
    n=0;
    for (i=0; i<sizeof(inv); i++) {
        killer = inv[i];
        if (killer == me) continue;
        if (userp(killer) && living(killer) &&
            query("combat/PKS", killer)>10 &&
            query("combat/PKS", killer)>query("dietimes", killer)*2 &&
            killer->is_killing(query("id", me)) )
            n++;
    }
    if (n == 0) return 0;
    ret = allocate(n);
    n=0;
    for (i=0; i<sizeof(inv); i++) {
        killer = inv[i];
        if (killer == me) continue;
        if (userp(killer) && living(killer) &&
            query("combat/PKS", killer)>10 &&
            query("combat/PKS", killer)>query("dietimes", killer)*2 &&
            killer->is_killing(query("id", me))){
            ret[n] = killer;
            n++;
          }
    }
    return ret;
}

void stop_fighting(object me, object room)
{
        int i;
        object killer, *inv;

        inv = all_inventory(room);
        for (i=0; i<sizeof(inv); i++) {
                killer = inv[i];
                if (killer->is_fighting()) {
                        killer->remove_all_killer();
                        if( !killer->is_busy() )
                                killer->start_busy(3);
                }
        }
}


//
// We traverse the map within range to make youmin effects, we try to stop
// everybody who fights and if a guy kills too many players (bad guy), he
// will be very upset and may try to hurt himself.
//
// There are 4 cases:
// distance < range/7: bad guys try to hurt self real hard
// distance < range/5: bad guys try to hit self hard
// distance < range/3: bad guys try to hit self
// distance < range: everybody stop fighting
//
// range = (ljz-180)/2, so a 200 lvl player can make it range 10

int visit_room(string room_path, mapping t_info, mapping r_info, mapping data)
{
        int dist, range;
        object me, room, *bad_guys;
        string dist_msg, dist_msg2;

        dist = t_info["dist"];
        if (dist >= 15) return -1; // don't affect more than 15 steps

        room = find_object(room_path);
        if (! objectp(room))  return (dist>=range)?1:0;
        if( query("no_fight", room))return (dist >= range)?1:0;

        me = data["user"];
        range=data["range"];
        bad_guys = find_bad_guys(me, room);
        stop_fighting(me,room);
        if (dist < range) {
            dist_msg = "";
            dist_msg2 = "";
            if (dist > 10) {
                dist_msg="極遙遠處";
                dist_msg2="雖然聲音極遠極輕, 卻令";
            }else if (dist > 5) {
                dist_msg="遠處";
                dist_msg2="雖然聲音不大, 卻令";
            }
            message("vision",
                HIY+"只聽"+dist_msg+me->name()+"口中佛號不絕傳來, 其意大慈大悲, 通幽冥, 越生死, 渾不似人間所有。\n"+
                dist_msg2+"眾人聽的都呆住了, 不自覺地停手罷鬥。\n"+NOR,
                room, me);
            if (bad_guys) {
                if (dist < range/7) {
                    hitself(me, bad_guys, 3);
                }else if (dist < range/5) {
                    hitself(me, bad_guys, 2);
                }else  if (dist < range/3) {
                    hitself(me, bad_guys, 1);
                }
               }
            return 0;
        }
        return 1;
}

void make_youmin_effect(object me, int range)
{
        object traverser;
        mapping data;


        seteuid(getuid());
        traverser = new (TRAVERSER);

        if (! objectp(traverser)) {
                write("youming.c: tell wiz traverser not found!\n");
                return;
        }

        data = ([ "user":me ]);
        data["range"]=range;
        traverser->traverse(base_name(environment(me)), (: visit_room :), data);
        destruct(traverser);
}
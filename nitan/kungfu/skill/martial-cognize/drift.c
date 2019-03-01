// drift.c
// Modified by Dumbness, 2003-5-25 13:24

#include <ansi.h>

inherit F_SSERVER;
int perform(object me, object target)
{
        int i;
        object *inv;
        string *can_perform;

        // ???不明白什麼意思
        can_perform=query("can_perform/martial-cognize", me);
        set("test", can_perform, me);

        if(!arrayp(can_perform) || 
                !sizeof(can_perform) || 
                member_array("drift",can_perform) == -1)
                return notify_fail("你還沒有學會使用天龍之翼！\n");

        if( me->is_fighting() )
                return notify_fail("戰鬥中無法使用天龍之翼！\n");

        if(me->is_busy())
                return notify_fail("你上一個動作還沒有完成，無法使用天龍之翼。\n");
        
        //By Dumbness, 設置了no_drift屬性的房間禁止飛入與飛出
        if( query("no_drift", environment(me)) )
                return notify_fail("這裡禁止使用天龍之翼。\n");

        if( query("jing", me)<300 )
                return notify_fail("你的精神不好！\n");

        if( query("jingli", me)<500 )
              return notify_fail("你的精力不夠！\n");
 
        if( query("max_jingli", me) <= 1000 )
              return notify_fail("你的精力還沒有達到這個層次！\n");

        if( me->is_ghost())
                return notify_fail("鬼魂無法使用天龍之翼！\n");

        if( me->in_prison())
                return notify_fail("監獄裡無法使用天龍之翼！\n");

        if( query("trds", environment(me)) )
                return notify_fail("屠人場裡無法使用天龍之翼！\n");     
        
        if((int) me->query_skill("martial-cognize",1) < 300)
                return notify_fail("你的武學修養不夠高深！\n");

        inv = deep_inventory(me);
        for (i = 0; i < sizeof(inv); i++)
        {
                if (! userp(inv[i]) && ! inv[i]->is_muxiang()) continue;
                if (userp(inv[i]))
                        return notify_fail("你背的是誰？背一個大活人還怎麼飛？\n");
                if (inv[i]->is_muxiang())
                        return notify_fail("你又不是飛機，背著這麼大一個木箱，能飛得動麼？\n");
        }

        inv = 0;
        write("你要移動到哪一個人身邊？");
        input_to( (: call_other, __FILE__, "select_target", me :));
        return 1;
}

void select_target(object me, string name)
{
        object ob;
        int effect;

        if( !name || name=="" ) {
                write("中止使用天龍之翼。\n");
                return;
        }

        ob = find_player(name);
        if( !ob || !me->visible(ob) || wizardp(ob) )
                ob = find_living(name);

        //by rama 修正了可以通過暈倒的大米drift到別人身上get物品的bug
        if( !ob || 
            !living(ob) || 
            !me->visible(ob) || 
            wizardp(ob) || 
            !environment(ob) || 
            !query("max_jingli", ob) || 
            (strsrch(base_name(ob), "/kungfu/class/generate/") == 0 ) ||
            !query("jingli", ob)){
                write("你無法感受到這個人的存在 ....\n");
                write("你要移動到哪一個人身邊？");
                input_to( (: call_other, __FILE__, "select_target", me :));
                return;
        }

        if( environment(ob) == environment(me)) {
                write(ob->name() + "不就正在你身邊嘛 ....\n");
                return;
        }

        //By Dumbness, 設置了no_drift屬性的房間禁止飛入與飛出
        if( query("no_drift", environment(me)) )
        {
                write("這裡禁止使用太龍之翼。\n");
                return;
        }

        if( me->is_fighting() ) {
                write("戰鬥中無法使用天龍之翼！\n");
                return;
        }else if( query("jingli", me)<100){
                write("你的精力不夠！\n");
                return;
        }else if( query("jing", me)<300){
                write("你的精神不好! \n");
                return;
        } else if( me->is_ghost()) {
                write("鬼魂不能使用天龍之翼！\n");
                return;
        } else if( me->in_prison()) {
                write("監獄裡不能使用天龍之翼！\n");
                return;
        }else if( query("trds", environment(me))){
                write("屠人場裡不能使用天龍之翼！\n");
                return;
        }

        effect = random(200);
        addn("jingli", -(100+effect), me);
        me->receive_damage("jing", 100+effect);
        
        if( query("max_jingli", ob)<500){
                write("你感受到了對方的存在，但是不能精確定位。\n");
                return;
        }

        //By Dumbness, 設置了no_drift屬性的房間禁止使用天龍之翼進出
        if( query("no_drift", environment(ob)) || query("no_fight", environment(ob)) )
        {
                write("你想要去的地方不可以用天龍之翼。\n");
                return;
        }

        // 一些特別的區域不允許使用天龍之翼
        if( query("trds", environment(ob)) || 
            strsrch(base_name(environment(ob)),"/data/room/") != -1 ||
            strsrch(base_name(environment(ob)),"/u/") != -1 ||
            strsrch(base_name(environment(ob)),"/d/xiakedao/") != -1 ||
            strsrch(base_name(environment(ob)),"/d/tulong/") != -1 ) {
                write("你想要去的地方不可以用天龍之翼！\n");
                return;
        }

        message_vision( HIY "$N一陣長嘯，渾身彌漫一陣金色雲霧，逐漸在後背匯聚，形成一對金色翅膀，似乎要振翅高飛 ....\n" NOR, me);

        //if( random(ob->query("max_jingli")) > me->query("max_jingli")) {
        //Modified by Dumbness for use effect jingli as conform condition
        if( random(query("max_jingli", ob))>(query("max_jingli", me)>query("eff_jingli", me)?query("max_jingli", me):query("eff_jingli", me))){
                write("你因為不夠熟練而失敗了。\n");
                return;
        }

        /* Sigh, 失敗。鑒于目前華夏已經是一個運行“穩定”地MUD，就算是設計上的失敗，也已經難以
        從本質上作出有效的控制，多次討論並參考一些玩家意見後對天龍之翼地控制嘗試迫于阻力取消，
        原因很大程度上源于玩家的習慣性思維方式很難改變。至此宣布所有有關解體的設想與構思也一並
        取消，本巫師不再對此作任何嘗試。
        //Added by Dumbness for contract with level of skill which named 'martial-cognize'
        if( (random(( (int) me->query_skill("martial-cognize",1)-250)) > 50) 
                 && (query_temp("drift_fail_times", me)<4)){
                addn_temp("drift_fail_times", 1, me);
                write("你因為不夠熟練而失敗了。\n");
                return;
        }
        delete_temp("drift_fail_times", me);
        */
        
        message( "vision", HIY "\n" + me->name() + "輕輕展開雙臂，背後的金色翅膀溫柔的卷起一陣暖風"
                + "，只見" + me->name() + "緩緩升空，瞬間消失得無影無蹤！\n\n" NOR, environment(me), ({ me }) );
        me->move(environment(ob));
        message( "vision", HIY "\n一陣微風吹過，" + me->name() + "宛若天神般緩緩而降，金色的翅膀光芒四射。\n\n" NOR,
                environment(ob), ({ me }) );
}

// xiuxi.c 玉女心經修習exert
// by April 01/08/09
// update April 01/09/22

string *phases = ({
        "你正在修煉玉女心經，真氣運行至“少陰”經“太陰”走“少陽” \n",
        "你終于功至“陽明”，頭上產生微微白氣正是內功到了火候之象！\n",
        "你修煉玉女心經已經有了一段時候，周身白霧絲絲縷縷，漸漸集聚。\n",
        "你加緊運功，真氣行遍全身，練功時發出的熱量變成的白氣漸漸將你籠罩了起來，好象騰雲駕霧一般！\n",
        "你修習玉女心經時間越來越長，頭頂凝聚白氣也越來越多，如同置身于蒸籠之中！\n",
        "你的真氣運行得越來越暢快，身體所發的熱氣也越來越多，已將身體包圍了起來！\n",
        "你只覺得一股股暖流自內而外緩緩發散，心底更加沉寂，無欲無喜。\n",
});

int xiuxi(object me);
int halt_xiuxi(object me);

int exert(object me)
{
        object         where = environment(me);
        int xj_lvl = (int)me->query_skill("yunv-xinfa", 1);        //玉女心經等級
        int force_lvl = (int)me->query_skill("force", 1);                //基本內功等級
        int v,i,j,k;                // 臨時變量
        string *sname;        // skill名字
        object *inv;
        mapping skl;        // 所有skill

        seteuid(getuid());

        return notify_fail("本功能暫時沒有開放！\n");
        
        if( query("pigging", where) )
                return notify_fail("你還是專心拱豬吧！\n");

        if( query("sleep_room", where) )
                return notify_fail("在睡房裡不能練玉女心經，這會影響他人。\n");

        if( query("no_fight", where) )
                return notify_fail("在這裡練玉女心經，你始終心煩意亂，無法克制，只得作罷。\n");

        if( me->is_busy() || query_temp("pending/exercising", me) )
                return notify_fail("你現在正忙著呢。\n");

        if( me->is_fighting() )
                return notify_fail("戰鬥中不能練玉女心經，會走火入魔。\n");

        if( !stringp(me->query_skill_mapped("force")) )
                return notify_fail("你必須先用 enable 選擇你要用的內功心法。\n");

        if( query_temp("is_riding", me) )
                return notify_fail("在坐騎上運功，會走火入魔的。\n");

        // 基本內功小于玉女心經60%不能練
        if( force_lvl < xj_lvl*60/100)
                return notify_fail("你的基本功火候未到，必須先打好基礎才能繼續提高。\n");

        if( me->query_skill_mapped("force") != "yunv-xinfa" )
                return 0;

        // lvl小于25不能練
        if (xj_lvl<25)
                return notify_fail("你試著運了一下體內真氣，顯然玉女心經修為不夠，真氣無法運轉。\n");

        // 必須空手
        if( query_temp("weapon", me) )
        return notify_fail("練習玉女心經必須空手，靜坐誠心方可。\n");

        // 必須裸體
        inv = all_inventory(me);
        for(i=0; i<sizeof(inv); i++)
                if( query("equipped", inv[i] )
                         && query("armor_type", inv[i]) == "cloth" )
                        i = sizeof(inv)+1;
        if (i==sizeof(inv)+2)
        return notify_fail("練習玉女心經必須衣襟敞開方能及時散發熱氣。\n");

        // 四周必須無異性
        inv = all_inventory(environment(me));
        for (i=0; i<sizeof(inv); i++) 
                if( query("race", inv[i]) == "人類"
                        && inv[i] != me && !me->is_spouse_of(inv[i]) 
                         && query("gender", inv[i]) != query("gender", me) )
                return notify_fail("眾目睽睽之下脫光衣裳練功，你不嫌害臊嗎？！\n");

        // 內功要純，否則大傷元氣
        skl=this_player()->query_skills();
        sname=sort_array( keys(skl), (: strcmp :) );
    for(v=0; v<sizeof(skl); v++) {
                if (SKILL_D(sname[v])->check() == "force")
                        k++;
    }
    if ( k >=2 ) {
                // 這裡加傷害
        set("neili", 0, me);
        set("jingli", 50, me);
        set("qi", 50, me);
                i=(query("max_jing", me)*65/100);
                set("eff_jing", i, me);
                return notify_fail("你體內不同內力互相沖撞，翻江倒海，難以克制。 \n"
                        +"你猛一咬牙，狂噴一口熱血，才不至于走火入魔。\n");
        }

        if( query("neili", me)<query("max_neili", me)*60/100 )
                return notify_fail("你體內的真氣不夠修習玉女心經。\n");

        if( query("eff_qi", me)<query("max_qi", me) )
                return notify_fail("你身受內傷，只怕一運真氣便有生命危險！\n");

        if( query("eff_jing", me)<query("max_jing", me) )
                return notify_fail("你中的毒沒完全好，只怕一運真氣便有生命危險！\n");

        if( query("jing", me)<query("max_jing", me)*90/100 )
                return notify_fail("你現在精不夠，無法控制內息的流動！\n");

        if( query("qi", me)<query("max_qi", me)*60/100 )
                return notify_fail("你現在的氣太少了，無法產生內息運行全身經脈。\n");

        // 不能靠練習過關 ---- 30n-1時必須過關
        if ( (xj_lvl<270) && ((xj_lvl+1)/30*30 == xj_lvl + 1) )
                return notify_fail("你繼續練習著玉女心經，忽然體內真氣一滯... \n"
                        +"你似乎遇到了無法突破瓶頸，看來是時候過關了。 \n");

        write("你盤膝坐下，緩緩地長舒一口氣，一股暖流開始在體內流動。\n");

        set_temp("pending/xiuxi", 1, me);
        message_vision("$N盤膝坐下，開始修煉上乘內功。\n", me);
        me->start_busy((: xiuxi :), (:halt_xiuxi:));
        
        return 1;
}

int xiuxi(object me)
{
        int qi_cost;        //氣消耗
        int jingli_cost;        //精力消耗
        int neili_gain;                //內力報酬
        int xj_gain;        //心經報酬
        int sx_gain;        //素心訣報酬
        int xj_lvl = (int)me->query_skill("yunv-xinfa",1);        //心經級別
        int force_lvl = (int)me->query_skill("force",1);        //基本內功級別
        object  where = environment(me);
        object *inv;
        int i;

        if( me->query_skill_mapped("force") != "yunv-xinfa" ){
                set_temp("pending/xiuxi", 0, me);
                return 0;
        }

        if( me->is_fighting() ){
                set_temp("pending/xiuxi", 0, me);
                return 0;
        }

        // 必須裸體
        inv = all_inventory(me);
        for(i=0; i<sizeof(inv); i++)
                if( query("equipped", inv[i] )
                         && query("armor_type", inv[i]) == "cloth" )
                        i = sizeof(inv)+1;
        if (i==sizeof(inv)+2){
        set("neili", 0, me);
        set("jingli", 50, me);
        set("qi", 50, me);
                i=(query("max_jing", me)*65/100);
                set("eff_jing", i, me);
                write("突然，你體內熱氣逐漸積聚，無法發散！熱氣頓時在五臟六腑翻江倒海，難以克制。 \n"
                        +"你猛一咬牙，狂噴一口熱血，才不至于走火入魔。\n");
                set_temp("pending/xiuxi", 0, me);
                return 0;
        }

        // 四周必須無人
        inv = all_inventory(environment(me));
        for (i=0; i<sizeof(inv); i++) 
                if( query("race", inv[i]) == "人類"
                        && inv[i] != me && !me->is_spouse_of(inv[i])
                         && query("gender", inv[i]) != query("gender", me)){
                        write("突然，你發現有人走了過來！\n你慌忙中止練功。\n");
                        set_temp("pending/xiuxi", 0, me);
                        return 0;
                }

        //計算消耗
        neili_gain = 1 + (int)me->query_skill("force") / 8;
        jingli_cost = to_int(sqrt(xj_lvl/to_float(150))*60);
        qi_cost = jingli_cost + neili_gain;

        if( query("qi", me)>query("max_qi", me)*30/100
                 && query("jingli", me)>query("max_jingli", me)*30/100
                && (xj_lvl>270 || (xj_lvl+1)/30*30 != xj_lvl+1) )
        {
                addn("neili", neili_gain, me);
                if( random(2))addn("combat_exp", 1, me);
                xj_gain = to_int(pow(force_lvl/4+1,1.1));
                sx_gain = xj_gain;
                if (!me->is_married()) sx_gain = sx_gain * (1+to_int(sqrt(me->query_skill("lovingness",1)/xj_lvl)));
                me->improve_skill("yunv-xinfa", xj_gain, 0);
                me->improve_skill("suxin-jue", sx_gain, 0);
                write(phases[random(6)]);
                me->receive_damage("qi", qi_cost, "練內功走火入魔死了");
                me->receive_damage("jingli", jingli_cost, "練內功走火入魔死了");

                  if( wizardp(me) ) tell_object(me, "每次得"+chinese_number(neili_gain)+"點內力，"
                        +chinese_number(xj_gain)+"點玉女心經，"
                        +chinese_number(sx_gain)+"點素心訣；\n"
                        +"消耗"+chinese_number(qi_cost)+"點氣，"
                        +chinese_number(jingli_cost)+"點精力。\n");

                return 1;
        }
        else {
                set_temp("pending/xiuxi", 0, me);
                message_vision("$N運功完畢，內息輕吐，神情冷漠地站了起來。\n", me);
                if( query("neili", me)<query("max_neili", me)*2);
                else {
                        if( query("max_neili", me)>me->query_skill("force")*query("con", me)*2/3){
                                write("你的內力修為似乎已經達到了瓶頸。\n");
                                set("neili",query("max_neili",  me), me);
                        }
                        else {
                                addn("max_neili", 1, me);
                                set("neili",query("max_neili",  me), me);
                                write("你的內力增加了！！\n");
                        }
                }
                return 0;
        }
}

int halt_xiuxi(object me)
{
        if( query("neili", me)>query("max_neili", me)*2 )
        set("neili",query("max_neili",  me)*2, me);
        set_temp("pending/xiuxi", 0, me);
        message_vision("$N把正在運行的真氣強行壓回丹田，中止了修煉。\n", me);
        return 1;
}
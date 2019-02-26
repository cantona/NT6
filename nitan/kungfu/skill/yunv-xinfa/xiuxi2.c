// xiuxi.c 玉女心經修習exert
// by April 01/08/09
// update April 01/09/22

#include <ansi.h>

/*
$N同$n修習玉女心經一會的時間，頭上的熱氣漸漸增多。
$N一邊給$n輸送真氣一邊將自己體內真氣運行全身，熱汗從頭頂一點一點滲了出來！
$n受$N真氣的幫助，玉女心經的境界又有了提高，身體被不停產生的白霧漸漸包圍了！
*/

string *phases_me = ({
        "你正在修煉玉女心經，真氣運行至“少陰”經“太陰”走“少陽” \n",
        "你終於功至“陽明”，頭上產生微微白氣正是內功到了火候之象！\n",
        "你修煉玉女心經已經有了一段時候，周身白霧絲絲縷縷，漸漸集聚。\n",
        "你加緊運功，真氣行遍全身，練功時發出的熱量變成的白氣漸漸將你籠罩了起來，好像騰雲駕霧一般！\n",
        "你修習玉女心經時間越來越長，頭頂凝聚白氣也越來越多，如同置身於蒸籠之中！\n",
        "你的真氣運行得越來越暢快，身體所發的熱氣也越來越多，已將身體包圍了起來！\n",
        "你只覺得一股股暖流自內而外緩緩發散，心底更加沉寂，無慾無喜。\n",
});

int xiuxi(object me);
int halt_xiuxi(object me);

int exert(object me, object target)
{
        object         where = environment(me);
        int xj_lvl_me = (int)me->query_skill("yunu-xinjing", 1);        //玉女心經等級me
        int force_lvl_me = (int)me->query_skill("force", 1);                //基本內功等級me
        int xj_lvl_target;         //玉女心經等級target
        int force_lvl_target;                //基本內功等級target
        int v,i,j,k;                // 臨時變量
        string *sname;        // skill名字
        object *inv;        // 身上帶的東西
        mapping skl;        // 所有skill

        seteuid(getuid());

        return notify_fail("本功能暫時沒有開放！\n");
                
        if( !objectp(target) || target == me )
                return notify_fail("你要和誰一起練功啊？\n");

        //非婚男女只能在花房樹屋練功
        if( query("gender", target) != query("gender", me )
                && !me->is_spouse_of(target)
                 && query("short", where) != "花房樹屋" )
                return notify_fail("你們倆在一起練功？羞不羞啊！\n");

        xj_lvl_target = (int)target->query_skill("yunu-xinjing", 1);        //玉女心經等級
        force_lvl_target = (int)target->query_skill("force", 1);                //基本內功等級

        if( query("pigging", where) )
                return notify_fail("你還是專心拱豬吧！\n");

        if( query("sleep_room", where) )
                return notify_fail("在睡房裏不能練玉女心經，這會影響他人。\n");

        if( query("no_fight", where) )
                return notify_fail("在這裏練玉女心經，你始終心煩意亂，無法剋制，只得作罷。\n");

        if( me->is_busy() || query_temp("pending/exercising", me) )
                return notify_fail("你現在正忙着呢。\n");
        if( target->is_busy() || query_temp("pending/exercising", target) )
                return notify_fail("你的夥伴現在正忙着呢。\n");

        if( me->is_fighting() )
                return notify_fail("戰鬥中不能練玉女心經，會走火入魔。\n");
        if( target->is_fighting() )
                return notify_fail("等你的夥伴打完架再説吧。\n");

        if( !stringp(me->query_skill_mapped("force")) )
                return notify_fail("你必須先用 enable 選擇你要用的內功心法。\n");
        if( !stringp(target->query_skill_mapped("force")) )
                return notify_fail("你的夥伴好像不喜歡玉女心經。\n");

        if( objectp(query_temp("is_riding", me)) )
                return notify_fail("在坐騎上運功，會走火入魔的。\n");
        if( objectp(query_temp("id_riding", target)) )
                return notify_fail("還是先讓你的夥伴從坐騎上下來吧。\n");

        // 基本內功小於玉女心經60%不能練
        if( force_lvl_me < xj_lvl_me*60/100)
                return notify_fail("你的基本功火候未到，必須先打好基礎才能繼續提高。\n");
        if( force_lvl_target < xj_lvl_target*60/100)
                return notify_fail("你的夥伴基本功太差了。\n");

        // lvl小於30不能練
        if (xj_lvl_me<30)
                return notify_fail("你試着運了一下體內真氣，顯然玉女心經修為不夠，真氣無法運轉。\n");
        if (xj_lvl_target<30)
                return notify_fail("你的夥伴功力還不夠。\n");

        // 必須空手
        if( query_temp("weapon", me) )
        return notify_fail("練習玉女心經必須空手，靜坐誠心方可。\n");
        if( query_temp("weapon", target) )
        return notify_fail("先讓你的夥伴把兵器放下吧。\n");

        // 必須裸體
        inv = all_inventory(me);
        for(i=0; i<sizeof(inv); i++)
                if( query("equipped", inv[i] )
                         && query("armor_type", inv[i]) == "cloth" )
                        i = sizeof(inv)+1;
        if (i==sizeof(inv)+2)
        return notify_fail("練習玉女心經必須衣襟敞開方能及時散發熱氣。\n");
        inv = all_inventory(target);
        for(i=0; i<sizeof(inv); i++)
                if( query("equipped", inv[i] )
                         && query("armor_type", inv[i]) == "cloth" )
                        i = sizeof(inv)+1;
        if (i==sizeof(inv)+2)
        return notify_fail("你的夥伴看來還不打算練功。\n");

        // 四周必須無異性
        inv = all_inventory(environment(me));
        for (i=0; i<sizeof(inv); i++) 
                if( query("race", inv[i]) == "人類"
                        && inv[i] != me && inv[i] != target
                        && !me->is_spouse_of(inv[i]) 
                         && query("gender", inv[i]) != query("gender", me) )
                return notify_fail("眾目睽睽之下脱光衣裳練功，你不嫌害臊嗎？！\n");

        // 內功要純，否則大傷元氣
        k=0;
        skl=me->query_skills();
        sname=sort_array( keys(skl), (: strcmp :) );
    for(v=0; v<sizeof(skl); v++) {
                if (SKILL_D(sname[v])->check() == "force")
                        k++;  
    }
    if ( k >=2 ) {
                return notify_fail("你感覺體內不同內力互相沖撞，只得作罷。\n");
        }
        k=0;
        skl=target->query_skills();
        sname=sort_array( keys(skl), (: strcmp :) );
    for(v=0; v<sizeof(skl); v++) {
                if (SKILL_D(sname[v])->check() == "force")
                        k++;  
    }
    if ( k >=2 ) {
                return notify_fail("你的夥伴內功不太純啊!\n");
        }

        if( query("neili", me)<query("max_neili", me)*60/100 )
                return notify_fail("你體內的真氣不夠修習玉女心經。\n");
        if( query("neili", target)<query("max_neili", target)*60/100 )
                return notify_fail("你的夥伴真氣不足。\n");

        if( query("eff_qi", me)<query("max_qi", me) )
                return notify_fail("你身受內傷，只怕一運真氣便有生命危險！\n");
        if( query("eff_qi", target)<query("max_qi", target) )
                return notify_fail("你的夥伴身受內傷，先幫他療傷吧！\n");

        if( query("eff_jing", me)<query("max_jing", me) )
                return notify_fail("你中的毒沒完全好，只怕一運真氣便有生命危險！\n");
        if( query("eff_jing", target)<query("max_jing", target) )
                return notify_fail("你的夥伴中的毒沒完全好！\n");

        if( query("jing", me)<query("max_jing", me)*90/100 )
                return notify_fail("你現在精不夠，無法控制內息的流動！\n");
        if( query("jing", target)<query("max_jing", target)*90/100 )
                return notify_fail("你的夥伴現在精不夠，無法控制內息的流動！\n");

        if( query("jingli", me)<query("max_jingli", me)*60/100 )
                return notify_fail("你現在精力不夠，無法控制內息的流動！\n");
        if( query("jingli", target)<query("max_jingli", target)*60/100 )
                return notify_fail("你的夥伴現在精力不夠，無法控制內息的流動！\n");

        if( query("qi", me)<query("max_qi", me)*60/100 )
                return notify_fail("你現在的氣太少了，無法產生內息運行全身經脈。\n");
        if( query("qi", target)<query("max_qi", target)*60/100 )
                return notify_fail("你的夥伴現在的氣太少了，無法產生內息運行全身經脈。\n");

        // 不能靠練習過關 ---- 30n-1時必須過關
        if ( (xj_lvl_me<270) && ((xj_lvl_me+1)/30*30 == xj_lvl_me + 1) )
                return notify_fail("你繼續練習着玉女心經，忽然體內真氣一滯... \n"
                        +"你似乎遇到了無法突破瓶頸，看來是時候過關了。 \n");
        if ( (xj_lvl_target<270) && ((xj_lvl_target+1)/30*30 == xj_lvl_target +1 ) )
                return notify_fail("你的夥伴該過關了。\n");

        if( query_temp("pending/xiuxi", target) != me )
        {
                set_temp("pending/xiuxi", target, me);
                message_vision("\n$N對著$n説道：" 
                        + RANK_D->query_self(me) 
                        + me->name() + "，請問能和"
                        + RANK_D->query_respect(target) + "一起修習玉女心經嗎？\n\n", me, target);
                tell_object(target,YEL"如果你願意和對方一起修習玉女心經，請你也對"+me->name()+"("+query("id", me)+")"+"下一次yunxiuxi2指令。\n"NOR);
                write(YEL "由於對方是由玩家控制的人物，你必須等對方同意才能共同修習玉女心經。\n" NOR);
                return 1;
        }
        else
        {
                message_vision("\n$N和$n解開衣衫，盤膝坐下，四掌相對，開始共同修習玉女心經。\n" , me, target);
                set_temp("pending/target", target, me);
                set_temp("pending/xiuxi", 2, me);
                me->start_busy((: xiuxi :), (:halt_xiuxi:));
                set_temp("pending/xiuxi", 2, target);
                set_temp("pending/target", me, target);
                target->start_busy((: xiuxi :), (:halt_xiuxi:));
        }
        
        return 1;
}

int xiuxi(object me)
{
        int qi_cost;        //氣消耗
        int jingli_cost;        //精力消耗
        int neili_gain;                //內力報酬
        int xj_gain;        //心經報酬
        int love_gain;        //lovingness報酬
        int xj_lvl = (int)me->query_skill("yunu-xinjing",1);        //心經級別
        int force_lvl = (int)me->query_skill("force",1);        //基本內功級別
        float f,g,h;        //可變參數
        string wiz_report;        //巫師報告
        object where = environment(me);        //地理環境
        object target=query_temp("pending/target", me);//夥伴
        int xj_lvl_target = (int)target->query_skill("yunu-xinjing",1);        //夥伴心經級別
        object *inv;
        int i;

        //夥伴停就停
        if( query_temp("pending/xiuxi", target) != 2 )
        {
                message_vision("$N把正在運行的真氣強行壓回丹田，中止了修煉。\n", me);
                set_temp("pending/xiuxi", 0, me);
                set_temp("pending/target", me, me);
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

        if( me->query_skill_mapped("force") != "yunu-xinjing" ){
                set_temp("pending/xiuxi", 0, me);
                set_temp("pending/target", me, me);
                return 0;
        }

        if( me->is_fighting() ){
                set_temp("pending/xiuxi", 0, me);
                set_temp("pending/target", me, me);
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
                write("突然，你體內熱氣逐漸積聚，無法發散！熱氣頓時在五臟六腑翻江倒海，難以剋制。 \n"
                        +"你猛一咬牙，狂噴一口熱血，才不至於走火入魔。\n");
                set_temp("pending/xiuxi", 0, me);
                set_temp("pending/target", me, me);
                return 0;
        }

        inv = all_inventory(environment(me));
        for (i=0; i<sizeof(inv); i++) 
                if( query("race", inv[i]) == "人類"
                        && inv[i] != me && inv[i] != target
                        && !me->is_spouse_of(inv[i]) 
                         && query("gender", inv[i]) != query("gender", me)){
                                write("突然，你發現有人走了過來！\n你們慌忙中止練功。\n");
                                set_temp("pending/xiuxi", 0, me);
                                set_temp("pending/target", me, me);
                                return 0;
                }

        //計算消耗和所得，這是複雜的算法
        neili_gain = 1 + (int)me->query_skill("force") / 8;
        jingli_cost = to_int(sqrt((xj_lvl/to_float(150)))*60);
        qi_cost = jingli_cost + neili_gain;

        if( query("qi", me)>query("max_qi", me)*30/100
                 && query("jingli", me)>query("max_jingli", me)*30/100
                &&         ((xj_lvl>270) || ((xj_lvl+1)/30*30 != xj_lvl+1)))
        {
                addn("neili", neili_gain, me);
                addn("combat_exp", 1, me);
/*
                f=to_float(query("combat_exp", target))/to_float(query("combat_exp", me));
                if (f>=2) f=2;
                else if (f>=0.5) f = to_float(1.8*pow(f-0.5,0.25));
                else f=0;
                xj_gain = to_int(pow(force_lvl/4+1,1.1)*f);
*/
                if (xj_lvl_target > xj_lvl * 2/3 ) xj_gain = to_int(pow(force_lvl/4+1,1.1)*1.5);
                else xj_gain = to_int(pow(force_lvl/4+1,1.1)*1.2);

                if (me->is_spouse_of(target)){
                        xj_gain *= 1.5;
                        love_gain =xj_gain*2;
                }
                else if( query("gender", me) != query("gender", target))xj_gain*=1.2;
                me->improve_skill("yunu-xinjing", xj_gain, 0);
                write(phases_me[random(6)]);
                me->receive_damage("qi", qi_cost, "練內功走火入魔死了");
                me->receive_damage("jingli", jingli_cost, "練內功走火入魔死了");

                wiz_report = "每次得"+chinese_number(neili_gain)+"點內力，"
                        +chinese_number(xj_gain)+"點玉女心經";
                if (me->is_spouse_of(target)){
                        wiz_report = wiz_report+chinese_number(love_gain)+"點雙棲雙飛";
                        me->improve_skill("lovingness", love_gain, 0);
                }
                wiz_report = wiz_report + "; \n 消耗" + chinese_number(qi_cost) + "點氣，"
                        +chinese_number(jingli_cost)+"點精力。\n";

                  if( wizardp(me) ) tell_object(me, wiz_report);

                return 1;
        }
        else {
                set_temp("pending/xiuxi", 0, me);
                message_vision("$N和$n運功完畢，內息輕吐，神態輕鬆地站了起來。\n", me,target);
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
                set_temp("pending/xiuxi", 0, me);
                set_temp("pending/target", me, me);
                return 0;
        }
}

int halt_xiuxi(object me)
{
        if( query("neili", me)>query("max_neili", me)*2 )
        set("neili",query("max_neili",  me)*2, me);
        set_temp("pending/xiuxi", 0, me);
        set_temp("pending/target", me, me);
        message_vision("$N把正在運行的真氣強行壓回丹田，中止了修煉。\n", me);
        return 1;
}

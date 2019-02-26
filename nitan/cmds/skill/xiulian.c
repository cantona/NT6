// xiulian.c

#include <ansi.h>

inherit F_CLEAN_UP;

int mending(object me);
int halt_mending(object me);

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        int lvl;
        object where;
        string msg, sign;

        seteuid(getuid());
        where = environment(me);

        if (! arg) return notify_fail("你要修煉什麼？\n");
                
        if( query("pigging", where) )
                return notify_fail("你還是專心拱豬吧！\n");

        if( !query("no_fight", where) )
                return notify_fail("在這裏修煉？不太安全吧？\n");

        if( !query("sleep_room", where) )
                return notify_fail("你得找一個能夠休息的地方修煉。\n");

        if (me->is_busy())
                return notify_fail("你現在正忙着呢。\n");

        if( query("qi", me)*100/query("max_qi", me)<90 )
                return notify_fail("你現在的氣太少了，無法靜心修煉。\n");

        if( query("jing", me)*100/query("max_jing", me)<90 )
                return notify_fail("你現在的精太少了，無法靜心修煉。\n");

        if( query("neili", me)*100/query("max_neili", me)<90 )
                return notify_fail("你現在的內力太少了，無法靜心閉關。\n");
                
        if (! me->query_skill("yinyang-shiertian"))
                return notify_fail("你連陰陽九轉十二重天還沒有學會，怎麼去修煉？\n");

        if( query("yinyang-shiertian/succeed", me) )
                return notify_fail("你已經將陰陽九轉十二重天修煉到了最高境界！\n");
                                
        lvl = me->query_skill("yinyang-shiertian", 1);                                
        
        switch (arg)
        {
        case "shier":         
        
                if( !query("can_perform/yinyang-shiertian/zhen", me) )
                        return notify_fail("你還沒有修煉成陰陽境界，就想修煉十二重天境界？\n");
                 
                if( !query("can_perform/yinyang-shiertian/jiu", me) )
                        return notify_fail("你還沒有修煉成乾坤境界，就想修煉十二重天境界？\n");
                        
                if (lvl < 1200)
                        return notify_fail("你的陰陽九轉十二重天修為不夠，難以修煉十二重天境界！\n");

                if( query("max_neili", me)<50000 )
                        return notify_fail("你覺得內力頗有不足，看來目前還難以修煉十二重天境界。\n");

                if( query("max_jingli", me)<50000 )
                        return notify_fail("你覺得精力頗有不足，看來目前還難以修煉十二重天境界。\n");

                if( query("max_qi", me)<50000 )
                        return notify_fail("你覺得氣血頗有不足，看來目前還難以修煉十二重天境界。\n");

                if( query("potential", me)-query("learned_points", me)<500000 )
                        return notify_fail("你的潛能不夠，沒法修煉。\n");
                                                                
                msg = "十二重天";
                sign = "shier";
                break;
                
        case "qiankun":        
        
                if( !query("can_perform/yinyang-shiertian/zhen", me) )
                        return notify_fail("你還沒有修煉成陰陽境界，就想修煉乾坤境界？\n");
                 
                if( query("can_perform/yinyang-shiertian/jiu", me) )
                        return notify_fail("你已經修煉成乾坤境界，不必再重複修煉！\n");
                                                        
                if (lvl < 800)
                        return notify_fail("你的陰陽九轉十二重天修為不夠，難以修煉乾坤境界！\n");

                if( query("max_neili", me)<30000 )
                        return notify_fail("你覺得內力頗有不足，看來目前還難以修煉乾坤境界。\n");

                if( query("max_jingli", me)<30000 )
                        return notify_fail("你覺得精力頗有不足，看來目前還難以修煉乾坤境界。\n");

                if( query("max_qi", me)<30000 )
                        return notify_fail("你覺得氣血頗有不足，看來目前還難以修煉乾坤境界。\n");

                if( query("potential", me)-query("learned_points", me)<300000 )
                        return notify_fail("你的潛能不夠，沒法修煉。\n");                        
                        
                msg = "乾坤";
                sign = "qiankun";
                break;
                
        case "yinyang":

                if( query("can_perform/yinyang-shiertian/zhen", me) )
                        return notify_fail("你已經修煉成陰陽境界，不必再重複修煉！\n");
                        
                if (lvl < 500)
                        return notify_fail("你的陰陽九轉十二重天修為不夠，難以修煉陰陽境界！\n");

                if( query("max_neili", me)<10000 )
                        return notify_fail("你覺得內力頗有不足，看來目前還難以修煉陰陽境界。\n");

                if( query("max_jingli", me)<10000 )
                        return notify_fail("你覺得精力頗有不足，看來目前還難以修煉陰陽境界。\n");

                if( query("max_qi", me)<10000 )
                        return notify_fail("你覺得氣血頗有不足，看來目前還難以修煉陰陽境界。\n");

                if( query("potential", me)-query("learned_points", me)<100000 )
                        return notify_fail("你的潛能不夠，沒法修煉。\n");                        
                
                msg = "陰陽";
                sign = "yinyang";
                break;
                
        default:
                return notify_fail("你想要修煉什麼？！\n");                
        }


        message_vision("$N盤膝坐下，開始冥神運功，閉關修行陰陽九轉十二重天。\n", me);
        set("startroom", base_name(where), me);
        set("doing", "xiulian", me);
        set("yinyang-shiertian/xiulian", sign, me);
        CLOSE_D->user_closed(me);
        me->start_busy(bind((: call_other, __FILE__, "mending" :), me),
                       bind((: call_other, __FILE__, "halt_mending" :), me));
        CHANNEL_D->do_channel(this_object(), "rumor",
                              sprintf("%s%s(%s)開始閉關修行，試圖修煉陰陽九轉十二重天的" + msg + "境界。",
                              ultrap(me) ? "大宗師" : "",
                              me->name(1),query("id", me)));

        return 1;
}

int continue_mending(object me)
{
        me->start_busy(bind((:call_other, __FILE__, "mending" :), me),
                       bind((:call_other, __FILE__, "halt_mending" :), me));
        CLOSE_D->user_closed(me);
        tell_object(me, HIR "\n你繼續閉關修行陰陽九轉十二重天...\n" NOR);
        return 1;
}

private void stop_mending(object me)
{
        CLOSE_D->user_opened(me);
        if (! interactive(me))
        {
                me->force_me("chat* sigh");
                call_out("user_quit", 0, me);
        }
}

int mending(object me)
{
        string msg = "";

        if( query("potential", me) <= query("learned_points", me) )
        {
                tell_object(me, "你的潛能耗盡了。\n");
                message_vision("$N睜開雙目，緩緩吐了一口氣，站了起來。\n", me);
                msg = "退出";
        }
        
        switch(query("yinyang-shiertian/xiulian", me) )
        {
        case "shier":
        
                if( query("max_qi", me)<10000 || query("max_neili", me)<10000
                 || query("max_jingli", me)<2000 )
                {
                        tell_object(me, "你的狀態不佳，無法繼續修煉陰陽九轉十二重天。\n");
                        message_vision("$N睜開雙目，緩緩吐了一口氣，站了起來。\n", me);
                        msg = "退出";
                }
                set("max_qi",query("max_qi",  me)-2, me);
                set("max_neili",query("max_neili",  me)-2, me);
                set("max_jingli",query("max_jingli",  me)-1, me);
                
                break;

        case "qiankun":
        
                if( query("max_jingli", me)<2000 )
                {
                        tell_object(me, "你的狀態不佳，無法繼續修煉陰陽九轉十二重天。\n");
                        message_vision("$N睜開雙目，緩緩吐了一口氣，站了起來。\n", me);
                        msg = "退出";
                }
                set("max_jingli",query("max_jingli",  me)-1, me);
                
                break;

        case "yinyang":

                if( query("max_neili", me)<2000 )
                {
                        tell_object(me, "你的狀態不佳，無法繼續修煉。\n");
                        message_vision("$N睜開雙目，緩緩吐了一口氣，站了起來。\n", me);
                        msg = "退出";
                }
                set("max_neili",query("max_neili",  me)-1, me);
                
                break;
        }       

        if( query("neili", me)<query("max_neili", me) )
                set("neili",query("max_neili",  me), me);

        if( query("eff_jingli", me)<query("max_jingli", me) )
                set("eff_jingli",query("max_jingli",  me), me);

        if( query("eff_qi", me)<query("max_qi", me) )
                set("eff_qi",query("max_qi",  me), me);

        if (msg == "退出")
        {
                CLOSE_D->user_opened(me);
                CHANNEL_D->do_channel(this_object(), "rumor",
                        sprintf("聽説%s(%s)閉關修煉陰陽九轉十二重天結束，似乎沒有太大的進展。",
                                me->name(1),query("id", me)));

                if (! interactive(me))
                {
                        me->force_me("chat* sigh");
                        call_out("user_quit", 0, me);
                }
                return 0;
        }
        
        addn("learned_points", 1, me);


        if (random(10) == 0)
                tell_object(me, "修煉陰陽九轉十二重天中...\n");

        if (random(4000000) < me->query_skill("yinyang-shiertian", 1))
        {
                tell_object(me, HIR "恭喜你對陰陽九轉十二重天有新的領悟，武學境界又有突破！\n" NOR);
 
                if( query("yinyang-shiertian/xiulian", me) == "shier" )
                {
                        addn("yinyang-shiertian/shier", 1, me);
                        if( query("yinyang-shiertian/shier", me) == 12 )
                        {
                                delete("yinyang-shiertian", me);
                                set("yinyang-shiertian/succeed", 1, me);
                                set("can_perform/yinyang-shiertian/tian", 1, me);
                                set("potential",query("learned_points",  me), me);
                                CHANNEL_D->do_channel(this_object(), "rumor",
                                                sprintf("聽説%s(%s)領悟到了陰陽九轉十二重天的「十二重天」，窺視到了無上的武學境界。",
                                                                me->name(1),query("id", me)));
                                CHAR_D->setup_char(me);
                                stop_mending(me);
                                return 0;
                        }
                
                }

                if( query("yinyang-shiertian/xiulian", me) == "qiankun" )
                {
                        addn("yinyang-shiertian/jiu", 1, me);
                        if( query("yinyang-shiertian/jiu", me) == 9 )
                        {
                                delete("yinyang-shiertian", me);
                                set("can_perform/yinyang-shiertian/jiu", 1, me);
                                set("potential",query("learned_points",  me), me);
                                CHANNEL_D->do_channel(this_object(), "rumor",
                                                sprintf("聽説%s(%s)領悟到了陰陽九轉十二重天的「九轉乾坤」，武學境界又有突破。",
                                                        me->name(1),query("id", me)));
                                CHAR_D->setup_char(me);
                                stop_mending(me);
                                return 0;
                        }                
                }
        
                if( query("yinyang-shiertian/xiulian", me) == "yinyang" )
                {
                        switch(query("yinyang-shiertian/zhen", me) )
                        {
                        case "yinyang":
                                delete("yinyang-shiertian", me);
                                set("can_perform/yinyang-shiertian/zhen", 1, me);
                                set("potential",query("learned_points",  me), me);
                                CHANNEL_D->do_channel(this_object(), "rumor",
                                        sprintf("聽説%s(%s)領悟到了陰陽九轉十二重天「鎮陰陽」，武學境界又有突破。",
                                                me->name(1),query("id", me)));
                                CHAR_D->setup_char(me);
                                stop_mending(me);
                                return 0;

                        case "yin":
                                delete("yinyang-shiertian/zhen", me);
                                set("yinyang-shiertian/zhen", "yinyang", me);
                                break;

                        default:
                                set("yinyang-shiertian/zhen", "yin", me);
                        }
                } 

                CHANNEL_D->do_channel(this_object(), "rumor",
                                      sprintf("聽説%s(%s)經過閉關苦修，對陰陽九轉十二重天有新的領悟。",
                                              me->name(1),query("id", me)));

                me->improve_skill("yinyang-shiertian", 250000);
        }

        if( query("yinyang-shiertian/xiulian", me) == "shier" )
        {
                switch (random(4))
                {
                case 0:
                        msg = "隨着時間的流逝，$N頭頂蒸騰出陣陣白色煙霞，剎那間，"
                              "異香四散飄開，原來的渾濁污穢之氣全被驅散，只留下心曠神怡的清新與芬芳。\n";
                        break;

                case 1:
                        msg = "$N頂上的那股白霧舒捲不定，彷彿什麼都不是，但若仔細看時，"
                              "卻是在不斷地幻化成世間萬物的種種神態，但其中好像有什麼東西卻是不變的。\n";
                        break;

                case 2:
                        msg = "那股白霧再度變換姿態，逐漸地沉了下去，裹住$N的身形，"
                              "不停地在$N的周圍轉動，速度越來越快，遠遠望去，像是一條白龍圍着$N的身形撒歡。\n";
                        break;

                default:
                        msg = "$N的嘴角微微上翹，盪漾出一陣笑意在臉頰上，周圍的白霧隨着笑意"
                              "的流淌慢慢地變淡了，變沒了，只是$N的眼神裏平添了一分光華。\n";
                        break;
                }
        }
                
        if( query("yinyang-shiertian/xiulian", me) == "qiankun" )
        {
                switch (random(5))
                {
                case 0:
                        msg =  "$N想了想，説了一聲“山”，然後便一動不動地佇立於天地間，"
                               "整個人從內到外都處於一種極靜止的狀態，任世間怎樣的動盪，也決不動搖半分。\n";
                        break;

                case 1:
                        msg = "$N想了想，説了一聲“水”，身形還是在那裏不動分毫，但是旁人"
                              "看來$N好像是一朵雪花，一直在飄搖不定，竟無法"
                              "捕捉住$N的影子。\n";
                        break;

                case 2:
                        msg = "$N想了想，説了一聲“風”，只見周圍地上的落葉漸漸地被捲起，"
                              "無助的在半空中飄着，可是$N卻感覺不出風自哪個方向"
                              "掠過$N的胸膛。\n";
                        break;

                case 3:
                        msg = "$N忽然長笑三聲，一種看穿一切的自信流露在一投手、一舉足之中，"
                              "顯見得胸中自有丘壑，不與人同。\n";
                        break;

                default:
                        msg = "$N突然伸出手在半空中劃了一道痕跡，那道痕跡彷彿山那般極靜，"
                              "又如水那樣極動，更像風似的極變，它藴含了天地間的至理，一切都在循環變動"
                              "中往復。\n";
                        break;
                }
        }

        if( query("yinyang-shiertian/xiulian", me) == "yinyang" )
        {
                if( query("yinyang-shiertian/zhen", me) == "yin" )
                        msg = "$N腳下不丁不八，倚着渾厚的大地身形凝重如山，一股寒陰之氣"
                              "自地底極深處傳入$N的四經八脈。\n";
                else
                if( query("yinyang-shiertian/zhen", me) == "yinyang" )
                {
                        if (random(2) == 1)
                                msg = "$N臉色紅白不定，雙目顏色也變了樣，一瞳含火，鮮紅欲滴，"
                                      "一瞳含冰，秋霜不化，良久方自散去。\n"; 
                        else
                                msg = "$N周身中，寒陰之氣盤旋於經脈之間，唯獨心神處熾熱不變，"
                                      "一個恍惚，玄陽之氣卻進入經脈，寒陰之氣倒守護在心神左右。\n";
                }
                else
                        msg = "$N運目逼視光芒四射的紅日，化神為虛，竟不覺如何的刺眼，"
                              "一道玄陽之氣於頭頂間散落於空中再復回到$N的心間。\n";                
        }

        message_vision(msg, me);
        return 1;
}

int halt_mending(object me)
{
        CLOSE_D->user_opened(me);
        tell_object(me, "你中止了修煉陰陽九轉十二重天。\n");
        message_vision(HIY "$N" HIY "輕輕歎了一口氣，緩緩的睜開眼。\n\n" NOR, me);
        addn("potential", (query("learned_points", me)-query("potential", me))/2, me);
        CHANNEL_D->do_channel(this_object(), "rumor", "聽説" + me->name(1) +
                              "修煉陰陽九轉十二重天中途突然復出。");
        return 1;
}

private void user_quit(object me)
{
        if (! me || interactive(me))
                return;

        me->force_me("quit");
}

int help(object me)
{
        write(@HELP
指令格式 : xiulian

修煉境界乃是將自身的武學境界融入陰
陽九轉十二重天當中，陰陽九轉十二重
天在來世當中從某中意義上來説已經不
算是一種單純的武學招式，而是一種武
學境界，因為其乃天下最厲害的幾種武
學演練而成，其威力可想而知，所以不
能靠單純的幾招幾式來體現出其整體，
所以需要修煉出幾種特殊的境界，只有
擁有者將這幾種境界修煉成功後，方能
將陰陽九轉十二重天發揮自如。

HELP );
        return 1;
}
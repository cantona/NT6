// Room: /d/xingxiu/shiguan.c
// Last Modified by Winder on Apr. 25 2001

#include <ansi.h>
inherit ITEM;

int start_liandu(object me);
int halt_liandu(object me);
void create()
{
        set_name(HIM"石棺"NOR, ({ "shi guan", "coffin", "shi", "guan"}) );
        set_weight(30000000);
        set_max_encumbrance(200000);
        if( clonep() )
                set_default_object(__FILE__);
        else{
                set("no_carry",1);
                set("no_get_from",1);
                set("no_put",1);
                set("unit", "張");
                set("long", "這是一張用整塊巨石鑿空而製成的石棺，上面殘留了一些"RED"血跡"NOR"，
散發出的一股腐爛氣味，瀰漫了整個山洞。\n");
                set("material","stone");
                set("no_get",1);
                set_temp("poison_type", "陰");
        }
        setup();
}

void init()
{
        add_action("do_liandu", "liandu");
}

void over_liandu(object ob)
{
        object corp;
        remove_call_out("over_liandu");
        delete_temp("liandu", ob);
        if(objectp(corp = present("corpse", ob)))
        {
                if( query_temp("liandued", ob) )
                        message_vision("\n$N"RED"裏腐爛的屍體猶如一隻泄了氣的皮球一樣，慢慢開始萎縮，最後只剩下一小片血跡在棺底！\n"NOR, ob);
                else message_vision("\n$N"RED"裏腐爛的屍體“膨”的一下爆裂開來，濺得到處都是血跡！\n"NOR, ob);
                destruct(corp);
                delete_temp("liandued", ob);
        }
}

int do_liandu()
{
        int liandu_cost, neili_lost, times;
        object ob, me, corp;

        ob = this_object();
        me = this_player();

        if( !query_temp("liandu", ob))return 0;
        if( query_temp("liandu_target", ob) != query("id", me) )
                return notify_fail("你的手掌剛剛伸出，卻被一股無形的大力給震了回來。\n");
        if(!objectp(corp = present("corpse", ob)))
                return notify_fail("你要拿什麼煉毒？\n");
        if (me->is_busy())
                return notify_fail("你現在正忙着呢。\n");
        if( me->is_fighting() )
                return notify_fail("戰鬥中煉毒？只怕你還沒那造詣吧？\n");
        if(me->query_condition("xx_liandu"))
                return notify_fail("你剛剛煉毒完成不久，頻繁煉毒會有生命危險的！\n");
        if( query("neili", me)<query("max_neili", me)/2 )
                return notify_fail("你現在的內力不足，強制煉毒會很危險的。\n");
        if( query("jing", me)*100/query("max_jing", me)<70 )
                return notify_fail("你現在精不夠，這樣下去會很危險的！\n");
        
        if (me->query_skill_mapped("force") != "huagong-dafa" ||
        me->query_skill_mapped("strike") != "chousui-zhang")
                return notify_fail("你沒有使用星宿武功，無法煉毒。\n");                                                                                 
        if( query("max_neili", me)<1000 )
                return notify_fail("你的內力太弱，強制煉毒會很危險的！\n");
        if( objectp(query_temp("weapon", me)) )
                return notify_fail("煉毒時需要雙手的配合，所以你最好還是不要拿武器。\n");

        write(BLU"你開始凝神運氣，將化功大法功力滿布全身。\n"NOR);
        tell_room(environment(me), BLU+me->name()+"臉色忽然變為紫青，雙目閃爍出陰陰的藍光。\n"NOR, ({ me }));
        
        neili_lost = (int)me->query_skill("force")/10 + me->query_skill("poison")/4;
        times=query("neili", me)/neili_lost;
        set_temp("pending/liandu", 1, me);
        set_temp("liandu_times", times, me);
        set_temp("liandu/period", 1, me);
        set_temp("liandu", 1, ob);
        call_out("over_liandu",query("neili", me)/10,ob);
        me->start_busy((: start_liandu :), (:halt_liandu:));
        return 1;
}

int start_liandu(object me)
{
        string force;
        int neili_lost = (int)me->query_skill("force")/10 + me->query_skill("poison")/4;
        int times=query_temp("liandu_times", me);
        int period=query_temp("liandu/period", me);
        
        addn("neili", -neili_lost, me);
        me->receive_damage("qi", 5+random(10));
        me->improve_skill("poison", 1);
        switch(period) {
        case 1:
                write("你將內力聚於三焦，舌根微微上抬，雙掌平伸按在腐爛的屍體上。\n");
                tell_room(environment(me), "只見"+me->name()+"輕吸了口氣，雙掌平伸，按在石棺內腐爛的屍體上。\n",({ me }));
                break;
        case 3:
                write("你急催化功大法，將體內的毒素和功力順手臂直傳到腐爛的屍體上。\n");
                break;
        case 5:
                write(HIY"腐屍內的毒素開始緩緩聚於一點，並順着你的手掌向你侵來。\n"NOR);
                break;
        case 11:
                write(YEL"你全身放鬆，將內息自丹田循任脈引向會陰穴，引導那毒素向氣海而去。\n"NOR);
                tell_room(environment(me), YEL+me->name()+"雙掌成爪，一股股青氣從指尖透出，直插在腐屍的膻中穴上，好像在吸取什麼。\n"NOR,({ me }));
                me->improve_skill("force", me->query_con());
                break;
        case 21:
                write(HIY"\n你雙掌遊動，指尖扣住腐屍的肺手太陰之脈。功力起於中焦，下絡大腸，還循胃口，橫出腋下，
行少陰心主之前，循臂內上骨下廉，入寸口，上魚，左指勁力循魚際，出大指之端，右指勁力直
出次指內廉，出其端，復匯於中焦。\n"NOR);
                tell_room(environment(me), CYN+me->name()+"雙手遊動，又扣住了腐屍的肺手太陰之脈。\n"NOR,({ me }));
                break;
        case 31:
                write(HIY"\n腐屍內的毒素越聚越密。你雙爪晃過，內力注入其手陽明之脈，起於大指次指之端，循指上廉，
出合谷兩骨之間，上入兩筋之中，循臂上廉，上肩，上出於柱骨之會上，下入缺盆絡肺；其支者，
從上頸貫頰，入下齒中，還出挾口，交人中，左之右，右之左，上挾鼻孔，將內息會引，流向氣
海。\n"NOR);
                tell_room(environment(me), CYN+me->name()+"吐氣吹向腐屍，只見其片片肌膚隨風滑落，脛骨卻包裹着一層淡淡的青氣！\n"NOR,({ me }));
                break;
        case 41:
                write(HIY"\n你再將雙掌按在腐屍三焦手少陽之脈處，一吐一引，過其陽池，外關，上出兩指之間，出臂外兩骨
之間，上肩而交出足少陽之後，入缺盆，布膻中，散絡心胞；又從膻中上出缺盆，上項，直上出耳
上角，以屈下頰至；又從耳後入耳中，出走耳前，交頰。三路合於一處！\n"NOR);
                tell_room(environment(me), CYN+me->name()+"雙掌如畫太極般划動，只見腐屍上所呈現的青色開始慢慢聚合於其胸口，其色甚陰！\n"NOR,({ me }));
                me->improve_skill("force", me->query_dex());
                break;
        case 51:
                write(YEL"你雙掌平抬，凌空運氣，開始匯聚腐屍於奇經八脈之毒氣！\n"NOR);
                tell_room(environment(me), HIY+me->name()+"雙掌平抬，凌空運氣，一條條青線圍繞著石棺飄動着，倍顯陰森！\n"NOR,({ me }));
                break;
        case 61:
                write(BLU"入任脈，起於中極之下，以上毛際，循腹裏，上關元，至咽喉，上頤循面，入目絡舌！\n"NOR);                
                break;
        case 71:
                write(BLU"入陽脈者，起於跟中，循外踝，上行入風池！\n"NOR);                
                break;
        case 81:
                write(BLU"入陰脈，起於跟中，循內踝，上行至咽喉，交貫衝脈！\n"NOR);                
                break;
        case 91:
                write(BLU"入陽維脈，起於外踝下的金門穴處，循行於下肢，上行到額部陽白穴處！\n"NOR);                
                break;
        case 121:
                write(BLU"入陰維脈，起於內踝上的築賓穴，上行到頷下的廉泉穴處！\n"NOR);                
                break;
        case 141:
                write(BLU"入衝脈者，起於氣衝，並足陽明之經，夾臍上行，至胸中而散也！\n"NOR);                
                break;
        case 161:
                write(BLU"入帶脈者，起於季脅，回身一週！\n"NOR); 
                me->improve_skill("force", me->query_con());
                addn("max_neili", 1, me);
                break;
        case 201:
                write(RED"豁然間，你感覺到那具屍體就象消失了重量一樣，在你內力的催動下緩緩飄浮了起來！\n"NOR);
                tell_room(environment(me), RED"突然，那具屍體就象消失了重量一樣，在"+me->name()+"內力的催動下緩緩飄浮了起來！\n"NOR,({ me }));
                break;
        }

        if( query("neili", me)<0 || query("jingli", me)<0 )
        {
                write(GRN"突然間，你感覺到自己丹田中已經空空如也，大驚之下竟被陰寒的毒素順勢而上直抵肺腑！\n"NOR);
                tell_room(environment(me), GRN"突然間，你看見"+me->name()+"全身發顫，一股青氣竟然從石棺裏自下而上直衝到"+me->name()+"的前胸！\n"NOR,({ me }));
                set("neili", 0, me);
                me->apply_condition("xx_liandu", 10 + random(50));
                over_liandu(this_object());
                me->unconcious();
                return 0;
        }

        if(period==times)
        {
                write(HIW"\n猛地，你感覺到一股至陰的毒氣順手臂襲來，竟然透過你的內勁直抵丹田！\n"NOR);
                write(HIW"這一瞬間，你發覺那至陰的毒氣和自己體內原本的毒氣相互融合，一同歸納進了氣海！\n"NOR);
                tell_room(environment(me),HIY+me->name()+"緩緩收回雙掌，籠罩着全身的青氣也隨之消散了。\n"NOR, ({ me }));
                if(me->query_skill("poison", 1) < 180)
                        me->improve_skill("poison",times*neili_lost/2*query_temp("liandu", this_object()));
                if(me->query_skill("huagong-dafa", 1) < 200)
                        me->improve_skill("huagong-dafa", me->query_con()*3);
                me->apply_condition("xx_liandu", 200 + random(200));
                set_temp("liandued", 1, this_object());
                over_liandu(this_object());
                return 0;
        }
        period++;
        set_temp("liandu/period", period, me);
        return 1;        
}

int halt_liandu(object me)
{
        me->start_busy(1 + random(4));
        if(!wizardp(me))
                me->apply_condition("xx_liandu", 10 + random(50));
        if(living(me))
                message_vision("\n$N輕喝一聲，吐氣納精，把雙掌從石棺上急急收回。\n", me);        
        over_liandu(this_object());
        return 1;
}
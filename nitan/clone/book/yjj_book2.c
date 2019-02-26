//rama@sz
//易筋經殘篇

inherit BOOK;

int do_xiulian();
int finish(object me);

void setup()
{}
void init()
{
        add_action("do_xiulian", "xiulian");
        add_action("do_xiulian", "xiu");
}

void create()
{
        set_name("易筋經殘篇", ({ "yijinjing" }));
        set_weight(600);
              set("no_drop",1);
              set("no_get",1);
              set("no_steal",1);
        if( clonep() )
        set_default_object(__FILE__);
        else
        {
                set("unit", "本");
                set("long", "這是一本梵文經書，每一頁上都寫彎彎曲曲的文字，沒一個識得。\n");
                set("value", 5000);
                set("material", "paper");
                
        }
}

int do_xiulian()
{
        object me,ob;
        object where_1;
        int poison_lvl;
        me=this_player();
        if(!me->query_skill("poison",1))
        return notify_fail("你連基本的毒功都不會，還想領略這麼高深的技巧？\n");
         
        poison_lvl = me->query_skill("poison",1);
               
        where_1 = environment(me);

        if (!present("yijinjing", me))
                return 0;
                
        if( me->is_busy() )
             return notify_fail("你正忙着呢！\n");       
        if( query("pigging", where_1) )
                return notify_fail("你還是專心拱豬吧！\n");

        if( query("sleep_room", where_1) )
                return notify_fail("不能在睡房裏修煉，這會影響他人。\n");

        if( query("no_fight", where_1) )
                return notify_fail("這裏空氣不好，還是找別處吧！\n");

        if( query("name", where_1) == "大車裏" )
                return notify_fail("車裏太顛簸, 修練會走火入魔. \n");

        if( me->is_busy() || query_temp("pending/exercising", me) )
        if( me->is_fighting() )
                return notify_fail("戰鬥中不能修煉，會走火入魔。\n");

        if( query_temp("is_riding", me) )
                return notify_fail("在坐騎上修練，會走火入魔。\n");

        if( query("canewhua", me) == 1 )
                return notify_fail("你無法再從這本書上學到任何新東西了。\n");

        if( !stringp(me->query_skill_mapped("force")) || me->query_skill_mapped("force") != "huagong-dafa")
                return notify_fail("你必須先用 enable 化功大法。\n");

        if (poison_lvl < 250) 
                return notify_fail("第一頁上面的一些用毒技巧，你怎麼也領略不了，看來你的毒功還有待加強。");
        
        if(present("yijinjing",me) && !present("shenmuwang ding",me))
        {
                write("你開始按照定春秋教你的獨特練功方法調息打坐。\n");
                if(random(4)==1){
                        write("沒有神木王鼎的幫助，你根本無法控制住自己的氣，你只覺得體內橫衝直撞，你有些神智不清了！\n");
                        write("你哇的吐出一口鮮血，你只覺得意識在慢慢的消失！\n");
                        set_temp("die_reason", "修煉易筋經殘扁，走火入魔死了", me);
                        me->receive_damage("qi",query("eff_qi", me)+200);
                        return 1;
                }
                else
                me->start_busy(30);
                call_out("finish",60);
                return 1;
        }

        ob=present("shenmuwang ding",me);
        if( query("fake", ob) || query("item_make", ob) )
        {
                return notify_fail("你試了半天，神木王鼎沒有半點動靜，看來是個假貨！\n");
        }

        write("你開始按照易筋經上面獨特的練功方法開始調息打坐。\n");
        write("神木王鼎也冒出了裊裊的清煙，一切都讓你你覺得和諧極了，慢慢的甚至忘記了自我的存在。\n");
        if( random((200/query("int", me)))>3 )
        {
                write("忽然你覺得腦子裏面有些混亂，好像哪個地方不對了！\n");
                write("你哇的吐出一口鮮血，你只覺得意識在慢慢的消失！\n");
                me->receive_damage("jing",30);
                me->receive_damage("qi",100);
                me->start_busy(30);
                return 1;
        }
        else
        {
                 me->start_busy(30);
                call_out("finish",60);
        }
        return 1;
}

int finish(object me)
{
        me=this_player();
        write("你只覺得渾身上下舒暢無比，不由暗自歎道：“真不愧是易筋經！”\n");
        me->clear_condition("bingcan_poison",5);
        if( query("yijinjing", me)<1 )
        {
                set("yijinjing", 1, me);
        }
        addn("yijinjing", 1, me);
        if( query("yijinjing", me) >= 10 )
        {
                write("你心台忽然一片明朗，多日來的疑慮一掃而空！你領悟出了化功大法真正精髓的所在！\n");
                delete("yijinjing", me);
                set("canewhua", 1, me);
                set("huagong_hua", 1, me);
                me->clear_condition("bingcan_poison");
                return 1;
                //學會yun hua
         }
         return 1;
}

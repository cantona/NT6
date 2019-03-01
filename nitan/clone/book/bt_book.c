// bt_book.c 歐陽鋒手跡
// Last Modified by Winder on May. 15 2001

#include <ansi.h>

inherit ITEM;
void setup()
{}

void init()
{
        add_action("do_du", "du");
        add_action("do_du", "study");
        add_action("do_du", "read");
}

void create()
{
        set_name("線裝書", ({ "xianzhuang shu", "shu", "book", "xianzhuang"}));
        set_weight(600);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long", "一本薄薄的線裝書。封面上寫有“白駝歐陽鋒”幾個字。\n");
                set("value", 1);
                set("material", "paper");
                set("no_drop", "這樣東西不能離開你。\n");
                set("no_get", "這樣東西不能離開那兒。\n");
        }
}

int do_du(string arg)
{
        object ob, me = this_player();
        mapping skill;
        int level, neili_lost;

        if (me->is_busy())
        {
                write("你現在正忙著呢。\n");
                return 1;
        }
        if( me->is_fighting() )
        {
                write("你無法在戰鬥中專心下來讀書！\n");
                return 1;
        }
        if( !me->query_skill("literate", 1) )
        {
                write("你是個文盲，先學點文化(literate)吧。\n");
                return 1;
        }
        if (arg=="xianzhuang shu" || arg=="shu")
        {
                write( "白駝秘要，分制藥(zhiyao)、練功(liangong)、圖解(tujie) 和功夫(gongfu)。\n");
                set_temp("baituo_book", 1, me);
                return 1;
        }
        if( arg == "zhiyao" && query_temp("baituo_book", me) )
        {
                tell_object(me, "\n
制藥：
  汝可于我藥房之中找到各種制藥器具及草藥，
  而要制成絕世之藥，非得另找原料。

  鶴紅丹：以毒攻毒可克我白駝怪蛇之奇毒。雖是如此，也將消耗內力真元。
          原料：新鮮鶴頂紅一個，腹蛇膽五個，斷腸草三株。
          制法：。。。待定。。。
\n
    白駝山莊莊主 歐陽鋒字\n\n" NOR);  
                return 1;
        }
        if( arg == "tujie" && query_temp("baituo_book", me) )
        {
                tell_object(me, "\n
汝可推開後院鐵門，于院中找到藍、紅、彩三塊石塊。將之順序
推下(push)之後于其中一院內等待一刻便可入白駝秘道。秘道可
直達山後亂石堆。秘道中之丹頂仙鶴乃是神物，如非性命悠關不
可取它紅頂，切記！
\n
    白駝山莊莊主 歐陽鋒字\n\n" NOR); 
                return 1;
        }
        if( arg == "liangong" && query_temp("baituo_book", me) )
        {
                tell_object(me, "\n
蛤蟆神功是由當日捕捉玄冰蟾蜍時由此畜生身上習得。現我將玄
冰蟾蜍封閉在後院巨石堆裡，沒有一定的西毒毒技修為不得冒然
進入，切記！
\n
    白駝山莊莊主 歐陽鋒字\n\n" NOR);    
                set_temp("baituo_yun", 1, me);
                return 1;
        }

        if( arg == "gongfu" && query_temp("baituo_book", me) )
        {
                tell_object(me, "\n
白駝功夫分內外兩種，內功便是蛤蟆功，汝可每日去後院亂石堆
練習(strike stone)。外功則是我集多年經驗觀察蛇蟒搏鬥而從
中變化出來的《白駝蛇杖》。蛇杖功夫要點在于靈、狠、毒三字。
汝可從此書中學得(read book)。

\n
    白駝山莊莊主 歐陽鋒字\n\n" NOR);          
                set_temp("baituo_book", 2, me);
                return 1;
        }
        if (arg=="xianzhuang" || arg=="book" && 
                query_temp("baituo_book", me) == 2 )
        {
                if( query("jing", me)<25 )
                {
                        write("你現在過于疲倦，無法專心下來研讀新知。\n");
                        return 1;
                }        
                if( query("neili", me)<50 )
                {
                        write("你內力不夠，無法繼續鑽研。\n");
                        return 1;
                }
                level = me->query_skill("lingshe-zhangfa", 1);
                if( query("combat_exp", me)<level*level*level/10 )
                {
                        write("你的實戰經驗不足，再怎麼讀也沒用。\n");
                        return 1;
                }        
                if( me->query_skill("lingshe-zhangfa", 1) > 50)
                {
                        write( "你研讀了一會兒，但是發現上面所說的對你而言都太淺了，沒有學到任何東西。\n");
                        return 1;
                }
                me->receive_damage("jing", 15);
                addn("neili", -1, me);
        
                me->improve_skill("lingshe-zhangfa", (int)me->query_skill("literate", 1)/3+1);
                write("你開始仔細研讀蛇杖杖法。\n");
                return 1;
        }
}
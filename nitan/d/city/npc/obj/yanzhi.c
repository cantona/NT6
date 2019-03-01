inherit ITEM;
#include <ansi.h>

int do_makeup();
void remove_effect(object);

void create()
{
        set_name(HIR "胭脂" NOR, ({ "yan zhi","yanzhi"}) );
        set_weight(50);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "盒");
                set("long", "這是一盒用上好玫瑰花瓣層層疊熏細濾而成的胭脂，艷如雲霞，香氣襲人。這是女\n孩子化妝(makeup)的必備品。\n");
                set("value", 1);
        }
}

void init()
{
        add_action("do_makeup", "makeup");
}

int do_makeup()
{
        object me;
        object huafen, you;
        string str;
        
        me = this_player();
        if( query_temp("makeuped", me) )
        {
                write("你剛剛化過妝，不用再化了，妝化太濃效果會適得其反的。\n");
                return 0;
        }
        
        str=query("gender", me);
        if( (str != "女性") && (str != "無性"))
        {
                if(str == "男性")
                {
                        write("大男人化什麼妝！\n");
                        return 0;
                }
                else
                {
                        write("你不可以化妝！\n");
                        return 0;
                }
        }

        huafen = present("huafen dai",me); 
        if(!huafen) 
        {
                write("買袋花粉吧，沒有花粉耶。\n");
                return 1;
        }
        you = present("baohua you",me); 
        if(!you) 
        {
                write("買樽刨花油吧，沒有刨花油耶。\n");
                return 1;
        }

        message_vision("$N用小鬃刷熬上點刨花油，理了理略顯凌亂的頭發。\n", me);
        message_vision("$N拔下發間銀簪，小心的挑出些胭脂膏子放在手心，用右手小指沾了些點在唇上，\n更顯紅唇飽滿嬌艷欲滴。\n", me);
        if((me->query_per()>25) && (str != "無性"))
                message_vision(HIM"$N將剩下的胭脂小心地用兩掌暈開，輕輕拍在雙頰，攬鏡自照，但見面若芙蓉目似\n秋雨，不由嫣然一笑，真個是百媚千嬌。\n"NOR, me);
        else if(me->query_per()<15)
                message_vision(BLU"$N將剩下的胭脂小心地用兩掌暈開，輕輕拍在雙頰，攬鏡自照，發現自己滿臉的白\n粉嗖嗖往下掉，化完妝後的樣子仍是不敢恭維。\n"NOR, me);
        else
                message_vision(HIG"$N將剩下的胭脂小心地用兩掌暈開，輕輕拍在雙頰，攬鏡自照，似乎變漂亮了點。\n"NOR, me);

        me->start_busy(5);
        addn_temp("apply/per", 1, me);
        set_temp("makeuped", 1, me);

        destruct(huafen);
        destruct(you);
        destruct(this_object());
        return 1;
}
        
void remove_effect(object me)
{
        if( query_temp("makeuped", me) )
        {
                addn_temp("apply/per", -1, me);
                delete_temp("makeuped", me);
                tell_object(me, "忙碌了一天，你的妝全亂了，該找個地方梳洗一下了。\n");
        }
}

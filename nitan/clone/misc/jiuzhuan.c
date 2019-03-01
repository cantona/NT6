// jiuzhuan.c 九轉金丹

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIY "九轉金丹" NOR, ({ "jiuzhuan jindan", "dan" }) );
        set_weight(200);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "一顆金色的仙丹，傳說是太上老君"
                            "精心修煉的靈丹妙藥。\n");
                set("value", 1500000);
                set("unit", "顆");
                set("only_do_effect", 1);
        }
}

int do_effect(object me)
{
        int effect;

        log_file("static/using", sprintf("%s(%s) eat 九轉金丹 at %s.\n",
                 me->name(1),query("id", me),ctime(time())));

        effect = 0;
        message_vision("$N一仰脖，吞下了一顆" + this_object()->name() +
                       "。\n", me);
        if( query("gift/int/succeed", me)<4 && random(2) )
        {
                effect++;
                write(HIM "你覺得自己的頭腦更清醒了。\n" NOR);
                addn("gift/xiandan", 1, me);
                addn("gift/int/succeed", 1, me);
                addn("int", 1, me);
        }

        if( query("gift/dex/succeed", me)<4 && random(2) )
        {
                effect++;
                write(HIR "你覺得自己的腿腳更靈活了。\n" NOR);
                addn("gift/unknowdan", 1, me);
                addn("dex", 1, me);
                addn("gift/dex/succeed", 1, me);
        }

        if( query("gift/con/succeed", me)<4 && random(2) && 
            query("gender", me) != "無性" )
        {
                effect++;
                write(HIC "你覺得自己的內息更通暢了。\n" NOR);
                addn("gift/xisuidan", 1, me);
                addn("con", 1, me);
                addn("gift/con/succeed", 1, me);
        }

        if( query("gift/str/succeed", me)<4 && random(2) )
        {
                effect++;
                write(HIG "你覺得自己的膂力更強健了。\n" NOR);
                addn("gift/shenliwan", 1, me);
                addn("str", 1, me);
                addn("gift/str/succeed", 1, me);
        }

        write(HIM "冥冥中你有所感悟。只覺得靈台一片空明，純凈無比。\n" NOR);
        addn("magic_points", 1000+random(1000), me);

        destruct(this_object());
        return 1;
}



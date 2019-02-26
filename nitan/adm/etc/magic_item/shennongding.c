// 上古十大神器之 神農鼎
// Create by Rcwiz for Hero.cn 2003/09

#include <ansi.h>

inherit ITEM;

int is_magic_item() { return 1; }

// 煉製的丹藥
string *gifts = ({
        "/clone/fam/pill/neili1",
        "/clone/fam/pill/neili2",
        "/clone/fam/pill/linghui1",
        "/clone/fam/pill/linghui2",
        "/clone/fam/pill/lingzhi4",
        "/clone/fam/pill/lingzhi3",
        "/clone/fam/pill/puti1",
        "/clone/fam/pill/puti2",
        "/clone/fam/pill/puti3",
        "/clone/fam/pill/puti4",
        "/clone/fam/pill/renshen3",
        "/clone/fam/pill/renshen4",
        "/clone/fam/pill/sheli1",
        "/clone/fam/pill/sheli2",
        "/clone/fam/pill/sheli3",
        "/clone/fam/pill/sheli4",
        "/clone/fam/pill/xuelian3",
        "/clone/fam/pill/xuelian4",        
        "/clone/fam/gift/int3",
        "/clone/fam/gift/con3",
        "/clone/fam/gift/str3",                        
        "/clone/fam/gift/dex3",
        "/clone/fam/pill/neili1",
        "/clone/fam/pill/neili2",
        "/clone/fam/pill/linghui1",
        "/clone/fam/pill/linghui2",
        "/clone/fam/pill/lingzhi4",
        "/clone/fam/pill/lingzhi3",
        "/clone/fam/pill/puti1",
        "/clone/fam/pill/puti2",
        "/clone/fam/pill/puti3",
        "/clone/fam/pill/puti4",
        "/clone/fam/pill/renshen3",
        "/clone/fam/pill/renshen4",
        "/clone/fam/pill/sheli1",
        "/clone/fam/pill/sheli2",
        "/clone/fam/pill/sheli3",
        "/clone/fam/pill/sheli4",
        "/clone/fam/pill/xuelian3",
        "/clone/fam/pill/xuelian4",        
        "/clone/fam/gift/int4",
        "/clone/fam/gift/con4",
        "/clone/fam/gift/str4",
        "/clone/fam/gift/dex4",                                                
        "/clone/fam/max/naobaijin",
        "/clone/fam/pill/neili1",
        "/clone/fam/pill/neili2",
        "/clone/fam/pill/linghui1",
        "/clone/fam/pill/linghui2",
        "/clone/fam/pill/lingzhi4",
        "/clone/fam/pill/lingzhi3",
        "/clone/fam/pill/puti1",
        "/clone/fam/pill/puti2",
        "/clone/fam/pill/puti3",
        "/clone/fam/pill/puti4",
        "/clone/fam/pill/renshen3",
        "/clone/fam/pill/renshen4",
        "/clone/fam/pill/sheli1",
        "/clone/fam/pill/sheli2",
        "/clone/fam/pill/sheli3",
        "/clone/fam/pill/sheli4",
        "/clone/fam/pill/xuelian3",
        "/clone/fam/pill/xuelian4",
        "/clone/fam/pill/yulu",
        "/clone/fam/pill/neili1",
        "/clone/fam/pill/neili2",
        "/clone/fam/pill/linghui1",
        "/clone/fam/pill/linghui2",
        "/clone/fam/pill/lingzhi4",
        "/clone/fam/pill/lingzhi3",
        "/clone/fam/pill/puti1",
        "/clone/fam/pill/puti2",
        "/clone/fam/pill/puti3",
        "/clone/fam/pill/puti4",
        "/clone/fam/pill/renshen3",
        "/clone/fam/pill/renshen4",
        "/clone/fam/pill/sheli1",
        "/clone/fam/pill/sheli2",
        "/clone/fam/pill/sheli3",
        "/clone/fam/pill/sheli4",
        "/clone/fam/pill/xuelian3",
        "/clone/fam/pill/xuelian4",        
});

void create()
{
        set_name(HIG "神農鼎" NOR, ({ "shennong ding", "shennong", "ding" }) );
        set_weight(400);
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("unit", "個");
                set("long", HIG "這是一個具有神奇作用的鼎，據説上古神農嘗百草煉奇藥，所用"
                                "之煉製器具就是這個神農鼎。\n"
                                "你可以用它來煉製(lianzhi)出神奇的丹藥，使用liandan ? "
                                "查看可使用次數。\n煉製丹藥需要煉丹術一百級。\n" NOR);
        }

        setup();
}

void init()
{
        add_action("do_lianzhi", "lianzhi");
}

int do_lianzhi(string arg)
{
        object me, ob;
        int i;
        string gift;

        me = this_player();
        
        if(! objectp(present("shennong ding", me)))return 0;

        if (arg == "?")
        {
                 write(HIG "使用次數 " + this_object()->query("count") + "/5\n" NOR);
                 return 1;
        }
        if (me->is_fighting() || me->is_busy())
                 return notify_fail("你正忙呢！\n");          

        message_sort(HIG "\n$N" HIG "將神農鼎放在地上，隨手仍進去一些藥材，漸漸地，鼎中陣"
                         "陣青煙冒出，光華萬道 ……\n" NOR, me);

        gift = gifts[random(sizeof(gifts))];
        ob = new(gift);
        if (! objectp(ob))
        {
                write(HIR "物件 " + gift + " 複製出錯！\n" NOR);
        }
        else
        {
                write(HIG "你煉製出了 " + ob->name() + HIG + " 。\n" NOR);
                ob->move(me, 1);
        }
             
        me->start_busy(2);
        this_object()->add("count", 1);
        if (this_object()->query("count") >= 5)
        {
                write(HIW "只聽得一陣破碎的聲音，神農鼎已損壞了。\n" NOR);
                destruct(this_object());                        
        }
        
        return 1;
}

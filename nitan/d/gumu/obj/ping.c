#include <ansi.h>

inherit ITEM;

void init()
{
        add_action("do_qufeng","qufeng");
}

void create()
{
        set_name("蜂漿瓶", ({ "fengjiang ping", "ping" }) );
        set_weight(4500);
        if( clonep() )
                set_default_object(__FILE__);
        else {
        set("unit", "個");
        set("value", 0);
        set("jian",5) ;
        set("material", "玉");
        set("long", "這是一個用上古美玉雕成的小瓶，還未拔開瓶塞，就可以聞到\n"
                    "一股濃鬱的香味，可以用來驅蜂。\n") ;
        }
        setup();
}
int do_qufeng(string arg)
{
        object me, obj;
        mixed myexp , objexp ;
        int mylev , objlev ;
        int myforce , obforce ;
        int steps ;

        me = this_player();
        if( query("no_fight", environment(me)) )
                return notify_fail("這裡禁止戰鬥。\n");

        if (! arg)
                return notify_fail("你想驅蜂攻擊誰？\n");

        if( query("jian", this_object())<1 )
                return notify_fail("小瓶裡的玉蜂蜜已經給用光了。\n");

        if (! objectp(obj = present(arg, environment(me))))
                return notify_fail("這裡沒有這個人。\n");

        if (! obj->is_character() || obj->is_corpse())
                return notify_fail("看清楚一點，那並不是活物。\n");

        if (me->is_busy())
                return notify_fail("你現在正忙，沒有時間驅蜂。\n");

        if (obj == me)
                return notify_fail("玉蜂不能攻擊你。\n");

        if (! me->is_fighting(obj))
                return notify_fail("驅蜂只能在戰鬥中對對手使用。\n");

        myexp=query("combat_exp", me);
        objexp=query("combat_exp", obj);
        mylev =  me->query_skill("qufeng" );
        objlev = obj->query_skill("qufeng" );
        myforce =  me->query_skill("force" );
        obforce = obj->query_skill("force" );

        if (mylev <= 0)
                return notify_fail("你不會驅蜂之術，不能驅使玉蜂為你攻擊敵人！\n");

        myexp = 30 * objexp/myexp;
        if (myexp < 30) myexp = 30 ;

        if( query("jing", me)<myexp )
                return notify_fail("你的精不足以驅動玉蜂傷敵！\n");

        if (myforce + 15 <= obforce)
                return notify_fail("對手的內功太深厚了，驅蜂術對他不起作用！\n");

        addn("jian", -1, this_object());
        steps = (mylev - objlev) * 1;
        if (steps < 2) steps = 2 ;
        message_vision(HIY "$N" HIY "拔開玉瓶塞，手捂玉瓶潛運內力，使"
                       "得瓶中的香氣遠遠飄了開去，\n突然嗡嗡之聲大作，"
                       "不知道從哪裡飛來一大群玉蜂，向$n" HIY "圍了過去。\n" NOR,
                       me, obj);
        me->start_busy(3);

        if (random(mylev) < objlev * 2 / 3)
                message_vision(YEL "但$n" YEL "撮唇一嘯，玉蜂似乎聽"
                               "懂了號令，遠遠避了開去。\n" NOR, me, obj);
        else
        {
                tell_object(obj, HIR "你周圍剎那間盡是玉蜂圍繞，一只只玉蜂悍不畏死地向你\n"
                                 "蜇了過來，你只覺得背心微微一痛，已被玉蜂蜇中！\n" NOR  ) ;
                obj->receive_damage("jing", steps * 5, me);
                obj->receive_damage("qi", steps * 6, me);
                if (! obj->is_busy()) obj->start_busy(3);
                me->start_busy(1);
        }
        me->receive_damage("jing", myexp);
        return 1;
}
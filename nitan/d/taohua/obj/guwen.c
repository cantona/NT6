//Cracked by Kafei
//桃花島經書，literate 100lv後可以請教別人至200lv，但是比learn慢很多。
//可以向player請教。(literate > 200 ，桃花弟子)
//maco 1999/5/9

#include <ansi.h>
inherit ITEM;
string* names = ({
        "《國策》",
        "《楚辭》",
        "《詩經》",
        "《周髀算經》",
});

string* longs = ({
        "這是一冊厚重的古書，文字極多，卻很少註解。\n",
        "這是一冊破舊的古書，有些字跡已經模糊不清，難以理解。\n",
        "這是一冊薄皮古書，寫滿了蠅頭小字，不易看得清楚。\n",
});
void create()
{
        set_name(names[random(sizeof(names))], ({"book","jing","book"}));
        set_weight(300);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "冊");
                set("value", 4000);
                set("no_sell",1);
             set("long",longs[random(sizeof(longs))]);
        }
}
void init()
{
        add_action("do_qingjiao", "qingjiao");
}

int do_qingjiao(string arg)
{
        object me, ob;
        int jing_cost,grade;

        me = this_player();
        jing_cost=150/query("int", me)+1;
        if (me->is_busy())
                return notify_fail("你現在正忙着呢。\n");
        if( me->is_fighting() )
                return notify_fail("先把這場架打完吧。\n");
        if( !arg )
                return notify_fail("你想請教誰？\n");
        if(!objectp(ob = present(arg, environment(this_player()))))
                return notify_fail("這裏沒有這個人。\n");
        if (me == ob)
                return notify_fail("自己請教自己？\n");
        if( !ob->is_character() || ob->is_corpse() )
                return notify_fail("看清楚一點，那並不是活物。\n");
        if( !living(ob) )
                return notify_fail("嗯....你得先把" + ob->name() + "弄醒再説。\n");
        if( query("potential", me)<2 )
                return notify_fail("你的潛能不足，無法領會任何東西。\n");

        if(me->query_skill("literate",1) < 100 )
                return notify_fail("憑你現在的學識，還無法理解經書上的知識。\n");
        if(ob->query_skill("literate",1) < 200 )
                return notify_fail("以"+ ob->name() +"的學識，還不足以指導你。\n");
        if(me->query_skill("literate",1) > 300 )
                return notify_fail("你的學識已經相當精深，理解這本書無甚困難之處。\n");
        
        if( query("family/family_name", me) != "桃花島" || 
        query("family/family_name", ob) != "桃花島" )
        {
        printf("你向%s請教經書上的疑難之處，然而對方似乎不想為你解釋。\n", ob->name());
        }
        else if (me->query_skill("literate") >= ob->query_skill("literate"))
        {
        printf("%s的學問已經無法再指導你什麼了。\n", ob->name());
        }

         else if( query("jing", me)>jing_cost )
        {
                printf("你向%s請教經書上的疑難之處，用心思考其中涵義。\n", ob->name());
                if ((int)me->query_skill("literate",1) < 200) {
                addn("potential", -2, me);
                me->improve_skill("literate",(random(10)+query("int", me)*2/3));}
                
                else {
                addn("potential", -2, me);
                me->improve_skill("literate",(random(10)+query("int", me)/3));
                        }
                }
        
        else
        {
                jing_cost=query("jing", me);
                write("你現在太累了，沒有辦法專心研讀經書。\n");
        }
        me->receive_damage("jing", jing_cost );
        return 1;
}

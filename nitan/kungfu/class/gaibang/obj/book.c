// dgb_book.c

#include <ansi.h>
inherit ITEM;
inherit F_UNIQUE;

int do_start(object me);


void create()
{
        set_name("打狗棒譜", ({ "dgb book", "book" }));
        set_weight(600);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
        set("long", "打狗棒的口訣向來都是口傳，這個冊子記載著打狗棒的最後一招天下無狗的詳解。\n");
                set("material", "paper");
                                set("no_drop","這樣東西不能離開你。\n");
                                set("no_get",1);
                                set("no_steal",1);
                set("value", 300000);

        }
}
void init()
{
  add_action("do_lingwu","lingwu");
  
}
int do_lingwu(string arg)
{
        object me;
        int cost;
        object *ob;
        object weapon;
        int i;
        me=this_player();
         if (me->is_busy())
            return notify_fail("你正忙著呢!\n");

        
        if( arg != query("id", this_object()))return notify_fail("你要領悟什麼?\n");
        if(me->query_skill("dagou-bang", 1) <250)
        return notify_fail("你連打狗棒法最基本的招式還未嫻熟呢？\n");
        if( query("wugou", me)>500 )
        {
            set("can_perform/dagou-bang/tian", 1, me);
        return notify_fail("你已經完全領悟了打狗棒的絕招。\n");
        }
        if( query("no_fight", environment(me)))return notify_fail("這裡空氣不好，無法專心領悟。\n");
        ob = all_inventory(environment(me));
        for(i=0; i<sizeof(ob); i++) {
            if( query("race", ob[i]) == "人類" && ob[i] != me )
            return notify_fail("打狗棒的絕招可不能輕易讓人看的哦。\n");
        }
        if( !objectp(weapon=query_temp("weapon", me)) )
        return notify_fail("你手中無打狗棒如何領悟絕招!\n");
        
        if( query("skill_type", weapon) != "staff" )
        return notify_fail("手中拿著竹杖才能領悟打狗棒法的絕招!\n");
        if( query("qi", me)<query("max_qi", me) || query("jing", me)<query("max_jing", me) )
        return notify_fail("你的身體狀況不佳！\n");
        if( query("neili", me)<query("max_neili", me) || query("jingli", me)<query("max_jingli", me) )
        return notify_fail("你的精力，內力還未充盈，無法領悟！\n");
        if( query("max_neili", me)<1000 )
                return notify_fail("你的內力不夠深厚，無法領悟打狗棒法！\n");
        if( query("master", this_object()) != query("id", me) )
        {
        if( query("max_neili", me)<20 )
                return notify_fail("你覺得渾身無力，似乎一身內功已經盡數散去。\n");
        addn("max_neili", -20, me);
        return notify_fail(HIR"你不知口訣，強行領悟招式，突然心口有說不出的難受。\n"NOR);

        }
if (wizardp(me)) printf("int = %d\n",me->query_int());
        message_vision(HIY"$N默念口訣，手拿打狗棒，按照書中的姿勢比劃著......\n"NOR,me);
        if (random(me->query_int())>35 || random(10)==3)
        {
                 addn("wugou", 1, me);
                if( query("wugou", me)<60 )
                 tell_object  (me,HIR"你似乎對打狗棒最後一招有一絲領悟。\n"NOR);
                 else if( query("wugou", me) == 60 )
                 tell_object  (me,HIR"你領悟出六式天下無狗中的三式，也許你該試驗試驗了。\n"NOR);
                 else if( query("wugou", me)>500 )
                 {
                         set("can_perform/dagou-bang/tian", 1, me);
             if (me->can_improve_skill("staff")) 
                     me->improve_skill("staff", 1500000); 
             if (me->can_improve_skill("staff")) 
                     me->improve_skill("staff", 1500000); 
             if (me->can_improve_skill("staff")) 
                     me->improve_skill("staff", 1500000); 
             if (me->can_improve_skill("dagou-bang")) 
                     me->improve_skill("dagou-bang", 1500000); 
             if (me->can_improve_skill("dagou-bang")) 
                     me->improve_skill("dagou-bang", 1500000); 
             if (me->can_improve_skill("dagou-bang")) 
                     me->improve_skill("dagou-bang", 1500000); 
             me->improve_skill("martial-cognize", 1500000); 
                 tell_object  (me,HIR"你終于領悟出天下無狗的所有的絕招。\n"NOR);
             }
                 else
                 tell_object  (me,HIR"你對天下無狗這招有了更深的了解。\n"NOR);
        }
        else
        {
                tell_object(me,HIR"你心煩意亂，費盡心神也難以領悟。\n"NOR);
        }
        addn("qi", -100, me);
        addn("jing", -100, me);
        addn("neili", -100, me);
        addn("jingli", -100, me);
        if (!wizardp(me)) me->start_busy(2+random(5));
        return 1;

}

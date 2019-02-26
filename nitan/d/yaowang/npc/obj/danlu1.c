#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(CYN"煉丹爐"NOR, ({ "liandan lu", "liandan", "lu" }) );
        set_weight(300000);
        set_max_encumbrance(500000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "個");
                set("long", "這是一個青銅鑄成的煉丹爐。\n");
                set("value", 1000);
                set("no_get",1);
                set("amount",10);
                set("container",1);
        }
        setup();
}
int is_container() { return 1; }
void init()
{
//      add_action("do_fang", "fang");
        add_action("do_lian", "liandan");
        add_action("do_ran", "ran");
}
/*
int do_fang(string arg)
{
        object me, ob;
        me = this_player();

        if( query("family/family_name", me) != "藥王谷" || me->query_skill("medical",1)<80){
                return notify_fail("你還不能在這裏煉丹！\n");
        }

        if( query("shen", me)<0){
                return notify_fail("你應當到別的煉丹房去煉丹！\n");
        }

        if(!arg || !ob=present(arg, me))
                return notify_fail("你要把什麼放進煉丹爐中\n");

        if( me->is_fighting() || me->is_busy() )
                return notify_fail("你正忙着呢！\n");

        message_vision(YEL"\n$N把一"+query("unit", ob)+query("name", ob )
                +"放進煉丹爐中\n\n"NOR, me);

        destruct(ob);
        ob->move(this_object());
        return 1;
}
*/
int do_lian(string arg)
{
        object ob1, ob2, ob3, ob4, ob5;
        object me, ob, obj;
        me=this_player();
        ob=this_object();

        if( query("family/family_name", me) != "藥王谷" || me->query_skill("medical",1)<80){
                return notify_fail("你還不能在這裏煉丹！\n");
        }

        if( query("shen", me)<0){
                return notify_fail("你應當到別的煉丹房去煉丹！\n");
        }

        if( !arg && ((arg!="bigu wan")) )
                return notify_fail("指令格式：liandan <丹藥ID> \n"
                "        可以練的丹藥有： 辟穀丸(bigu wan)\n"
                "                         ******(********)\n");

        if( me->is_fighting() || me->is_busy() )
                return notify_fail("你正忙着呢！\n");

        if( !query_temp("liandan", me) )
                return notify_fail("丹爐還沒有點燃，怎麼煉丹！\n");

        if( objectp(ob1=present("lu xue",ob))
                && objectp(ob2=present("lu rong",ob))
                && objectp(ob3=present("xiong dan",ob))
                && objectp(ob4=present("xiong zhang",ob))
                && objectp(ob5=present("she dan",ob)) ) {
                        destruct(ob1);
                        destruct(ob2);
                        destruct(ob3);
                        destruct(ob4);
                        destruct(ob5);
                if(arg=="bigu wan") { obj=new(__DIR__"biguwan"); }
        message_vision(HIR"$N關上丹爐的爐門，催動火力開始煉丹。\n\n"NOR, me);
        call_out("lian_over", 5, me);   
                return 1;
                }
        else
        return notify_fail("可是藥材還沒準備齊呀！\n");
}
int lian_over(object me)
{
        int lvl;
        object obj;
        lvl = me->query_skill("medical",1);
        if (random(lvl) > 80)
        {
        message_vision(HIR"一會兒爐膛內的火焰漸漸熄滅。\n\n"NOR, me);
        message_vision(HIR"$N的丹藥練成了。\n"NOR, me);
        message_vision(HIR"爐火漸漸熄滅了！\n"NOR, me);
        message_vision(HIR"$N你從爐裏拿出一顆辟穀丸\n"NOR, me);
        me->improve_skill("medical", ((int)me->query_skill("medical",1)/10));
        obj=new(__DIR__"biguwan");
        obj->move(me);
        delete_temp("liandan", me);
        return 1;
        }
        else
        {
                message_vision(HIR"$N的丹藥練失敗了。\n"NOR, me);
                return 1;
                
        }

}
int do_ran(string arg)
{
        object me;
        me=this_player();

        if( query("family/family_name", me) != "藥王谷" || me->query_skill("medical",1)<80
                 || query("shen", me)<0){
                return notify_fail("不許亂碰這裏的東西！\n");
        }

        if( query_temp("liandan", me) )
                return notify_fail("丹爐的火已經很旺了，快開始煉丹吧！\n");

        set_temp("liandan", 1, me);
        message_vision(HIR"$N拿起火折塞進爐膛，把丹爐點燃。\n"NOR, this_player());
        return 1;
}

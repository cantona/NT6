// box.c 功德箱

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name("功德箱", ({ "gongde xiang", "xiang", "box" }) );
        set_weight(3000);
        set_max_encumbrance(5000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "個");
                set("long", "這是一個小廟裏常見的功德箱，專門用來接受善男信女們的捐款。\n");
                set("value", 1000);
                set("material", "wood");
                set("no_get",1);
                set("no_drop",1);
                set("amount",30);
        }
        setup();
}

int is_container() { return 1; }

void init()
{
        object ob;
        object me = this_player();
        /*
        if( query("combat_exp", me) <= 5000
         && query("amount", this_object()) >= 10
        &&  random(2) == 1 )
        {
                ob=new("/clone/money/silver");
                ob->set_amount(10);
                ob->move(this_object());
                tell_object(me, "\n你忽然看到功德箱裏有什麼東西在閃閃發光！\n\n");
                addn("combat_exp", 1, me);
        }
        */
        add_action("do_put", "put");
}

int do_put(string arg)
{
        object me, obj;
        string item, target;
        int amount;

        me = this_player();

        if(!arg) return notify_fail("你要將什麼東西放進哪裏？\n");

        if( sscanf(arg, "%s in %s", item, target)!=2
        ||  sscanf(item, "%d %s", amount, item)!=2
        ||  !objectp(obj = present(item, me)) )

        return notify_fail("你要給誰什麼東西？\n");

        if( query("money_id", obj) == "silver"
        &&  obj->query_amount() >= 5 && obj->query_amount() < 100000 && amount >= 5 )
        {
                if( query("begger", me)>0){
                        message_vision( sprintf(HIY "$N將一%s%s放進%s。\n" NOR,
                                query("unit", obj),obj->name(),
                                this_object()->name()),me );
                        obj->set_amount(obj->query_amount() - amount);;
                        addn("begger", (-1)*(amount/5), me);
                        if( query("begger", me)<0)set("begger", 0, me);
                        addn("amount", amount, this_object());
                        return 1;
                }
        }

        if( query("money_id", obj) && obj->value() >= 100000 )
        {
                tell_object(me,"你虔誠地祈禱，希望過去在江湖中的仇殺。\n");
                me->remove_all_killer();
                destruct(obj);
                return 1;
        }
        return 0;
}
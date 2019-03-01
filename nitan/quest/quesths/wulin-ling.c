inherit ITEM;

void create()
{
        set_name( "武林令", ({ "wulin ling", "ling"}) );
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "塊");
                set("long", "這是一塊武林同盟使用的鐵令，見令如見盟主。 由黃裳簽發，處理武林同盟一應事務。\n");
                set("value", 0);
                set("material", "iron");
        }
        setup();
}

void init()
{
        add_action("do_chushi","chushi");
}

int do_chushi(string arg)
{
        object thing,obj,me,who;
        mapping quest;
        me = this_player();
        if( !quest=query("quest_hs", me) )
            return notify_fail("你沒有接到征收的任務，在這裡用英雄令晃啊晃的幹啥？\n");
        if (!arg) return notify_fail("你要向誰出示武林令？");
        if (! objectp(who = present(arg, environment(me))))
            return notify_fail("這裡沒有這個人。\n");
        if( query_temp("quester", who) != query("id", me) || quest["target"] != query("id", who) )
            return notify_fail("你不要仗著武林同盟的名聲到處招搖撞騙！\n");
        message_vision("$N高舉武林令，對著$n大聲說：“你這個家伙，準備躲著武林盟主多久？\n"
                       "好在今天讓我找到了你！黃大人讓我來收取"+quest["name"]+"，你就乖乖的交出來吧！\n",me,who);
        message_vision("$N見到$n手中的武林令，不由一聲長嘆：“躲了這麼久，還是給你們找到了，也罷也罷！\n"
                       "你要的東西我這裡有，就交給你了。\n",who,me);
        thing = new(quest["object"]);
        set_temp("zheng",query("id",  me), thing);
        if (!thing->move(me))
        {
                thing->move(environment(me));
            message_vision("$N將"+thing->name(1)+"放在地上。\n",who);
        }
        else
            message_vision("$N將"+thing->name(1)+"交給了$n。\n",who,me);

        message_vision("$N揮了揮手，轉身離開了。\n",who);
        destruct(who);
        return 1;
}
            
     
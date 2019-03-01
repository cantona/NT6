// meat.h

void setup()
{
        set("only_do_effect", 1);
        set("base_weight", 300);
        ::setup();
}

int do_effect(object me)
{
        write("這塊" + name() + "還是生的，烤熟了再吃吧。\n");
        return 1;
}

int broil(object me, object ob)
{
        object fob;

        me = this_player();

        if (me->is_busy())
        {
                write("你現在忙著呢，過會兒再烤吧。\n");
                return 1;
        }

        message_sort(HIM "$N" HIM "把" + name() + HIM "放在" + ob->name() +
                     HIM "上細細烤著，只聽畢啵畢啵幾聲，聞得一陣誘人的香味"
                     "漸漸散了出來。$P見狀連忙把烤好的" + name() + HIM "取"
                     "下。\n\n" NOR, me);

        fob = new("/clone/food/meat");
        fob->move(me, 1);

        add_amount(-1);

        if (query_amount() < 1)
                destruct(this_object());

        me->start_busy(1);
        return 1;
}
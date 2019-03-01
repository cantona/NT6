// fish.h

int is_fish() { return 1; }

int has_died = 0;

void setup()
{
        set_weight(500 + random(1000));
        set("value", query_weight() / 50);

        ::setup();
        if (clonep())
                call_out("die", 60 + random(60));
}

void die()
{
        remove_call_out("die");

        if (! environment())
        {
                destruct(this_object());
                return;
        }

        message("vision", name() + "一翻白肚，死了。\n", environment());
        set("long", "這是一條" + name() + "，它已經死了。\n");
        set_name("死" + name(), ({ "si yu", "siyu" }));
        has_died = 1;
        call_out("decay", 30 + random(30));
        set("value", query("value") / 2);
}

void decay()
{
        remove_call_out("decay");

        if (! environment())
        {
                destruct(this_object());
                return;
        }

        message("vision", name() + "腐爛了，發出一陣陣臭味。\n", environment());
        set("long", "這是一條" + name() + "，它已經開始腐爛了。\n");
        set_name("爛魚", ({ "lan yu", "lanyu" }));
        set("value", 0);
        call_out("vanish", 20 + random(20));
}

void vanish()
{
        if (environment())
        {
                message("vision", "一陣風吹過，把" + name() +
                        "給吹散了。\n", environment());
        }

        destruct(this_object());
}

void sold()
{
        destruct(this_object());
}

int broil(object me, object ob)
{
        object fob;

        if (query("value") == 0)
        {
                write("這麼一條臭魚還烤什麼！\n");
                return 1;
        }

        me = this_player();
        if (me->is_busy())
        {
                write("你現在忙著呢，過會兒再烤吧。\n");
                return 1;
        }

        message_vision("$N把" + name() + "放在" + ob->name() +
                       "上細細的烤著，只聽畢啵畢啵的聲音，一"
                       "陣誘人的香味散了出來。\n", me);

        write(HIY "你把魚烤好了！\n" NOR);
        fob = new("/clone/food/fish");
        fob->move(me, 1);
        destruct(this_object());
        me->start_busy(1);
        return 1;
}
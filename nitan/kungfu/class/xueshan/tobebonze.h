void init()
{
        add_action("do_kneel", "kneel");
}

string ask_for_join()
{
        object me;

        me = this_player();

        if( query("class", me) == "bonze" )
                return "你已經是出家人了，還跟我羅嗦些什麼？";

        if( query("gender", me) != "男性" )
                return "我們雪山寺歷來只收男徒，你還是走吧。";

        set_temp("pending/join_bonze", 1, me);

        return "甚好，甚好！你若真心皈依我佛，請跪下(kneel)受戒。";
}

int do_kneel()
{
        object me = this_player();

        if( !query_temp("pending/join_bonze", me) )
                return 0;

        message_vision(HIC "\n$N" HIC "你雙手合十，恭恭敬敬地跪了下來。\n\n"
                       NOR + CYN "$n" CYN "看着$N" CYN "説道：好吧，以後你就"
                       "在本寺修行吧。\n\n" HIY "$n" HIY "伸出手掌，在$N" HIY
                       "頭頂輕輕地摩挲了幾下，隨即便將$N" HIY "的頭髮盡數剃"
                       "去。\n\n" NOR, me, this_object());

        set("class", "bonze", me);
        set("title", "雪山寺喇嘛", me);

        command("nod");
        command("say 既然出了家，就得一心向佛，再不能還俗。");

        return 1;
}

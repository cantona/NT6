string ask_for_join()
{
        object me;
        mapping myfam;
        me = this_player();

        myfam=query("family", me);
        /*
        if (! myfam || (myfam["family_name"] != "峨嵋派"))
                return ("施主與我峨嵋派尚無淵源，貧尼不敢給你剃度。");
        */

        if( query("class", me) == "bonze" )
                return "阿彌陀佛！出家人不打誑語。你已經不是俗家人了。";

        if( query("gender", me) != "女性" )
                return "阿彌陀佛！善哉！善哉！施主若真心皈依我佛，可去少林寺受戒。";

        set_temp("pending/join_bonze", 1, me);
        command ("say 阿彌陀佛！善哉！善哉！施主若真心皈依我佛，請跪下(kneel)受戒。");
        return "記住，既然出了家，就一心向佛，不能還俗。";
}

int do_kneel()
{
        object me = this_player();
        string *prename = ({ "靈", "文", "心", "妙"});
        string name, new_name;

        if( !query_temp("pending/join_bonze", me) )
                return notify_fail("你在地上跪了一會兒，沒人理你。\n");

        message_vision(HIC "\n$N" HIC "你雙手合十，恭恭敬敬地跪了下來。\n\n"
                       NOR + CYN "$n" CYN "看着$N" CYN "説道：好吧，以後你就"
                       "在本庵修行吧。\n\n" HIY "$n" HIY "伸出手掌，在$N" HIY
                       "頭頂輕輕地摩挲了幾下，隨即便將$N" HIY "的頭髮盡數剃"
                       "去。\n\n" NOR, me, this_object());

        name=query("purename", me);
        if( !name)name=query("name", me);
        new_name = prename[random(sizeof(prename))] + name[0..1];
        command("say 從今以後你的法名叫做" + new_name + "。");
        command("nod");
        set("marks/old_name", name, me);
        delete_temp("pending/join_bonze", me);
        set("name", new_name, me);
        set("class", "bonze", me);
        set("K_record",query("combat/PKS",  me)+query("combat/MKS", me), me);
        set("shen_record",query("shen",  me), me);
        set("shen", 0, me);

        return 1;
}

void init()
{
        add_action("do_kneel", "kneel");
}

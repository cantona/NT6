string ask_for_join()
{
        object me = this_player();
        mapping myfam;

        myfam=query("family", me);
        if (!myfam || (myfam["family_name"] != "恆山派"))
                return ("你和恆山沒有淵源，貧尼不敢給你剃度。\n");
        if( query("class", me) == "bonze" )
                return "阿彌陀佛！出家人不打誑語。你已經不是俗家人了。\n";
        if( query("gender", me) != "女性" )
                return "阿彌陀佛！善哉！善哉！施主若真心皈依我佛，可去少林寺受戒。\n";
        set_temp("pending/join_bonze", 1, me);
        command("say 阿彌陀佛！善哉！善哉！施主若真心皈依我佛，請跪下(kneel)受戒。\n");
        return "記住，一旦出了家，是不能還俗的，否則將會受到懲罰。\n";
}

int do_kneel()
{
        object me = this_player();

        string name, new_name;
        if( !query_temp("pending/join_bonze", me) )
                return 0;
        message_vision("$N你雙手合十，恭恭敬敬地跪了下來。\n\n$n看着$N説道：好吧，你就在本庵修行吧。\n\n$n伸出手掌，在$N頭頂輕輕地摩挲了幾下，將$N的頭髮盡數剃去。\n\n", me, this_object() );
        name=query("purename", me);
        if( !name)name=query("name", me);
        new_name = "容" + name[0..1];;
        command("say 從今以後你的法名叫做" + new_name + "。");
        command("chat "+name+"削髮為尼，在恆山修行，取法名"+new_name+"。");
        command("smile");
        set("marks/old_name", name, me);
        delete_temp("pending/join_bonze", me);
        set("name", new_name, me);
        set("class", "bonze", me);
        set("K_record",query("combat/PKS",  me)+query("combat/MKS", me), me);
        set("shen_record",query("shen",  me), me);
        set("shen", 0, me);

        return 1;
}

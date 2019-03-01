// emei.h

int permit_recruit(object ob)
{
        object me;

        me = this_object();
        if( query("detach/峨嵋派", ob) || 
            query("betrayer/峨嵋派", ob) )
        {
                command("say 你當年既然離開了峨嵋派，今天又何必回來？");
                return 0;
        }

        if( query("betrayer/times", ob) )
        {
                command("say 你欺師滅主，背叛師門，"
                        "這種人我們峨嵋派不會收留的。");
                return 0;
        }

        if( query("family/family_name", ob) && 
            query("family/family_name", ob) != "峨嵋派" )
        {
                command("say 你已有名師指點，為何又來峨嵋派？"
                        "莫非你要判師不成？");
                return 0;
        }

        if( query("class", me) == "bonze" )
        {
                if( query("class", ob) != "bonze" )
                {
                        command("say 阿彌陀佛！貧尼不收俗家弟子。");
                        command("say 你若想繼續學峨嵋派的功夫，"
                                "還是去找我俗家師妹吧。");
                        return 0;
                }

                if( query("gender", ob) != "女性" )
                {
                        command("say 阿彌陀佛！貧尼不收男弟子。"
                                "施主若想學藝可去找我俗家師妹。");
                        return 0;
                }
        }

        if( query("shen", ob)<0 )
        {
                command("say 唉，你現在正入歧途，我怎能收你為徒？");
                return 0;
        }

        return 1;
}

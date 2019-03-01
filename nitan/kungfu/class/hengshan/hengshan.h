// hengshan.h

int permit_recruit(object ob)
{
        command("say 恆山派暫不開放。");
        return 0;
        if( query("detach/恆山派", ob) || query("betrayer/恆山派", ob) )
        {
                command("say 你當年都已經離開了恆山派，何必又要回來？");
                return 0;
        }

        if( query("betrayer/times", ob) )
        {
                command("say 我們恆山派乃名門正派，決不收判師之徒！");
                return 0;
        }

        if( query("family/family_name", ob) && 
            query("family/family_name", ob) != "恆山派" )
        {
                command("say 你既然已經有了名師指點，不好好學習，來我們恆山派作甚？");
                return 0;
        }

        if( query("class", ob) != "bonze" )
        {
                command("say 阿彌陀佛！貧尼不收俗家弟子。");
                return 0;
        }

        if( query("gender", ob) != "女性" )
        {
                command("say 阿彌陀佛！貧尼不收男弟子。");
                return 0;
        }

        return 1;
}

int permit_recruit(object ob)
{
        if( query("detach/逍遙派", ob) || query("betrayer/逍遙派", ob) )
        {
                command("say 你當年都已經離開了逍遙派，何必又要回來？");
                return 0;
        }

        if( query("betrayer/times", ob) )
        {
                command("say 我們逍遙派乃名門正派，決不收判師之徒！");
                return 0;
        }

        if( query("family/family_name", ob) && 
            query("family/family_name", ob) != "逍遙派" )
        {
                command("say 你既然已經有了名師指點，不好好學習，來我們逍遙派作甚？");
                return 0;
        }

        if( query("per", ob)<26 )
        {
                command("look"+query("id", ob));
                command("say " + RANK_D->query_respect(ob) + "的尊容未免次了"
                        "點，這樣可入不了我們逍遙派！");
                return 0;
        }

        return 1;
}

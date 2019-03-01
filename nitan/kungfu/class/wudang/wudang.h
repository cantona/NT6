// check recruit

int permit_recruit(object ob)
{
        if( query("detach/武當派", ob) || query("betrayer/武當派", ob) )
        {
                command("say 你當年既然離開武當派，何必又要回來？");
                return 0;
        }

        if( query("betrayer/times", ob) )
        {
                command("say 我們武當派乃名門正派，決不收判師之徒！");
                return 0;
        }

        if( query("family/family_name", ob) && 
            query("family/family_name", ob) != "武當派" )
        {
                command("say 你既然已經有了名師指點，不好好學習，來我們武當派作甚？");
                return 0;
        }

        return 1;
}

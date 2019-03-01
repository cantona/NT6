// check recruit

int permit_recruit(object ob)
{
        if( query("detach/全真教", ob) || query("betrayer/全真教", ob) )
        {
                command("say 你當年既然離開全真教，何必又要回來？");
                return 0;
        }

        if( query("betrayer/times", ob) )
        {
                command("say 我們全真教乃名門正派，決不收判師之徒！");
                return 0;
        }

        if( query("family/family_name", ob) && 
            query("family/family_name", ob) != "全真教" )
        {
                command("say 你既然已經有了名師指點，不好好學習，來我們全真教作甚？");
                return 0;
        }

        return 1;
}

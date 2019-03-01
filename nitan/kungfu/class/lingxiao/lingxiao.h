// check recruit

int permit_recruit(object ob)
{
        if( query("detach/凌霄城", ob) || query("betrayer/凌霄城", ob) )
        {
                command("say 你當年既然已經離開凌霄城，現在何必又要回來？");
                return 0;
        }

        if( query("betrayer/times", ob) )
        {
                command("say 我們雪山凌霄城最狠就是你這樣的背信棄義之徒！");
                return 0;
        }

        if( query("family/family_name", ob) && 
            query("family/family_name", ob) != "凌霄城" && 
            query("family/family_name", ob) != "玄素莊" && 
            query("family/master_name", ob) != "石清" )
        {
                command("say 你既然已經有了名師指點，還來我們雪山劍派幹嘛？");
                return 0;
        }

        return 1;
}

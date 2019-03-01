// check recruit

int permit_recruit(object ob)
{
        command("say 梅莊暫不開放！");
        return 0;
        if( query("detach/梅莊", ob) || query("betrayer/梅莊", ob) )
        {
                command("say 你當年既然已經離開本莊，現在何必又要回來？");
                return 0;
        }

        if( query("betrayer/times", ob) )
        {
                command("say 我梅莊雖小，但是也不會接納你這樣的背信棄義之徒！");
                return 0;
        }

        if( query("family/family_name", ob) && 
            query("family/family_name", ob) != "梅莊" && 
            query("family/family_name", ob) != "日月神教" && 
            query("family/master_name", ob) != "東方不敗" )
        {
                command("say 你既然已經有了名師指點，還來我們梅莊幹嘛？");
                return 0;
        }

        return 1;
}

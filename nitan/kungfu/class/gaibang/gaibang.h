int permit_recruit(object ob)
{
        if( query("detach/丐幫", ob) || query("betrayer/丐幫", ob) )
        {
                command("say 嘿嘿，你當初走的時候是怎麼說的？");
                return 0;
        }

        if( query("betrayer/times", ob) )
        {
                command("say 我們丐幫行事堂堂正正，絕不接納判師之徒。");
                return 0;
        }

        if( query("family/family_name", ob )
            && query("family/family_name", ob) != "丐幫" )
        {
                command("say 你既然已經有了名師指點，還來我們丐幫幹什麼？");
                return 0;
        }
        return 1;
}

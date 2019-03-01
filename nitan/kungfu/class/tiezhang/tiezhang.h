// check recruit

int permit_recruit(object ob)
{
        if( query("detach/鐵掌幫", ob) || query("betrayer/鐵掌幫", ob) )
        {
                command("say 你當年既然已經離開本幫，現在幹嘛又要回來？");
                return 0;
        }

        if( query("betrayer/times", ob) )
        {
                command("say 我鐵掌幫雖然不是名門正派，但是你這樣的背信棄義之徒還是不會要的！");
                return 0;
        }

        if( query("family/family_name", ob) && 
            query("family/family_name", ob) != "鐵掌幫" && 
            query("family/family_name", ob) != "絕情谷" && 
            query("family/master_name", ob) != "裘千尺" )
        {
                command("say 你既然已經有了名師指點，還來我們鐵掌幫幹嘛？");
                return 0;
        }

        return 1;
}

// check recruit

int permit_recruit(object ob)
{
        if( query("detach/雲龍門", ob) || query("betrayer/雲龍門", ob) )
        {
                command("say 你當年既然離開雲龍門們，就不必回來了！");
                return 0;
        }

        if( query("betrayer/times", ob) )
        {
                command("say 我們雲龍門反清復明，最講信義，你走吧！");
                return 0;
        }

        if( query("family/family_name", ob) && 
            query("family/family_name", ob) != "雲龍門" )
        {
                command("sigh");
                command("shake");
                return 0;
        }

        return 1;
}

// check recruit

int permit_recruit(object ob)
{
        if( query("detach/雪山寺", ob) || query("betrayer/雪山寺", ob) )
        {
                command("say 你離開了雪山寺們，雪山寺已經不認你了！");
                return 0;
        }

        if( query("betrayer/times", ob) )
        {
                command("say 我們雪山寺最恨判師之徒，你還不快滾？");
                return 0;
        }

        if( query("family/family_name", ob) && 
            query("family/family_name", ob) != "雪山寺" )
        {
                command("say 你有師傅指點，當循序漸進，怎可貿然判師？");
                return 0;
        }

        return 1;
}

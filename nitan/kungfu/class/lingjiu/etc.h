int permit_recruit(object ob)
{
        if( query("detach/靈鷲宮", ob) || 
            query("betrayer/靈鷲宮", ob) )
        {
                command("say 你既然已經背叛了主公，我可不敢再作收留。");
                return 0;
        }

        if( query("family/family_name", ob) && 
            query("family/family_name", ob) == "靈鷲宮" )
        {
                command("say 你既然已經投入了主公門下，我自然不會吝嗇我所知的武功。");
                command("say 若有需要，你直接來找我學好了，不用再作拜師之禮。");
                return 0;
        }

        if( query("family/family_name", ob) )
        {
                command("say 找你的師父去，別來跟我羅嗦。");
                return 0;
        }

        return 1;
}

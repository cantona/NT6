// lingjiu.h

int permit_recruit(object ob)
{
        if( query("detach/靈鷲宮", ob) || 
            query("betrayer/靈鷲宮", ob) )
        {
                command("say 離開了縹緲峰就不要再回來！");
                return 0;
        }

        if( query("betrayer/times", ob) )
        {
                command("say 閣下不忠不信，我們靈鷲宮最恨的就是你這種人。");
                return 0;
        }

        if( query("family/family_name", ob) && 
            query("family/family_name", ob) != "靈鷲宮" )
        {
                command("say 你有了師傅，就不要來我們靈鷲宮了！");
                return 0;
        }

        return 1;
}

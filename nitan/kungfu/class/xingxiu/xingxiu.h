// xingxiu.h

int welcome(object ob)
{
        if( query("detach/星宿派", ob) || query("betrayer/星宿派", ob) )
        {
                command("say 哈哈！想來想去都是我們星宿派好吧！");
                return 0;
        }

        if( query("betrayer/times", ob) )
        {
                command("say 沒關系，你雖然判過幾次師，不過最後終于棄暗投明，可喜可賀！");
                return 0;
        }

        if( query("family/family_name", ob) && 
            query("family/family_name", ob) != "星宿派" )
        {
                command("say 呵呵，好啊！"+query("family/family_name", ob)+
                        "算什麼！");
                return 0;
        }

        return 1;
}

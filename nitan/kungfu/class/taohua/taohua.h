// taohua.h

int permit_recruit(object ob)
{
        if( query("detach/桃花島", ob) || 
            query("betrayer/桃花島", ob) )
        {
                command("say 虧你還有臉回桃花島？滾！");
                return 0;
        }

        if( query("betrayer/times", ob) )
        {
                command("say 閣下不忠不信，我最痛恨你這種人了。");
                return 0;
        }

        if( query("family/family_name", ob) && 
            query("family/family_name", ob) != "桃花島" )
        {
                command("say 你既有了名師指點，還來我們桃花島做什麼？");
                return 0;
        }

        return 1;
}

// honghua.h

int permit_recruit(object ob)
{
        if( query("detach/紅花會", ob) || 
            query("betrayer/紅花會", ob) )
        {
                command("say 我們紅花會四大戒條你還記得嗎？虧你還有臉回來！");
                return 0;
        }

        if( query("betrayer/times", ob) )
        {
                command("say 哼，閣下不忠不信，我們紅花會可不會收留。");
                return 0;
        }

        if( query("family/family_name", ob) && 
            query("family/family_name", ob) != "紅花會" )
        {
                command("say 閣下既有了師承，還來我們紅花會做什麼？");
                return 0;
        }

        return 1;
}

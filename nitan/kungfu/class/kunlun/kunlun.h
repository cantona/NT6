// kunlun.h

int permit_recruit(object ob)
{
        if( query("detach/昆侖派", ob) || 
            query("betrayer/昆侖派", ob) )
        {
                command("say 虧你還有臉回我昆侖山？給我滾開！");
                return 0;
        }

        if( query("betrayer/times", ob) )
        {
                command("say 閣下不忠不信，我最痛恨你這種人了。");
                return 0;
        }

        if( query("family/family_name", ob) && 
            query("family/family_name", ob) != "昆侖派" )
        {
                command("say 閣下既有了名師指點，還來我們昆侖派做什麼？");
                return 0;
        }

        return 1;
}

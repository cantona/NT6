int permit_recruit(object ob)
{

        if( query("detach/古墓派", ob) || 
            query("betrayer/古墓派", ob) )
        {
                command("say 唉！去便去了，回來又是何苦由來？");
                return 0;
        }

        if( query("betrayer/times", ob) )
        {
                command("say 閣下不忠不信，我不敢收你為徒。");
                return 0;
        }

        if( query("family/family_name", ob) && 
            query("family/family_name", ob) != "古墓派" )
        {
                command("say 你既有了名師指點，就要勤下苦功，勿要三心二意！");
                return 0;
        }

        return 1;
}

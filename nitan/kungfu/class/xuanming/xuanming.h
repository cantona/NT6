int permit_recruit(object ob)
{

        if( query("detach/玄冥谷", ob) || 
            query("betrayer/玄冥谷", ob) )
        {
                command("say 哼，你既然走了就不要再回來！");
                return 0;
        }

        if( query("betrayer/times", ob) )
        {
                command("say 閣下不忠不信，我不敢收你為徒。");
                return 0;
        }

        if( query("family/family_name", ob) && 
            query("family/family_name", ob) != "玄冥谷" )
        {
                command("say 你既有了名師指點，就要勤下苦功，勿要三心二意！");
                return 0;
        }

        return 1;
}

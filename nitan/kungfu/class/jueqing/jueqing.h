int permit_recruit(object ob)
{
        if( query("detach/絕情谷", ob) || query("betrayer/絕情谷", ob) )
        {
                command("say 你當年都已經離開了絕情谷，何必又要回來？");
                return 0;
        }

        if( query("betrayer/times", ob) )
        {
                command("say 我們絕情谷乃名門正派，決不收判師之徒！");
                return 0;
        }

        if( query("family/family_name", ob) && 
            query("family/family_name", ob) != "絕情谷" )
        {
                command("say 你既然已經有了名師指點，不好好學習，來我們絕情谷作甚？");
                return 0;
        }

        return 1;
}

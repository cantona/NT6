int permit_recruit(object ob)
{
        command("say 泰山派暫不開放。");
        return 0;
        if( query("detach/泰山派", ob) || query("betrayer/泰山派", ob) )
        {
                command("say 你當年都已經離開了泰山派，何必又要回來？");
                return 0;
        }

        if( query("betrayer/times", ob) )
        {
                command("say 我們泰山派乃名門正派，決不收判師之徒！");
                return 0;
        }

        if( query("family/family_name", ob) && 
            query("family/family_name", ob) != "泰山派" )
        {
                command("say 你既然已經有了名師指點，不好好學習，來我們泰山派作甚？");
                return 0;
        }

        return 1;
}

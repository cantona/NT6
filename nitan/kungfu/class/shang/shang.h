int permit_recruit(object ob)
{
        if( query("detach/商家堡", ob) || query("betrayer/商家堡", ob) )
        {
                command("sneer");
                command("say 你吃裡爬外，反復無常，叫我如何收你？");
                return 0;
        }

        if( query("born_family", ob) != "山東商家" )
        {
                command("heng");
                command("say 我商家堡向來不收外人，給我走開。");
                return 0;
        }

        if( query("family/family_name", ob) && 
            query("family/family_name", ob) != "商家堡" )
        {
                command("sneer");
                command("say 你既然已經離家拜師，又跑回來作甚？");
                return 0;
        }

        return 1;
}

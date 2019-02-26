int permit_recruit(object ob)
{
        if( query("detach/唐門世家", ob) || query("betrayer/唐門世家", ob) )
        {
                command("say 你反覆無常，我不能收你為徒！");
                return 0;
        }
        
        if( query("betrayer/times", ob) )
        {
                command("say 哼，我們唐門世家最痛恨的就是不忠不義之徒。"); 
                return 0;
        }
        
/*
        if( query("born_family", ob) != "唐門世家" && !query("reborn/times", ob) ) 
        {
                command("hmm");
                command("say 我們唐門世家乃世家出身，不收外人。"); 
                return 0;
        }
*/

        if( query("family/family_name", ob) && 
            query("family/family_name", ob) != "唐門世家" )
        {
                command("hmm");
                command("say 你既然已經離家拜師，就應有所作為，又跑回來作甚？");
                return 0;
        }

        return 1;
}

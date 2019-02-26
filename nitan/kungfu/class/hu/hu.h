int permit_recruit(object ob)
{
        if( query("detach/關外胡家", ob) || query("betrayer/關外胡家", ob) )
        {
                command("say 你反覆無常，我不能收你為徒！");
                return 0;
        }

/*
        if( query("born_family", ob) != "關外胡家" && !query("reborn/times", ob) )
        {
                command("hmm");
                command("say 我關外胡家雖然人丁稀少，但也不收納族外之人。");
                return 0;
        }
*/

        if( query("family/family_name", ob) && 
            query("family/family_name", ob) != "關外胡家" )
        {
                command("hmm");
                command("say 你既然已經離家拜師，就應有所作為，又跑回來作甚？");
                return 0;
        }

        return 1;
}

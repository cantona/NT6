int permit_recruit(object ob)
{
        if( query("detach/中原苗家", ob) || query("betrayer/中原苗家", ob) )
        {
                command("heng");
                command("say 你反復無常，我不能收你為徒！");
                return 0;
        }

        if( query("born_family", ob) != "中原苗家" )
        {
                command("hmm");
                command("say 我苗家向來便不收容外人。");
                return 0;
        }

        if( query("family/family_name", ob) && 
            query("family/family_name", ob) != "中原苗家" )
        {
                command("hmm");
                command("say 你既已在外面投師學藝，就應有所作為，又跑回來作甚？");
                return 0;
        }

        return 1;
}

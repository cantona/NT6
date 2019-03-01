// MingJiao.h for all npc of mingjiao

int permit_recruit(object ob)
{
        if( query("detach/明教", ob) || 
            query("betrayer/明教", ob) )
        {
                command("say 離開了明教就不要再回來！");
                return 0;
        }

        if( query("betrayer/times", ob) )
        {
                command("say 閣下不忠不信，我們明教最恨的就是你這種人。");
                return 0;
        }

        if( query("family/family_name", ob) && 
            query("family/family_name", ob) != "明教" )
        {
                command("say 你有了師傅，就不要來我們明教了！");
                return 0;
        }

        return 1;
}

/*
int recognize_apprentice(object ob, string skill)
{
        object me = this_object();
        mapping ob_fam;

        if( !(ob_fam=query("family", ob)) || ob_fam["family_name"] != "明教" )
        {
                command("say " + RANK_D->query_respect(ob) + "與本教素無來往，不知此話從何談起？");
                return -1;
        }

        if( ob_fam["generation"] <= query("family/generation", me) )
        {
                return 1;
        }

        return 0;
}
*/

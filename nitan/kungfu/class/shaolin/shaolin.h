// shaolin.h

int permit_recruit(object ob)
{
        if( query("detach/少林派", ob) || 
            query("betrayer/少林派", ob) )
        {
                command("say 你反反覆覆，唉！怎麼一心向佛？");
                return 0;
        }

        if( query("betrayer/times", ob) )
        {
                command("say 你大逆不道，私自判師，不能容於少林！");
                return 0;
        }

        if( query("family/family_name", ob) && 
            query("family/family_name", ob) != "少林派" )
        {
                command("say 你已經名師指點，為何不下苦功，反而來我們"
                        "少林寺呢？");
                return 0;
        }

        return 1;
}

// ben.h for fight

int accept_hit(object ob)
{
        object kr;

        if( is_killing(query("id", ob)) )
                return 1;

        if (! objectp(kr = present("ku rong")))
                return 1;

        command("say 枯榮大師！這" + RANK_D->query_rude(ob) +
                "打上門來了！");
        kr->start_fight(ob);
        return 1;
}

int accept_kill(object ob)
{
        object kr;

        if( is_killing(query("id", ob)) )
                return 1;

        if (! objectp(kr = present("ku rong")))
                return 1;

        command("say 枯榮大師！這" + RANK_D->query_rude(ob) +
                "妄圖行兇，強搶劍譜！");
        kr->start_fight(ob);
        return 1;
}

int accept_fight(object ob)
{
        command("say 善哉！善哉！施主何出此言？");
        return 0;
}
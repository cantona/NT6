// check recruit

int permit_recruit(object ob)
{
        if( query("detach/八卦門", ob) || query("betrayer/八卦門", ob) )
        {
                command("say 你當年既然已經離開了咱鏢局，現在幹嘛又要回來？");
                return 0;
        }

        if( query("betrayer/times", ob) )
        {
                command("say 嘿！咱鏢局留着你這樣的背信棄義之徒肯定是吃裏爬外！");
                return 0;
        }

        if( query("family/family_name", ob) && 
            query("family/family_name", ob) != "八卦門" && 
            query("family/family_name", ob) != "商家堡" && 
            query("family/master_name", ob) != "商劍鳴" )
        {
                command("say 不妥，不妥！你已經有師承了。");
                return 0;
        }

        return 1;
}

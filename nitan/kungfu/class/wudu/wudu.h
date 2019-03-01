// wudu.h

int permit_recruit(object ob)
{
        if( query("detach/五毒教", ob) || query("betrayer/五毒教", ob) )
        {
                command("say 你既然已經離教，就別再回來！");
                return 0;
        }

        if( query("betrayer/times", ob) )
        {
                command("say 判師之徒，哼！小心我把你千刀萬剮！");
                return 0;
        }

        if( query("family/family_name", ob) && 
            query("family/family_name", ob) != "五毒教" )
        {
                command("say 你不是已經有了師傅麼，還來幹什麼？做臥底麼？");
                return 0;
        }

        if( query("family/master_name", ob) == "何鐵手" )
        {
                command("sneer");
                command("say 既然你已經跟隨了那個賤人，卻又來找我作甚？");
                return 0;
        }

        return 1;
}

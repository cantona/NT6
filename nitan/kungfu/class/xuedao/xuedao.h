// check recruit

int permit_recruit(object ob)
{
        if( query("detach/血刀門", ob) || query("betrayer/血刀門", ob) )
        {
                command("say 你離開了血刀門們，就別回來！");
                return 0;
        }

        if( query("betrayer/times", ob) )
        {
                command("say 判師之徒，哼！哼！我把你千刀萬剮！");
                return 0;
        }

        if( query("family/family_name", ob) && 
            query("family/family_name", ob) != "血刀門" )
        {
                command("say 你不是已經有了師傅麼，還來幹什麼？偷學我派祕技啊！");
                return 0;
        }

        return 1;
}

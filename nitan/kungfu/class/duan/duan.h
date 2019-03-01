// duan.h

int permit_recruit(object ob)
{
        if( query("detach/段氏皇族", ob) || query("betrayer/段氏皇族", ob) )
        {
                command("say 既然離開了我們段家，就不要回來了");
                return 0;
        }

        if( query("betrayer/times", ob) )
        {
                command("say 哼，我們大理段氏最痛恨的就是不忠不義之徒。");
                return 0;
        }

/*
        if( query("born_family", ob) != "段氏皇族" && !query("reborn/times", ob) )
        {
                command("shake");
                command("say 我們段家乃皇族出身，不收外人。");
                return 0;
        }
*/

        if( query("family/family_name", ob )
            && query("family/family_name", ob) != "段氏皇族" )
        {
                command("hmm");
                command("say 你當年跑出去的時候怎麼就沒想過要回來？");
                return 0;
        }

        return 1;
}

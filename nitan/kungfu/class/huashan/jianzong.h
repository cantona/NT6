// qizong.h

int permit_recruit(object ob)
{
        if( query("family/family_name", ob) == "華山派" )
        {
                command("say 哼，你還是跟着偽君子他們學習什麼"
                        "氣宗的武功吧。");
                return 0;
        }

        if( query("detach/華山劍宗", ob) || 
            query("betrayer/華山劍宗", ob) )
        {
                command("say 華山派自今未成收過破門弟子！");
                return 0;
        }

        if( query("betrayer/times", ob) )
        {
                command("say 華山派講究的就是信義，你這判師之人焉能理解？");
                return 0;
        }

        if( query("family/family_name", ob) && 
            query("family/family_name", ob) != "華山劍宗" )
        {
                command("say 你既有了名師指點，還何必來我們華山派！");
                return 0;
        }

        return 1;
}

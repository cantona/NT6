int permit_recruit(object ob) 
{
        if( query("detach/華山派", ob) || 
            query("betrayer/華山派", ob) )
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
            query("family/family_name", ob) != "華山劍宗" && 
            query("family/family_name", ob) != "華山派" )
        {
                command("say 你既有了名師指點，還何必來我們華山派！");
                return 0;
        }

        return 1;
}

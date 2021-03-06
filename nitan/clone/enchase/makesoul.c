mapping soul_list = ([
        "weapon"        :"武器",
        "head"          :"頭盔",
        "neck"          :"項鍊",
        "cloth"         :"戰衣",
        "armor"         :"護甲",
        "surcoat"       :"披風",
        "waist"         :"腰帶",
        "wrists"        :"護腕",
        "hands"         :"鐵掌",
        "boots"         :"戰靴",
        "finger"        :"指套",
        "rings"         :"戒指",
        "charm"         :"護身符",
]);
        
void create_soul_file()
{
        string file, filename;
        string *list;
        string id, name;
        int i, n = 0;
        int status;

        list = keys(soul_list);

        for( i = 0; i < sizeof(list); i ++ )
        {
                reset_eval_cost();
                for( status = 1; status < 7; status++ )
                {
                        id = list[i];
                        name = soul_list[list[i]];
                        filename = id+"_soul"+status;
                 
                        file = read_file("/clone/enchase/equipsoul.h");
                        file = replace_string(file, "RP_NAME", name);
                        file = replace_string(file, "RP_ID", id);
                        file = replace_string(file, "RP_STATUS", to_string(status));

                        write_file("/clone/enchase/" + filename + ".c", file, 1);
                        n++;
                }
        }

        write(sprintf("%d", n) + " Files created at /clone/enchase/ .\n");
        return;
}


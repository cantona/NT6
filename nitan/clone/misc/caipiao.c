inherit ITEM;
inherit F_SAVE;

void create()
{
        if( !restore() ) {
                set_name("彩票", ({"cai piao"}));
                set("long","這是一張泥潭彩票\n");
        }
        set("unit", "張");
        seteuid(getuid());
}

string query_save_file() { return  "/data/caipiao/"+ query("z_num"); }
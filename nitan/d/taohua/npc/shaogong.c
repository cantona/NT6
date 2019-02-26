// Last Modified by winder on Nov. 17 2000

inherit NPC;

int ask_location();
string ask_name();
string ask_rumors();
string ask_thd();

void create()
{
        set_name("艄公", ({ "gong", "shaogong" }) );
        set("gender", "男性" );
        set("age", 50);
        set("combat_exp", 100);
        set("attitude", "friendly");
        set("rank_info/respect", "老船家");
        set("inquiry", ([
                "name": (: ask_name :),
                "rumors": (: ask_rumors :),
                "here": "這裏叫做東海，傳説四海龍王裏的東海王就住在水底。",
                "位置": (: ask_location :),
                "taohuadao": (: ask_thd :),
                "桃花島": (: ask_thd :),
                "weizhi": (: ask_location :),
                "走": "您得告訴我往哪邊開呀(turn n|w|s|e)！",
                "出海": "您得告訴我往哪邊開呀(turn n|w|s|e)！",
                "開船": "您得告訴我往哪邊開呀(turn n|w|s|e)！",
                "起航": "您得告訴我往哪邊開呀(turn n|w|s|e)！",
                "啟航": "您得告訴我往哪邊開呀(turn n|w|s|e)！",
        ]) );
        setup();
}

int ask_location()
{
        object ob=this_player();

        say("艄公看了看海圖，説道：我們現在的位置是("+query_temp("thd_locx", ob)+","+query_temp("thd_locy", ob)+")。\n");
        return 1;
}

string ask_name()
{
        object ob=this_player();

        if( query_temp("thd_target", ob) == "thd" )
                return "不敢不敢，老漢名喚陳阿生，已經在這裏劃了三十多年船了。\n";
        if( query_temp("thd_target", ob) == "bay" )
                return "老漢只不過是黃島主的屬下而已，哪有什麼名字。\n";
}

string ask_rumors()
{
        object ob=this_player();

        if( query_temp("thd_target", ob) == "thd" )
                return "聽説桃花島上住着一個惡魔，唉，要不是為了這每趟五兩銀子的辛苦費，\n老漢是説什麼也不會去的。\n";
        if( query_temp("thd_target", ob) == "bay" )
                return "老漢長居桃花島，沒聽説過什麼流言。\n";
}

string ask_thd()
{
        object ob=this_player();

        if( query_temp("thd_target", ob) == "thd" )
                return "聽説桃花島上住着一個惡魔，唉，要不是為了這每趟20兩銀子的辛苦費，\n老漢是説什麼也不會去的。\n";
        if( query_temp("thd_target", ob) == "bay" )
                return "老漢長居桃花島，黃島主待我們很好。\n";
}
// book.c

inherit ITEM;

int is_book() { return 1; }

string extra_long()
{
        string str;
        
        str  = sprintf("\n物品屬性 : 書本<秘籍>，下線%s丟失\n", 
                       (this_object()->query_autoload() || query("autoload")) ? "不" : "" );
        str += sprintf("記載內容 : %s\n", to_chinese(query("skill/name")));
        str += sprintf("經驗要求 : %d\n", query("skill/exp_required"));
        str += sprintf("研習難度 : %d\n", query("skill/difficulty"));
        str += sprintf("研習要求 : %s %d 級\n", to_chinese(query("skill/name")), query("skill/min_skill"));
        str += sprintf("研習限制 : %d 級\n", query("skill/max_skill"));
        str += sprintf("精力消耗 : %d 點/次\n", query("skill/jing_cost"));
        // str += sprintf("研習方法 : 輸入指令 du %s 研讀。\n", query("id"));
        
        return str;
}

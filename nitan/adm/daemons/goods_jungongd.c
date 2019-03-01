// This program is a part of NT MudLIB
// goodsd.c
// Written by Lonely@nitan.org

#include <ansi.h>
#include <command.h>

inherit F_DBASE;

#define NAME            0
#define VALUE           1
#define TYPE            2
#define FILE            3
#define DESC            4

#define VIP1_RATE       95
#define VIP2_RATE       88
#define VIP3_RATE       80
#define GOODS_FILE      CONFIG_DIR "goods_jungong"

class goods {
        string name;
        int value;
        string file;
        string type;
        string desc;
        int number;
}

int rate = 100;
nosave class goods *all_goods = ({});
void init_goods();
int clean_up() { return 1; }
void set_rate(int r) { rate = r; }
int query_rate() { return rate; }

void create()
{
        seteuid(ROOT_UID);
        set("name", HIC"朝廷軍功商城"NOR);
        init_goods();
}

void init_goods()
{
        class goods item;
        string *all, *tmp;
        string file;
        string line;
        int i, n;

        all_goods = ({});

        if( file_size(GOODS_FILE) <= 0 )
                return;

        file = read_file(GOODS_FILE);
        if( !stringp(file) ) return;

        file = replace_string(file, "\r", "");
        all =  filter_array(explode(file, "\n") - ({ "" }), (: $1[0] != '#' :));
        if( !n = sizeof(all) ) {
                log_file("static/goods_jungong",sprintf("all_goods: Have not valid goods. %s\n",
                        ctime(time())));
                return;
        }

        for( i=0;i<n;i++ ) {
                reset_eval_cost();
                line = all[i];

                //line = remove_fringe_blanks(line);
                while( strlen(line) && line[0] == ' ' ) line = line[1..<1];
                tmp = explode(line, ":");
                if( sizeof(tmp) < 4 ) {
                        log_file("static/goods_jungong", sprintf("%s isn't a full line.\n", line));
                        break;
                }

                item = new(class goods);
                item->name = tmp[NAME];
                item->value = to_int(tmp[VALUE]);
                item->type = tmp[TYPE];
                if( sizeof(tmp) > FILE )
                        item->file = tmp[FILE];
                if( sizeof(tmp) > DESC )
                        item->desc = tmp[DESC];
                item->number = sizeof(all_goods) + 1;
                all_goods += ({ item });
        }
}

string chinese_type(string type)
{
        switch(type)
        {
        case "object"   : return HIC "物品" NOR;
        case "pill"     : return HIM "丹藥" NOR;
        case "special"  : return HIG "先天技能" NOR;
        case "special2" : return HIB "轉世技能" NOR;
        case "story"    : return WHT "故事" NOR;
        case "enchase"  : return HIW "鑲嵌" NOR;
        case "symbol"   : return YEL "神符" NOR;
        case "card"     : return HIY "會員卡" NOR;
        case "gold"     : return HIY "黃金" NOR;
        case "prop"     : return HIY "裝備" NOR;
        case "module"   : return HIG "套裝" NOR;
        case "package"  : return HIR "禮包" NOR;
        case "srv"      : return HIM "服務" NOR;
        case "other"    : return HIR "其他" NOR;
        default         : return HIR "未知" NOR;
        }
}

public varargs int show_goods(object me, string arg)
{
        class goods item;
        string msg;
        int len = 0;

        if( !sizeof(all_goods) ) {
                tell_object(me, sprintf("目前%s沒有可以兌換的東西。\n", query("name")));
                return 1;
        }

        if( !arg ) arg = "all";

        msg  = sprintf("%s目前可以兌換以下貨物：\n\n" NOR, query("name"));
        msg += sprintf(HIW "%-6s%-16s%-11s%-10s%s\n" NOR,
                      "編號", "名稱", "軍功", "種類", "功能簡要");
        msg += HIG "------------------------------------------------------------------------------------------\n\n" NOR;
        foreach( item in all_goods ) {
                if( item->type == arg || arg == "all"  )
                {
#ifndef LONELY_IMPROVED
                        len = color_len(chinese_type(item->type));
#endif
                        msg += sprintf(HIW"(%3d) "HIC"%-16s" HIY "%-11d"NOR"%-"+(10+len)+"s"CYN"%-50s\n" NOR,
                                      item->number,
                                      item->name,
                                      item->value,
                                      chinese_type(item->type),
                                      item->desc);
                }
        }

        msg += "\n";
        msg += HIG "請認真閱讀有關說明，兌換前請考慮清楚， 如無差錯，恕不退貨！\n" NOR;
        msg += HIG "------------------------------------------------------------------------------------------\n" NOR;
        me->start_more(msg);
        return 1;
}

public int exchange_goods(object ob, string arg, int amount)
{
        string which;
        object item;
        mixed specials;
        int value, level;
        int i, j, n, vip, money;

        n = sizeof(all_goods);
        if( !n ) {
                write(sprintf("目前%s沒有可以兌換的東西。\n", query("name")));
                return 1;
        }
        
        if( !amount || amount < 1 ) {
                write("你要到底兌換幾個物品？\n");
                return 1;
        }

        if( query("jungong", ob) < 1 ) {
                write("你還沒有獲得任何門派貢獻點。\n");
                return 1;
        }

        for( i=0; i<n; i++ ) {
                if( filter_color(all_goods[i]->name) == arg
                ||  sprintf("%d", all_goods[i]->number) == arg )
                        break;
        }

        if( i >= n ) {
                write(HIR "你想兌換什麼？ 請使用 fmstore show all 查詢。\n" NOR);
                return 1;

        }

        if( all_goods[i]->type == "manual" ) {
                write("對不起，該服務必須由 admin 手動實現，請及時與 admin 聯系！\n");
                return 1;
        }

        vip   = MEMBER_D->db_query_member(ob, "vip");
        value = (all_goods[i]->value)*amount;
        value = value*rate/100;
        if( vip == 3) value = value*VIP3_RATE/100;
        else if( vip == 2) value = value*VIP2_RATE/100;
        else if( vip == 1) value = value*VIP1_RATE/100;
        
        //if( query("family/first", ob) )
        //        value /= 2;
                
        if( value < 1 ) value = 1;
        money = query("jungong", ob);
        
        if( money < value ) {
                write("對不起，您的軍功不夠！\n");
                return 1;
        }

        switch(all_goods[i]->type)
        {
        case "object":
        case "pill":
        case "symbol":
        case "enchase":
                //which = all_goods[i]->name;
                
                if( !function_exists("query_amount", get_object(all_goods[i]->file)) ) 
                {
                        for( j=0; j<amount; j++ )
                        {
                                item = new(all_goods[i]->file);
                                item->move(ob, 1);
                        }
                }
                else
                {
                        item = new(all_goods[i]->file);
                        item->set_amount(amount);
                        item->move(ob, 1);
                }

                addn("jungong", -value, ob);

                item->move(ob, 1);
               
                write(HIC "您總共花費了 " HIY + value + HIC + " 點軍功獻, 祝您好運！\n" NOR);
                return 1;
        case "gold":
                addn("balance", 100000000*amount, ob); 
                addn("jungong", -value, ob);
                write(HIC "您總共花費了 " HIY + value + HIC + " 點軍功獻, 祝您好運！\n" NOR);
                return 1;
        default:
                write("無效物品種類！\n");
                return 0;
        }
}
